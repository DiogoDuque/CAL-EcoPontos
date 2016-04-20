#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Graph.h"
#include "jung/graphviewer.h"

class Coord {
public:
	Coord() {
	}
	;
	Coord(double latitude, double longitude) {
		lat = latitude;
		lon = longitude;
	}
	;
	double getLat() const {
		return lat;
	}
	;
	double getLon() const {
		return lon;
	}
	;
	bool operator==(const Coord c) {
		return lat == c.getLat() && lon == c.getLon();
	}
	;
	double calcWeight(Coord c) {
		return sqrt(pow((lon + c.getLon()), 2) + pow((lat + c.getLat()), 2));
	}
	;
private:
	double lat;
	double lon;
};

Graph<Coord> parseTxtToGraph() {
	cout << "Started parser <txt> <Graph>\n";
	Graph<Coord> gr;
	unordered_map<int, Coord> coords;
	fstream file, file2;

	//Nodes.txt
	file.open("Nodes.txt");
	if (!file.is_open())
		throw "Could not open file 'Nodes.txt'!";
	cout << "Reading 'Nodes.txt'\n";
	while (!file.eof()) {
		bool eofFound=false; //fica true se a ultima linha do ficheiro existir, mas nao tiver carateres
		string str[5];
		double coordX, coordY;
		int id;
		//ler da stream
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
		//transformar para int
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> coordX;
		(stringstream) str[2] >> coordY;
		//adicionar ao grafo
		Coord coord(coordX, coordY);
		coords[id] = coord;
		gr.addVertex(coord);
	}
	file.close();
	cout << "Finished reading 'Nodes.txt'\n";

	//Roads.txt e Connections.txt
	file.open("Roads.txt");
	if (!file.is_open())
		throw "Could not open file 'Roads.txt'!";
	file2.open("Connections.txt");
	if (!file.is_open())
		throw "Could not open file 'Connections.txt'!";

	cout << "Reading 'Roads.txt' and 'Connections.txt'\n";
	int oldID = -1; //estas 2 vars sao para controlo da sincronizacao dos 2 ficheiros
	string twoway;
	while (!file2.eof()) {
		string str[3];
		double node1, node2;
		int id;
		bool eofFound=false;

		//ler as connections
		for (int i = 0; i < 2; i++)
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
		getline(file2, str[2]);
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> node1;
		(stringstream) str[2] >> node2;

		if (id != oldID) //atualizar oneway e id caso seja necessario
		{
			oldID = id;
			for (int i = 0; i < 2; i++)
			{
				getline(file, twoway, ';');
				if(file.eof())
				{
					if(str[0]=="")
					{
						eofFound=true;
						break;
					}
					else throw "Reached end of file 'Roads.txt' too soon! Is file complete?";
				}
			}
			if(eofFound)
				break;
			getline(file, twoway);
		}//ENDIF

		//adicionar ao grafo
		int weight = coords[node1].calcWeight(coords[node2]);
		if (twoway == "yes") {
			gr.addEdge(coords[node1], coords[node2], weight);
			gr.addEdge(coords[node2], coords[node1], weight);
		} else {
			gr.addEdge(coords[node1], coords[node2], weight);
		}

	}
	file.close();
	file2.close();
	cout << "Finished reading 'Roads.txt' and 'Connections.txt'\n";
	cout << "Finished parser <txt> <Graph>\n\n\n";
	return gr;
}

void parseGraphToGraphViewer(GraphViewer* gv, Graph<Coord> gr) {
	cout << "Started parser <Graph> to <GraphViewer>\n";
	gv->createWindow(600, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("red");

	fstream file, file2;
	unordered_map <int, Coord> coords;

	//Nodes.txt
	file.open("Nodes.txt");
	if (!file.is_open())
		throw "Could not open file 'Nodes.txt'!";
	cout << "Reading 'Nodes.txt'\n";
	while (!file.eof()) {
		string str[5];
		double coordX, coordY;
		int id;
		bool eofFound=false;
		//ler da stream
		for (int i = 0; i < 4; i++)
		{
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
		//transformar para int
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> coordX;
		(stringstream) str[2] >> coordY;
		//adicionar ao grafo
		coords[id]=Coord(coordX,coordY);
		gv->addNode(id,coordX*1000000,coordY*1000000);

	}
	file.close();
	gv->rearrange();
	cout << "Finished reading 'Nodes.txt'\n";

	//Roads.txt e Connections.txt
	file.open("Roads.txt");
	if (!file.is_open())
		throw "Could not open file 'Roads.txt'!";
	file2.open("Connections.txt");
	if (!file.is_open())
		throw "Could not open file 'Connections.txt'!";

	cout << "Reading 'Roads.txt' and 'Connections.txt'\n";
	int oldID = -1; //estas 2 vars sao para controlo da sincronizacao dos 2 ficheiros
	string roadInfo[3];
	while (!file2.eof()) {
		string str[3];
		double node1, node2;
		int id;
		bool eofFound=false;

		//ler as connections
		for (int i = 0; i < 2; i++) {
			getline(file2, str[i], ';');
			if (file2.eof())
				if (file.eof())
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
		getline(file2, str[2]);
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> node1;
		(stringstream) str[2] >> node2;

		if (id != oldID) //atualizar oneway e id caso seja necessario
		{
			oldID = id;
			for (int i = 0; i < 2; i++) {
				getline(file, roadInfo[i], ';');
				if (file.eof())
				{
					if(str[0]=="")
					{
						eofFound=true;
						break;
					}
					else throw "Reached end of file 'Roads.txt' too soon! Is file complete?";
				}
			}
			if(eofFound)
				break;
			getline(file, roadInfo[2]);
		}
		int weight = coords[node1].calcWeight(coords[node2])*pow(10,12);
		//adicionar ao grafo
		if (roadInfo[2] == "yes") {
			gv->addEdge(id,node1,node2,EdgeType::DIRECTED);
			gv->setEdgeLabel(id,roadInfo[1]);
			gv->setEdgeWeight(id,weight);
		} else {
			gv->addEdge(id,node1,node2,EdgeType::UNDIRECTED);
			gv->setEdgeLabel(id,roadInfo[1]);
			gv->setEdgeWeight(id,weight);
		}

	}
	file.close();
	file2.close();
	cout << "Finished reading 'Roads.txt' and 'Connections.txt'\n";
	cout << "Finished parser <Graph> to <GraphViewer>\n\n\n";
}

#endif
