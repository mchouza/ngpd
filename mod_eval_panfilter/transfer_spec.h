#ifndef TRANSFER_SPEC_H
#define TRANSFER_SPEC_H

#include <string>
#include <utility>
#include <vector>

/// Especifica la forma de la transferencia que se desea
class TransferSpec
{
public:
	/// Constructor a partir de una cadena
	TransferSpec(const std::string& sTS);

	/// Nos da el valor deseado del módulo de la transferencia para una
	/// frecuencia dada
	double operator()(double freq) const;

private:
	/// Vector con los pares frecuencia - voltaje
	std::vector<std::pair<double, double> > freqVoltage_;
};

#endif
