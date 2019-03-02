#pragma once

#include <SFML/Graphics.hpp>

#include "Drawables/TileBased/TileBased.h"

class Structure : public TileBased
{
public:
	Structure(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viTileDims);
	virtual ~Structure();
};