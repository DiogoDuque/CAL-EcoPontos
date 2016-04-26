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
	bool validValues;

	do{
		validValues = true;

		cout << "Please insert maximum load of the recycling bins in kg (0 to 100): ";
		cin >> max_load;
		cin.ignore(1000, '\n');

		if (max_load > 100 || cin.fail())
		{
			validValues = false;
			cin.clear();											// clears state of error
			cout << "Invalid input. Please try again.\n";
		}
	} while (!validValues);
	cout << endl;

	// GraphToGraphViewer
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

	// verify Graph connectivity from initial point (central) to the ecopontos
	vector<Coord> connected = gr->bfs(gr->getVertex(initial));	// connected contains Coord of all the nodes that we can access from the initial point
	gr->resetVisited();											// resets the visited member of every vertex (so that we can use other functions that use visited)

	for(list<Ecoponto>::iterator it = eco.begin(); it!=eco.end(); it++) // for every ecoponto
	{
		for(unsigned int i=0; i<=connected.size(); i++) // for every node that we can access from initial
		{
			if(connected[i] == (*it).getLocation())		// verifies if ecoponto can be reached
				break;
			if(i==connected.size()){ 					// if not found
				cout << "Ecoponto cannot be reached!" << endl;
				getchar();
				exit(1);
			}
		}
	}

	// shows the most efficient route for all the trucks
	while(eco.size() != 0 && trucks.size() != 0){
		Truck best_truck = popBestTruck(trucks,totalTrash(eco));		// returns and pops best truck
		list<Ecoponto> assignedEco = fillMax(eco, best_truck);			// ecopontos assigned to the truck
		vector<Coord> ecoCoord = ecoToCoord(assignedEco, initial);		// location and id (Coord) of the central and ecopontos
		vector<Coord> route = gr->shortestTravelOrder(ecoCoord);		// obtains the shortest route
		try{
			parser.setGraphViewerPath(route, best_truck);				// shows the route on GraphViewer
		} catch(const char* black_color){								// if the truck is black this catches an exception
			cerr << black_color << endl;
			getchar();
			exit(1);
		}
	}

	getchar();
	return 0;
}
