#include "Utilities.h"
#include "Graph.h"
#include "jung/graphviewer.h"

using namespace std;

int main()
{
	//parse txtToGraph
	Graph<Coord> gr;

	//apply alg

	//GraphToGraphViewer
	GraphViewer gv = parseGraphToGraphViewer(gr);

	//display Graph
	gv.rearrange();
	getchar();
	return 0;
}
