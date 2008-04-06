#ifndef COMPONENT_H
#define COMPONENT_H

#include "component_namer.h"
#include <panf_genome.h>

// FIXME: Tener en cuenta la tabla de valores al dividir o multiplicar...
/// Struct que representa un componente
struct Component
{
	/// Constructor sin parámetros
	Component() : type_(INVALID), value_(0.0), name_()
	{
	}

	/// Constructor con parámetros
	Component(EComponentType type, double value, const std::string& name,
		bool adaptValue = true) :
		type_(type), value_(value), name_(name)
	{
		// El valor de los capacitores y de lso inductores se expresa en pico
		if (adaptValue && (type_ == CAPACITOR || type_ == INDUCTOR))
			value_ *= 1e-12;
	}
	
	/// Modifica el valor de este componente y retorna otro de modo de que la
	/// combinación serie entre ambos nos de el mismo valor que el del 
	/// componente original
	Component SeriesDivide(ComponentNamer& namer)
	{
		// Modifico el valor
		switch (type_)
		{
		case RESISTOR:
		case INDUCTOR:
			value_ /= 2.0;
			break;
		case CAPACITOR:
			value_ *= 2.0;
			break;
		case WIRE:
		case PROBE:
			// El valor no tiene importancia...
			break;
		default:
			// Atrapo casos perdidos
			// FIXME: Hacer más específico
			throw;
		}

		// Devuelvo uno nuevo
		return Component(type_, value_, namer.GetComponentName(type_), false);
	}

	/// Modifica el valor de este componente y retorna otro de modo de que la
	/// combinación paralelo entre ambos nos de el mismo valor que el del 
	/// componente original
	Component ParallelDivide(ComponentNamer& namer)
	{
		// Modifico el valor
		switch (type_)
		{
		case RESISTOR:
		case INDUCTOR:
			value_ *= 2.0;
			break;
		case CAPACITOR:
			value_ /= 2.0;
			break;
		case WIRE:
		case PROBE:
			// El valor no tiene importancia...
			break;
		default:
			// Atrapo casos perdidos
			// FIXME: Hacer más específico
			throw;
		}

		// Devuelvo uno nuevo
		return Component(type_, value_, namer.GetComponentName(type_), false);
	}

	/// Tipo del componente
	EComponentType type_;

	/// Valor del componente
	double value_;

	/// Nombre del componente
	std::string name_;
};

#endif
