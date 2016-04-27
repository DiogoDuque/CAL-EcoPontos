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

	// parse txtToGraph
	Parser parser;
	Graph<Coord>* gr;

	try
	{
		gr = parser.txtToGraph();		// gr contains the graph with the info from the files
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
		getchar();
		exit(1);
	}

	list<Truck> trucks;
	try{
		trucks = getTrucks();
	} catch(const char* msg){		// if the file 'Trucks.txt' could not be opened or the data on the file is wrong or incomplete
		cerr << msg << endl;		// this block catches an exception and shows a message on the screen
		getchar();
		exit(1);
	}

	list<Ecoponto> eco;
	try{
		eco = getEcopontos();
	} catch(const char* msg){		// if the file 'Ecopontos.txt' could not be opened or the data on the file is wrong or incomplete
		cerr << msg << endl;		// this block catches an exception and shows a message on the screen
		getchar();
		exit(1);
	}

	Coord initial = Coord(parser.getNodeID(137896696),41.14596,-8.597403);		// initial point (central)

	unsigned int min_load;
	bool validValue;		// checks if the character input is valid

	do{
		validValue = true;

		cout << "Please insert minimum load of the ecopontos in kg (0 to 100): ";
		cin >> min_load;
		cin.ignore(1000, '\n');

		if (min_load > 100 || cin.fail())
		{
			validValue = false;
			cin.clear();											// clears state of error of the buffer
			cout << "Invalid input. Please try again.\n";
		}
	} while (!validValue);
	cout << endl;

	// GraphToGraphViewer
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

	parser.setGraphViewerEcopontos(eco);			// shows the ecopontos on GraphViewer

	std::list<Ecoponto>::iterator i = eco.begin();
	while (i != eco.end())
	{
		bool notEnough;						// true if ecoponto hasn't enough trash

		if ((*i).getTrash() < min_load)
			notEnough = true;
		else notEnough = false;

		if (notEnough)
		{
			eco.erase(i++);					// erases ecoponto from list
		}
		else
		{
			++i;
		}
	}

	// verify Graph connectivity from initial point (central) to the ecopontos

	vector<Coord> connected = gr->bfs(gr->getVertex(initial));	// connected contains Coord of all the nodes that we can access from the initial point
	gr->resetVisited();											// resets the visited member of every vertex (so that we can use other functions that use visited)

	cout << "\nStarting connectivity test..." << endl;

	for(list<Ecoponto>::iterator it = eco.begin(); it!=eco.end(); it++) // for every ecoponto
	{
		for(unsigned int i=0; i<=connected.size(); i++) // for every node that we can access from initial
		{
			if(connected[i] == (*it).getLocation())		// verifies if ecoponto can be reached
				break;
			if(i==connected.size()){ 					// if not found
				cout << "Connectity error: Ecoponto cannot be reached!" << endl;
				getchar();
				exit(1);
			}
		}
	}

	cout << "Finished connectivity test." << endl;

	cout << "\nAdding truck routes..." << endl;

	// shows the most efficient route for all the trucks
	while(eco.size() != 0 && trucks.size() != 0){
		Truck best_truck = popBestTruck(trucks,totalTrash(eco));		// returns and pops best truck
		list<Ecoponto> assignedEco = fillMax(eco, best_truck);			// ecopontos assigned to the truck
		parser.setGraphViewerEcoLabel(assignedEco, best_truck.getColor());
		vector<Coord> ecoCoord = ecoToCoord(assignedEco, initial);		// location and id (Coord) of the central and ecopontos
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
