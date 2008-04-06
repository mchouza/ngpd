#ifndef COMPONENT_NAMER_H
#define COMPONENT_NAMER_H

#include <panf_genome.h>
#include <map>
#include <sstream>
#include <string>

/// Se ocupa de darle nombre a los componentes
class ComponentNamer
{
public:
	/// Constructor
	// FIXME: Arreglar para que siga la secuencia de los nombres ya
	// existentes en el embri�n. (Usar constructor de copia?)
	ComponentNamer()
	{
		charByComp_[RESISTOR] = 'R';
		charByComp_[CAPACITOR] = 'C';
		charByComp_[INDUCTOR] = 'L';
		charByComp_[WIRE] = 'Z';
		charByComp_[VSRC] = 'V';
		charByComp_[PROBE] = 'P';
		nextNum_[RESISTOR] = 1;
		nextNum_[CAPACITOR] = 1;
		nextNum_[INDUCTOR] = 1;
		nextNum_[WIRE] = 1;
		nextNum_[VSRC] = 1;
		nextNum_[PROBE] = 1;
	}

	/// Avanza para evitar colisiones con una netlist que se le pasa como
	/// par�metro
	void Advance(std::istream& is)
	{
		// Leo y descarto la primera l�nea (el t�tulo)
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Leo l�nea a l�nea
		std::string line;
		while (getline(is, line))
		{			
			// Transformo la l�nea a may�sculas
			transform(line.begin(), line.end(), line.begin(), toupper);
			
			// Obtengo el primer caracter
			std::istringstream lineSS(line);
			char compTypeCh;
			lineSS >> compTypeCh;

			// Obtengo el n�mero
			unsigned number;
			lineSS >> number;

			// De acuerdo al tipo de componente, actualizo
			// FIXME: Ver si no se puede centralizar mucho de este trabajo
			EComponentType compType;
			switch (compTypeCh)
			{
			case 'R':
				compType = RESISTOR;
				break;
			case 'C':
				compType = CAPACITOR;
				break;
			case 'L':
				compType = INDUCTOR;
				break;
			case 'Z':
				compType = WIRE;
				break;
			case 'V':
				compType = VSRC;
				break;
			case 'P':
				compType = PROBE;
				break;
			default:
				// FIXME: Lanzar algo m�s espec�fico
				throw;
			}
			nextNum_[compType] = std::max(nextNum_[compType], number + 1);
		}
	}

	/// Obtiene el pr�ximo nombre
	std::string GetComponentName(EComponentType compType)
	{
		// Donde armo la salida
		std::ostringstream oss;
		
		// Devuelvo el que sigue
		oss << charByComp_.find(compType)->second << nextNum_[compType]++;

		// Devuelvo el valor
		return oss.str();
	}	

private:
	/// Mapa que guarda el siguiente n�mero a asignar
	std::map<EComponentType, unsigned> nextNum_;

	/// Mapa que guarda las letras por cada tipo de componente
	std::map<EComponentType, char> charByComp_;
};	

#endif
