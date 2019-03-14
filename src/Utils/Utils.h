#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

inline sf::Vector2i convertMapPosToTilePos(const sf::Vector2f vfMapPos)
{
	return sf::Vector2i(vfMapPos / (float)TILE_SIZE);
}

inline float getDistance(const sf::Vector2f vfSource, const sf::Vector2f vfDest)
{
	return sqrt(pow(abs(vfSource.x - vfDest.x), 2) +
		pow(abs(vfSource.y - vfDest.y), 2));
}
