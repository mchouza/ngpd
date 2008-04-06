#ifndef PANF_GENOME_ITERATOR_H
#define PANF_GENOME_ITERATOR_H

#include <genome.h>
#include <panf_genome.h>
#include <vector>

/// Clase que representa un opcode o un valor
class OCOrVal
{
public:
	/// Operador de cast a entero
	operator unsigned() const;

	/// Operador de cast a opcode
	operator EOpCode() const;

	/// Indica si se trata de un valor
	bool IsVal() const
	{
		return !isOC_;
	}

	/// Indica si se trata de un opcode
	bool IsOC() const
	{
		return isOC_;
	}

private:
	/// Constructor
	OCOrVal(TGenomeIterator it, bool isOC) : it_(it), isOC_(isOC)
	{
	}

	/// Iterador sobre el genoma "raw"
	TGenomeIterator it_;

	/// Indica si se trata de un opcode
	bool isOC_;

	/// La clase del iterador puede construirla
	friend class PANFGenomeIterator;
};

/// Clase del iterador que recorre el genoma
class PANFGenomeIterator
{
public:
	/// Constructor a partir de un genoma en posición cero
	PANFGenomeIterator(TGenome& genome) : ancestors_(),
		genome_(genome), pos_(0), kind_(EOK_CC)
	{
	}

	/// Constructor  apartir de un genoma en posición distinta a cero
	PANFGenomeIterator(TGenome& genome, size_t pos);

	/// Incremento prefijo
	PANFGenomeIterator& operator ++();

	/// Incremento posfijo
	PANFGenomeIterator operator ++(int);

	/// Desreferenciación
	OCOrVal operator *();

	/// Devuelve la profundidad
	size_t GetDepth() const
	{
		return ancestors_.size();
	}

	/// Devuelve la posición
	size_t GetPos() const
	{
		return pos_;
	}

	/// Devuelve la clase de elemento
	EOpKind GetKind() const
	{
		return kind_;
	}

private:
	/// Ancestros
	std::vector<std::pair<size_t, size_t> > ancestors_;

	/// Referencia al genoma
	TGenome& genome_;

	/// Posición en el genoma
	size_t pos_;

	/// Tipo del opcode donde está parado
	EOpKind kind_;
};

#endif
