/*
 * Parser.h
 *
 *  Created on: 22/04/2016
 *      Author: Diogo
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "jung/graphviewer.h"
#include "Utilities.h"
#include "Ecoponto.h"

class Ecoponto;

using namespace std;

class Parser {
public:
	Parser();
	virtual ~Parser();
	Graph<Coord>* txtToGraph();
	void graphToGraphViewer(Graph<Coord>* gr);
	int convertDoubleToIntID(double nr);
	Coord getCoordFromIntID(int nr);
	void setGraphViewerPath(vector<Coord> path, Truck truck);
private:
	int getNextID(); //é private pq so é usada dentro da propria classe
	static int nextID;
	static vector<Coord> bounds;
	static unordered_map <double,int> doubleToInt;
	static unordered_map<int, Coord> coords;
	unordered_map<int,unordered_map<int,int>> edgesIDs; //edges[source][destination]=idAresta
	GraphViewer* gv;
};

#endif /* PARSER_H_ */
