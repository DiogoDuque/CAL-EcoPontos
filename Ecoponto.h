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

list<Ecoponto> fillMax(list<Ecoponto>, Truck);


list<Ecoponto> getEcopontos();
#endif /* ECOPONTO_H_ */
