#include "Tile.h"

Tile::Tile(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos, 
	float fSpeedMod):
	TileBased(viTilePos, viTileMapPos,
		sf::Vector2i(1, 1)),
	m_fDefaultSpeedMod(fSpeedMod),
	m_fSpeedMod(fSpeedMod),
	m_pStructure(nullptr)
{}

Tile::~Tile() {}


float Tile::getSpeedMod() const
{
	return m_fSpeedMod;
}

bool Tile::setStructure(Structure* pStructure, bool bOverwrite)
{
	if (m_pStructure && !bOverwrite)
		return false;

	m_pStructure = pStructure;
	if (pStructure == nullptr)
		m_fSpeedMod = m_fDefaultSpeedMod;
	else
		m_fSpeedMod = pStructure->getSpeedMod();
	return true;
}