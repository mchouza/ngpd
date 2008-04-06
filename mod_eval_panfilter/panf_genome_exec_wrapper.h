#ifndef PANF_GENOME_WRAPPER_H
#define PANF_GENOME_WRAPPER_H

#include "writing_head.h"
#include <evalmodule.h>

/// Actua como un "wrapper" del genoma, permitiendo su ejecución sobre el
/// embrión
class PANFGenomeExecWrapper
{
public:
	/// Constructor
	PANFGenomeExecWrapper(const TGenome& genome) :
	  genome_(genome)
	{
	}

	/// Ejecuta el genoma. Aplica los efectos de la ejecución sobre un
	/// conjunto de cabezas de escritura.
	void Execute(std::list<WritingHead>& writingHeads,
		const ComponentNamer& embryoCompNamer,
		const ComponentValueTransl& transl) const;

protected:
	/// Ejecuta una parte del genoma encargada de constinuar la construcción
	/// en forma recursiva
	static void RecExecuteCC(TGenomeConstIterator& itBegin,
		TGenomeConstIterator itEnd,
		std::list<WritingHead>& writingHeads,
		std::list<WritingHead>::iterator itWHL,
		ComponentNamer& compNamer,
		const ComponentValueTransl& transl,
		bool onlyCheck = false);

	/// Ejecuta una parte del genoma destinada a determinar un tipo de
	/// componente
	static EComponentType RecExecuteCT(TGenomeConstIterator& itBegin,
		TGenomeConstIterator itEnd,
		bool onlyCheck = false);

	/// Ejecuta una parte del genoma destinada a determinar un valor del
	/// componente
	static double RecExecuteVal(TGenomeConstIterator& itBegin,
		TGenomeConstIterator itEnd,
		const ComponentValueTransl& transl,
		bool onlyCheck = false);

private:
	/// Referencia al genoma original
	const TGenome& genome_;
};

#endif
