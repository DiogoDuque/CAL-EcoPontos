/*
 * Ecoponto.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Filipe
 */

#include "Ecoponto.h"

Ecoponto::Ecoponto() {
	// TODO Auto-generated constructor stub

}

Ecoponto::Ecoponto(unsigned int trash, double id) {
	this->trash = trash;
	Parser temp;
	this->location=temp.getCoordFromIntID(temp.convertDoubleToIntID(id));
}

Ecoponto::~Ecoponto() {
	// TODO Auto-generated destructor stub
}

unsigned int Ecoponto::getTrash() const {
	return trash;
}

void Ecoponto::setTrash(unsigned int trash) {
	this->trash = trash;
}

Coord Ecoponto::getLocation() const {
	return location;
}

void Ecoponto::setLocation(Coord location) {
	this->location = location;
}

bool Ecoponto::operator<(const Ecoponto& other){
	return (this->trash < other.trash);
}

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
list<Ecoponto> fillMax(list<Ecoponto> &ecopontos, Truck truck){
	list<Ecoponto> res = {};
	unsigned int currentCapacity = truck.getCapacity();
	for (list<Ecoponto>::reverse_iterator it = ecopontos.rbegin(); it != ecopontos.rend() && currentCapacity > 0;){
		if((*it).getTrash() <= currentCapacity){
			currentCapacity -= (*it).getTrash();
			res.push_back(*it);
			++it;
			it= list<Ecoponto>::reverse_iterator(ecopontos.erase(it.base()));
		}
		else
			++it;
	}
	return res;
}

/**
 * Le os ecopontos do ficheiro 'Ecopontos.txt' e retorna uma lista com os mesmos.
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
		int trash;
		double id;
		string str[2];
		getline(file,str[0],';');
		if(file.eof())
		{
			throw "Reached end of file 'Ecopontos.txt' too soon! Is file complete?";
		}
		getline(file,str[1]);
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> trash;
		ecopontos.push_back(Ecoponto(trash,id));
	}
	file.close();
	ecopontos.sort();
	return ecopontos;
}

int totalTrash(list<Ecoponto> ecopontos){
	int res = 0;
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
		res+=(*it).getTrash();
	return res;
}

vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord first){
	vector<Coord> res = {};
	res.push_back(first);
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
			res.push_back(it->getLocation());
	return res;
}
