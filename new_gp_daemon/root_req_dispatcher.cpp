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
// root_req_dispatcher.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 25 de marzo de 2008
//=============================================================================

#include "root_req_dispatcher.h"
#include "config_data_req_proc.h"
#include "error_req_proc.h"
#include "req_processor.h"
#include "static_req_proc.h"
#include <Poco/URI.h>

using namespace WebInterface;

RootReqDispatcher::RootReqDispatcher() :
pErrorReqProc_(new ErrorReqProc())
{
	// Inicializo el mapa de despacho
	dispatchMap_["config-data"].reset(new ConfigDataReqProc());
	dispatchMap_["error"].reset(pErrorReqProc_.get());
	dispatchMap_["static"].reset(new StaticReqProc());
}

void RootReqDispatcher::dispatch(const Poco::Net::HTTPServerRequest& procReq,
								 Poco::Net::HTTPServerResponse &out)
{
	using Poco::URI;
	using std::string;
	using std::vector;

	// Construyo una URI
	URI uri(procReq.getURI());

	// Obtengo los segmentos del path
	vector<string> pathSegs;
	uri.getPathSegments(pathSegs);
	if (pathSegs.size() == 0)
		pathSegs.push_back(""); // Por consistencia

	// Uso el primer segmento para determinar a donde despachar
	TDispatchMap::iterator itDisp = dispatchMap_.find(pathSegs[0]);
	
	// Si no encontré a donde mandarlo, es error
	if (itDisp == dispatchMap_.end())
	{
		pErrorReqProc_->process(URI("/error?code=404"), out);
		return;
	}

	// Lo mando a donde corresponda
	itDisp->second->process(procReq, out);
}
