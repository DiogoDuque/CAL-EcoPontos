#include <iostream>
#include <string>
#include "Graph.h"
#include "jung/graphviewer.h"
#include "Ecoponto.h"
#include "Truck.h"
#include "Parser.h"
#include "Utilities.h"

#define INITIAL_POINT 1010
#define MINIMUM_ECO_LOAD 40

using namespace std;

int initialPoint(){
	string val;
	bool valid = true;		// checks if the character input is valid

	do{
		valid = true;

		cout << "Do you want to change default initial point? (YES/NO) ";
		cin >> val;
		cin.ignore(1000, '\n');

		for (size_t i = 0; i < val.length(); i++)
			val[i] = toupper(val[i]);

		if ((val != "YES" && val != "NO") || cin.fail())
		{
			valid = false;
			cin.clear();											// clears state of error of the buffer
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!valid);

	valid = true;

	int id = INITIAL_POINT;

	if (val == "YES"){
		do{
			valid = true;

			cout << "Insert initial point: ";
			cin >> id;
			cin.ignore(1000, '\n');

			if (id < 0 || cin.fail())
			{
				valid = false;
				cin.clear();										// clears state of error of the buffer
				cout << "Invalid input. Please try again." << endl;
			}
		} while (!valid);
	}
	return id;
}

int main()
{
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
		trucks = getTrucks();	// Truck.h
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
		eco = getEcopontos();	// Ecoponto.h
	}
	catch(const char* msg) 		// if the file 'Ecopontos.txt' could not be opened or the data
	{							// on the file is wrong or incomplete this block catches
		cerr << msg << endl;	// an exception and shows a message on the screen
		getchar();
		exit(1);
	}

	//----------------------AddEcopontos----------------------

	//cout << "Do you want to add ecopontos to the map? (YES/NO) ";

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
	/*bool validValue = true;		// checks if the character input is valid

	do{
		validValue = true;

		cout << endl << "Please insert minimum load of the ecopontos in kg (0 to 100): ";
		cin >> min_load;
		cin.ignore(1000, '\n');

		if (min_load > 100 || min_load < 0 || cin.fail())
		{
			validValue = false;
			cin.clear();											// clears state of error of the buffer
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!validValue);*/

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

	//----------------------UpdateGraphViewer----------------------
	parser.setGraphViewerEcopontos(eco);			// shows the ecopontos on GraphViewer
	parser.setGraphViewerBlockedRoads(roads);		// shows the blocked roads on GraphViewer

	//----------------------CheckEcopontosToUnload----------------------

	eco = CheckEcopontosToUnload(eco, min_load);	// Ecoponto.h

	//----------------------RemoveBlockedRoadsFromGraph----------------------
	for(unsigned int i = 0; i < roads.size(); i++){
		gr->removeEdge(parser.getCoordFromID(roads[i].source),
						parser.getCoordFromID(roads[i].dest));
	}

	// initial point (central)
	Coord initial = parser.getCoordFromID(id);

	//----------------------CheckGraphConnectivity----------------------
	vector<Coord> connected = gr->bfs(gr->getVertex(initial));	// connected contains Coord of all the nodes that we can access from the initial point
	gr->resetVisited();											// resets the visited member of every vertex (so that we can use other functions that use visited)

	cout << "\nStarting connectivity test..." << endl;

	for(list<Ecoponto>::iterator it = eco.begin(); it!=eco.end(); it++) // for every ecoponto
	{
		for(unsigned int i=0; i<=connected.size(); i++) 	// for every node that we can access from initial
		{
			if(connected[i] == (*it).getLocation()){		// verifies if ecoponto can be reached
				break;
			}
			if(i==connected.size()){ 						// if not found
				stringstream ss;
				string id;

				ss << (*it).getLocation().getID();
				id = ss.str();

				cout << "Connectity error: Ecoponto " + id + " cannot be reached!" << endl;
				getchar();
				exit(1);
			}
		}

		for(list<Ecoponto>::iterator ita = eco.begin(); ita!=eco.end(); ita++){
			if (it != ita){
				vector<Coord> connected2 = gr->bfs(gr->getVertex((*it).getLocation()));
				gr->resetVisited();

				for(unsigned int i=0; i<=connected2.size(); i++) // for every node that we can access from the current ecoponto
				{
					if(connected2[i] == (*ita).getLocation())	// verifies if ecoponto can be reached
						break;
					if(i==connected2.size()){ 					// if not found
						stringstream ss1, ss2;
						string id_s, id_d;

						ss1 << (*it).getLocation().getID();
						id_s = ss1.str();

						ss2 << (*ita).getLocation().getID();
						id_d = ss2.str();

						cout << "Connectity error: Ecoponto " + id_d + " cannot be reached from " + id_s + "!" << endl;
						getchar();
						exit(1);
					}
				}

			}
		}
	}
	cout << "Finished connectivity test." << endl;

	//----------------------ChooseTrucksRoutes----------------------
	cout << "\nAdding truck routes..." << endl;
	// shows the most efficient route for all the trucks
	while(eco.size() != 0 && trucks.size() != 0){
		Truck best_truck = popBestTruck(trucks,totalTrash(eco));		// returns and pops best truck (popBestTruck - Truck.h, totalTrash - Ecoponto.h)
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
	}

	cout << "Finished!" << endl;
	getchar();
	return 0;
}
