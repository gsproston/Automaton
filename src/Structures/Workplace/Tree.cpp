#include "Tree.h"

#include "Constants.h"

Tree::Tree(const int x, const int y) : Workplace(x, y) {};


void Tree::draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const
{
	sf::Texture texture;
	texture.loadFromFile("images/structures/workplaces/tree.png");
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	sprite.setPosition(sf::Vector2f((float)m_ix*TILE_SIZE + iOffsetX, (float)m_iy*TILE_SIZE + iOffsetY));
	window.draw(sprite);
}

void Tree::work()
{

}