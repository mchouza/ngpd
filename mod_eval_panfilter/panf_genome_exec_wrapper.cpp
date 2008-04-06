#include "component_namer.h"
#include "component_value_transl.h"
#include "panf_genome_exec_wrapper.h"
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;
using std::istream;
using std::istream_iterator;
using std::list;
using std::ostream;
using std::string;

void PANFGenomeExecWrapper::Execute(list<WritingHead> &writingHeads,
								const ComponentNamer& embryoCompNamer,
								const ComponentValueTransl& transl) const
{
	// Obtengo los iteradores del genoma
	TGenomeConstIterator itBegin = genome_.begin();
	TGenomeConstIterator itEnd = genome_.end();

	// Creo el objeto encargado de asignar nombres a los componentes
	ComponentNamer compNamer(embryoCompNamer);

	// Ejecuto en forma recursiva sobre cada cabeza
	list<WritingHead>::iterator itWHL = writingHeads.begin();
	list<WritingHead>::iterator itWHLEnd = writingHeads.end();
	for (; itWHL != itWHLEnd;)
		RecExecuteCC(itBegin, itEnd, writingHeads, itWHL++, compNamer, transl);
}

void PANFGenomeExecWrapper::RecExecuteCC(TGenomeConstIterator& itBegin,
									 TGenomeConstIterator itEnd,
									 list<WritingHead> &writingHeads,
									 list<WritingHead>::iterator itWHL,
									 ComponentNamer& componentNamer,
									 const ComponentValueTransl& transl,
									 bool onlyCheck)
{
	// FIXME: Hacer que si marco onlyCheck no tenga side effects
	
	// Me fijo que no se haya pasado
	if (itBegin == itEnd)
		// FIXME: Lanzar algo m�s espec�fico
		throw;
	
	// Leo el c�digo
	EOpCode opCode = static_cast<EOpCode>(*itBegin++);

	// Hago el gran switch
	switch (opCode)
	{
	case TWO_LEAD:
	{
		// Quiere insertar un componente
		
		// Obtengo los dos primeros argumentos
		EComponentType compType = RecExecuteCT(itBegin, itEnd);
		double value = RecExecuteVal(itBegin, itEnd, transl);

		// Construyo el componente y obtengo el iterador para seguir la
		// construcci�n
		WritingHead::TWHLIt itCC = WritingHead::SetComponent(writingHeads,
			itWHL, Component(compType, value,
							componentNamer.GetComponentName(compType)));

		// Contin�o la construcci�n
		RecExecuteCC(itBegin, itEnd, writingHeads, itCC, componentNamer,
			transl);
	}
	break;
	case SERIES:
	{
		// Quiere hacer una divisi�n serie

		// Hago la divisi�n y obtengo el par de iteradores
		WritingHead::TWHLItPair itCCPair =
			WritingHead::SeriesDiv(writingHeads, itWHL, componentNamer);

		// Contin�o la construcci�n con cada uno de ellos
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCPair.get<0>(),
			componentNamer, transl);
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCPair.get<1>(),
			componentNamer, transl);
	}
	break;
	case PARALLEL:
	{
		// Quiere hacer una divisi�n en paralelo
		
		// FIXME: Considerar que hay m�s de una posibilidad para la divisi�n
		// en paralelo

		// Hago la divisi�n y obtengo el quad de iteradores
		WritingHead::TWHLItQuad itCCQuad =
			WritingHead::ParallelDiv(writingHeads, itWHL, componentNamer);

		// Contin�o la construcci�n en los cuatro
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCQuad.get<0>(),
			componentNamer, transl);
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCQuad.get<1>(),
			componentNamer, transl);
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCQuad.get<2>(),
			componentNamer, transl);
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCQuad.get<3>(),
			componentNamer, transl);
	}
	break;
	case TWO_GROUND:
	{
		// Es igual que una divisi�n serie, pero conecta el nodo creado a
		// tierra
		// Hago la divisi�n y obtengo el par de iteradores
		WritingHead::TWHLItPair itCCPair =
			WritingHead::TwoGround(writingHeads, itWHL, componentNamer);

		// Contin�o la construcci�n con cada uno de ellos
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCPair.get<0>(),
			componentNamer, transl);
		RecExecuteCC(itBegin, itEnd, writingHeads, itCCPair.get<1>(),
			componentNamer, transl);
	}
	break;
	case FLIP:
	{
		// Da vuelta una arista

		// Hago el trabajo sobre la arista
		WritingHead::TWHLIt itCC = WritingHead::Flip(writingHeads, itWHL);

		// Contin�o la construcci�n
		RecExecuteCC(itBegin, itEnd, writingHeads, itCC, componentNamer,
			transl);
	}
	break;
	case END:
	{
		// Termino la construcci�n tal como est�
		// FIXME: Borrar la cabeza de escritura
	}
	break;
	case SAFE_CUT:
	{
		// Si puede, corta la arista

		// Llamo a la funci�n que hace este trabajo
		WritingHead::SafeCut(writingHeads, itWHL);

		// Termino la ejecuci�n
	}
	break;
	default:
		// Opcode err�neo
		// FIXME: lanzar algo m�s espec�fico
		throw;
	}
}

double PANFGenomeExecWrapper::RecExecuteVal(TGenomeConstIterator &itBegin,
										TGenomeConstIterator itEnd,
										const ComponentValueTransl& transl,
										bool onlyCheck)
{
	// FIXME: Hacer que si marco onlyCheck no tenga side effects
	// FIXME: En caso de que 4 bytes sea muy largo en general, ver de
	// implementar alguna codificaci�n de longitud variable

	// �ndice en la tabla de componentes
	unsigned index = 0;

	// Reuno 4 bytes
	for (int i = 0; i < 4; i++)
	{
		// Si me paso es un error
		if (itBegin == itEnd)
			// FIXME: Lanzar algo m�s espec�fico
			throw;

		// Agrego el byte actual
		index = (index << CHAR_BIT) | *itBegin;

		// Avanzo la posici�n
		++itBegin;
	}

	// Devuelvo el valor que corresponda
	return transl.GetComponentValue(index);
}

EComponentType PANFGenomeExecWrapper::RecExecuteCT(TGenomeConstIterator &itBegin,
											   TGenomeConstIterator itEnd,
											   bool onlyCheck)
{
	// FIXME: Hacer que si marco onlyCheck no tenga side effects

	// Me fijo no haberme pasado
	if (itBegin == itEnd)
		// FIXME: Lanzar algo m�s espec�fico
		throw;

	// Elijo seg�n la clase de componente
	switch (*itBegin++)
	{
	case R:
		return RESISTOR;
	case C:
		return CAPACITOR;
	case L:
		return INDUCTOR;
	default:
		// FIXME: Lanzar algo m�s espec�fico
		// FIXME: Ver si todas estas conversiones no podr�na centralizarse un poco
		throw;
	}
}

