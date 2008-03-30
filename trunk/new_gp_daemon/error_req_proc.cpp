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
// error_req_proc.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 30 de marzo de 2008
//=============================================================================

#include "error_req_proc.h"
#include <boost/lexical_cast.hpp>
#include <Poco/URI.h>

using namespace WebInterface;

namespace
{
	/// Maneja un mensaje de error con código numérico
	void error(unsigned errCode, Poco::Net::HTTPServerResponse& resp)
	{
		// FIXME: Usar una plantilla
		resp.send() << "<h1>Error " << errCode << "</h1>";
	}

	/// Maneja un mensaje de error con código en un string
	void error(const std::string& strErrCode, 
		Poco::Net::HTTPServerResponse& resp)
	{
		using boost::bad_lexical_cast;
		using boost::lexical_cast;
		
		// Convierto el código a un número y lo proceso...
		try
		{
			unsigned errCode = lexical_cast<unsigned>(strErrCode);
			error(errCode, resp);
		}
		catch (bad_lexical_cast&)
		{
			error(400, resp);
		}
	}
}

void ErrorReqProc::process(const Poco::Net::HTTPServerRequest& procReq,
						   Poco::Net::HTTPServerResponse& resp)
{
	using Poco::URI;
	using std::map;
	using std::string;
	
	// Si el método es incorrecto, es bad request
	if (procReq.getMethod() != procReq.HTTP_GET)
	{
		error(400, resp);
		return;
	}

	// Hago un parse de la URI
	URI uri(procReq.getURI());

	// La mando al procesamiento por URI
	process(uri, resp);
}

void ErrorReqProc::process(const Poco::URI& uri, 
						   Poco::Net::HTTPServerResponse& resp)
{
	using std::string;
	
	// Me fijo si el query string empieza con code
	string qs = uri.getQuery();
	string prefix("code=");
	if (qs.find(prefix) != 0)
		// Si no está bien el formato, es error 400
		error(400, resp);
	else
		// Caso contrario, mando el error que corresponda
		error(qs.substr(prefix.size()), resp);
}
