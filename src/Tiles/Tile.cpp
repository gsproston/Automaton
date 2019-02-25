#include "Tile.h"

#include "Constants.h"

Tile::Tile(const int iTileX, const int iTileY,
	const int iTileMapX, const int iTileMapY):
	m_iTileX(iTileX),
	m_iTileY(iTileY),
	m_iTileMapX(iTileMapX),
	m_iTileMapY(iTileMapY)
{}

Tile::~Tile() {}


void Tile::addQuadVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// top left
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE, (float) m_iTileY * TILE_SIZE),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE, (float) m_iTileMapY * TILE_SIZE)));
	// top right
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE + TILE_SIZE, (float) m_iTileY * TILE_SIZE),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE + TILE_SIZE, (float) m_iTileMapY * TILE_SIZE)));
	// bottom right
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE + TILE_SIZE, (float) m_iTileY * TILE_SIZE + TILE_SIZE),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE + TILE_SIZE, (float) m_iTileMapY * TILE_SIZE + TILE_SIZE)));
	// bottom left
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f((float) m_iTileX * TILE_SIZE, (float) m_iTileY * TILE_SIZE + TILE_SIZE),
		sf::Vector2f((float) m_iTileMapX * TILE_SIZE, (float) m_iTileMapY * TILE_SIZE + TILE_SIZE)));
}