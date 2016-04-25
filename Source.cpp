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
		getchar();
		exit(1);
	}

	list<Truck> trucks = getTrucks();
	list<Ecoponto> eco = getEcopontos();
	Coord initial = Coord(parser.getNodeID(137896696),41.14596,-8.597403);

	unsigned int max_load;

	cout << endl << "Please insert maximum load of the recycling bins in kg (0 to 100): ";
	cin >> max_load;

	//GraphToGraphViewer
	try
	{
		parser.graphToGraphViewer(gr);
		parser.setGraphViewerEcopontos(eco);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		getchar();
		exit(1);
	}

	std::list<Ecoponto>::iterator i = eco.begin();
	while (i != eco.end())
	{
		bool notEnough;

		if ((*i).getTrash() < max_load)
			notEnough = true;
		else notEnough = false;

		if (notEnough)
		{
			eco.erase(i++);
		}
		else
		{
			++i;
		}
	}

	while(eco.size() != 0 && trucks.size() != 0){
		Truck best = popBestTruck(trucks,totalTrash(eco));
		list<Ecoponto> temp = fillMax(eco, best);
		vector<Coord> ecoCoord = ecoToCoord(temp, initial);
		vector<Coord> ecoCoord2 = gr->shortestTravelOrder(ecoCoord);
		try{
			parser.setGraphViewerPath(ecoCoord2, best);
		} catch(const char* msg){
			cerr << msg << endl;
			getchar();
			exit(1);
		}
		//getchar();
	}
	cin.ignore(1000, '\n');
	getchar();
	cout << "buh" << endl;
	return 0;
}
