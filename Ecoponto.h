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
#include "Parser.h"

using namespace std;

/**
 *
 * This class stores an Ecoponto object that represents an ecoponto (recycling bin).
 * An Ecoponto object is characterized by its location and the amount of trash it currently has.
 *
 */
class Ecoponto {
private:
	unsigned int trash;				// amount of trash in the ecoponto (0 to 100 kg)
	Coord location;					// location of the ecoponto (id and coordinates)
public:
	Ecoponto();

	Ecoponto(int trash, int id);

	virtual ~Ecoponto();

	int getTrash() const;
	void setTrash(int trash);

	Coord getLocation() const;
	void setLocation(Coord location);

	bool operator<(const Ecoponto& other);

};


list<Ecoponto> fillMax(list<Ecoponto> &ecopontos, Truck truck);

list<Ecoponto> getEcopontos();

int totalTrash(list<Ecoponto> ecopontos);

vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord initial);

list<Ecoponto> CheckEcopontosToUnload(list<Ecoponto> eco, int min_load);

#endif /* ECOPONTO_H_ */
