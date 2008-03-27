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
// ini_file.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 27 de marzo de 2008
//=============================================================================

#include "exceptions.h"
#include "ini_file.h"
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace Lib;

INIFile::INIFile(const std::string& fileName) :
fileName_(fileName)
{	
	// Trato de abrir el archivo
	std::ifstream f(fileName_.c_str());
	if (!f.is_open())
		throw Err::CantOpenFileException(fileName_);

	using boost::regex;
	using boost::regex_match;
	using boost::smatch;

	// Para reconocer secciones y pares clave-valor
	regex secRE("^\\[[A-Za-z0-9._-]\\]$");
	regex pairRE("^([A-Za-z0-9._-]+)=([A-Za-z0-9._-]+|\"([^\"\\]|\\.)*\")$");
	smatch reMatch;

	// Lo leo línea a línea
	std::string section, line;
	while (std::getline(f, line))
	{
		// Limpio la línea de espacios adelante y atrás
		boost::algorithm::trim(line);

		// Si es un comentario sigo de largo
		if (line.empty() || line[0] == ';')
			continue;

		// Me fijo si es una sección
		if (regex_match(line, reMatch, secRE))
		{
			// Pongo la sección en section
			section = reMatch.str();
			
			// Veo la próxima
			continue;
		}

		// Me fijo si es una par clave-valor
		if (regex_match(line, reMatch, pairRE))
		{
			// Guardo el par clave-valor
			data_[section][reMatch.str(0)] = reMatch.str(1);
			
			// Veo la próxima
			continue;
		}

		// Si llegué acá es inválido
		throw Err::INIFormatException(line);
	}
}

INIFile::~INIFile()
{
	// Guarda antes de que se destruya
	flush();
}

void INIFile::flush()
{
	// Trato de abrir el archivo
	std::ofstream f(fileName_.c_str());
	if (!f.is_open())
		throw Err::CantOpenFileException(fileName_);

	// Recorro sección por sección
	for (TData::const_iterator it = data_.begin(); it != data_.end(); ++it)
	{
		// Si no es el primero, pongo una línea en blanco
		if (it != data_.begin())
			f << "\n";
		
		// Imprimo el encabezado de sección
		f << "[" << it->first << "]\n";


	}
}

std::vector<std::string> INIFile::enumerateSections() const
{
	std::vector<std::string> ret;
	for (TData::const_iterator it = data_.begin(); it != data_.end(); ++it)
		ret.push_back(it->first);
	return ret;
}
