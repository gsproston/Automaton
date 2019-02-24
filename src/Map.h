#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Structures/Structure.h"
#include "Tile.h"

class Map
{
public:
	Map();
	~Map();

	void draw(sf::RenderWindow& window) const;

private:
	std::vector<Structure*> m_vStructures;
	std::vector<std::vector<Tile*>> m_vTiles;
};