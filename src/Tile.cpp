#include "Tile.h"

Tile::Tile() {}

void Tile::draw(sf::RenderWindow& window, const int x, const int y) const
{
	// rectangle shape
	sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1);
	shape.setPosition(sf::Vector2f((float)x, (float)y));
	window.draw(shape);
}