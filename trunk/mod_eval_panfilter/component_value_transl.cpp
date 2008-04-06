#include "component_value_transl.h"
#include <cmath>

using std::pow;

/// Namespace anónimo para ocultar las tablas
namespace
{
	// Todas las tablas están basadas en las del estándar IEC 606063.
	// Ver más información en http://en.wikipedia.org/wiki/Preferred_number.

	/// Tabla de valores de la serie de 5 % (E24)
	int fivePercentTable[] =
	{
		100, 110, 120, 130, 150, 160, 180, 200, 220, 240, 270, 300,
        330, 360, 390, 430, 470, 510, 560, 620, 680, 750, 820, 910
	};
}

ComponentValueTransl::ComponentValueTransl(int tolerance)
{
	// Se fija si es uno de los valores permitidos
	switch (tolerance)
	{
	case 50:
		// La tabla es la del 5 %
		table_ = fivePercentTable;
		valuesPerDec_ = sizeof(fivePercentTable) / sizeof(int);
		break;
	default:
		// No es una tolerancia válida
		// FIXME: lanzar algo apropiado
		throw;
	}

	// En todos los casos válidos guardo el valor de la tolerancia
	tolerance_ = tolerance;

	// En todos los casos tengo 12 décadas
	// R: 0.1 - 1 - 10 - 100 - 1k - 10k - 100k - 1M - 100M - 1G - 10G - 100G
	// C/L: 0.1p - 1p - 10p - 100p - 1n - 10n - 100n - 1u - 10u - 100u - 1m -
	// 10m - 100m
	cantDec_ = 12;
}

double ComponentValueTransl::GetComponentValue(unsigned index) const
{
	// Primero escalo el número al rango apropiado
	index %= (cantDec_ * valuesPerDec_);

	// Obtengo la década y el offset adentro de ella
	int dec = index / valuesPerDec_;
	int offset = index % valuesPerDec_;

	// Obtengo el multiplicador representando a las décadas
	double mult = pow(10.0, dec);

	// Obtengo el valor correspondiente de la tabla
	double offsetValue = table_[offset] / 1000.0;

	// Devuelvo el resultado (asume que es una resistencia,
	// sino debe escalarse)
	return offsetValue * mult;
}

int ComponentValueTransl::GetMaxIndex() const
{
	// FIXME: Hacer que funcione
	return -1;
}

