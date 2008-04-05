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
// ngpd_job_manager.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 3 de abril de 2008
//=============================================================================

#include "ngpd_job_manager.h"

using namespace Core;

// Inicializo el nombre
const char* NGPDJobManager::name_ = "NGPDJobManager";

NGPDJobManager::NGPDJobManager(Poco::Util::Application& app) :
NGPDSubsystem(app, name_)
{
}

NGPDJobManager::~NGPDJobManager()
{
}

void NGPDJobManager::initialize(Poco::Util::Application&)
{
	// Indico que estoy cargando los trabajos
	logger_.information("Cargando los trabajos...");

	// Realizo la carga de trabajos
	loadJobsAtDir("");

	// Indico que terminé de cargar los trabajos
	logger_.information("Carga de trabajos finalizada.");
}

void NGPDJobManager::uninitialize()
{
	// FIXME: Liberar recursos!!
}

const char* NGPDJobManager::name() const
{
	return name_;
}

void NGPDJobManager::loadJobsAtDir(const std::string& path)
{
	// FIXME: Hacer que cargue a los trabajos
}