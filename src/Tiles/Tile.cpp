#include "Tile.h"

#include "Constants.h"

Tile::Tile(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos):
	m_viTilePos(viTilePos),
	m_viTileMapPos(viTileMapPos)
{}

Tile::~Tile() {}


void Tile::addQuadVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// convert to map positions
	sf::Vector2f vfMapPos(m_viTilePos * TILE_SIZE);
	sf::Vector2f vfTileMapPos(m_viTileMapPos * TILE_SIZE);

	// top left
	rvVertices.push_back(sf::Vertex(
		vfMapPos,
		vfTileMapPos));
	// top right
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(TILE_SIZE, 0),
		vfTileMapPos + sf::Vector2f(TILE_SIZE, 0)));
	// bottom right
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(TILE_SIZE, TILE_SIZE),
		vfTileMapPos + sf::Vector2f(TILE_SIZE, TILE_SIZE)));
	// bottom left
	rvVertices.push_back(sf::Vertex(
		vfMapPos + sf::Vector2f(0, TILE_SIZE),
		vfTileMapPos + sf::Vector2f(0, TILE_SIZE)));
}