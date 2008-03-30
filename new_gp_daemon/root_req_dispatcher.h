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
// root_req_dispatcher.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 25 de marzo de 2008
//=============================================================================

#ifndef ROOT_REQ_DISPATCHER_H
#define ROOT_REQ_DISPATCHER_H

#include "req_dispatcher.h"
#include "web_interface_fwd.h"
#include <boost/shared_ptr.hpp>

namespace WebInterface
{
	/// Se encarga de tomar las decisiones en base a las URI originales
	class RootReqDispatcher : public ReqDispatcher
	{
		/// Tipo del mapa para despachar
		typedef std::map<std::string, boost::shared_ptr<ReqProcessor> >
			TDispatchMap;

		/// Dispatcher especial para casos de error
		boost::shared_ptr<ErrorReqProc> pErrorReqProc_;
		
		/// Mapa para despachar
		TDispatchMap dispatchMap_;

	public:
		/// Constructor
		RootReqDispatcher();

		/// Envía el pedido hacia donde deba procesarse
		virtual void dispatch(const Poco::Net::HTTPServerRequest& procReq,
			Poco::Net::HTTPServerResponse& out);
	};
}

#endif
