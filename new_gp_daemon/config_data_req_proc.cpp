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
#include <Poco/Util/Application.h>

using namespace WebInterface;

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
			r << "<li>" << keys[i];
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
