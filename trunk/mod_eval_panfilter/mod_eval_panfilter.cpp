#include "mod_eval_panfilter.h"
#include "panf_genome_exec_wrapper.h"
#include "profiling.h"
#include "spice_ac_out.h"
#include <complex>
#include <limits>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <Poco/ClassLibrary.h>

using boost::lexical_cast;
using boost::shared_ptr;
using std::abs;
using std::complex;
using std::istringstream;
using std::map;
using std::numeric_limits;
using std::string;
using std::stringstream;
using std::vector;
using Poco::UUID;

namespace
{
	const Poco::UUID spiceModID =
		UUID("027a5ea0-d94b-11db-8314-0800200c9a66");

	/// Para elevar al cuadrado
	template <typename T>
	inline T square(T x)
	{
		return x * x;
	}
}

const string ModEvalPAnFilter::name_ = "EvalPassiveAnalogFilter";
const UUID ModEvalPAnFilter::id_ =
	UUID("3cffb826-d232-11db-8314-0800200c9a66");
	
const unsigned int ModEvalPAnFilter::version_ = 0;

// Solo requiere al módulo del SPICE
const vector<Module::Req> ModEvalPAnFilter::reqs_ =
	std::vector<Module::Req>(
		1,
		// SPICE
		Module::Req(spiceModID, 0));

// FIXME: Solo para impresión con propósitos de debugging
#include <iostream>

POCO_BEGIN_MANIFEST(Module)
	POCO_EXPORT_CLASS(ModEvalPAnFilter)
POCO_END_MANIFEST

ModEvalPAnFilter::~ModEvalPAnFilter()
{
	// Obtengo los datos estadísticos
	//MyProfiler::generate_report();
}

bool ModEvalPAnFilter::GiveReqMods(const vector<shared_ptr<Module> > &reqMods)
{
	using boost::dynamic_pointer_cast;
	
	// Debe ser uno solo
	if (reqMods.size() != 1)
		return false;
	
	// Me fijo que sea el del SPICE
	if (reqMods[0]->GetID() != spiceModID)
		return false;

	// La versión no importa

	// Guardo el puntero
	pSpiceModule_ = dynamic_pointer_cast<IModSpice>(reqMods[0]);

	// OK
	return true;
}

// FIXME: Faltan más datos
// FIXME: Organizarlo mejor
bool ModEvalPAnFilter::GiveConfigData(const map<string, string>& configData)
{
	// Iteradores
	map<string, string>::const_iterator itIE, itTol, itPN, itDT, itPenZ,
		itPenMult, itStartFreq, itEndFreq, itPointsPerDec;
	
	// Sí no está el embrión inicial, es un error
	if ((itIE = configData.find("InitialEmbryo")) == configData.end())
		return false;

	// Si no está la tolerancia es un error
	if ((itTol = configData.find("Tolerance")) == configData.end())
		return false;

	// Si no está la transferencia deseada es un error
	if ((itDT = configData.find("DesiredTransfer")) == configData.end())
		return false;

	// Si no están lso iteradores de las penalidades es un error
	if ((itPenZ = configData.find("PenaltyZero")) == configData.end() ||
		(itPenMult = configData.find("PenaltyMultiplier")) == configData.end())
		return false;

	// Si no están los parámetros de análisis
	if ((itStartFreq = configData.find("StartFreq")) == configData.end() ||
		(itEndFreq = configData.find("EndFreq")) == configData.end() ||
		(itPointsPerDec = configData.find("PointsPerDec")) == configData.end())
		return false;

	// Construyo al embrión inicial
	pEmbryo_.reset(new Individual(istringstream(itIE->second)));

	// Actualizo al "component namer" con los componentes del embrión
	embryoCompNamer_.Advance(istringstream(itIE->second));

	// Creo al traductor
	pTransl_.reset(new ComponentValueTransl(lexical_cast<unsigned>(itTol->second)));

	// Incializo la transferencia buscada
	pDesiredTransfer_.reset(new TransferSpec(itDT->second));

	// Inicializo los valores de penalidad
	expPenaltyZero_ = lexical_cast<double>(itPenZ->second);
	expPenaltyMult_ = lexical_cast<double>(itPenMult->second);

	// Inicializo los valores del barrido
	startFreq_ = lexical_cast<double>(itStartFreq->second);
	endFreq_ = lexical_cast<double>(itEndFreq->second);
	pointsPerDec_ = lexical_cast<unsigned>(itPointsPerDec->second);

	// OK
	return true;
}

