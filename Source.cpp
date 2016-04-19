#include "Graph.h"
#include "jung/graphviewer.h"

using namespace std;

int main()
{
	GraphViewer* gv = new GraphViewer(600,600,false);
	gv->createWindow(600, 600);
	gv->rearrange();
	getchar();
	return 0;
}
