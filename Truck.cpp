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

/**
 * Receives a list of trucks and the amount of trash to collect.
 * POPS the best truck for the job.
 *
 * Example: (Truck, TruckCapacity)
 * trucks: (A,100), (B,150), (C,200)
 *
 * amount of trash to collect:
 * 45 - pops A
 * 60 - pops B
 * 99 - pops B
 * 100- pops B
 * 101 - Pops C
 * 160 - Pops C
 *
 * @param trucks - list of trucks
 * @param totalTrash - amount of trash to collect
 * @return most suitable truck to collect the trash
 */
Truck popBestTruck(list<Truck> &trucks, int totalTrash){
	int bestCapacity = 0;
	Truck best;
	for (list<Truck>::iterator it=trucks.begin(); bestCapacity < totalTrash && it != trucks.end(); ++it){
		best = (*it);
		bestCapacity = (*it).getCapacity();
	}
	trucks.remove(best);
	return best;
}

/**
 * Reads file 'Trucks.txt' and returns a list with the trucks on the file
 *
 * @return list with the trucks on the file 'Trucks.txt'
 */
list<Truck> getTrucks()
																										{
	list<Truck> trucks;
	fstream file;
	file.open("Trucks.txt");
	if(!file.is_open())
		throw "Could not open file 'Trucks.txt'!";
	while(!file.eof())
	{
		string name, color;
		int capacity;
		string str[3];
		for(unsigned int i=0; i<2; i++)
		{
			getline(file,str[i],';');
			if(file.eof())
			{
				throw "Reached end of file 'Trucks.txt' too soon! Is file complete?";
			}
		}
		getline(file,str[2]);
		(stringstream) str[0] >> name;
		(stringstream) str[1] >> capacity;
		(stringstream) str[2] >> color;

		if (capacity < 100)
			throw "Not enough capacity! The capacity must be above 100!";

		trucks.push_back(Truck(name,capacity,color));
	}
	file.close();
	trucks.sort();				// sorts trucks by capacity
	return trucks;
}
