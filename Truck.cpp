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

/*
 * Receives a list of trucks and the amount of thrash to collect.
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
 */
Truck popBestTruck(list<Truck> &trucks, int totalTgrash){
	int bestCapacity = 0;
	Truck best;
	for (list<Truck>::iterator it=trucks.begin(); bestCapacity < totalTgrash && it != trucks.end(); ++it){
		best = (*it);
		bestCapacity = (*it).getCapacity();
	}
	trucks.remove(best);
	return best;
}

/**
 * Le o ficheiro 'Trucks.txt' e retorna uma lista com os Trucks lidos do ficheiro.
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
		for(unsigned i=0; i<2; i++)
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
		trucks.push_back(Truck(name,capacity,color));
	}
	file.close();
	trucks.sort();
	return trucks;
}
