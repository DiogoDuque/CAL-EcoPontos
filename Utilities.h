#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Graph.h"
#include "jung/graphviewer.h"

class Coord
{
public:
	Coord(double latitude, double longitude) {
		lat=latitude;
		lon=longitude;
	};
	double getLat() const {return lat;};
	double getLon() const {return lon;};
	bool operator==(const Coord c) {return lat==c.getLat() && lon==c.getLon();};
	double calcWeight(Coord c) {return sqrt( pow((lon+c.getLon()),2) + pow((lat+c.getLat()),2));};
private:
	double lat;
	double lon;
};

Graph<Coord> parseTxtToGraph()
{
	Graph<Coord> gr;
	unordered_map <int, Coord> coords;
	fstream file, file2;

	//Nodes.txt
	file.open("Nodes.txt");
	if(!file.is_open())
		throw "Could not open file 'Nodes.txt'!";
	while(!file.eof())
	{
		string str[5];
		double coordX,coordY;
		int id;
		//ler da stream
		for(int i=0; i<4; i++)
		{
			getline(file,str[i],';');
			if(file.eof())
				throw "Reached end of file 'Nodes.txt' too soon! Is file complete?";
		}
		getline(file,str[4]);
		//transformar para int
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> coordX;
		(stringstream) str[2] >> coordY;
		//adicionar ao grafo
		Coord coord(coordX,coordY);
		coords[id]=coord;
		gr.addVertex(coord);
	}
	file.close();

	//Roads.txt e Connections.txt
	file.open("Roads.txt");
	if(!file.is_open())
		throw "Could not open file 'Roads.txt'!";
	file2.open("Connections.txt");
	if(!file.is_open())
		throw "Could not open file 'Connections.txt'!";

	int oldID = -1;
	string twoway;
	while(!file2.eof())
	{
		string str[3];
		double node1, node2;
		int id;
		//ler as connections
		for(int i=0; i<2; i++)
		{
			getline(file2,str[i],';');
			if(file2.eof())
				throw "Reached end of file 'Connections.txt' too soon! Is file complete?";
		}
		getline(file2,str[2]);
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> node1;
		(stringstream) str[2] >> node2;
			if(id!=oldID) //atualizar oneway e id caso seja necessario
		{
			oldID=id;
			for(int i=0; i<2; i++)
			{
				getline(file,twoway,';');
				if(file.eof())
					throw "Reached end of file 'Roads.txt' too soon! Is file complete?";
			}
			getline(file,twoway);
		}
			int weight = coords[node1].calcWeight(coords[node2]);
		if(twoway=="yes")
		{
			gr.addEdge(coords[node1],coords[node2],weight);
			gr.addEdge(coords[node2],coords[node1],weight);
		} else {
			gr.addEdge(coords[node1],coords[node2],weight);
		}

		//adicionar ao grafo
	}
	file.close();
	file2.close();
	return gr;
}

GraphViewer parseGraphToGraphViewer(Graph<Coord> gr)
{
	GraphViewer gv(600,600,false);
	gv.createWindow(600, 600);

	//adicionar vertices
	vector<Vertex<Coord>*> vertices = gr.getVertexSet();
};
