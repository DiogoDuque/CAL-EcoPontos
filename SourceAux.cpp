#include "SourceAux.h"

#define INITIAL_POINT 1010

string askUser(string question){
	string val;
	bool valid = true;		// checks if the character input is valid

	do{
		valid = true;

		cout << question;
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

	return val;
}

list<Truck> getTrucks()																										{
	list<Truck> trucks;
	fstream file;
	file.open("Trucks.txt");
	if(!file.is_open())
		throw "Could not open file 'Trucks.txt'!";
	while(!file.eof())
	{
		string name, color;
		int capacity;
		string str[3];
		for(unsigned int i=0; i<2; i++)
		{
			getline(file,str[i],';');
			if(file.eof())
			{
				throw "Reached end of file 'Trucks.txt' too soon! Is file complete?";
			}
		}
		getline(file,str[2]);
		(stringstream) str[0] >> name;
		(stringstream) str[1] >> capacity;
		(stringstream) str[2] >> color;

		if (capacity < 100)
			throw "Not enough capacity! The capacity must be above 100!";

		trucks.push_back(Truck(name,capacity,color));
	}
	file.close();
	trucks.sort();				// sorts trucks by capacity
	return trucks;
}

list<Ecoponto> getEcopontos()
{
	list<Ecoponto> ecopontos;
	fstream file;
	file.open("Ecopontos.txt");
	if(!file.is_open())
		throw "Could not open file 'Ecopontos.txt'!";
	while(!file.eof())
	{
		int id, trash;
		string str[2];
		getline(file,str[0],';');
		if(file.eof())
		{
			throw "Reached end of file 'Ecopontos.txt' too soon! Is file complete?";
		}
		getline(file,str[1]);
		(stringstream) str[0] >> id;
		(stringstream) str[1] >> trash;

		if (trash > 100 || trash < 0)
			throw "Invalid amount of trash! The ecoponto must have 0 to 100 kg of trash...";

		ecopontos.push_back(Ecoponto(trash,id));
	}
	file.close();
	ecopontos.sort();			// sort ecopontos by amount of trash
	return ecopontos;
}

vector<Road> getBlockedRoads(){
	vector<Road> blockedRoads;
	fstream file;
	file.open("BlockedRoads.txt");
	if(!file.is_open())
		throw "Could not open file 'BlockedRoads.txt'!";

	while(!file.eof())
	{
		int long long id_source, id_dest;
		string str[2];
		getline(file,str[0],';');
		if(file.eof())
		{
			vector<Road> tmp;
			cout << "Warning: file 'BlockedRoads.txt' is empty or incomplete" << endl;
			return tmp;
		}
		getline(file,str[1]);
		(stringstream) str[0] >> id_source;
		(stringstream) str[1] >> id_dest;

		Road road;
		road.source = id_source;
		road.dest = id_dest;

		blockedRoads.push_back(road);
	}
	file.close();

	return blockedRoads;
}

int initialPoint(){
	string question = "Do you want to change default initial point? (YES/NO) ";
	string val = askUser(question);

	bool valid = true;		// checks if the character input is valid
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
		cout << endl;
	}
	return id;
}

string getRoadName(){
	bool valid;
	string name;

	do{
		valid = true;

		cout << "Insert name of the road where you want to place the ecoponto: ";
		cin >> name;
		cin.ignore(1000, '\n');

		if (cin.fail())
		{
			valid = false;
			cin.clear();										// clears state of error of the buffer
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!valid);

	return name;
}

int getTrash(){
	bool valid;
	int trash;

	do{
		valid = true;

		cout << "Insert name of the road where you want to place the ecoponto: ";
		cin >> trash;
		cin.ignore(1000, '\n');

		if (trash < 0 || trash > 100 || cin.fail())
		{
			valid = false;
			cin.clear();										// clears state of error of the buffer
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!valid);
	cout << endl;

	return trash;

}

list<Ecoponto> addEcoponto(list<Ecoponto> eco, vector<int> nodes, int trash){

	for(list<Ecoponto>::iterator i = eco.begin(); i != eco.end(); i++)
		for (vector<int>::iterator it =nodes.begin(); it!=nodes.end(); )
			if (i->getLocation().getID() == *it){
				it = nodes.erase(it);
			} else it++;

	int index = rand() % nodes.size();

	Ecoponto ecoponto = Ecoponto(trash,nodes[index]);

	eco.push_back(ecoponto);
	return eco;
}

void ecopontosLoad(){
	int min_load;
	bool validValue = true;		// checks if the character input is valid

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
	} while (!validValue);
}

list<Ecoponto> CheckEcopontosToUnload(list<Ecoponto> eco, int min_load){
	list<Ecoponto>::iterator i = eco.begin();
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

	return eco;
}

bool connectivityTest(list<Ecoponto> eco, Graph<Coord> *gr, Coord initial){
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
				return false;
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
						return false;
					}
				}

			}
		}
	}
	cout << "Finished connectivity test." << endl;
	return true;
}

Truck popBestTruck(list<Truck> &trucks, int totalTrash){
	int bestCapacity = 0;
	Truck best;
	for (list<Truck>::iterator it=trucks.begin(); bestCapacity < totalTrash && it != trucks.end(); ++it){
		best = (*it);
		bestCapacity = (*it).getCapacity();
	}
	trucks.remove(best);
	return best;
}

int totalTrash(list<Ecoponto> ecopontos){
	int res = 0;
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
		res+=(*it).getTrash();
	return res;
}

list<Ecoponto> fillMax(list<Ecoponto> &ecopontos, Truck truck){
	list<Ecoponto> res = {};
	int currentCapacity = truck.getCapacity();
	for (list<Ecoponto>::reverse_iterator it = ecopontos.rbegin(); it != ecopontos.rend() && currentCapacity > 0;){
		if((*it).getTrash() <= currentCapacity){
			currentCapacity -= (*it).getTrash();
			res.push_back(*it);
			++it;
			it = list<Ecoponto>::reverse_iterator(ecopontos.erase(it.base()));
		}
		else
			++it;
	}
	return res;
}

vector<Coord> ecoToCoord(list<Ecoponto> ecopontos, Coord initial){
	vector<Coord> res = {};
	res.push_back(initial);
	for (list<Ecoponto>::iterator it = ecopontos.begin(); it != ecopontos.end(); ++it)
		res.push_back(it->getLocation());
	return res;
}
