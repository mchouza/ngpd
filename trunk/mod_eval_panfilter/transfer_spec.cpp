#include "transfer_spec.h"
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>

using std::istringstream;
using std::lower_bound;
using std::pair;
using std::sort;
using std::string;
using std::vector;

TransferSpec::TransferSpec(const string& sTS)
{
	// FIXME: Asume que no hay errores

	// Leo de a pares
	istringstream issTS(sTS);
	do
	{
		// El par frecuencia tensión
		pair<double, double> freqVoltagePair;

		// Leo la frecuencia
		issTS >> freqVoltagePair.first;

		// Leo la tensión
		issTS >> freqVoltagePair.second;

		// Guardo el par
		freqVoltage_.push_back(freqVoltagePair);

	} while (!issTS.eof());

	// Ordeno los pares por la frecuencia en orden creciente
	sort(freqVoltage_.begin(), freqVoltage_.end());
}

double TransferSpec::operator ()(double freq) const
{
	// Busco donde podría insertar esta frecuencia
	pair<double, double> tmp(freq, 0);
	vector<pair<double, double> >::const_iterator it =
		lower_bound(freqVoltage_.begin(), freqVoltage_.end(), tmp);

	// Si es al final o al principio, no tengo datos para interpolar
	if (it == freqVoltage_.begin() || it == freqVoltage_.end())
		// FIXME: Lanzar algo más específico
		throw;

	// Caso contrario, interpolo
	return 	(freq - (it-1)->first) /
			(it->first - (it-1)->first) * (it-1)->second +
			(it->first - freq) /
			(it->first - (it-1)->first) * it->second;
}