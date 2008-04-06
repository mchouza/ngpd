#include "mod_genops_panfilter.h"
#include "panf_genome_ops_wrapper.h"
#include <Poco/ClassLibrary.h>

using boost::shared_ptr;
using Poco::UUID;
using std::istream;
using std::map;
using std::ostream;
using std::string;
using std::vector;

const string ModGenOpsPAnFilter::name_ = "GenOpsPassiveAnalogFilter";
const UUID ModGenOpsPAnFilter::id_ =
	UUID("0b0656d6-5d68-11dc-8314-0800200c9a66");
const unsigned int ModGenOpsPAnFilter::version_ = 0;
const vector<Module::Req> ModGenOpsPAnFilter::reqs_ =
	std::vector<Module::Req>();

POCO_BEGIN_MANIFEST(Module)
	POCO_EXPORT_CLASS(ModGenOpsPAnFilter)
POCO_END_MANIFEST

bool ModGenOpsPAnFilter::GiveConfigData(const map<string,string> &configData)
{
	// FIXME: Hacer que funcione
	return true;
}

bool ModGenOpsPAnFilter::GiveReqMods(const vector<shared_ptr<Module> > &reqMods)
{
	// No requiere módulos, devuelvo error si me los dan
	return reqMods.size() == 0;
}

void ModGenOpsPAnFilter::RandomInit(TGenome &genome) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.MakeRandom();
}

void ModGenOpsPAnFilter::Mutate(TGenome &genome) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.Mutate();
}

void ModGenOpsPAnFilter::Cross(TGenome &genome1, TGenome &genome2) const
{
	PANFGenomeOpsWrapper wrapper(genome1);
	wrapper.Cross(genome2);
}

void ModGenOpsPAnFilter::AltOp(TGenome& genome) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.AltOp();
}

void ModGenOpsPAnFilter::Load(istream& is, TGenome& genome, bool textualFormat) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.Load(is, textualFormat);
}

void ModGenOpsPAnFilter::Save(ostream& os, TGenome& genome, bool textualFormat) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.Save(os, textualFormat);
}