#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cmath>

/**
 *
 */
struct Road {
	int source;
	int dest;
};

/**
 *
 * This class stores an Coord object that represents the location of an object.
 * An Coord object is characterized by its location and the id of the object in this location.
 *
 */
class Coord {
public:
	Coord() {
		id = 0;
		lat = 0;
		lon = 0;
	};
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

	/**
	 * Compares two locations: one Coord is equal to other if all its latitute and longitute are equal
	 *
	 * @param other - Coord object that will be compared with this object
	 * @return true if the location is equal, false if otherwise
	 */
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
