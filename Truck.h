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
 * This class stores an truck object that represents a truck.
 * An truck object is characterized by its name, capacity and color.
 */
class Truck {
private:
	string name;
	int capacity;
	string color;

public:

	Truck();

	Truck(string name, int capacity, string color);

	virtual ~Truck();

	int getCapacity() const;
	void setCapacity(int capacity);

	const string& getColor() const;
	void setColor(const string& color);

	const string& getName() const ;
	void setName(const string& name);

	bool operator<(const Truck& other);

	bool operator==(const Truck& other);
};

#endif /* TRUCK_H_ */
