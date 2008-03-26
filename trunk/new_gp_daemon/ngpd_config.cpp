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
// ngpd_config.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 26 de marzo de 2008
//=============================================================================

#include "exceptions.h"
#include "ngpd_config.h"
#include <fstream>
#include <cctype>

using namespace Core;

namespace
{
	/// Saca los espacios del comienzo de la cadena
	void trimLeading(std::string& s, char* extraneousChars = " \t")
	{
		s = s.substr(s.find_first_not_of(extraneousChars));
	}

	/// Saca los espacios del final de la cadena
	void trimTrailing(std::string& s, char* extraneousChars = " \t")
	{
		s = s.substr(0, s.find_last_not_of(extraneousChars)+1);
	}

	/// Obtiene una sección completa a partir de una línea como
	/// "[Sección1.SubsecciónA]"
	std::string parseSection(const std::string& line)
	{
		// Reviso que termine en ']'
		if (line[line.length() - 1] != ']')
			throw Err::INIFormatException(line);

		// Quito principio y fin, esa es la sección
		return line.substr(1, line.length() - 2);
	}

	/// Asigna una variable al mapa como corresponda
	void parseVar(const std::string& section, const std::string& line,
		std::map<std::string, std::string>& dataMap)
	{
		// FIXME: HACER QUE FUNCIONE
	}
	
	/// Carga los datos desde un INI a un map
	void loadMapFromINI(const std::string& fileName,
		std::map<std::string, std::string>& dataMap)
	{
		std::ifstream file(fileName.c_str());
		std::string line;
		std::string section;

		// Para cada línea
		while (std::getline(file, line))
		{
			// Elimino los espacios de adelante
			trimLeading(line);
			
			// Si empieza con ';' o está en blanco, no existe...
			if (line.empty() || line[0] == ';')
				continue;

			// Si empieza con '[', cambio de sección
			if (line[0] == '[')
			{
				section = parseSection(line);
				continue;
			}

			// Si empieza con un caracter alfabético, debería ser una variable
			if (std::isalpha(line[0]))
			{
				parseVar(section, line, dataMap);
			}

			// Si llega acá, es un error
			throw Err::INIFormatException(line);
		}
	}

	// Guarda los datos de un map en un INI
	void saveMapToINI(const std::string& fileName,
		const std::map<std::string, std::string>& dataMap)
	{
		// FIXME: Guardar
	}
}

NGPDConfig::NGPDConfig(const std::string& fileName, bool readOnly) :
readOnly_(readOnly),
iniFileName_(fileName)
{
	loadMapFromINI(iniFileName_, dataMap_);
}

NGPDConfig::~NGPDConfig()
{
	if (!readOnly_)
		saveMapToINI(iniFileName_, dataMap_);
}

void NGPDConfig::setRaw(const std::string& key, const std::string& value)
{ 
	// Si es solo lectura, falla
	if (readOnly_)
		throw Err::FatalException(	"No se puede escribir en una configuración"
									" de solo lectura.");

	// Pongo los datos al map
	dataMap_[key] = value;
}

bool NGPDConfig::getRaw(const std::string& key, std::string& value) const
{
	TDataMap::const_iterator it = dataMap_.find(key);
	if (it == dataMap_.end())
	{
		return false;
	}

	value = it->second;
	return true;
}

void NGPDConfig::enumerate(const std::string& key, 
						   Poco::Util::AbstractConfiguration::Keys& range)
						   const
{
	// FIXME: Devolver lo que corresponda
}