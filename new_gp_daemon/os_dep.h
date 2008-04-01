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
// os_dep.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 26 de marzo de 2008
//=============================================================================

#ifndef OS_DEP_H
#define OS_DEP_H

#include <string>
#include <Poco/Path.h>

namespace OSDep
{
	/// Paths absolutos que se pueden pedir
	enum EPath
	{
		PATH_APP_DATA, PATH_CFG_BASE, PATH_CFG_WRITEABLE
	};
	
	/// Devuelve el path absoluto pedido
	std::string getPath(EPath pathType);

	/// Cambia de directorio en base a una string
	void chDir(const std::string& newPath);

	/// Cambia de directorio con un path de POCO
	void chDir(const Poco::Path& newPath);

	/// Desactiva los dialogs de error del sistema
	void disableErrorDialogs();

	/// Activa los dialogs de error del sistema
	void enableErrorDialogs();
}

#endif