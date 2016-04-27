/*
 * Parser.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Diogo
 */

#include "Parser.h"

unordered_map <long long,int> Parser::nodeID;
unordered_map<int, Coord> Parser::coords;

Parser::Parser() {
	nextID=0;
	gv=NULL;
}

Parser::~Parser() {}

Graph<Coord>* Parser::txtToGraph() {
	cout << "Started parser <txt> <Graph>" << endl;
	double xMin=1000, xMax=-1000, yMin=1000, yMax=-1000;
	Graph<Coord>* gr = new Graph<Coord>;
	fstream file, file2;

	// Nodes.txt
	file.open("Nodes.txt");
	if (!file.is_open())
		throw "Could not open file 'Nodes.txt'!";

	cout << "Reading 'Nodes.txt'" << endl;
	while (!file.eof()) {
		bool eofFound=false;		// true if last line of the file is empty
		string str[5];
		double coordX, coordY;		// coordinates of the nodes
		long long id;				// int would not be enough to store the numbers on the file since they are too big

		// ler da stream
		for (int i = 0; i < 4; i++) {
			getline(file, str[i], ';');
			if (file.eof())
			{
				if(str[0]=="")
				{
					eofFound=true;
					break;
				}
				else throw "Reached end of file 'Nodes.txt' too soon! Is file complete?";
			}
		}

		if(eofFound)
			break;
		getline(file, str[4]);

		// extract numbers from the strings obtained from 'Nodes.txt'
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> coordX;
		(stringstream) str[2] >> coordY;

		// obtain new int ID (instead of long long)
		nodeID[id]=getNextID();

		// add node to the graph
		Coord coord(nextID-1,coordX, coordY);
		coords[nextID-1] = coord;
		gr->addVertex(coord);

		// update maxs/mins
		if(coordX>xMax)
			xMax=coordX;
		if(coordY>yMax)
			yMax=coordY;
		if(coordX<xMin)
			xMin=coordX;
		if(coordY<yMin)
			yMin=coordY;
	}
	file.close();
	cout << "Finished reading 'Nodes.txt'" << endl;

	// Roads.txt and Connections.txt
	file.open("Roads.txt");
	if (!file.is_open())
		throw "Could not open file 'Roads.txt'!";
	file2.open("Connections.txt");
	if (!file.is_open())
		throw "Could not open file 'Connections.txt'!";

	cout << "Reading 'Roads.txt' and 'Connections.txt'" << endl;

	int oldID = -1; // controls files' synchronization (checks if the files are being read correctly)
	string twoway;
	while (!file2.eof()) {
		string str[3];
		string road[2];
		long long node1, node2;
		int id;
		bool eofFound=false;

		// read connections
		for (int i = 0; i < 3; i++)
		{
			getline(file2, str[i], ';');
			if (file2.eof())
			{
				if(str[0]=="")
				{
					eofFound=true;
					break;
				}
				else throw "Reached end of file 'Connections.txt' too soon! Is file complete?";
			}
		}
		if(eofFound)
			break;
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> node1;
		(stringstream) str[2] >> node2;
		getline(file2, str[0]);

		if (id != oldID) // update oneway and id if necessary
		{
			oldID = id;
			for (int i = 0; i < 2; i++)
			{
				getline(file, road[i], ';');
				if(file.eof())
					throw "Reached end of file 'Roads.txt' too soon! Is file complete?";
			}
			getline(file, twoway);
		}//ENDIF

		// add to graph
		int weight = coords[nodeID[node1]].calcWeight(coords[nodeID[node2]]);
		if (twoway == "True") {
			gr->addEdge(coords[nodeID[node1]], coords[nodeID[node2]], weight);
			roads[nodeID[node1]][nodeID[node2]] = road[1];				// name of the road

			gr->addEdge(coords[nodeID[node2]], coords[nodeID[node1]], weight);
			roads[nodeID[node2]][nodeID[node1]] = " ";					// same name doesn't show two times
		} else {
			gr->addEdge(coords[nodeID[node1]], coords[nodeID[node2]], weight);
			roads[nodeID[node1]][nodeID[node2]] = road[1];
		}
	}
	file.close();
	file2.close();
	cout << "Finished reading 'Roads.txt' and 'Connections.txt'" << endl;
	cout << "Finished parser <txt> <Graph>" << endl << endl;
	bounds.push_back(Coord(-1,xMax,yMax));
	bounds.push_back(Coord(-1,xMin,yMin));
	return gr;
}

