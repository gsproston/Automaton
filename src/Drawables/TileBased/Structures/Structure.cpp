#include "Structure.h"

#include "Constants.h"

Structure::Structure(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims,
	const float fSpeedMod):
	TileBased(viTilePos, viTileMapPos, viTileDims),
	m_fSpeedMod(fSpeedMod)
{}

Structure::~Structure() {}


float Structure::getSpeedMod() const
{
	return m_fSpeedMod;
}