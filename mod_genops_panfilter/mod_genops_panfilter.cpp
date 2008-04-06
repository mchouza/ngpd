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
// mod_genops_panfilter.cpp
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Agregado a NGPD el 6 de abril de 2008
//=============================================================================

#include "mod_genops_panfilter.h"
#include "panf_genome_ops_wrapper.h"
#include <Poco/ClassLibrary.h>

using boost::shared_ptr;
using Poco::UUID;
using std::istream;
using std::map;
using std::ostream;
using std::string;
using std::vector;

const string ModGenOpsPAnFilter::name_ = "GenOpsPassiveAnalogFilter";
const UUID ModGenOpsPAnFilter::id_ =
	UUID("0b0656d6-5d68-11dc-8314-0800200c9a66");
const unsigned int ModGenOpsPAnFilter::version_ = 0;
const vector<Module::Req> ModGenOpsPAnFilter::reqs_ =
	std::vector<Module::Req>();

POCO_BEGIN_MANIFEST(Module)
	POCO_EXPORT_CLASS(ModGenOpsPAnFilter)
POCO_END_MANIFEST

bool ModGenOpsPAnFilter::GiveConfigData(const map<string,string> &configData)
{
	// FIXME: Hacer que funcione
	return true;
}

bool ModGenOpsPAnFilter::GiveReqMods(const vector<shared_ptr<Module> > &reqMods)
{
	// No requiere m�dulos, devuelvo error si me los dan
	return reqMods.size() == 0;
}

void ModGenOpsPAnFilter::RandomInit(TGenome &genome) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.MakeRandom();
}

void ModGenOpsPAnFilter::Mutate(TGenome &genome) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.Mutate();
}

void ModGenOpsPAnFilter::Cross(TGenome &genome1, TGenome &genome2) const
{
	PANFGenomeOpsWrapper wrapper(genome1);
	wrapper.Cross(genome2);
}

void ModGenOpsPAnFilter::AltOp(TGenome& genome) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.AltOp();
}

void ModGenOpsPAnFilter::Load(istream& is, TGenome& genome, bool textualFormat) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.Load(is, textualFormat);
}

void ModGenOpsPAnFilter::Save(ostream& os, TGenome& genome, bool textualFormat) const
{
	PANFGenomeOpsWrapper wrapper(genome);
	wrapper.Save(os, textualFormat);
}