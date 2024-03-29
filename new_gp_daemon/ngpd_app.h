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
// ngpd_app.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 25 de marzo de 2008
//=============================================================================

#ifndef NGPD_APP_H
#define NGPD_APP_H

#include "core_fwd.h"
#include "web_interface_fwd.h"
#include <boost/scoped_ptr.hpp>
#include <Poco/Util/ServerApplication.h>

namespace Core
{
	/// Clase de la aplicación servidor
	class NGPDApp : public Poco::Util::ServerApplication
	{
		/// Servidor web para la interfaz
		boost::scoped_ptr<WebInterface::WebServer> pWebServer_;
	
	public:
		/// Constructor
		NGPDApp();

		/// Destructor
		virtual ~NGPDApp();

	protected:
		/// Maneja la inicialización
		virtual void initialize(Poco::Util::Application& self);

		/// Maneja la liberación de recursos
		virtual void uninitialize();

		/// Carga la configuración (pisa al método de la clase base)
		int loadConfiguration(int priority = PRIO_DEFAULT);

		/// Método que realiza el trabajo
		virtual int main(const std::vector<std::string>& args);

		/// Agrega un subsistema
		void addSubsystem(NGPDSubsystem* pSubsystem);
	};
}

#endif
