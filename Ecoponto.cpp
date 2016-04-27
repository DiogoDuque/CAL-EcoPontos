/*
 * Ecoponto.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Filipe
 */

#include "Ecoponto.h"

/**
 * Default constructor
 */
Ecoponto::Ecoponto() {
	trash = 0;
}

/**
 * Construtor
 * @param trash - amount of trash this Ecoponto has inside.
 * @param id - id of the node where this Ecoponto is located at.
 */
Ecoponto::Ecoponto(int trash,  int id) {
	this->trash = trash;
	Parser temp;
	this->location=temp.getCoordFromID(id);
}

/**
 * Destructor
 */
Ecoponto::~Ecoponto() {
	// TODO Auto-generated destructor stub
}

/**
 * @return amount of trash in this Ecoponto.
 */
int Ecoponto::getTrash() const {
	return trash;
}

/**
 * @param trash - new amount of trash in this Ecoponto.
 */
void Ecoponto::setTrash(int trash) {
	this->trash = trash;
}

/**
 * @return Ecoponto's location.
 */
Coord Ecoponto::getLocation() const {
	return location;
}

/**
 * @param location - Ecoponto's new location.
 */
void Ecoponto::setLocation(Coord location) {
	this->location = location;
}

/**
 * Compares the contents of the ecopontos: if one ecoponto has more trash than the other then it is 'bigger'
 *
 * @param other - ecoponto object that will be compared with this object
 * @return true if other has less trash than this object, false if otherwise
 */
bool Ecoponto::operator<(const Ecoponto& other){
	return (this->trash < other.trash);
}

/**
 * Receives the list of ecopontos and a truck (should be selected by poopBestTruck(trucks,[sum of trash in the ecopontos's list]))
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
list<Ecoponto> fillMax(list<Ecoponto> &ecopontos, Truck truck){
	list<Ecoponto> res = {};
	int currentCapacity = truck.getCapacity();
	for (list<Ecoponto>::reverse_iterator it = ecopontos.rbegin(); it != ecopontos.rend() && currentCapacity > 0;){
		if((*it).getTrash() <= currentCapacity){
			currentCapacity -= (*it).getTrash();
			res.push_back(*it);
			++it;
			it = list<Ecoponto>::reverse_iterator(ecopontos.erase(it.base()));
		}
		else
			++it;
	}
	return res;
}

/**
 * Reads from file 'Ecopontos.txt' and returns a list with the ecopontos on the file
 *
 * @return list with the ecopontos on 'Ecopontos.txt'
 */
list<Ecoponto> getEcopontos()
						{
	list<Ecoponto> ecopontos;
	fstream file;
	file.open("Ecopontos.txt");
	if(!file.is_open())
		throw "Could not open file 'Ecopontos.txt'!";
	while(!file.eof())
	{
		int id, trash;
		string str[2];
		getline(file,str[0],';');
		if(file.eof())
		{
			throw "Reached end of file 'Ecopontos.txt' too soon! Is file complete?";
		}
		getline(file,str[1]);
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> trash;

		if (trash > 100 || trash < 0)
			throw "Invalid amount of trash! The ecoponto must have 0 to 100 kg of trash...";

		ecopontos.push_back(Ecoponto(trash,id));
	}
	file.close();
	ecopontos.sort();			// sort ecopontos by amount of trash
	return ecopontos;
						}

/**
 * Receives the list of ecopontos and returns the sum of the trash of every Ecoponto on the list
 *
 * @param ecopontos - list of ecopontos
 * @return sum of the trash of every ecoponto on the list
 */
int totalTrash(list<Ecoponto> ecopontos){
	int res = 0;
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
		res+=(*it).getTrash();
	return res;
}

/**
 * Receives the list of ecopontos that will have its trash collected by a truck and the Coord of the initial point
 * Returns a vector with the Coord (location and id) of the central (initial) and of the ecopontos on the list
 *
 * @param ecopontos - list of ecopontos
 * @param initial - location and id (Coord) of the initial point (central)
 * @return vector with the Coord (location and id) of the central (initial) and of the ecopontos on the list
 */
vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord initial){
	vector<Coord> res = {};
	res.push_back(initial);
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
		res.push_back(it->getLocation());
	return res;
}
