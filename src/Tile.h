#pragma once

#include <SFML/Graphics.hpp>

#define TILE_SIZE 32

class Tile
{
public:
	Tile();

	void draw(sf::RenderWindow& window, const int x, const int y) const;

private:
	int m_iSpeed;
};