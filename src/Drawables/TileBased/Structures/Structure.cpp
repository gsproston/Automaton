#include "Structure.h"

#include "Constants.h"

Structure::Structure(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims):
	TileBased(viTilePos, viTileMapPos, viTileDims)
{}

Structure::~Structure() {}