#include "Tree.h"

#include "Constants.h"

Tree::Tree(const sf::Vector2i viTilePos) :
	Workplace(viTilePos,
		sf::Vector2i(0, 1),
		sf::Vector2i(1, 1),
		sf::Vector2i(4, 28)),
	m_fHealth(5.f)
{}


bool Tree::work(const sf::Time elapsedTime) 
{
	m_fHealth -= elapsedTime.asSeconds();
	return m_fHealth <= 0;
}