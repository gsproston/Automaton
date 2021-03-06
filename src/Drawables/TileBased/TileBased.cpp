#include "TileBased.h"

#include "Utils/Utils.h"

TileBased::TileBased(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims) :
	m_viTilePos(viTilePos),
	m_viTileDims(viTileDims)
{
	// convert to map position
	sf::Vector2f vfMapPos = utils::convertTilePosToMapPos(viTilePos);
	sf::Vector2f vfTileMapPos = utils::convertTileMapPosToMapPos(viTileMapPos);
	sf::Vector2f vfTileDims = utils::convertTilePosToMapPos(viTileDims);
	sf::Vector2f vfTileMapDims = utils::convertTileMapPosToMapPos(viTileDims);

	// init the vertices
	m_aVertices[0] = sf::Vertex(
		vfMapPos, 
		vfTileMapPos);
	// top right
	m_aVertices[1] = sf::Vertex(
		vfMapPos + sf::Vector2f(vfTileDims.x, 0),
		vfTileMapPos + sf::Vector2f(vfTileMapDims.x, 0));
	// bottom right
	m_aVertices[2] = sf::Vertex(
		vfMapPos + vfTileDims,
		vfTileMapPos + vfTileMapDims);
	// bottom left
	m_aVertices[3] = sf::Vertex(
		vfMapPos + sf::Vector2f(0, vfTileDims.y),
		vfTileMapPos + sf::Vector2f(0, vfTileMapDims.y));
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
	sf::Vector2f vfCentrePos = utils::convertTilePosToMapPos(m_viTilePos);
	return vfCentrePos + utils::convertTilePosToMapPos(m_viTileDims) / 2.f;
}