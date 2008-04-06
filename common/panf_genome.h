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
// panf_genome.h
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Agregado a NGPD el 6 de abril de 2008
//=============================================================================

#ifndef PANF_GENOME_H
#define PANF_GENOME_H

// FIXME: Sacar cuando translade lo relacionado con individuos
#include <boost/graph/adjacency_list.hpp>

// FIXME: Agregar una descripci�n de la estructura del genoma

/// Clases de operaci�n
enum EOpKind
{
	/// Contin�a la construcci�n
	EOK_CC,
	/// Determina el tipo de un componente
	EOK_CT,
	/// Determina un valor
	EOK_VAL,
	/// Inv�lido
	EOK_INVALID
};

// FIXME: Ponerle prefijo a los valores del tipo enumerado
/// C�digos de operaci�n
enum EOpCode
{
	/// Componente con dos terminales (los �nicos utilizados)
	TWO_LEAD,
	/// Resistor
	R,
	/// Capacitor
	C,
	/// Inductor
	L,
	/// Divisi�n en serie
	SERIES,
	/// Divisi�n en paralelo
	PARALLEL,
	/// Conexi�n dentro del sub�rbol
	NODE,
	/// Conexi�n a larga distancia
	VIA,
	/// Conexi�n a tierra
	TWO_GROUND,
	/// Final de la construcci�n
	END,
	/// Corte seguro
	SAFE_CUT,
	/// Da vuelta una arista
	FLIP,
	/// Valor no v�lido
	EOC_INVALID
};

// FIXME: No corresponde aca
/// Tipos de componente
enum EComponentType
{
	RESISTOR, CAPACITOR, INDUCTOR, VSRC, WIRE, PROBE, INVALID
};

// FIXME: No corresponde aca
// Forward para el tipo de digrafo
struct Component;

// FIXME: No corresponde aca
/// Tipo del digrafo utilizado
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS,
	int, Component> TDigraph;

#endif
