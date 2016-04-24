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

	list<Truck> trucks = getTrucks();
	list<Ecoponto> eco = getEcopontos();
	Coord initial = Coord(parser.convertDoubleToIntID(137896696),41.14596,-8.597403);

	//GraphToGraphViewer
	try
	{
		parser.graphToGraphViewer(gr);
		parser.setGraphViewerEcopontos(eco);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		exit(1);
	}

	while(eco.size() != 0 && trucks.size() != 0){
		Truck best = popBestTruck(trucks,totalTrash(eco));
		list<Ecoponto> temp = fillMax(eco, best);
		vector<Coord> ecoCoord = ecoToCoord(temp, initial);
		cerr << ecoCoord.size() << endl;
		vector<Coord> ecoCoord2 = gr->shortestTravelOrder(ecoCoord);
		cerr << ecoCoord2.size() << endl;
		parser.setGraphViewerPath(ecoCoord2, best);
		cerr << "Next" << endl;
		cerr << trucks.size();
		getchar();
	}



	getchar();

	/*list<Truck> trucks = getTrucks();


	Truck best = popBestTruck(trucks,70);
	list<Ecoponto> eco = fillMax(eco2, best);
	for(list<Ecoponto>::iterator it = eco.begin();it != eco.end();++it){
		cout << it->getTrash()<< endl;
	}*/

	return 0;
}
