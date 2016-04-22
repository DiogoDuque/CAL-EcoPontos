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
	//this->location=Coord(-1,0,0);//TODO DUQUE!!! Tenho de transformar id em Coord
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

/*Coord Ecoponto::getLocation() const {
	return location;
}

void Ecoponto::setLocation(Coord location) {
	this->location = location;
}*/

bool Ecoponto::operator<(const Ecoponto& other){
	return (this->trash < other.trash);
}

list<Ecoponto> fillMax(list<Ecoponto> ecopontos, Truck truck){
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
