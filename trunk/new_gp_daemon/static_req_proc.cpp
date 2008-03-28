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
// static_req_proc.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 25 de marzo de 2008
//=============================================================================

#include "static_req_proc.h"
#include "proc_request.h"
#include <algorithm>
#include <fstream>

using namespace WebInterface;

namespace
{
	/// Obtiene la extesnión del archivo representado en la URI
	std::string getFileExtension(const std::string& uri)
	{
		using std::string;
		
		// Obtengo la posición a la derecha de la última barra
		size_t slashPos = uri.rfind('/');
		if (slashPos == uri.npos)
			slashPos = 0;
		else
			slashPos++;

		// Busco la posición a la derecha del último punto que esté después de
		// la última barra
		size_t dotPos = uri.rfind('.');
		if (dotPos != uri.npos && dotPos >= slashPos)
			dotPos++;
		else
			dotPos = uri.npos;

		// Devuelvo el pedazo de cadena que corresponde a la extensión
		if (dotPos != uri.npos)
			return string(uri, dotPos);
		else
			return "";
	}
}

void StaticReqProc::process(const ProcRequest& procReq, 
							Poco::Net::HTTPServerResponse& resp)
{
	// FIXME: TEMPORAL!!!
	// FIXME: FIJARSE SI EL TRUCO DEL rdbuf() SIRVE CON BINARIOS!!!
	
	using std::ifstream;
	using std::ios;
	using std::string;

	// Trato de abrir el archivo
	ifstream file(procReq.getURI().c_str(), ios::in|ios::binary);

	// Si fallo, listo
	if (!file.is_open())
	{
		resp.setContentType("text/plain");
		resp.send() << "404";
		return;
	}

	// Obtengo la extensión
	string ext = getFileExtension(procReq.getURI());

	// Me fijo el tipo de archivo por la extensión
	if (ext == "html" || ext == "htm")
		resp.setContentType("text/html");
	else if (ext == "png")
		resp.setContentType("image/png");
	else
		resp.setContentType("application/octet-stream");

	// Copio el archivo a la salida
	resp.send() << file.rdbuf();
}