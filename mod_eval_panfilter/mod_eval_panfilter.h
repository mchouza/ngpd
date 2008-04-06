#ifndef MOD_EVAL_PANFILTER_H
#define MOD_EVAL_PANFILTER_H

#include "component_namer.h"
#include "component_value_transl.h"
#include "individual.h"
#include "spice_ac_out.h"
#include "transfer_spec.h"
#include <evalmodule.h>
#include <genome.h>
#include <i_mod_spice.h>
#include <boost/scoped_ptr.hpp>

/// Clase encargada de evaluar a cada individuo de la población de filtros
/// analógicos pasivos
class MODULE_API ModEvalPAnFilter : public EvalModule
{
public:
	// Requeridos por la interfaz
	virtual const std::string& GetName() const {return name_;};
	virtual const Poco::UUID& GetID() const {return id_;}
	virtual const std::vector<Req>& GetReqMods() const {return reqs_;}
	virtual unsigned int GetVersion() const {return version_;}
	virtual bool GiveConfigData(const std::map<std::string, std::string>& configData);
	virtual bool GiveReqMods(const std::vector<boost::shared_ptr<Module> >& reqMods);
	virtual double EvaluateGenome(const TGenome& genome) const;
	virtual void ShowIndiv(std::ostream& os, const TGenome& genome) const;

	// C & D
	ModEvalPAnFilter() {}
	virtual ~ModEvalPAnFilter();

protected:
	/// Obtiene una netlist a partir de un genoma
	void GetNetlist(const TGenome& genome, std::string& netlist,
		unsigned& probedNode) const;

	/// Realiza el análisis de la netlist con SPICE y devuelve el puntaje
	double SPICEAnalysis(const std::string& netlist,
		unsigned probedNode) const;

	/// Compara los resultados (interpretados) del análisis SPICE con los
	/// buscados
	double CompareResults(const SpiceACOut& interpretedResults,
		const std::string& probedNodeName) const;

	/// Agrega un epílogo al final de la netlist
	void AddAnalysisEpilog(std::stringstream& ssNetlist) const;

private:
	/// Objeto que encapsula la transferencia deseada
	boost::shared_ptr<TransferSpec> pDesiredTransfer_;

	/// Frecuencia de inicio del barrido
	double startFreq_;

	/// Frecuencia de finalización del barrido
	double endFreq_;

	/// Puntos por década
	unsigned pointsPerDec_;

	/// Cero para la penalidad exponencial por tamaño
	double expPenaltyZero_;

	/// Multiplicador para determinarla penalidad
	double expPenaltyMult_;
	
	/// Embrión que sirve como base para desarrollar el individuo
	boost::scoped_ptr<Individual> pEmbryo_;

	/// Objecto encargado de nombrar los componentes
	ComponentNamer embryoCompNamer_;

	/// Traductor de los valores de los componentes
	boost::scoped_ptr<ComponentValueTransl> pTransl_;

	/// Módulo del SPICE
	boost::shared_ptr<IModSpice> pSpiceModule_;

	/// Nombre del módulo
	static const std::string name_;

	/// ID del módulo
	static const Poco::UUID id_;

	/// Versión del módulo
	static const unsigned int version_;

	/// IDs de los módulos requeridos
	static const std::vector<Req> reqs_;
};

#endif
