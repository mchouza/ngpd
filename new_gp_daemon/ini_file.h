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
// ini_file.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 27 de marzo de 2008
//=============================================================================

#ifndef LIB_INI_H
#define LIB_INI_H

#include <boost/scoped_ptr.hpp>
#include <map>
#include <string>
#include <vector>

namespace Lib
{
	/// Clase encargada de manejar un INI
	class INIFile
	{
		/// Nombre del archivo
		std::string fileName_;
		
		/// Tipo de cada sección
		typedef std::map<std::string, std::string> TSection;

		/// Tipo de los datos
		typedef std::map<std::string, TSection> TData;
		
		/// Datos
		TData data_;

	public:
		/// Construye en base a los datos de un archivo
		INIFile(const std::string& fileName);

		/// Destructor. Guarda los cambios en el archivo desde donde cargó los
		/// datos
		virtual ~INIFile();

		/// Fuerza a guardar los cambios en el archivo
		void flush();

		/// Escribe un valor dada la sección y la clave 
		void writeValue(const std::string& section, const std::string& key, 
			const std::string& value);

		/// Lee un valor dada la sección y la clave
		std::string readValue(const std::string& section, 
			const std::string& key) const;

		/// Enumera las secciones del archivo
		std::vector<std::string> enumerateSections() const;

		/// Devuelve los pares clave-valor de una sección
		std::map<std::string, std::string> 
			enumeratePairs(const std::string& section) const;
	};
}

#endif
