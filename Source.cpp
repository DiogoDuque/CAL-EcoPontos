#include <iostream>
#include "Truck.h"
#include "Utilities.h"
#include "Graph.h"
#include "jung/graphviewer.h"
#include "Ecoponto.h"
using namespace std;

int main()
{
	cout << "Starting EcoPontos..." << endl << endl;
	/*//parse txtToGraph
	Graph<Coord> gr;
	vector<Coord>* bounds = new vector<Coord>;
	try
	{
		gr = parseTxtToGraph(bounds);
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
		parseGraphToGraphViewer(gr,bounds);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		exit(1);
	}//*/

	list<Truck> trucks = getTrucks();

	//	for(list<Truck>::iterator it = trucks.begin();it != trucks.end();++it){
	//		cout << it->getName() << " " << it->getCapacity()<< " " << it->getColor() << endl;
	//	}

	list<Ecoponto> eco2 = getEcopontos();


	Truck best = popBestTruck(trucks,70);
	list<Ecoponto> eco = fillMax(eco2, best);
	for(list<Ecoponto>::iterator it = eco.begin();it != eco.end();++it){
		cout << it->getTrash()<< endl;
	}

	return 0;
}
