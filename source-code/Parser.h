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
#include <limits.h>
#include <algorithm>

#include "SourceAux.h"
#include "Graph.h"
#include "jung/graphviewer.h"
#include "Utilities.h"
#include "Ecoponto.h"
#include "StringSearch.h"

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
	Graph<Coord>* txtToGraph(bool show_names, bool all);

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
	int getNodeID(long long nr) const;

	/**
	 * Gets the location of the node with the id given as a parameter
	 *
	 * @param nr - id of the node
	 * @return location of the node with id equal to nr
	 */
	Coord getCoordFromID(int nr) const;

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

	/**
	 * Changes the label of all the ecopontos on the list on GraphViewer.
	 * This is necessary because sometimes different trucks may pass on the same ecoponto (but ONLY one truck collects its trash)
	 *
	 * @param ecopontos - list of ecopontos that will have their trash collected by the same truck
	 * @param color - color of the truck that will collect the trash
	 */
	void setGraphViewerEcoLabel(list<Ecoponto> ecopontos, string color);

	/**
	 * Shows the blocked roads on GraphViewer
	 *
	 * @param blockedRoads - vector of the blocked roads
	 */
	void setGraphViewerBlockedRoads(vector<Road> blockedRoads);

	/**
	 * Prints two questions and initializes the graph representing the map
	 *
	 * @return graph that represents a map
	 */
	Graph<Coord>* initializeGraph();

	/**
	 * Returns the nodes that represent the geometry of a road
	 *
	 * @param name_road - name of the road
	 * @return vector with the nodes' ids of the given road
	 */
	vector<int> getNodesRoad(string name_road);

	/**
	 * Returns all roads' names of the graph
	 *
	 * @return vector with all the roads' names
	 */
	vector<string> getRoadNames();

	/**
	 * Returns the number of ecopontos of a given road
	 *
	 * @param name_road - name of the road
	 * @param ecopontos - list of all ecopontos
	 * @return - number of ecopontos on name_road
	 */
	int getNumEcopontos(string name_road, list<Ecoponto> ecopontos);
private:
	/**
	 * Returns current nextID and increments it
	 * @return current nextID
	 */
	int getNextID(); 										// private because is only used inside the class

	int nextID;												// int node id
	vector<Coord> bounds;									// stores the coordinates corresponding to minimum and the maximum of the map
	static unordered_map <long long,int> nodeID;			// nodeID[id] gives the int node id corresponding to the long long id
	static unordered_map<int, Coord> coords;				// coords[id] gives the location of the node corresponding to id
	unordered_map<int,unordered_map<int,int>> edgeID; 		// edgeID[id_source][id_destination] gives the id of the edge (necessary because of GraphViewer)
	unordered_map<int,unordered_map<int,string>> roads;		// roads[id_source][id_destination] gives the name of the road
	GraphViewer* gv;										// shows the map

	unordered_map<string,vector<Road>> road_edges;			// associates a road with all its nodes
};

#endif /* PARSER_H_ */
