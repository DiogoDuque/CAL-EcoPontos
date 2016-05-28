#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "SourceAux.h"
#include "Graph.h"
#include "jung/graphviewer.h"
#include "Truck.h"
#include "Parser.h"
#include "Utilities.h"

#define MINIMUM_ECO_LOAD 40

using namespace std;

int main()
{
	srand(time(NULL));

	cout << "Starting EcoPontos..." << endl << endl;

	Parser parser;
	Graph<Coord>* gr;

	try{
		gr = parser.initializeGraph();		// gr contains the graph with the info from the files
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		getchar();
		exit(1);
	}

	//----------------------GetTrucks----------------------
	list<Truck> trucks;
	try
	{
		trucks = getTrucks();
	}
	catch(const char* msg) 		// if the file 'Trucks.txt' could not be opened or the data
	{							// on the file is wrong or incomplete this block catches
		cerr << msg << endl;	// an exception and shows a message on the screen
		getchar();
		exit(1);
	}

	//----------------------GetEcopontos----------------------
	list<Ecoponto> eco;
	try
	{
		eco = getEcopontos();
	}
	catch(const char* msg) 		// if the file 'Ecopontos.txt' could not be opened or the data
	{							// on the file is wrong or incomplete this block catches
		cerr << msg << endl;	// an exception and shows a message on the screen
		getchar();
		exit(1);
	}

	//----------------------GetDrivers----------------------
	vector<string> drivers = getDrivers();
	if(drivers.size()<trucks.size())
	{
		cerr << "There may not be enough drivers for the trucks...\n" <<
				"Add some more drivers, or withdraw some trucks!" << endl;
		exit(2);
	}


	//----------------------GraphToGraphViewer----------------------
		try
		{
			parser.graphToGraphViewer(gr);
		}
		catch(const char* msg)
		{
			cerr << msg << endl;
			getchar();
			exit(1);
		}

	//----------------------AddEcopontos-----------------------

	string question = "Do you want to add ecopontos to the map? (YES/NO) ";
	while(askUser(question)){
		string name = getRoadName();		// user road name input
		int trash = getTrash();
		string road_name = parser.searchRoad(name);
		int num_ecopontos = parser.getNumEcopontos(road_name, eco);

		cout << "There are " << num_ecopontos << " ecopontos on the road " << road_name << endl;

		if(askUser("Are you sure you want to add it here? "))
		{
			vector<int> nodes = parser.getNodesRoad(road_name);
			eco = addEcoponto(eco,nodes, trash);
		}
	}

	//----------------------AssignDriversToTrucks----------------------
	cout << "Please assign drivers to all the trucks" << endl;
	for(list<Truck>::iterator it=trucks.begin(); it!=trucks.end(); it++)
	{
		cout << "Drivers available for truck " << (*it).getName() << ":" << endl;
		for(unsigned i=0; i<drivers.size(); i++)
			cout << drivers[i] << endl;

		string name;
		int driverIndex=-1;
		cout << "\nDriver: ";
		cin >> name;
		for(unsigned i=0; i<drivers.size(); i++)
		{
			int temp=kmp(drivers[i],name);
			if(temp>0) //found
			{
				driverIndex=i;
				break;
			}
		}
		if(driverIndex<0){
			it--;
			cout << "Name not found!\n";
		} else {
			(*it).setDriver(drivers[driverIndex]);
			drivers.erase(drivers.begin() + driverIndex);
		}
	}

	//----------------------getBlockedRoads----------------------
	vector<Road> roads;
	try
	{
		roads = getBlockedRoads();
	}
	catch(const char* msg)	// if the file 'BlockedRoads.txt' could not be opened or the
	{						// data on the file is wrong or incomplete this block catches
		cerr << msg << endl;// an exception and shows a message on the screen
		getchar();
		exit(1);
	}

	//----------------------InitialPoint----------------------

	int id = initialPoint();

	//----------------------EcopontosLoad----------------------
	int min_load = MINIMUM_ECO_LOAD;

	// min_load = ecopontosLoad();

	//----------------------UpdateGraphViewer----------------------
	parser.setGraphViewerEcopontos(eco);			// shows the ecopontos on GraphViewer
	parser.setGraphViewerBlockedRoads(roads);		// shows the blocked roads on GraphViewer

	//----------------------CheckEcopontosToUnload----------------------

	eco = CheckEcopontosToUnload(eco, min_load);

	//----------------------RemoveBlockedRoadsFromGraph----------------------
	for(unsigned int i = 0; i < roads.size(); i++){
		gr->removeEdge(parser.getCoordFromID(roads[i].source), parser.getCoordFromID(roads[i].dest));
	}

	// initial point (central)
	Coord initial = parser.getCoordFromID(id);

	//----------------------CheckGraphConnectivity----------------------
	if (!connectivityTest(eco, gr, initial))
		exit(1);

	//----------------------ChooseTrucksRoutes----------------------
	cout << "\nAdding truck routes..." << endl;

	// shows the most efficient route for all the trucks
	while(eco.size() != 0 && trucks.size() != 0){
		Truck best_truck = popBestTruck(trucks,totalTrash(eco));		// returns and pops best truck
		list<Ecoponto> assignedEco = fillMax(eco, best_truck);			// ecopontos assigned to the truck (fillMax - Ecoponto.h)
		parser.setGraphViewerEcoLabel(assignedEco, best_truck.getColor());
		vector<Coord> ecoCoord = ecoToCoord(assignedEco, initial);		// location and id (Coord) of the central and ecopontos (ecoToCoord - Ecoponto.h)
		vector<Coord> route = gr->shortestTravelOrder(ecoCoord);		// obtains the shortest route
		try{
			parser.setGraphViewerPath(route, best_truck);				// shows the route on GraphViewer
		} catch(const char* msg){										// if the truck is black this catches an exception
			cerr << msg << endl;
			getchar();
			exit(1);
		}
		//print info about driver, truck and route
		cout << best_truck.getDriver() << " is driving truck " << best_truck.getName() <<
				" through " << assignedEco.size() << " ecopontos" << endl;
	}

	cout << "\nFinished!" << endl;
	getchar();
	return 0;
}
