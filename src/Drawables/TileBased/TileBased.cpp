#include "TileBased.h"

#include "Constants.h"

TileBased::TileBased(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims) :
	m_viTilePos(viTilePos),
	m_viTileMapPos(viTileMapPos),
	m_viTileDims(viTileDims)
{}

TileBased::~TileBased() {}


void TileBased::addVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// convert to map position
	sf::Vector2f vfMapPos(m_viTilePos * TILE_SIZE);
	sf::Vector2f vfTileMapPos(m_viTileMapPos * TILE_SIZE);
	sf::Vector2f vfTileDims(m_viTileDims * TILE_SIZE);

	// top left
	rvVertices.push_back(sf::Vertex(
		vfMapPos,
		vfTileMapPos));
	// top right
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(vfTileDims.x, 0),
		vfTileMapPos + sf::Vector2f(vfTileDims.x, 0)));
	// bottom right
	rvVertices.push_back(sf::Vertex(
		vfMapPos + vfTileDims,
		vfTileMapPos + vfTileDims));
	// bottom left
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(0, vfTileDims.y),
		vfTileMapPos + sf::Vector2f(0, vfTileDims.y)));
}

sf::Vector2f TileBased::getCentrePos() const
{
	sf::Vector2f vfCentrePos(m_viTilePos * TILE_SIZE);
	return vfCentrePos + sf::Vector2f(m_viTileDims * TILE_SIZE) / 2.f;
}

sf::Vector2i TileBased::getTilePos() const
{
	return m_viTilePos;
}