#pragma once

#include "SFML/Graphics.hpp"

#include "Drawables/TileBased/Structures/Structure.h"

class Road : public Structure
{
public:
	Road(const sf::Vector2i viTilePos);
};