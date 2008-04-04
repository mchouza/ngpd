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
// web_server.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 27 de marzo de 2008
//=============================================================================

#include "web_server.h"
#include "req_handler_factory.h"
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Util/Application.h>

using namespace WebInterface;

// Inicializo el nombre
const char* WebServer::name_ = "WebServer";

WebServer::WebServer(Poco::Util::Application& app) :
app_(app),
logger_(Poco::Logger::get("WebServer"))
{
}

WebServer::~WebServer()
{
}

void WebServer::initialize(Poco::Util::Application&)
{
	// Indico que estoy cargando los módulos
	logger_.information("Iniciando servidor web...");
	
	// Creo el "server socket"
	// FIXME: Hacer configurable
	pSrvSocket_.reset(new Poco::Net::ServerSocket(1234));

	// Creo al servidor HTTP
	pServer_.reset(new Poco::Net::HTTPServer(
		new WebInterface::ReqHandlerFactory(), 
		*pSrvSocket_, 
		new Poco::Net::HTTPServerParams()));
	
	// Arranco el servidor HTTP
	pServer_->start();

	// Indico que el servidor web está iniciado
	logger_.information("Servidor web iniciado.");
}

void WebServer::uninitialize()
{
	// Detengo el servidor HTTP
	pServer_->stop();

	// Destruyo al servidor HTTP
	pServer_.reset();

	// Destruyo al "server socket"
	pSrvSocket_.reset();
}

const char* WebServer::name() const
{
	return name_;
}
