#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cmath>

/**
 *
 * This class stores an Coord object that represents the location of an object.
 * An Coord object is characterized by its location and the id of the object in this location.
 *
 */
class Coord {
public:
	Coord() {};
	Coord(int ID, double latitude, double longitude) {
		id = ID;
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
	/**
	 * This function calculates the weight of the edge that connects two nodes given its respective ids and locations.
	 * The weight is calculated calculating the distance between the nodes
	 *
	 * @param c - id and location of the node
	 * @return weight of the edge
	 */
	double calcWeight(Coord c) {
		return sqrt(pow((c.getLon() - lon), 2) + pow((c.getLat() - lat), 2));
	};

private:
	int id;
	double lat;
	double lon;
};

#endif
