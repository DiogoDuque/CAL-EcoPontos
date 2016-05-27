/*
 * Ecoponto.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Filipe
 */

#include "Ecoponto.h"
#include "Parser.h"

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
