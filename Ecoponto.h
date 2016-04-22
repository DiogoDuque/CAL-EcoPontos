/*
 * Ecoponto.h
 *
 *  Created on: 22/04/2016
 *      Author: Filipe
 */

#ifndef ECOPONTO_H_
#define ECOPONTO_H_

#include <list>
#include "Utilities.h"
#include "Truck.h"
#include "Parser.h"

using namespace std;

class Ecoponto {
private:
	unsigned int trash;
	Coord location;
public:
	Ecoponto();
	Ecoponto(unsigned int trash, double id);
	virtual ~Ecoponto();

	unsigned int getTrash() const;
	void setTrash(unsigned int trash);

	Coord getLocation() const;
	void setLocation(Coord location);

	bool operator<(const Ecoponto& other);

};

/*
 * Receives the list of ecopontos and a truck (should be selected by popBestTruck(trucks,[sum of trash in the ecopontos's list]))
 * Returns the best list of ecopontos that tries to fill the truck to the maximum.
 *
 * Example: (Ecoponto, amount )
 *
 * ecopontos (A, 10), (B, 30), (C,50) , (D, 70)
 * Truck -> capacity = 100
 *
 *	Returns (B,D)
 *
 *	IMPORTANT: pops the result so ecopontos becomes just A,C
 */
list<Ecoponto> fillMax(list<Ecoponto> ecopontos, Truck truck);



list<Ecoponto> getEcopontos();
#endif /* ECOPONTO_H_ */