void Parser::graphToGraphViewer(Graph<Coord>* gr) {
	cout << "Started parser <Graph> to <GraphViewer>" << endl;
	Coord min = bounds[1];
	Coord max = bounds[0];
	double xMin=min.getLat(), yMin=min.getLon(), xMax=max.getLat(), yMax=max.getLon();

	gv = new GraphViewer(2000,800,false);
	gv->createWindow(2000, 800);
	gv->defineEdgeColor("black");
	gv->defineVertexColor("black");
	gv->defineVertexSize(10);
	gv->defineEdgeCurved(false);

	cout << "Adding nodes..." << endl;
	vector<Vertex<Coord> *> vertices = gr->getVertexSet();
	for(unsigned i=0; i<vertices.size(); i++)
	{
		Coord temp(vertices[i]->getInfo().getID(),
					(vertices[i]->getInfo().getLat()-xMin)*10000/(xMax-xMin)-5000,
					(vertices[i]->getInfo().getLon()-yMin)*10000/(yMax-yMin)-5000);
		gv->addNode(temp.getID(),temp.getLat(),temp.getLon());
		//gv->setVertexSize(temp.getID(), 5);
	}
	gv->rearrange();

	cout << "Adding edges..." << endl;
	int id=0;
	for(unsigned i=0; i<vertices.size(); i++)
	{
		vector<Edge<Coord> > edges = vertices[i]->getAdj();
		for(unsigned j=0; j<edges.size(); j++)
		{
			int source = vertices[i]->getInfo().getID();
			int destination = edges[j].getDest()->getInfo().getID();
			edgeID[source][destination]=id;							// assigns int id
			gv->addEdge(id,source,destination,EdgeType::DIRECTED);
			id++;
		}
	}
	gv->rearrange();

	for(unsigned i=0; i<vertices.size(); i++)
	{
		gv->setVertexSize(vertices[i]->getInfo().getID(), 1);

		vector<Edge<Coord> > edges = vertices[i]->getAdj();
		for(unsigned j=0; j<edges.size(); j++)
		{
			int source = vertices[i]->getInfo().getID();
			int destination = edges[j].getDest()->getInfo().getID();
			gv->setEdgeLabel(edgeID[source][destination], roads[source][destination]);
		}
	}

	gv->rearrange();

	cout << "Finished parser <Graph> to <GraphViewer>" << endl;
}

int Parser::getNodeID(long long nr) const
{
	return nodeID[nr];
}

Coord Parser::getCoordFromID(int nr) const
{
	return coords[nr];
}

void Parser::setGraphViewerPath(vector<Coord> path, Truck truck)
{
	if(gv==NULL)
		throw "GraphViewer object not defined!";

	int initialId = path[0].getID();
	gv->setVertexColor(initialId, "green");

	for(unsigned i=1; i<path.size(); i++)
	{
		int source=path[i-1].getID();
		int destination=path[i].getID();
		int id=edgeID[source][destination];
		if(truck.getColor()=="black")
			throw "Truck color cannot be the same as the GraphViewer standard color!";
		gv->setEdgeColor(id,truck.getColor());
		gv->setEdgeThickness(id,10);
	}

	gv->rearrange();
}

int Parser::getNextID()
{
	int ret = nextID;
	nextID++;
	return ret;
}

void Parser::setGraphViewerEcopontos(list<Ecoponto> ecopontos) {
	for(list<Ecoponto>::const_iterator it=ecopontos.begin(); it != ecopontos.end(); ++it) {
		gv->setVertexColor((*it).getLocation().getID(), "red");
	}
}

void Parser::setGraphViewerEcoLabel(list<Ecoponto> ecopontos, string color) {
	for(list<Ecoponto>::const_iterator it=ecopontos.begin(); it != ecopontos.end(); ++it) {
		string label;
		string id;
		stringstream ss;

		ss << (*it).getLocation().getID();
		id = ss.str();

		label = id + " " + color;		// shows id of the ecoponto and the color of the truck that colected its trash

		gv->setVertexLabel((*it).getLocation().getID(), label);
	}
}

void Parser::setGraphViewerBlockedRoads(vector<Road> blockedRoads){
	for(unsigned int i = 0; i < blockedRoads.size(); i++){
		int source=blockedRoads[i].source;
		int destination=blockedRoads[i].dest;
		int id=edgeID[source][destination];

		gv->setEdgeLabel(id, "BLOCKED ROAD");
		gv->setEdgeThickness(id, 15);
	}
}

vector<Road> getBlockedRoads(){
	vector<Road> blockedRoads;
	fstream file;
	file.open("BlockedRoads.txt");
	if(!file.is_open())
		throw "Could not open file 'BlockedRoads.txt'!";

	while(!file.eof())
	{
		int id_source, id_dest;
		string str[2];
		getline(file,str[0],';');
		if(file.eof())
		{
			vector<Road> tmp;
			cout << "Warning: file 'BlockedRoads.txt' is empty or incomplete" << endl;
			return tmp;
		}
		getline(file,str[1]);
		(stringstream) str[0] >> id_source;
		(stringstream) str[1] >> id_dest;

		Road road;
		road.source = id_source;
		road.dest = id_dest;

		blockedRoads.push_back(road);
	}
	file.close();

	return blockedRoads;
}
