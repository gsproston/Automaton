#include "Tile.h"

Tile::Tile(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos):
	TileBased(viTilePos, viTileMapPos,
		sf::Vector2i(1, 1)),
	m_bPassable(true)
{}

Tile::~Tile() {}