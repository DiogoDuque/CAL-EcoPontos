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

Truck popBestTruck(list<Truck> trucks, int totalThrash);

list<Truck> getTrucks();


#endif /* TRUCK_H_ */
