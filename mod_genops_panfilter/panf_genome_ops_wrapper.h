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
