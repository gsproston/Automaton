#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Drawables/TileBased/TileBased.h"

class Tile : public TileBased
{
public:
	Tile(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos);
	virtual ~Tile();

	bool m_bPassable;
};