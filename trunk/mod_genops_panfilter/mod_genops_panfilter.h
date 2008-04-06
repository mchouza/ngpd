#ifndef MOD_GENOPS_PANFILTER_H
#define MOD_GENOPS_PANFILTER_H

#include <ops_module.h>

/// Clase del m�dulo encargado de operar con el genoma (mutarlo,
/// hacer cruzas, etc)
class MODULE_API ModGenOpsPAnFilter : public OpsModule
{
public:
	// Requeridos por la interfaz
	virtual const std::string& GetName() const {return name_;};
	virtual const Poco::UUID& GetID() const {return id_;}
	virtual const std::vector<Req>& GetReqMods() const {return reqs_;}
	virtual unsigned int GetVersion() const {return version_;}
	virtual bool GiveReqMods(const std::vector<boost::shared_ptr<Module> >& reqMods);
	virtual bool GiveConfigData(const std::map<std::string, std::string>& configData);
	virtual void RandomInit(TGenome& genome) const;
	virtual void Mutate(TGenome& genome) const;
	virtual void Cross(TGenome& genome1, TGenome& genome2) const;
	virtual void AltOp(TGenome& genome) const;
	virtual void Save(std::ostream& os, TGenome& genome, bool textualFormat = true) const;
	virtual void Load(std::istream& is, TGenome& genome, bool textualFormat = true) const;

private:
	/// Nombre del m�dulo
	static const std::string name_;

	/// ID del m�dulo
	static const Poco::UUID id_;

	/// Versi�n del m�dulo
	static const unsigned int version_;

	/// IDs de los m�dulos requeridos
	static const std::vector<Req> reqs_;
};

#endif
