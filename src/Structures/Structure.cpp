#include "Structure.h"

#include "Constants.h"

Structure::Structure(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viDimensions):
	m_viTilePos(viTilePos),
	m_viTileMapPos(viTileMapPos),
	m_viDimensions(viDimensions)
{}

Structure::~Structure() {}


void Structure::addQuadVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// convert to map position
	sf::Vector2f vfMapPos(m_viTilePos * TILE_SIZE);
	sf::Vector2f vfTileMapPos(m_viTileMapPos * TILE_SIZE);

	// top left
	rvVertices.push_back(sf::Vertex(
		vfMapPos,
		vfTileMapPos));
	// top right
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f((float) m_viDimensions.x, 0),
		vfTileMapPos + sf::Vector2f((float) m_viDimensions.x, 0)));
	// bottom right
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(m_viDimensions),
		vfTileMapPos + sf::Vector2f(m_viDimensions)));
	// bottom left
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(0, (float) m_viDimensions.y),
		vfTileMapPos + sf::Vector2f(0, (float) m_viDimensions.y)));
}

sf::Vector2i Structure::getDirection(const sf::Vector2f vfMapPos) const
{
	sf::Vector2i vfDirection(0, 0);
	sf::Vector2f vfCentrePos = getCentrePos();

	if (vfMapPos.x < vfCentrePos.x)
		vfDirection.x = 1;
	else if (vfMapPos.x > vfCentrePos.x)
		vfDirection.x = -1;

	if (vfMapPos.y < vfCentrePos.y)
		vfDirection.y = 1;
	else if (vfMapPos.y > vfCentrePos.y)
		vfDirection.y = -1;

	return vfDirection;
}

// returns the distance from the centre of the tile to the position
float Structure::getDistance(const sf::Vector2f vfMapPos) const
{
	sf::Vector2f vfCentrePos = getCentrePos();
	return sqrt(pow(abs(vfCentrePos.x - vfMapPos.x), 2) + 
		pow(abs(vfCentrePos.y - vfMapPos.y), 2));
}

// get the centre position of the tile
sf::Vector2f Structure::getCentrePos() const
{
	sf::Vector2f vfCentrePos(m_viTilePos * TILE_SIZE);
	return vfCentrePos + sf::Vector2f(m_viDimensions.x / 2.f, m_viDimensions.y / 2.f);
}

sf::Vector2i Structure::getTilePos() const
{
	return m_viTilePos;
}

// returns true if the coordinates are close to the structure
bool Structure::isClose(const sf::Vector2f vfMapPos) const
{
	return (getDistance(vfMapPos) < TILE_SIZE - 5);
}