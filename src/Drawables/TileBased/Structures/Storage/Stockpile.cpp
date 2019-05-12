#include "Stockpile.h"

Stockpile::Stockpile(const sf::Vector2i viTilePos) :
	Storage(viTilePos,
		sf::Vector2i(2, 1),
		sf::Vector2i(1, 1),
		{ sf::Vector2f(2 / 8, 2 / 8) })
{}