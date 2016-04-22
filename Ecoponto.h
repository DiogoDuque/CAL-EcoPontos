/*
 * Ecoponto.h
 *
 *  Created on: 22/04/2016
 *      Author: Filipe
 */

#ifndef ECOPONTO_H_
#define ECOPONTO_H_

#include <list>
#include "Truck.h"

using namespace std;

class Ecoponto {
private:
	unsigned int thrash;
public:
	Ecoponto();
	Ecoponto(unsigned int thrash);
	virtual ~Ecoponto();

	unsigned int getThrash() const;
	void setThrash(unsigned int thrash);

	bool operator<(const Ecoponto& other);
};

list<Ecoponto> fillMax(list<Ecoponto>, Truck);

#endif /* ECOPONTO_H_ */
