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
// ngpd_modules.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 28 de marzo de 2008
//=============================================================================

#ifndef NGPD_MODULES_H
#define NGPD_MODULES_H

#include <module.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <Poco/Logger.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/Util/Subsystem.h>

namespace Core
{
	/// Contiene los módulos de la aplicación
	class NGPDModules : public Poco::Util::Subsystem
	{
		/// Nombre del subsistema
		static const char* name_;

		/// Aplicación
		Poco::Util::Application& app_;
		
		/// Módulos cargados
		std::vector<boost::shared_ptr<Module> > modules_;

		/// Logger
		Poco::Logger& logger_;

	public:
		/// Constructor
		NGPDModules(Poco::Util::Application& app);

		/// Destructor
		virtual ~NGPDModules();

		/// Inicialización
		virtual void initialize(Poco::Util::Application&);

		/// Liberación de recursos
		virtual void uninitialize();

		/// Obtiene el nombre
		virtual const char* name() const;
	};
}

#endif
