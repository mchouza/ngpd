#ifndef SPICE_AC_OUT_H
#define SPICE_AC_OUT_H

#include <complex>
#include <iosfwd>
#include <set>
#include <vector>

/// Clase encargada de mostrarnos la salida de un análisis AC hecho con
/// SPICE
class SpiceACOut
{
public:
	/// Construye la salida en base a la salida textual
	SpiceACOut(const std::vector<char>& spiceRawOutput);

	/// Muestra la salida en forma de texto
	friend std::ostream& operator<<(std::ostream& os, const SpiceACOut& out);

	/// Obtiene el vector de valores de voltaje en un nodo dado
	void GetNodeVoltages(const std::string& node,
		std::vector<std::complex<double> >& voltages) const;

	/// Obtiene el vector de frecuencias
	const std::vector<double>& GetFreqs() const;

protected:
	/// Rellena los vectores de la clase
	void FillVectors(const std::vector<char>& spiceRawOutput);

private:
	/// Vector de vectores. Las filas representan cada nodo y las columnas
	/// cada frecuencia
	std::vector<std::vector<std::complex<double> > > data_;

	/// Vector indicando las frecuencias
	std::vector<double> freqs_;

	/// Vector indicando los nodos (siempre uso números, no strings)
	std::vector<unsigned> nodes_;
};

#endif
