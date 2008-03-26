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
// ngpd_config.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 26 de marzo de 2008
//=============================================================================

#ifndef NGPD_CONFIG_H
#define NGPD_CONFIG_H

#include <map>
#include <Poco/Util/AbstractConfiguration.h>

namespace Core
{
	/// Clase de la configuración de la aplicación (implemento una propia 
	/// porque la del framework no guarda)
	class NGPDConfig : public Poco::Util::AbstractConfiguration
	{
		/// Solo lectura?
		bool readOnly_;
		
		/// Nombre del archivo INI
		std::string iniFileName_;

		/// Tipo del map asociado
		typedef std::map<std::string, std::string> TDataMap;

		/// Map asociado
		TDataMap dataMap_;

	public:
		/// Construye a partir de un archivo INI
		NGPDConfig(const std::string& fileName, bool readOnly = true);

		/// Destructor (se encarga de guardar los datos)
		virtual ~NGPDConfig();

	protected:
		/// Obtiene los datos "en bruto"
		virtual bool getRaw(const std::string& key, std::string& value) const;

		/// Pone los datos "en bruto"
		virtual void setRaw(const std::string & key,
			const std::string & value);
	
		/// Devuelve en 'range' las claves que encuentre con prefijo 'key'
		virtual void enumerate(const std::string& key, Keys& range) const;
	};
}

#endif
