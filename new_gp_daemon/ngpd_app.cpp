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

#include "ngpd_app.h"
#include "ngpd_modules.h"
#include "os_dep.h"
#include "web_server.h"
#include <Poco/Util/PropertyFileConfiguration.h>

using namespace Core;

NGPDApp::NGPDApp()
{
}

NGPDApp::~NGPDApp()
{
}

void NGPDApp::initialize(Poco::Util::Application& self)
{
	using WebInterface::WebServer;
	
	// Cargo la configuración
	loadConfiguration();

	// FIXME: Ver como hacer aparecer el primer mensaje en el log

	// Indico que estoy inicializando
	logger().information("Iniciando NGPD (New Genetic Programming Daemon)...");

	// Cargo los módulos
	addSubsystem(new NGPDModules(*this));

	// Inicio el servidor web
	addSubsystem(new WebServer(*this));

	// Llamo a la implementación de la clase base
	ServerApplication::initialize(self);
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
	using OSDep::chDir;
	using OSDep::getPath;
	using OSDep::PATH_APP_DATA;
	using OSDep::PATH_CFG_BASE;
	using OSDep::PATH_CFG_WRITEABLE;
	using Poco::Path;
	using Poco::Util::PropertyFileConfiguration;

	// Cambio al directorio de trabajo correcto
	chDir(getPath(PATH_APP_DATA));

	// Cargo la configuración base
	config().add(
		new PropertyFileConfiguration(getPath(PATH_CFG_BASE)),
		priority, false, false);

	// Cargo la configuración "editable" con una prioridad más baja, de modo 
	// que no pueda sobreescribir los parámetros básicos
	config().add(
		new PropertyFileConfiguration(getPath(PATH_CFG_WRITEABLE)),
		priority + 1, false, false);

	// Devuelvo la cantidad de configuraciones cargadas
	return 2;
}

int NGPDApp::main(const std::vector<std::string>& args)
{
	// Espero
	waitForTerminationRequest();

	// Terminé OK
	return EXIT_OK;
}
