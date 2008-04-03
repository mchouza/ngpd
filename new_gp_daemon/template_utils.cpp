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
// template_utils.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 1 de abril de 2008
//=============================================================================

#include "template_utils.h"
#include <port.h> // El orden importa, debe ser anterior a 'template.h'
#include <google/template.h>

namespace Utils { namespace Template {

// FIXME: Usar strings predefinidas!!!

void fillHeader(google::TemplateDictionary& dict, const std::string& pageTitle,
				const std::string& scriptSrc)
{
	using google::TemplateDictionary;
	
	TemplateDictionary* pHeaderDict = dict.AddIncludeDictionary("HEADER");
	pHeaderDict->SetFilename("header.tpl");
	pHeaderDict->SetValue("TITLE", pageTitle);

	// Si me indican que va con un script, lo agrego
	if (!scriptSrc.empty())
	{
		// Agrego el valor y muestro la sección
		pHeaderDict->SetValueAndShowSection("SCRIPT_SRC", scriptSrc,
			"SCRIPT_SEC");
	}
}

void fillPageHeader(google::TemplateDictionary& dict)
{
	using google::TemplateDictionary;
	
	TemplateDictionary* pPageHeaderDict = 
		dict.AddIncludeDictionary("PAGE_HEADER");
	pPageHeaderDict->SetFilename("page_header.tpl");
}

void fillMenu(google::TemplateDictionary& dict)
{
	using google::TemplateDictionary;
	
	TemplateDictionary* pMenuDict = dict.AddIncludeDictionary("MENU");
	pMenuDict->SetFilename("menu.tpl");
}

void fillFooter(google::TemplateDictionary& dict)
{
	using google::TemplateDictionary;
	
	TemplateDictionary* pFooterDict = dict.AddIncludeDictionary("FOOTER");
	pFooterDict->SetFilename("footer.tpl");
}

}} // Cierro los namespaces
