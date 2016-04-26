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
	/**
	 * Default constructor
	 */
	Ecoponto();

	/**
	 * Construtor
	 */
	Ecoponto(unsigned int trash, unsigned int id);

	/**
	 * Destructor
	 */
	virtual ~Ecoponto();

	unsigned int getTrash() const;
	void setTrash(unsigned int trash);

	Coord getLocation() const;
	void setLocation(Coord location);

	/**
	 * Compares the contents of the ecopontos: if one ecoponto has more trash than the other then it is 'bigger'
	 *
	 * @param other - ecoponto object that will be compared with this object
	 * @return true if other has less trash than this object, false if otherwise
	 */
	bool operator<(const Ecoponto& other);

};

/**
 * Receives the list of ecopontos and a truck (should be selected by popBestTruck(trucks,[sum of trash in the ecopontos's list]))
 * Returns the best list of ecopontos that tries to fill the truck to the maximum.
 *
 * Example: (Ecoponto, amount)
 * ecopontos (A, 10), (B, 30), (C,50) , (D, 70)
 * Truck -> capacity = 100
 *
 * Returns (B,D)
 *
 * IMPORTANT: pops the result so ecopontos becomes just A,C
 *
 * @param ecopontos - list of all of the ecopontos
 * @param truck - selected by popBestTruck
 * @return best list of ecopontos that tries to fill the truck to the maximum
 * @return list with the ecopontos on 'Ecopontos.txt'
 */
list<Ecoponto> fillMax(list<Ecoponto> &ecopontos, Truck truck);


/**
 * Reads from file 'Ecopontos.txt' and returns a list with the ecopontos on the file
 *
 * @return list with the ecopontos on 'Ecopontos.txt'
 */
list<Ecoponto> getEcopontos();


/**
 * Receives the list of ecopontos and returns the sum of the trash of every Ecoponto on the list
 *
 * @param ecopontos - list of ecopontos
 * @return sum of the trash of every ecoponto on the list
 */
int totalTrash(list<Ecoponto> ecopontos);


/**
 * Receives the list of ecopontos that will have its trash collected by a truck and the Coord of the initial point
 * Returns a vector with the Coord (location and id) of the central (initial) and of the ecopontos on the list
 *
 * @param ecopontos - list of ecopontos
 * @param initial - location and id (Coord) of the initial point (central)
 * @return vector with the Coord (location and id) of the central (initial) and of the ecopontos on the list
 */
vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord initial);

#endif /* ECOPONTO_H_ */
