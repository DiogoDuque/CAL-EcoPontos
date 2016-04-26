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

/**
 * This class cointains all the functions responsible for manipulating GraphViewer.
 * Also obtains Graph from files and GraphViewer from Graph
 *
 */

class Parser {
public:
	/**
	 * Construtor
	 */
	Parser();

	/**
	 * Destructor
	 */
	virtual ~Parser();

	/**
	 * Reads the files 'Nodes.txt', 'Roads.txt' and 'Connections.txt'.
	 *
	 * @return graph with information obtained from the files.
	 */
	Graph<Coord>* txtToGraph();

	/**
	 *  Represents the graph given as a parameter through GraphViewer.
	 *
	 *  @param gr - graph to represent through GraphViewer
	 */
	void graphToGraphViewer(Graph<Coord>* gr);

	/**
	 * Converts a long long obtained from the file 'Nodes.txt' to corresponding int used on the graph
	 *
	 * @param nr - long long id
	 */
	int getNodeID(long long nr);

	/**
	 * Gets the location of the node with the id given as a parameter
	 *
	 * @param nr - id of the node
	 * @return location of the node with id equal to nr
	 */
	Coord getCoordFromID(int nr);

	/**
	 * Changes GraphViewer so that the route of the truck is shown on GraphViewer with the color of truck
	 *
	 * @param path - vector of nodes (Coord) that are part of the route of the truck
	 * @param truck - truck that will collect the garbage of the ecopontos
	 */
	void setGraphViewerPath(vector<Coord> path, Truck truck);

	/**
	 * Represents the ecopontos on GraphViewer
	 *
	 * @param ecopontos - list of all ecopontos
	 */
	void setGraphViewerEcopontos(list<Ecoponto> ecopontos);
private:
	/**
	 * Returns current nextID and increments it
	 * @return current nextID
	 */
	int getNextID(); 										// private because is only used inside the class

	static int nextID;										// int node id
	static vector<Coord> bounds;							// stores the coordinates corresponding to minimum and the maximum of the map
	static unordered_map <long long,int> nodeID;			// nodeID[id] gives the int node id corresponding to the long long id
	static unordered_map<int, Coord> coords;				// coords[id] gives the location of the node corresponding to id
	unordered_map<int,unordered_map<int,int>> edgeID; 		// edgeID[id_source][id_destination] gives the id of the edge (which is an int)
	unordered_map<int,unordered_map<int,string>> roads;		// roads[id_source][id_destination] gives the name of the road
	GraphViewer* gv;										// shows the map
};

#endif /* PARSER_H_ */
