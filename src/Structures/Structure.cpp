#include "Structure.h"

#include "Constants.h"

Structure::Structure(const int iTileX, const int iTileY,
	const int iTileMapX, const int iTileMapY,
	const int iHeight, const int iWidth):
	m_iTileX(iTileX),
	m_iTileY(iTileY),
	m_iTileMapX(iTileMapX),
	m_iTileMapY(iTileMapY),
	m_iHeight(iHeight),
	m_iWidth(iWidth)
{}

Structure::~Structure() {}


void Structure::addQuadVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// top left
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE, (float) m_iTileY * TILE_SIZE),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE, (float) m_iTileMapY * TILE_SIZE)));
	// top right
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE + m_iWidth, (float) m_iTileY * TILE_SIZE),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE + m_iWidth, (float) m_iTileMapY * TILE_SIZE)));
	// bottom right
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE + m_iWidth, (float) m_iTileY * TILE_SIZE + m_iHeight),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE + m_iWidth, (float) m_iTileMapY * TILE_SIZE + m_iHeight)));
	// bottom left
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE, (float) m_iTileY * TILE_SIZE + m_iHeight),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE, (float) m_iTileMapY * TILE_SIZE + m_iHeight)));
}

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
	return m_iTileX * TILE_SIZE + TILE_SIZE / 2;
}

int Structure::getCentreY() const
{
	return m_iTileY * TILE_SIZE + TILE_SIZE / 2;
}

// returns true if the coordinates are close to the structure
bool Structure::isClose(const int x, const int y) const
{
	int dist = pow(abs(getCentreX() - x), 2) + 
		pow(abs(getCentreY() - y), 2);
	dist = sqrt(dist);

	return (dist < TILE_SIZE - 5);
}