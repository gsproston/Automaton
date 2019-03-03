#include "TileBased.h"

#include "Constants.h"

TileBased::TileBased(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims) :
	m_viTilePos(viTilePos),
	m_viTileDims(viTileDims)
{
	// convert to map position
	sf::Vector2f vfMapPos(viTilePos * TILE_SIZE);
	sf::Vector2f vfTileMapPos(viTileMapPos * TILE_SIZE);
	sf::Vector2f vfTileDims(viTileDims * TILE_SIZE);

	// init the vertices
	m_aVertices[0] = sf::Vertex(
		vfMapPos, 
		vfTileMapPos);
	// top right
	m_aVertices[1] = sf::Vertex(
		vfMapPos + sf::Vector2f(vfTileDims.x, 0),
		vfTileMapPos + sf::Vector2f(vfTileDims.x, 0));
	// bottom right
	m_aVertices[2] = sf::Vertex(
		vfMapPos + vfTileDims,
		vfTileMapPos + vfTileDims);
	// bottom left
	m_aVertices[3] = sf::Vertex(
		vfMapPos + sf::Vector2f(0, vfTileDims.y),
		vfTileMapPos + sf::Vector2f(0, vfTileDims.y));
}

TileBased::~TileBased() {}


void TileBased::addVertices(std::vector<sf::Vertex>& rvVertices) const
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		rvVertices.push_back(m_aVertices[i]);
	}
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