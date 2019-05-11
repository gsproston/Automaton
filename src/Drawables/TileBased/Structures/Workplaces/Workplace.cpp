#include "Workplace.h"

#include "Drawables/PointBased/Workers/Worker.h"
#include "Map.h"
#include "Utils/Utils.h"

Workplace::Workplace(Map& rMap,
	const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viDimensions,
	const sf::Vector2f vfWorkerPos):
	Structure(viTilePos,
		viTileMapPos,
		viDimensions,
		0),
	m_rMap(rMap),
	m_vfWorkerPos(vfWorkerPos)
{}

Workplace::~Workplace() {}


// returns the worker position on the map
sf::Vector2f Workplace::getWorkerPos() const
{
	return utils::convertTilePosToMapPos(m_viTilePos) + m_vfWorkerPos * (float) TILE_SIZE;
}