double ModEvalPAnFilter::EvaluateGenome(const TGenome& genome) const
{
	// Mido todo el tiempo que se pasa evaluando
	//MyProfiler p("Eval");
	
	// Si no le dieron lo que pide, no funciona
	if (!pSpiceModule_)
		// FIXME: Lanzar algo específico
		throw;

	// Obtiene la netlist y el nodo que nos interesa
	string netlist;
	unsigned probedNode;
	GetNetlist(genome, netlist, probedNode);

	// Realiza una evaluación de la netlist utilziando SPICE
	double spiceScore =  SPICEAnalysis(netlist, probedNode);

	// Devuelve el puntaje del SPICE más una penalidad por tamaño
	return spiceScore +
		std::exp(expPenaltyMult_ * (genome.size() - expPenaltyZero_));
}

void ModEvalPAnFilter::GetNetlist(const TGenome& genome, string& netlist,
								  unsigned& probedNode) const
{
	// FIXME: Solo para profiling
	// Mido el tiempo que se pasa construyendo la netlist
	//MyProfiler p("GetNetlist");
	
	// Creo un individuo en base al embrión
	Individual indiv(*pEmbryo_);

	// Le aplico el proceso de construcción
	PANFGenomeExecWrapper wrapper(genome);
	wrapper.Execute(indiv.GetWritingHeads(), embryoCompNamer_, *pTransl_);

	// Numero los vértices en forma consecutiva
	indiv.ReenumerateVertices();

	// Simplifico al individuo para que el SPICE lo acepte
	indiv.SPICECleanUp();

	// Numero los vértices en forma consecutiva
	indiv.ReenumerateVertices();

	// Convierto el individuo desarrollado en una netlist
	stringstream ssNetList;
	indiv.ConvertToNetlist(ssNetList, false);

	// Agrego al final un epílogo de análisis
	AddAnalysisEpilog(ssNetList);

	// Paso la string de la netlist al parámetro
	netlist.assign(ssNetList.str());

	// Indico cual es el nodo analizado
	probedNode = indiv.GetProbedNode();
}

double ModEvalPAnFilter::SPICEAnalysis(const string& netlist,
									   unsigned probedNode) const
{
	// Mido el tiempo que se pasa haciendo el análisis con el SPICE
	//MyProfiler p("SPICEAnalysis");
	
	// Por si hay problemas al evaluarlo o la salida del SPICE es cualquier
	// cosa
	try
	{
		// Envío dicha netlist al SPICE
		vector<char> spiceResult;
		pSpiceModule_->ProcNetlist(netlist, spiceResult);

		// Interpreto los resultados del SPICE
		SpiceACOut interpretedResult(spiceResult);

		// Comparo los resultados del SPICE con los buscados para obtener el
		// score
		return CompareResults(interpretedResult,
			lexical_cast<string>(probedNode));
	}
	catch (...)
	{
		// En ese caso devuelvo el peor puntaje: + infinito
		return numeric_limits<double>::infinity();
	}
}

double ModEvalPAnFilter::CompareResults(const SpiceACOut&
										interpretedResults,
										const string& probedNodeName) const
{
	//MyProfiler p("ModEvalPAnFilter::CompareResults");
	
	// FIXME: Demasiado simplista, solo uso diferencias al cuadrado

	// Obtengo el vector de valores de tensión para el nodo
	vector<complex<double> > voltageVec;
	interpretedResults.GetNodeVoltages(probedNodeName, voltageVec);

	// Obtengo el vector de valores de frecuencia
	const vector<double>& freqVec = interpretedResults.GetFreqs();

	// Obtengo la trnsferencia deseada
	const TransferSpec& desiredTransfer = *pDesiredTransfer_;

	assert(voltageVec.size() == freqVec.size());

	// Recorro ambos comparando con los datos base
	double acumDif = 0.0;
	for (size_t i = 0; i < voltageVec.size(); i++)
		acumDif += square(abs(voltageVec[i]) - desiredTransfer(freqVec[i]));
	
	// Devuelvo las diferencias acumuladas
	return acumDif;
}

void ModEvalPAnFilter::AddAnalysisEpilog(std::stringstream &ssNetlist) const
{
	// Agrego el final a la netlist
	ssNetlist << "* ANALYSIS\n";
	ssNetlist << ".AC DEC " << pointsPerDec_ << ' '
		<< startFreq_ << ' ' << endFreq_ << '\n';
	ssNetlist << ".END\n";
}

void ModEvalPAnFilter::ShowIndiv(ostream& os, const TGenome& genome) const
{
	// Obtengo la netlist
	unsigned dummy;
	string netlist;
	GetNetlist(genome, netlist, dummy);

	// Muestro la netlist
	os << netlist;
}