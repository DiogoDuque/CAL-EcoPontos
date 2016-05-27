/*
 * Map.h
 *
 *  Created on: 27/05/2016
 *      Author: Claudia Marinho
 */

#ifndef MAP_H_
#define MAP_H_

#include <list>
#include "Truck.h"
#include "Graph.h"
#include "Ecoponto.h"

using namespace std;

string askUser(string question);

/**
 * Reads file 'Trucks.txt' and returns a list with the trucks on the file
 *
 * @return list with the trucks on the file 'Trucks.txt'
 */
list<Truck> getTrucks();

/**
 * Reads from file 'Ecopontos.txt' and returns a list with the ecopontos on the file
 *
 * @return list with the ecopontos on 'Ecopontos.txt'
 */
list<Ecoponto> getEcopontos();

/**
 * Reads the file 'BlockedRoads.txt' and returns a vector with the blocked roads on the file
 *
 * @return vector with the blocked roads
 */
vector<Road> getBlockedRoads();

int initialPoint();

list<Ecoponto> addEcoponto(list<Ecoponto> eco);

void ecopontosLoad();

list<Ecoponto> CheckEcopontosToUnload(list<Ecoponto> eco, int min_load);

bool connectivityTest(list<Ecoponto> eco, Graph<Coord> *gr, Coord initial);

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
 * Receives the list of ecopontos and returns the sum of the trash of every Ecoponto on the list
 *
 * @param ecopontos - list of ecopontos
 * @return sum of the trash of every ecoponto on the list
 */
int totalTrash(list<Ecoponto> ecopontos);

/**
 * Receives the list of ecopontos and a truck (should be selected by poopBestTruck(trucks,[sum of trash in the ecopontos's list]))
 * Returns the best list of ecopontos that tries to fill the truck to the maximum.
 *
 * Example: (Ecoponto, amount)
 * ecopontos (A, 10), (B, 30), (C,50) , (D, 70)
 * Truck -> capacity = 100
 *
 * Returns (B,D)
 *
 * IMPORTANT: pops the result so ecopontos becomes just A,C
 *
 * @param ecopontos - list of all of the ecopontos
 * @param truck - selected by popBestTruck
 * @return best list of ecopontos that tries to fill the truck to the maximum
 * @return list with the ecopontos on 'Ecopontos.txt'
 */
list<Ecoponto> fillMax(list<Ecoponto> &ecopontos, Truck truck);

/**
 * Receives the list of ecopontos that will have its trash collected by a truck and the Coord of the initial point
 * Returns a vector with the Coord (location and id) of the central (initial) and of the ecopontos on the list
 *
 * @param ecopontos - list of ecopontos
 * @param initial - location and id (Coord) of the initial point (central)
 * @return vector with the Coord (location and id) of the central (initial) and of the ecopontos on the list
 */
vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord initial);

#endif /* MAP_H_ */
