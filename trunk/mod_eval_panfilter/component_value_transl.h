#ifndef COMPONENT_VALUE_TRANSL_H
#define COMPONENT_VALUE_TRANSL_H

/// Clase encargada de traducir un entero representando una posición en una
/// serie de valores de componentes al valor efectivo
class ComponentValueTransl
{
public:
	/// Construye una instancia en base a una tolerancia en partes por mil
	/// dada
	ComponentValueTransl(int tolerance);

	/// Devuelve el valor del componente en base a un índice teniendo
	/// en cuenta la tolerancia previamente establecida
	double GetComponentValue(unsigned index) const;

	/// Obtengo el máximo índice para la tolerancia establecida
	int GetMaxIndex() const;

private:
	/// Tolerancia
	int tolerance_;

	/// Puntero indicando la tabla utilizada
	int* table_;

	/// Cantidad de valores por década que tiene la tabla utilizada
	int valuesPerDec_;

	/// Cantidad de décadas soportada
	int cantDec_;
};

#endif
