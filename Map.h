#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
	Map();
	~Map();

	void draw(sf::RenderWindow& window);

private:
	std::vector<std::vector<Tile*>> tiles;
};