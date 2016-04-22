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

using namespace std;

class Parser {
public:
	Parser();
	virtual ~Parser();
	Graph<Coord>* txtToGraph();
	void graphToGraphViewer(Graph<Coord>* gr);
	int convertDoubleToIntID(double nr);
private:
	int getNextID(); //é private pq so é usada dentro da propria classe
	vector<Coord> bounds;
	unordered_map <double,int> doubleToInt;
	int nextID;
};

#endif /* PARSER_H_ */
