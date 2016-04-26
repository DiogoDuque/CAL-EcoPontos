/*
 * Truck.h
 *
 *  Created on: 21/04/2016
 *      Author: Filipe
 */

#ifndef TRUCK_H_
#define TRUCK_H_

#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

/**
 *
 * This class stores an truck object that represents a truck.
 * An truck object is characterized by its name, capacity and color.
 *
 */
class Truck {
private:
	string name;
	int capacity;
	string color;

public:
	/**
	 * Default construtor
	 */
	Truck();

	/**
	 * Construtor
	 */
	Truck(string name, int capacity,string color);

	/**
	 * Destructor
	 */
	virtual ~Truck();

	int getCapacity() const;
	void setCapacity(int capacity);

	const string& getColor() const;
	void setColor(const string& color);

	const string& getName() const ;
	void setName(const string& name);

	/**
	 * Compares the contents of the trucks: if one truck has more capacity than the other then it is 'bigger'
	 *
	 * @param other - truck object that will be compared with this object
	 * @return true if other has less capacity than this object, false if otherwise
	 */
	bool operator<(const Truck& other);

	/**
	 * Compares the contents of the trucks: one truck is equal to other truck if all its data members are equal
	 *
	 * @param other - truck object that will be compared with this object
	 * @return true if all data members are equal, false if otherwise
	 */
	bool operator==(const Truck& other);
};

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
Truck popBestTruck(list<Truck> &trucks, int totalTrash);

/**
 * Reads file 'Trucks.txt' and returns a list with the trucks on the file
 *
 * @return list with the trucks on the file 'Trucks.txt'
 */
list<Truck> getTrucks();


#endif /* TRUCK_H_ */
