/*
 * Truck.cpp
 *
 *  Created on: 21/04/2016
 *      Author: Filipe
 */

#include "Truck.h"

Truck::Truck() {
	// TODO Auto-generated constructor stub

}

Truck::~Truck() {
	// TODO Auto-generated destructor stub
}

int Truck::getCapacity() const {
	return capacity;
}

void Truck::setCapacity(int capacity) {
	this->capacity = capacity;
}

const string& Truck::getColor() const {
	return color;
}

void Truck::setColor(const string& color) {
	this->color = color;
}

const string& Truck::getName() const {
	return name;
}

Truck::Truck(string name, int capacity, string color) {
	this->name = name;
	this->capacity = capacity;
	this->color = color;
}

bool Truck::operator <(const Truck& other) {
	return capacity < other.capacity;
}

bool Truck::operator ==(const Truck& other) {
	return (
		name == other.name &&
		capacity == other.capacity &&
		color == other.color
	);
}

void Truck::setName(const string& name) {
	this->name = name;
}

Truck popBestTruck(list<Truck> trucks, int totalTrash){
	int bestCapacity = 0;
	Truck best;
	for (list<Truck>::iterator it=trucks.begin(); bestCapacity < totalTrash && it != trucks.end(); ++it){
		 best = (*it);
		 bestCapacity = (*it).getCapacity();
	}
	trucks.remove(best);
	return best;
}
