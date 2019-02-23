#pragma once

#include <SFML/Graphics.hpp>

#define TILE_SIZE 32

class Tile
{
public:
	Tile(const int x, const int y);

	void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const;

private:
	int m_iSpeed;
	int m_ix;
	int m_iy;
};