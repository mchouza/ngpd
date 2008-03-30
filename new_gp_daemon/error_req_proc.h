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
// error_req_proc.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 30 de marzo de 2008
//=============================================================================

#ifndef ERROR_REQ_PROC_H
#define ERROR_REQ_PROC_H

#include "req_processor.h"
#include <Poco/URI.h>

namespace WebInterface
{
	/// Procesa los pedidos de mensajes de error
	class ErrorReqProc : public ReqProcessor
	{
	public:
		/// Toma el ProcReq y devuelve el mensaje de error correspondiente
		virtual void process(const Poco::Net::HTTPServerRequest& procReq,
			Poco::Net::HTTPServerResponse& resp);

		/// Toma una URI y devuelve el mensaje de error correspondiente
		virtual void process(const Poco::URI& uri, 
			Poco::Net::HTTPServerResponse& resp);
	};
}

#endif
