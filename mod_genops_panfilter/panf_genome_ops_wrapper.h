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
// panf_genome_ops_wrapper.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Agregado a NGPD el 6 de abril de 2008
//=============================================================================

#ifndef PANF_GENOME_OPS_WRAPPER_H
#define PANF_GENOME_OPS_WRAPPER_H

#include <genome.h>

/// Actua como un "wrapper" del genoma, permitiendo la realizaci�n de 
/// operaciones sobre el mismo as� como su serializaci�n
class PANFGenomeOpsWrapper
{
public:
	/// Constructor a partir de un genoma
	PANFGenomeOpsWrapper(TGenome& genome) : genome_(genome) {}

	/// Construye un genoma en forma aleatoria
	void MakeRandom();

	/// Realiza la cruza con otro genoma
	void Cross(TGenome& otherGenome);

	/// Realiza la cruza con otro genoma con su corespondiente wrapper
	void Cross(PANFGenomeOpsWrapper& otherGenomeWrapper);

	/// Realiza una mutaci�n en el genoma
	void Mutate();

	/// Realiza una operaci�n de alteraci�n de arquitectura
	void AltOp();

	/// Devuelve el genoma en un formato textual o binario
	/// (por defecto textual).
	void Save(std::ostream& os, bool textualFormat = true) const;

	/// Carga un genoma  a partir de una descripci�n textual o binaria
	/// (por defecto textual).
	void Load(std::istream& is, bool textualFormat = true);

private:
	/// Referencia al genoma
	TGenome& genome_;
};

#endif
