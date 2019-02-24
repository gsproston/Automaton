#include "Structure.h"

#include "Constants.h"

Structure::Structure(const int x, const int y) :
	m_ix(x),
	m_iy(y)
{}


int Structure::getDirectionX(const int x) const
{
	// convert structure coordinates to centre coords
	int structx = getCentreX();

	if (x < structx)
		return 1;
	else if (x > structx)
		return -1;
	return 0;
}

int Structure::getDirectionY(const int y) const
{
	// convert structure coordinates to centre coords
	int structy = getCentreY();

	if (y < structy)
		return 1;
	else if (y > structy)
		return -1;
	return 0;
}

int Structure::getDistance(const int x, const int y) const
{
	// convert structure coordinates to centre coords
	int structx = getCentreX();
	int structy = getCentreY();

	return (abs(structx - x) + abs(structy - y));
}

int Structure::getCentreX() const
{
	return m_ix * TILE_SIZE + TILE_SIZE / 2;
}

int Structure::getCentreY() const
{
	return m_iy * TILE_SIZE + TILE_SIZE / 2;
}

// returns true if the coordinates are close to the structure
bool Structure::isClose(const int x, const int y) const
{
	// convert structure coordinates to centre coords
	int structx = getCentreX();
	int structy = getCentreY();

	return (abs(structx - x) < TILE_SIZE &&
		abs(structy - y) < TILE_SIZE);
}