#include <iostream>
#include "Graph.h"
#include "jung/graphviewer.h"
#include "Ecoponto.h"
#include "Truck.h"
#include "Parser.h"
#include "Utilities.h"

using namespace std;

int main()
{
	cout << "Starting EcoPontos..." << endl << endl;
	//parse txtToGraph
	Parser parser;
	Graph<Coord>* gr;
	try
	{
		gr = parser.txtToGraph();
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		exit(1);
	}

	//apply algs

	//GraphToGraphViewer
	try
	{
		parser.graphToGraphViewer(gr);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		exit(1);
	}//*/

	/*list<Truck> trucks = getTrucks();

	list<Ecoponto> eco2 = getEcopontos();


	Truck best = popBestTruck(trucks,70);
	list<Ecoponto> eco = fillMax(eco2, best);
	for(list<Ecoponto>::iterator it = eco.begin();it != eco.end();++it){
		cout << it->getTrash()<< endl;
	}*/

	return 0;
}
