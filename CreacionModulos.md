**OBSOLETO - MODIFICADO EN NGPD**

# Introducción #

En esta página explico los pasos requeridos para crear módulos para el sistema GPGD, cualquiera sea la función que realicen. Los módulos deben ser compatibles con el modelo de exportación de símbolos utilizado por [POCO](http://www.appinf.com/poco/).

# Creación en Visual C++ 2005 #

  1. Crear un nuevo proyecto vacío del tipo Win32 DLL.
  1. En "Aditional Include Directories", agregar "<_path de poco_>**\Foundation\include**" y el directorio donde estén los _.h_ de las interfaces para distintas clases de módulos (evaluación, mutación, auxiliares, etc.).
  1. En "Preprocessor Definitions" agregar "**MODULE\_EXPORTS;POCO\_DLL**".
  1. En "Aditional Libraries Directories" agregar "<_path de poco_>**\lib**".
  1. En "Aditional Dependencies" agregar "**PocoFoundationd.lib PocoUtild.lib**" en la versión "Debug" y "**PocoFoundation.lib PocoUtil.lib**" en la "Release".
  1. En el archivo _.h_ que declare la interfaz del módulo respetar la siguiente estructura mínima (no incluye la funcionalidad que el módulo deberá implementar):

```
#include "interfazaheredar.h"

class MODULE_API MiModulo : public InterfazAHeredar
{
public:
	virtual const std::string& get_name() const {return name_;};

	virtual const Poco::UUID& get_id() const {return id_;}

	virtual const std::vector<Req>& get_req_mods() const {return reqs_;}

	virtual unsigned int get_version() const {return version_;}

	virtual bool give_req_mods(const std::vector<Poco::SharedPtr<Module> >& req_mods);

private:
	/// Nombre del módulo
	static const std::string name_;

	/// ID del módulo
	static const Poco::UUID id_;

	/// Versión del módulo
	static const unsigned int version_;

	/// IDs de los módulos requeridos
	static const std::vector<Req> reqs_;
};
```

Notar la presencia de MODULE\_API y que debe heredarse de la interfaz que corresponda a la clase de módulo que se desea desarrollar.

En cuanto al funcionamiento de los métodos, respetar las indicaciones dadas en la clase de interfaz de la que se hereda.

# Creación utilizando g++ #

**PROXIMAMENTE DISPONIBLE**