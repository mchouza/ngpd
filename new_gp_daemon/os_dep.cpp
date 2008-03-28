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
// os_dep.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 26 de marzo de 2008
//=============================================================================

#include "os_dep.h"
#include "exceptions.h"
#include <cassert>

#ifdef WIN32

#include <shlobj.h>

std::string OSDep::getPath(EPath pathType)
{
	using Err::FatalException;
	using std::string;
	
	// Obtengo el AppData
	char szPath[MAX_PATH];
	if (FAILED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath)))
		throw FatalException(	"No pudieron encontrarse los archivos de "
								"configuración.");

	const string cfgBaseRelPath = "\\NGPD\\base_config.properties";
	const string cfgWritRelPath = "\\NGPD\\xtra_config.properties";
	const string appdataRelPath = "\\NGPD\\";

	switch (pathType)
	{
	case PATH_APP_DATA:
		return szPath + appdataRelPath;
	case PATH_CFG_BASE:
		return szPath + cfgBaseRelPath;
	case PATH_CFG_WRITEABLE:
		return szPath + cfgWritRelPath;
	}

	assert(!"Falta un tipo de path en EPath");
	return "INVALID_NEVER_REACHED";
}

void OSDep::disableErrorDialogs()
{
	// FIXME: Poner que modos se quieren desactivar
/*	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT |
		SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);*/
	SetErrorMode(SEM_FAILCRITICALERRORS);
}

void OSDep::enableErrorDialogs()
{
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT |
		SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
}

#else

#error OS no soportado

#endif
