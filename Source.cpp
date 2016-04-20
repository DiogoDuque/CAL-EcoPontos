#include <iostream>

#include "Utilities.h"
#include "Graph.h"
#include "jung/graphviewer.h"

using namespace std;

int main()
{
	cout << "Starting EcoPontos..." << endl << endl;
	//parse txtToGraph
	Graph<Coord> gr;
	vector<Coord>* bounds = new vector<Coord>;
	try
	{
		gr = parseTxtToGraph(bounds);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
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
	}

	//display Graph
	getchar();//*/
	return 0;
}
