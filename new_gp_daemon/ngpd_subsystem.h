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
// ngpd_subsystem.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 5 de abril de 2008
//=============================================================================

#ifndef NGPD_SUBSYSTEM_H
#define NGPD_SUBSYSTEM_H

#include <Poco/Logger.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/Util/Subsystem.h>

namespace Core
{
	/// Subsistema de la aplicaci�n NGPD
	class NGPDSubsystem : public Poco::Util::Subsystem
	{
		/// Aplicaci�n
		Poco::Util::Application& app_;

	public:
		/// Constructor
		NGPDSubsystem(Poco::Util::Application& app,
			const std::string& name);

		/// Destructor
		virtual ~NGPDSubsystem();

		/// Inicializaci�n
		virtual void initialize(Poco::Util::Application&) = 0;

		/// Liberaci�n de recursos
		virtual void uninitialize() = 0;

		/// Obtiene el nombre
		virtual const char* name() const = 0;

	protected:
		/// Configuraci�n "propia"
		const Poco::Util::AbstractConfiguration& config_;

		/// Log "propio"
		Poco::Logger& logger_;
	};
}

#endif
