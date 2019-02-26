#include "Tree.h"

#include "Constants.h"

Tree::Tree(const sf::Vector2i viTilePos) :
	Workplace(viTilePos,
		sf::Vector2i(0, 1),
		sf::Vector2i(TILE_SIZE, TILE_SIZE))
{}


void Tree::work()
{

}