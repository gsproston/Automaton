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

sf::Vector2f Structure::getCentrePos() const
{
	sf::Vector2f vfCentrePos(m_viTilePos * TILE_SIZE);
	return vfCentrePos + sf::Vector2f(TILE_SIZE / 2.f, TILE_SIZE / 2.f);
}

sf::Vector2i Structure::getTilePos() const
{
	return m_viTilePos;
}