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
// exceptions.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 26 de marzo de 2008
//=============================================================================

#include <Poco/Exception.h>

namespace Err
{
	/// Base de las excepciones de NGPD
	class BaseException : public Poco::Exception
	{
	public:
		BaseException(const std::string& msg) : Poco::Exception(msg) {}
	};

	/// Indica una excepción no recuperable
	class FatalException : public BaseException
	{
	public:
		FatalException(const std::string& msg) : BaseException(msg) {}
	};

	/// Indica una excepción de propósito informativo
	class InfoException : public BaseException
	{
	public:
		InfoException(const std::string& msg) : BaseException(msg) {}
	};

	/// Indica un error en el formato de un archivo INI
	class INIFormatException : public FatalException
	{
	public:
		INIFormatException(const std::string& line) :
		  FatalException("Error de formato. No se entiende: '" + line + "'.")
		{
		}
	};
}
