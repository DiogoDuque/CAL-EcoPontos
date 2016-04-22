/*
 * Parser.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Diogo
 */

#include "Parser.h"

int Parser::nextID = 0;
vector<Coord> Parser::bounds;
unordered_map <double,int> Parser::doubleToInt;
unordered_map<int, Coord> Parser::coords;

/**
 * Construtor
 */
Parser::Parser() {
	nextID=0;
}

/**
 * Destrutor
 */
Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

/**
 * Le os ficheiros de texto 'Nodes.txt', 'Roads.txt' e 'Connections.txt',
 * e retorna o grafo feito a partir desses ficheiros.
 */
Graph<Coord>* Parser::txtToGraph() {
	cout << "Started parser <txt> <Graph>" << endl;
	double xMin=1000, xMax=-1000, yMin=1000, yMax=-1000;
	Graph<Coord>* gr = new Graph<Coord>;
	fstream file, file2;

	//Nodes.txt
	file.open("Nodes.txt");
	if (!file.is_open())
		throw "Could not open file 'Nodes.txt'!";
	cout << "Reading 'Nodes.txt'" << endl;
	while (!file.eof()) {
		bool eofFound=false; //fica true se a ultima linha do ficheiro existir, mas nao tiver carateres
		string str[5];
		double coordX, coordY;
		double id;
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

		//converter ID
		doubleToInt[id]=getNextID();

		//gravar no grafo
		Coord coord(nextID-1,coordX, coordY);
		coords[nextID-1] = coord;
		gr->addVertex(coord);
		//atualizar maxs/mins
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

	//Roads.txt e Connections.txt
	file.open("Roads.txt");
	if (!file.is_open())
		throw "Could not open file 'Roads.txt'!";
	file2.open("Connections.txt");
	if (!file.is_open())
		throw "Could not open file 'Connections.txt'!";

	cout << "Reading 'Roads.txt' and 'Connections.txt'" << endl;
	int oldID = -1; //estas 2 vars sao para controlo da sincronizacao dos 2 ficheiros
	string twoway;
	while (!file2.eof()) {
		string str[3];
		double node1, node2;
		int id;
		bool eofFound=false;

		//ler as connections
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

		if (id != oldID) //atualizar oneway e id caso seja necessario
		{
			oldID = id;
			for (int i = 0; i < 2; i++)
			{
				getline(file, twoway, ';');
				if(file.eof())
					throw "Reached end of file 'Roads.txt' too soon! Is file complete?";
			}
			getline(file, twoway);
		}//ENDIF

		//adicionar ao grafo
		int weight = coords[doubleToInt[node1]].calcWeight(coords[doubleToInt[node2]]);
		if (twoway == "True") {
			gr->addEdge(coords[doubleToInt[node1]], coords[doubleToInt[node2]], weight);
			gr->addEdge(coords[doubleToInt[node2]], coords[doubleToInt[node1]], weight);
		} else {
			gr->addEdge(coords[doubleToInt[node1]], coords[doubleToInt[node2]], weight);
		}

	}
	file.close();
	file2.close();
	cout << "Finished reading 'Roads.txt' and 'Connections.txt'" << endl;
	cout << "Finished parser <txt> <Graph>" << endl << endl << endl;
	bounds.push_back(Coord(-1,xMax,yMax));
	bounds.push_back(Coord(-1,xMin,yMin));
	return gr;
}

/**
 * Recebe um grafo e representa-o através do GraphViewer.
 */
void Parser::graphToGraphViewer(Graph<Coord>* gr) {
	cout << "Started parser <Graph> to <GraphViewer>" << endl;
	Coord min = bounds.back();
	bounds.pop_back();
	Coord max = bounds.back();
	bounds.pop_back();
	double xMin=min.getLat(), yMin=min.getLon(), xMax=max.getLat(), yMax=max.getLon();


	GraphViewer* gv = new GraphViewer(2000,800,false);
	gv->createWindow(2000, 800);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("black");
	gv->defineEdgeCurved(false);

	cout << "Adding nodes..." << endl;
	vector<Vertex<Coord> *> vertices = gr->getVertexSet();
	for(unsigned i=0; i<vertices.size(); i++)
	{
		Coord temp(vertices[i]->getInfo().getID(),
					(vertices[i]->getInfo().getLat()-xMin)*10000/(xMax-xMin)-5000,
					(vertices[i]->getInfo().getLon()-yMin)*10000/(yMax-yMin)-5000);
		gv->addNode(temp.getID(),temp.getLat(),temp.getLon());
	}
	gv->rearrange();

	cout << "Adding edges..." << endl;
	int edgeID=0;
	for(unsigned i=0; i<vertices.size(); i++)
	{
		vector<Edge<Coord> > edges = vertices[i]->getAdj();
		for(unsigned j=0; j<edges.size(); j++)
		{
			int source = vertices[i]->getInfo().getID();
			int destination = edges[j].getDest()->getInfo().getID();
			gv->addEdge(edgeID,source,destination,EdgeType::DIRECTED);
			edgeID++;
		}
	}
	gv->rearrange();
	cout << "Finished parser <Graph> to <GraphViewer>" << endl << endl << endl;
	getchar();
}

/**
 * Converte um double lido de um ficheiro para o int correspondente
 * usado no grafo.
 */
int Parser::convertDoubleToIntID(double nr)
{
	return doubleToInt[nr];
}

/**
 * Retorna as coordenadas do node com id nr.
 */
Coord Parser::getCoordFromIntID(int nr)
{
	return coords[nr];
}

/**
 * Retorna um id e incrementa para uma proxima utilizacao.
 */
int Parser::getNextID()
{
	int ret = nextID;
	nextID++;
	return ret;
}

