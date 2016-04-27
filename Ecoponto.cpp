/*
 * Ecoponto.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Filipe
 */

#include "Ecoponto.h"

Ecoponto::Ecoponto() {
	trash = 0;
}

Ecoponto::Ecoponto(int trash,  int id) {
	this->trash = trash;
	Parser temp;
	this->location=temp.getCoordFromID(id);
}

Ecoponto::~Ecoponto() {
	// TODO Auto-generated destructor stub
}

int Ecoponto::getTrash() const {
	return trash;
}

void Ecoponto::setTrash(int trash) {
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

int totalTrash(list<Ecoponto> ecopontos){
	int res = 0;
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
		res+=(*it).getTrash();
	return res;
}

vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord initial){
	vector<Coord> res = {};
	res.push_back(initial);
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
			res.push_back(it->getLocation());
	return res;
}
