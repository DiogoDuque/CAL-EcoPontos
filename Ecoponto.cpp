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

Ecoponto::Ecoponto(unsigned int thrash) {
	this->thrash = thrash;
}

Ecoponto::~Ecoponto() {
	// TODO Auto-generated destructor stub
}

unsigned int Ecoponto::getThrash() const {
	return thrash;
}

void Ecoponto::setThrash(unsigned int thrash) {
	this->thrash = thrash;
}

bool Ecoponto::operator<(const Ecoponto& other){
	return (this->thrash < other.thrash);
}

list<Ecoponto> fillMax(list<Ecoponto> ecopontos, Truck truck){
	list<Ecoponto> res = {};
	unsigned int currentCapacity = truck.getCapacity();
	for (list<Ecoponto>::reverse_iterator it = ecopontos.rbegin(); it != ecopontos.rend() && currentCapacity > 0;){
		if((*it).getThrash() <= currentCapacity){
			currentCapacity -= (*it).getThrash();
			res.push_back(*it);
			++it;
			it= list<Ecoponto>::reverse_iterator(ecopontos.erase(it.base()));
		}
		else
			++it;
	}
	return res;
}
