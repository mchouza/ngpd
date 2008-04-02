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

#include "exceptions.h"
#include "ngpd_modules.h"
#include "os_dep.h"
#include <module.h>
#include <Poco/ClassLoader.h>
#include <Poco/DirectoryIterator.h>
#include <Poco/SharedLibrary.h>
#include <Poco/Util/Application.h>

using namespace Core;

// Inicializo el nombre
const char* NGPDModules::name_ = "NGPDModules";

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
	void loadModule(std::vector<boost::shared_ptr<Module> >& modules,
		const std::string& modulePath)
	{
		using boost::shared_ptr;
		using Poco::AbstractMetaObject;
		using Poco::ClassLoader;
		typedef Poco::ClassLoader<Module>::Manif TManif;
		typedef TManif::Iterator TManifIt;
		
		// Creo el ClassLoader
		ClassLoader<Module> loader;

		// Cargo el módulo y obtengo el "manifest"
		loader.loadLibrary(modulePath);
		const TManif& manif = *loader.findManifest(modulePath);

		// Recorro el manifest
		TManifIt it = manif.begin();
		TManifIt itEnd = manif.end();
		for (; it != itEnd; ++it)
		{
			// Obtengo el MetaObject
			const AbstractMetaObject<Module>& meta = **it;

			// Guardo el puntero correspondiente
			modules.push_back(shared_ptr<Module>(meta.create()));
		}
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
		for (size_t i = 0; i < filesInDir.size(); i++)
			loadModule(modules, filesInDir[i]);
	}

	/// Trata de cumplir con las dependencias de todos los módulos. En caso de
	/// que no puedan satisfacerse las de alguno, lo descarga
	void checkNSatisfyDependencies(
		std::vector<boost::shared_ptr<Module> >& modules)
	{
		using boost::shared_ptr;
		using Err::FatalException;
		typedef Module::Req TReq;
		using Poco::UUID;
		using std::map;
		using std::vector;
		
		// Armo un índice de los módulos por ID
		map<UUID, size_t> index;
		for (int i = 0; i < modules.size(); i++)
			index[modules[i]->GetID()] = i;

		// Para cada módulo
		for (size_t i = 0; i < modules.size(); i++)
		{
			// Si ya encontré que el módulo tenía dependencias imposibles de 
			// satisfacer
			if (!modules[i])
				// Sigo con otro
				continue;
			
			// Obtengo sus dependencias
			const vector<TReq>& reqs = modules[i]->GetReqMods();

			// Para cada dependencia
			for (size_t j = 0; j < reqs.size(); j++)
			{
				// No está satisfecha?
				if (index.find(reqs[j].first) == index.end() ||
					modules[index[reqs[j].first]]->GetVersion()
					< reqs[j].second)
				{
					// Marco como imposible de utilizar al módulo
					modules[i] = shared_ptr<Module>();

					// Salgo del for
					break;
				}
			}

			// Encontré dependencias no satisfechas con el módulo?
			if (!modules[i])
				// Empiezo desde el principio
				i = -1; // ATENCIÓN!! Modifico el índice del loop
		}

		// Si llegué acá es porque todos los módulos estaban en alguna de dos
		// situaciones:
		// 1) Marcado como imposible de utilizar
		// 2) Con todas sus dependencias posibles de encontrar
		
		// Satisfago las dependencias
		for (size_t i = 0; i < modules.size(); i++)
		{
			// Si es null, pruebo con el siguiente
			if (!modules[i])
				continue;

			// Busco los requerimientos
			const vector<TReq>& reqVec = modules[i]->GetReqMods();
			
			// Armo el vector de requerimientos
			vector<shared_ptr<Module> > reqs;
			for (size_t j = 0; j < reqVec.size(); j++)
				reqs.push_back(modules[index[reqVec[j].first]]);

			// Lo entrego al módulo
			if (!modules[i]->GiveReqMods(reqs))
				throw FatalException(
				"Error al satisfacer los requermientos del módulo " +
				modules[i]->GetName() + ".");
		}
	}

	/// Limpia el vector de módulos, eliminando los punteros nulos
	void cleanModulesVec(std::vector<boost::shared_ptr<Module> >& modules)
	{
		using boost::shared_ptr;
		using std::vector;
		
		// Creo un vector con los punteros no nulos
		vector<shared_ptr<Module> > cleanVec;
		for (size_t i = 0; i < modules.size(); i++)
			if (modules[i])
				cleanVec.push_back(modules[i]);

		// Intercambio contenidos
		modules.swap(cleanVec);
	}

	/// Muestra los módulos cargados
	void showLoadedModules(Poco::Logger& logger,
		const std::vector<boost::shared_ptr<Module> >& modules)
	{
		logger.information("Módulos cargados: ");
		for (size_t i = 0; i < modules.size(); i++)
			logger.information("\t" + modules[i]->GetName() + " (ID " +
			modules[i]->GetID().toString() + ")");
	}
}

NGPDModules::NGPDModules(Poco::Util::Application& app) :
app_(app)
{
}

void NGPDModules::initialize(Poco::Util::Application&)
{
	using OSDep::getPath;
	using OSDep::PATH_APP_DATA;
	using std::string;

	// Indico que estoy cargando los módulos
	app_.logger().information("Cargando los módulos...");

	// Obtengo el path del directorio de los módulos
	string modulesDirPath = getPath(PATH_APP_DATA) +
		app_.config().getString("modules.relPath");

	// Cargo los módulos en ese directorio
	loadModulesAtDir(modules_, modulesDirPath);

	// Reviso y satisfago a las dependencias
	checkNSatisfyDependencies(modules_);

	// Limpio el vector de módulos
	cleanModulesVec(modules_);

	// Indico qué módulos cargué finalmente
	showLoadedModules(app_.logger(), modules_);
}

void NGPDModules::uninitialize()
{
}

const char* NGPDModules::name() const
{
	return name_;
}
