#include "panf_genome_iterator.h"

using std::pair;

namespace
{
	/// Devuelve la cantidad de argumentos de un opcode
	size_t GetCantArgs(EOpCode opCode)
	{
		switch (opCode)
		{
		case END:
		case SAFE_CUT:
			return 0;
		case FLIP:
			return 1;
		case SERIES:
		case TWO_GROUND:
			return 2;
		case TWO_LEAD:
			return 3;
		case PARALLEL:
			return 4;
		default:
			// FIXME: lanzar algo más específico
			throw;
		}
	}
}

PANFGenomeIterator::PANFGenomeIterator(TGenome& genome, size_t pos) :
	ancestors_(), genome_(genome), kind_(EOK_CC), pos_(0)
{
	// Avanzo hasta llegar o pasarme
	for (; pos_ < pos; ++*this);
}

// FIXME: Depende del tamaño
PANFGenomeIterator& PANFGenomeIterator::operator ++()
{
	// Si estoy en el final, lanza una excepción
	if (pos_ == genome_.size())
		// FIXME: Lanzar algo más específico
		throw;
	
	// De acuerdo a la clase de operador sobre el que esté parado
	switch (kind_)
	{
	case EOK_CC:
		// Si es un terminal
		if (genome_[pos_] == END || genome_[pos_] == SAFE_CUT)
		{
			// Si tiene ancestros
			if (ancestors_.size() > 0)
			{			
				// Si después de decrementar al ancestro tengo 0, significa
				// que terminé con los argumentos de él y por lo tanto él
				// también terminó. Por ello lo saco del vector y le aplico
				// el mismo procedimiento a su ancestro y así hasta que
				// llegue a un ancestro con argumentos por procesar o me
				// quede sin nada en el vector de ancestros
				do
				{
					assert(ancestors_.back().second > 0);
					
					// Decremento la cuenta del ancestro
					--ancestors_.back().second;

					// Si llego a cero lo saco
					if (ancestors_.back().second == 0)
						ancestors_.pop_back();
					// Sino no hay nada más que hacer
					else
						break;

					// Mientras queden ancestros
				} while (ancestors_.size() > 0);
			}
			// Si no tiene ancestros solo incremento...
		}
		// Si no es un terminal
		else
		{
			// Continúo la construcción
			ancestors_.push_back(
				pair<size_t, size_t>(pos_,
					GetCantArgs(static_cast<EOpCode>(genome_[pos_]))));
			
			// En caso de tratarse de un TWO_LEAD, debo cambiar el tipo
			if (genome_[pos_] == TWO_LEAD)
				kind_ = EOK_CT;
		}

		// Incremento la posición
		++pos_;
		break;

	case EOK_CT:
		// Estoy en el tipo, sigue el valor
		kind_ = EOK_VAL;

		// El padre debe tener los 3 argumentos y ser un TWO_LEAD
		assert(genome_[ancestors_.back().first] == TWO_LEAD && ancestors_.back().second == 3);

		// Consumo un argumento
		--ancestors_.back().second;

		// Avanzo uno
		++pos_;
		break;

	case EOK_VAL:
		// Estoy en el valor, sigue continuando la construcción
		kind_ = EOK_CC;

		// El padre debe tener los 2 argumentos y ser un TWO_LEAD
		assert(genome_[ancestors_.back().first] == TWO_LEAD && ancestors_.back().second == 2);

		// Consumo un argumento
		--ancestors_.back().second;

		// Avanzo 4
		pos_ += 4;
		break;

	default:
		// No debería llegar acá
		assert(0);
	}

	// Devuelvo la referencia
	return *this;
}

PANFGenomeIterator PANFGenomeIterator::operator ++(int)
{
	PANFGenomeIterator tmp(*this);
	++*this;
	return tmp;
}

OCOrVal PANFGenomeIterator::operator *()
{
	return OCOrVal(TGenomeIterator(&genome_[pos_], &genome_),
		(kind_ == EOK_VAL) ? false : true);
}