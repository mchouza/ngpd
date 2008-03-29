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
// ngpd_modules.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 28 de marzo de 2008
//=============================================================================

#include "ngpd_modules.h"
#include "os_dep.h"
#include <module.h>
#include <Poco/DirectoryIterator.h>
#include <Poco/Util/Application.h>

using namespace Core;

namespace
{
	/// Obtiene todos los archivos en un directorio dado
	std::vector<std::string> getAllFilesInDir(const std::string& dirPath)
	{
		using Poco::DirectoryIterator;
		using std::string;
		using std::vector;

		vector<string> ret;

		// Acumulo los paths de los módulos
		DirectoryIterator dirIt(dirPath);
		DirectoryIterator endDirIt;
		for (; dirIt != endDirIt; ++dirIt)
			ret.push_back(dirIt.path().toString());

		// Devuelvo la lista
		return ret;
	}

	/// Carga un módulo especificado por su path
	void loadModule(const std::string& modulePath)
	{
		// FIXME: Hacer que funcione
	}

	/// Carga los módulos en un directorio dado
	void loadModulesAtDir(std::vector<boost::shared_ptr<Module> >& modules,
		const std::string& dirPath)
	{
		using Poco::Util::Application;
		using std::string;
		using std::vector;

		// Obtengo primero todos los archivos que estén en el directorio
		vector<string> filesInDir = getAllFilesInDir(dirPath);

		// Cargo todos los módulos
		Application::instance().logger();
		for (size_t i = 0; i < filesInDir.size(); i++)
			loadModule(filesInDir[i]);
	}

	/// Trata de cumplir con las dependencias de todos los módulos. En caso de
	/// que no puedan satisfacerse las de alguno, lo descarga
	void checkNSatisfyDependencies(
		std::vector<boost::shared_ptr<Module> >& modules)
	{
		// FIXME: Hacer que funcione
	}
}

NGPDModules::NGPDModules(const Poco::Util::AbstractConfiguration& config)
{
	using OSDep::getPath;
	using OSDep::PATH_APP_DATA;
	using std::string;

	// Obtengo el path del directorio de los módulos
	string modulesDirPath = getPath(PATH_APP_DATA) +
		config.getString("modulesRelPath");

	// Cargo los módulos en ese directorio
	loadModulesAtDir(modules_, modulesDirPath);

	// Reviso y satisfago a las dependencias
	checkNSatisfyDependencies(modules_);
}