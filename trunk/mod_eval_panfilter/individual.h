#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "writing_head.h"

/// Clase de los individuos a evaluar
class Individual
{
public:
	/// Constructor sin parámetros
	Individual() {}
	
	/// Constructor de copia
	Individual(const Individual& indiv);

	/// Constructor a partir de una netlist
	Individual(std::istream& is);

	/// Transforma al individuo en una netlist
	void ConvertToNetlist(std::ostream& os, bool showProbe = true) const;

	/// Renumera los vértices
	void ReenumerateVertices();

	/// Limpia al individuo para que el SPICE pueda procesarlo
	void SPICECleanUp();

	/// Devuelve el nodo que tiene una probe
	unsigned GetProbedNode() const;

	/// Obtiene las "cabezas de escritura"
	std::list<WritingHead>& GetWritingHeads()
	{ return writingHeads_; }

private:
	/// Datos del individuo, básicamente un grafo dirigido que representa
	/// la netlist
	TDigraph netlist_;

	/// "Cabezas de escritura" del individuo. Solo se utilizan durante el
	/// desarrollo.
	std::list<WritingHead> writingHeads_;
};

#endif
