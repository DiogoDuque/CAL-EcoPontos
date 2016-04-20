#include <iostream>

#include "Utilities.h"
#include "Graph.h"
#include "jung/graphviewer.h"

using namespace std;

int main()
{
	cout << "Starting EcoPontos...\n\n";
	//parse txtToGraph
	Graph<Coord> gr;
	try
	{
		gr = parseTxtToGraph();
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
	}

	//apply algs

	//GraphToGraphViewer
	GraphViewer* gv = new GraphViewer(600, 600, false);

	try
	{
		parseGraphToGraphViewer(gv,gr);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
	}

	//display Graph
	gv->rearrange();
	getchar();//*/
	return 0;
}
