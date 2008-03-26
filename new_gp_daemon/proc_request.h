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
// proc_request.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 25 de marzo de 2008
//=============================================================================

#ifndef PROC_REQUEST_H
#define PROC_REQUEST_H

#include <map>
#include <string>
#include <Poco/Net/HTTPServerRequest.h>

namespace WebInterface
{
	/// Representa un pedido HTTP procesado para eliminar lo que no me interesa
	class ProcRequest
	{
		/// URI relativa a la "raíz" del servidor
		std::string uri_;

		/// Parámetros
		std::map<std::string, std::string> params_;

	public:
		/// Lo construye a partir de un pedido HTTP
		ProcRequest(const Poco::Net::HTTPServerRequest& request);

		/// Obtiene la URI
		const std::string& getURI() const
		{
			return uri_;
		}

		/// Obtiene el map de parámetros
		const std::map<std::string, std::string>& getParams() const
		{
			return params_;
		}
	};
}

#endif
