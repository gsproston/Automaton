#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Structures/Structure.h"
#include "Tile.h"

class Map
{
public:
	Map();

	void draw(sf::RenderWindow& window) const;

private:
	std::vector<std::unique_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_vTiles;
};