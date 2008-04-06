#ifndef WRITING_HEAD_H
#define WRITING_HEAD_H

#include "component.h"
#include <boost/tuple/tuple.hpp>

/// Clase de las cabezas de escritura. Se encargan de modificar componentes en
/// desarrollo del embrión. Muchas de las operaciones son destructivas, lo que
/// significa que invalidan la cabeza de escritura original.
class WritingHead
{
public:
	// Para simplificar la interfaz
	typedef std::list<WritingHead> TWHList;
	typedef std::list<WritingHead>::iterator TWHLIt;
	typedef std::list<WritingHead>::const_iterator TWHLCIt;
	typedef boost::tuple<TWHLIt, TWHLIt> TWHLItPair;
	typedef boost::tuple<TWHLIt, TWHLIt, TWHLIt> TWHLItTriple;
	typedef boost::tuple<TWHLIt, TWHLIt, TWHLIt, TWHLIt> TWHLItQuad;
	
	/// Constructor
	WritingHead(TDigraph& digraph,
		boost::graph_traits<TDigraph>::edge_descriptor& edge) :
		digraph_(digraph), edgeRef_(edge)
	{
	}

	// FIXME: Considerar las dos posibilidades!
	/// Divide en paralelo. Es destructiva.
	static TWHLItQuad ParallelDiv(TWHList& whList, TWHLIt whIt,
		ComponentNamer& compNamer);

	/// Divide en serie. Es destructiva.
	static TWHLItPair SeriesDiv(TWHList& whList, TWHLIt whIt,
		ComponentNamer& compNamer);

	/// Conecta a tierra. Es destructiva.
	static TWHLItPair TwoGround(TWHList& whList, TWHLIt whItconst,
		ComponentNamer& compNamer);

	/// Pone un componente asociado a la arista. Es destrutiva.
	static TWHLIt SetComponent(TWHList& whList, TWHLIt whIt,
		const Component& comp);

	/// Corta la arista en caso de que sea seguro, sino es los mismo que
	/// terminar
	static void SafeCut(TWHList& whList, TWHLIt whIt);

	/// Da vuelta una arista
	static TWHLIt Flip(TWHList& whList, TWHLIt whIt);

	/// Permite que lso individuos puedan copiarlas modificando el digrafo
	friend class Individual;

private:
	/// Referencia al digrafo
	TDigraph& digraph_;

	/// Referencia a la arista
	boost::graph_traits<TDigraph>::edge_descriptor edgeRef_;
};

#endif
