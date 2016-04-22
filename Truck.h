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

class Truck {
private:
	string name;
	int capacity;
	string color;

public:
	Truck();
	Truck(string name, int capacity,string color);
	virtual ~Truck();

	bool operator<(const Truck& other);
	bool operator==(const Truck& other);

	int getCapacity() const;
	void setCapacity(int capacity);
	const string& getColor() const;
	void setColor(const string& color);
	const string& getName() const ;
	void setName(const string& name);

};
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
Truck popBestTruck(list<Truck> trucks, int totalThrash);

list<Truck> getTrucks();


#endif /* TRUCK_H_ */
