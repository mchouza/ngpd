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
// config_data_req_proc.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 27 de marzo de 2008
//=============================================================================

#include "config_data_req_proc.h"
#include "log_req_proc.h"
#include "template_utils.h"
#include <sstream>
#include <port.h> // El orden importa, debe ser anterior a 'template.h'
#include <google/template.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/Application.h>

using namespace WebInterface;

namespace
{
	// FIXME: Hacer que funcione con lso datos de config
	/// Rellena los parámetros de la configuración
	void fillConfig(google::TemplateDictionary& dict)
	{
		using google::TemplateDictionary;
		using std::ostringstream;
		
		// Para cada variable
		for (int i = 0; i < 10; i++)
		{
			// Para armar el nombre de variable
			ostringstream oss;
			
			// Agrego un diccionario de sección
			TemplateDictionary* pSD = dict.AddSectionDictionary("VAR_SEC");

			// Le agrego la variable
			oss << "Var" << i;
			pSD->SetValue("VAR_NAME", oss.str());
			pSD->SetIntValue("VAR_VALUE", i + 2);
		}
	}
	
	/// Rellena el diccionario de las templates con los parámetros de 
	/// configuración
	void fillTemplateDict(google::TemplateDictionary& dict)
	{
		using Utils::Template::fillFooter;
		using Utils::Template::fillHeader;
		using Utils::Template::fillMenu;
		using Utils::Template::fillPageHeader;
		
		// FIXME: Poner el path del script de config desde la config :-)

		// Relleno las distintas partes del template
		// FIXME: Indicar el prefix en el título...
		fillHeader(dict, "NGPD::Config", "/static/config.js"); 
		fillPageHeader(dict);
		fillMenu(dict);
		fillFooter(dict);
		fillConfig(dict);
	}
}

void ConfigDataReqProc::process(const Poco::Net::HTTPServerRequest& procReq,
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
	
	// FIXME: Manejar errores en el pedido
	// FIXME: Sacar el path de los templates por la configuración, no ponerlo
	// "hardcoded". Ponerlo en la configuración del subsistema WebServer.
	// FIXME: Cargar los templates al arrancar el subsistema WebServer.

	// Diccionario
	TemplateDictionary dict("config");

	// Configuro el directorio raíz
	Template::SetTemplateRootDirectory("./templates");

	// Relleno el diccionario
	fillTemplateDict(dict);

	// Salida
	string outStr;

	// Cargo y expando el template
	Template* pTemplate = Template::GetTemplate("config.tpl", DO_NOT_STRIP);
	pTemplate->Expand(&outStr, &dict);

	// Mando un archivo HTML
	resp.setContentType("text/html");

	// Copio el template expandido a la salida
	resp.send() << outStr;
}

// FIXME: Eliminar una vez que funcione la alternativa
#if 0

namespace
{
	void recPrint(std::ostream& r, Poco::Util::AbstractConfiguration& c)
	{
		using Poco::Util::AbstractConfiguration;
		
		r << "<ul>";
		AbstractConfiguration::Keys keys;
		c.keys("", keys);
		for (size_t i = 0; i < keys.size(); i++)
		{
			r << "<li>" << "<b>" << keys[i] << "</b>";
			if (c.hasProperty(keys[i]))
				r << " - " << c.getRawString(keys[i]);		
			AbstractConfiguration& cc = *c.createView(keys[i]);
			recPrint(r, cc);
			r << "</li>";
		}
		r << "</ul>";
	}
}

void ConfigDataReqProc::process(const Poco::Net::HTTPServerRequest& procReq,
								Poco::Net::HTTPServerResponse& resp)
{
	using Poco::Util::AbstractConfiguration;
	using Poco::Util::Application;
	using std::ostream;
	
	resp.setContentType("text/html");
	ostream& r = resp.send();
	AbstractConfiguration& c =
		Application::instance().config();
	r << "<h1>Variables</h1>";
	recPrint(r, c);
}

#endif