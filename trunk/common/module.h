//
// Copyright (c) 2008, Mariano M. Chouza
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * The names of the contributors may not be used to endorse or promote
//      products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

//=============================================================================
// module.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Agregado a NGPD el 6 de abril de 2008
//=============================================================================

#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <Poco/Exception.h>
#include <Poco/UUID.h>

#if defined(WIN32) && defined(POCO_DLL)
	#ifdef MODULE_EXPORTS
		#define MODULE_API _declspec(dllexport)
	#else
		#define MODULE_API _declspec(dllimport)
	#endif
#endif

#ifndef MODULE_API
	#define MODULE_API
#endif

class MODULE_API Module
{
public:
	/// Excepciones relativas a los módulos
	class Exception : public Poco::Exception
	{
	public:
		Exception(const std::string& msg) : Poco::Exception(msg) {}
	};
	
	/// Constructor.
	Module() {}

	/// Destructor.
	virtual ~Module() {}

	/// Tipo de un requerimiento: par ID - versión
	typedef std::pair<Poco::UUID, unsigned int> Req;

	/// Devuelve el nombre del módulo.
	virtual const std::string& GetName() const = 0;

	/// Devuelve el UUID del módulo
	virtual const Poco::UUID& GetID() const = 0;

	/// Devuelve la versión
	virtual unsigned int GetVersion() const = 0;

	/// Devuelve un vector con los ids y versiones de los módulos que 
	/// requiere para poder ejecutarse.
	virtual const std::vector<Req>& GetReqMods() const = 0;

	/// Le pasa un map con pares clave - valor, indicando valores requeridos
	/// para configurar el módulo.
	/// Devuelve true en caso de que tenga todo lo que requiera y false
	/// en caso contrario.
	virtual bool GiveConfigData(const std::map<std::string, std::string>& configData) = 0;
	
	/// Le da los módulos que necesita.
	/// Devuelve true si puede funcionar con lso que le dimos, false
	/// en caso contrario.
	virtual bool GiveReqMods(const std::vector<boost::shared_ptr<Module> >& reqMods) = 0;
};

#endif
