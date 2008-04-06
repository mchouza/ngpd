#ifndef I_MOD_SPICE_H
#define I_MOD_SPICE_H

#include <module.h>
#include <string>
#include <Poco/UUID.h>

class MODULE_API IModSpice : public Module
{
public:
	// Destructor virtual
	virtual ~IModSpice() {}

	// Definidas por la interfaz
	virtual const std::string& GetName() const = 0;
	virtual const Poco::UUID& GetID() const = 0;
	virtual const std::vector<Req>& GetReqMods() const = 0;
	virtual unsigned int GetVersion() const = 0;
	virtual bool GiveConfigData(const std::map<std::string, std::string>& configData) = 0;
	virtual bool GiveReqMods(const std::vector<boost::shared_ptr<Module> >& reqMods) = 0;

	/// Procesa una netlist
	virtual bool ProcNetlist(const std::string& netlist,
		std::vector<char>& result, bool binaryResults = true) const = 0;
};

#endif
