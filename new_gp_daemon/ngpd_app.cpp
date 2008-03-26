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
// ngpd_app.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 25 de marzo de 2008
//=============================================================================

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include "ngpd_app.h"
#include "ngpd_config.h"
#include "os_dep.h"
#include "req_handler_factory.h"

using namespace Core;

void NGPDApp::initialize(Poco::Util::Application& self)
{
	// Llamo a la implementación de la clase base
	ServerApplication::initialize(self);

	// Indico que estoy inicializando
	logger().information("Iniciando NGPD (New Genetic Programming Daemon)...");
}

void NGPDApp::uninitialize()
{
	// Indico que estoy inicializando
	logger().information("Terminando la ejecución...");

	// Llamo a la implementación de la clase base
	ServerApplication::uninitialize();
}

int NGPDApp::loadConfiguration(int priority)
{
	// Cargo la configuración base
	config().add(new NGPDConfig(OSDep::getPath(OSDep::PATH_CFG_BASE)), 
		priority, false, false);

	// Cargo la configuración "editable" con una prioridad más baja, de modo 
	// que no pueda sobreescribir los parámetros básicos
	config().add(new NGPDConfig(OSDep::getPath(OSDep::PATH_CFG_WRITEABLE)),
		priority + 1, false, false);

	// Devuelvo la cantidad de configuraciones cargadas
	return 2;
}

int NGPDApp::main(const std::vector<std::string>& args)
{
	using Poco::Net::HTTPServer;
	using Poco::Net::ServerSocket;

	// Creo el socket de escucha
	// FIXME: Hacer configurable
	ServerSocket srvSocket(1234);
	
	// Creo el servidor
	HTTPServer server(new WebInterface::ReqHandlerFactory(), srvSocket, 
		new Poco::Net::HTTPServerParams());
	
	// Lo arranco
	server.start();

	// Espero
	waitForTerminationRequest();

	// Detengo el server
	server.stop();

	// Terminé OK
	return NGPDApp::EXIT_OK;
}
