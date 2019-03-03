#include "Road.h"

Road::Road(const sf::Vector2i viTilePos):
	Structure(viTilePos, 
		sf::Vector2i(1, 1), 
		sf::Vector2i(1, 1),
		2.f)
{}