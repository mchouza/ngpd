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
// log_req_proc.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 31 de marzo de 2008
//=============================================================================

#include "log_req_proc.h"
#include <fstream>
#include <sstream>
#include <port.h> // El orden importa, debe ser anterior a 'template.h'
#include <google/template.h>
#include <Poco/Net/HTTPServerRequest.h>

using namespace WebInterface;

void LogReqProc::process(const Poco::Net::HTTPServerRequest& procReq,
						 Poco::Net::HTTPServerResponse& resp)
{
	using google::DO_NOT_STRIP;
	using google::Template;
	using google::TemplateDictionary;
	using google::TemplateString;
	using std::ifstream;
	using std::ios;
	using std::ostringstream;
	using std::string;
	using std::vector;
	
	// FIXME: Manejar errores en el pedido o por ausencia de log
	// FIXME: Sacar el path del archivo de log por la configuración, no ponerlo
	// "hardcoded".
	// FIXME: Sacar el path de los templates por la configuración, no ponerlo
	// "hardcoded".
	// FIXME: Pensar como simplificar la creación de la salida

	// Trato de abrir el archivo
	ifstream logFile("NGPD.log", ios::in);

	// Diccionario
	TemplateDictionary dict("log");

	if (logFile.is_open())
	{
		// Stream para leer el archivo
		ostringstream oss;
		oss << logFile.rdbuf();

		// Relleno el diccionario
		dict.SetValue("LOG", oss.str());
	}
	else
	{
		// Relleno el diccionario indicando error
		dict.SetValue("LOG", "-- ERROR NO SE CARGÓ EL LOG --");
	}

	// Salida
	string outStr;

	// Cargo y expando el template
	Template* pTemplate = Template::GetTemplate("templates/log.tpl", 
		DO_NOT_STRIP);
	pTemplate->Expand(&outStr, &dict);

	// Mando un archivo HTML
	resp.setContentType("text/html");

	// Copio el template expandido a la salida
	resp.send() << outStr;
}
