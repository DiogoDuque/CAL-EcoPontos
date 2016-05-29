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
	vector<string> drivers = getDrivers();			// get all drivers' names
	if(drivers.size() < trucks.size())
	{
		cerr << "There may not be enough drivers for the trucks...\n" <<
				"Add some more drivers, or withdraw some trucks!" << endl;
		exit(2);
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

	//----------------------InitialPoint----------------------
	int id = initialPoint();

	//----------------------AddEcopontos-----------------------

	string question = "Do you want to add ecopontos to the map? (YES/NO) ";
	cout << endl;
	while(askUser(question)){
		cout << endl;
		string name = getRoadName();								// user road name input
		int trash = getTrash();										// user trash input

		vector<string> roads = parser.getRoadNames();				// gets all roads' names
		string road_name = searchName(name, roads);					// searches name on roads and returns the most similar name
		int num_ecopontos = parser.getNumEcopontos(road_name, eco);	// number of ecopontos on the road

		cout << "There are " << num_ecopontos << " ecopontos on the road " << road_name << endl;

		if(askUser("Are you sure you want to add it here? (YES/NO) "))
		{
			vector<int> nodes = parser.getNodesRoad(road_name);		// gets all the nodes of the road
			eco = addEcoponto(eco,nodes, trash);					// adds ecoponto
		}
		cout << endl;
	}
	cout << endl;

	//----------------------AssignDriversToTrucks----------------------

	cout << "Please assign drivers to all the trucks" << endl;
	for(list<Truck>::iterator it=trucks.begin(); it!=trucks.end(); it++) //iterates over all trucks
	{
		cout << "Drivers available for truck " << (*it).getName() << ":" << endl;
		for(unsigned i=0; i<drivers.size(); i++)
			cout << drivers[i] << endl;
		vector<string> tmp = drivers;
		string name;
		int driverIndex=-1;
		cout << "\nDriver: ";
		cin >> name;
		for (int j = 0; j < name.length(); j++)
			name[j] = toupper(name[j]);
		for(unsigned i=0; i<tmp.size(); i++)
		{
			for (int j = 0; j < tmp[i].length(); j++)
				tmp[i][j] = toupper(tmp[i][j]);
			int temp=kmp(tmp[i],name);
			if(temp>0) // name found
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
			drivers.erase(drivers.begin() + driverIndex);	// a driver cannot drive two trucks
		}
	}

	//----------------------EcopontosLoad----------------------
	int min_load = MINIMUM_ECO_LOAD;

	// min_load = ecopontosLoad();

	//----------------------UpdateGraphViewer----------------------
	parser.setGraphViewerEcopontos(eco);			// shows the ecopontos on GraphViewer
	parser.setGraphViewerBlockedRoads(roads);		// shows the blocked roads on GraphViewer

	//----------------------CheckEcopontosToUnload----------------------

	eco = CheckEcopontosToUnload(eco, min_load);	// all the ecopontos with trash below min_load are erased

	//----------------------RemoveBlockedRoadsFromGraph----------------------
	for(unsigned int i = 0; i < roads.size(); i++){
		gr->removeEdge(parser.getCoordFromID(roads[i].source), parser.getCoordFromID(roads[i].dest));
	}

	// initial point (central)
	Coord initial = parser.getCoordFromID(id);

	//----------------------CheckGraphConnectivity----------------------
	if (!connectivityTest(eco, gr, initial))					// checks connectivity and displays message in case it fails
		exit(1);

	//----------------------ChooseTrucksRoutes----------------------
	cout << "\nAdding truck routes..." << endl;

	// shows the most efficient route for all the trucks
	while(eco.size() != 0 && trucks.size() != 0){
		Truck best_truck = popBestTruck(trucks,totalTrash(eco));		// returns and pops best truck
		list<Ecoponto> assignedEco = fillMax(eco, best_truck);			// ecopontos assigned to the truck (fillMax - Ecoponto.h)
		parser.setGraphViewerEcoLabel(assignedEco, best_truck.getColor());
		vector<Coord> ecoCoord = ecoToCoord(assignedEco, initial);		// location and id (Coord) of the central and ecopontos (ecoToCoord - Ecoponto.h)
		vector<Coord> route = gr->hamiltonCircuit(gr->getSimplifiedGraph(ecoCoord)); // obtains the shortest route

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
