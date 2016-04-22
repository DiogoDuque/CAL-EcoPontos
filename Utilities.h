#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cmath>

class Coord {
public:
	Coord() {};
	Coord(int ID, double latitude, double longitude) {
		id=ID;
		lat = latitude;
		lon = longitude;
	};
	int getID() const {
		return id;
	};
	double getLat() const {
		return lat;
	};
	double getLon() const {
		return lon;
	};
	bool operator==(const Coord c) {
		return lat == c.getLat() && lon == c.getLon();
	};
	double calcWeight(Coord c) {
		return sqrt(pow((lon + c.getLon()), 2) + pow((lat + c.getLat()), 2));
	};

private:
	int id;
	double lat;
	double lon;
};

#endif
