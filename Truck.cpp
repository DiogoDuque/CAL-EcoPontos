/*
 * Truck.cpp
 *
 *  Created on: 21/04/2016
 *      Author: Filipe
 */

#include "Truck.h"

/**
 * Default construtor
 */
Truck::Truck() {
	capacity = 0;
}

/**
 * Construtor.
 * @param name - Truck's name.
 * @param capacity - Truck's maximum capacity.
 * @param color - color of this truck's path in GraphViewer.
 */
Truck::Truck(string name, int capacity, string color) {
	this->name = name;
	this->capacity = capacity;
	this->color = color;
}

/**
 * Destructor
 */
Truck::~Truck() {
	// TODO Auto-generated destructor stub
}

/**
 * @return Truck's capacity.
 */
int Truck::getCapacity() const {
	return capacity;
}

/**
 * @param capacity - Truck's new capacity.
 */
void Truck::setCapacity(int capacity) {
	this->capacity = capacity;
}

/**
 * @return Truck's path color in GraphViewer.
 */
const string& Truck::getColor() const {
	return color;
}

/**
 * @param color - Truck's new path color for GraphViewer.
 */
void Truck::setColor(const string& color) {
	this->color = color;
}

/**
 * @return Truck's name.
 */
const string& Truck::getName() const {
	return name;
}

/**
 * @param name - Truck's new name.
 */
void Truck::setName(const string& name) {
	this->name = name;
}

/**
 * Compares the contents of the trucks: if one truck has more capacity than the other then it is 'bigger'
 *
 * @param other - truck object that will be compared with this object
 * @return true if other has less capacity than this object, false otherwise
 */
bool Truck::operator <(const Truck& other) {
	return capacity < other.capacity;
}

/**
 * Compares the contents of the trucks: one truck is equal to other truck if all its data members are equal
 *
 * @param other - truck object that will be compared with this object
 * @return true if all data members are equal, false otherwise
 */
bool Truck::operator ==(const Truck& other) {
	return (
			name == other.name &&
			capacity == other.capacity &&
			color == other.color
	);
}
