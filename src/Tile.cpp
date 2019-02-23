#include "Tile.h"

Tile::Tile(const int x, const int y):
	m_ix(x),
	m_iy(y)
{}

void Tile::draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const
{
	// rectangle shape
	sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1);
	shape.setPosition(sf::Vector2f((float)m_ix*TILE_SIZE + iOffsetX, (float)m_iy*TILE_SIZE + iOffsetY));
	window.draw(shape);
}