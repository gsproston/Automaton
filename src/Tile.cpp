#include "Tile.h"

Tile::Tile(const int x, const int y):
	m_ix(x),
	m_iy(y)
{}

void Tile::draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const
{
	sf::Texture texture;
	texture.loadFromFile("images/tiles/grass.png");
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	sprite.setPosition(sf::Vector2f((float)m_ix*TILE_SIZE + iOffsetX, (float)m_iy*TILE_SIZE + iOffsetY));
	//Then, in PlayState::render()
	window.draw(sprite);
}