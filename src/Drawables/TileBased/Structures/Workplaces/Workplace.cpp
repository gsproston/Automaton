#include "Workplace.h"

#include "Constants.h"
#include "Drawables/PointBased/Workers/Worker.h"

Workplace::Workplace(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viDimensions,
	const sf::Vector2i viWorkerPos):
	Structure(viTilePos,
		viTileMapPos,
		viDimensions,
		0),
	m_pWorker(nullptr),
	m_viWorkerPos(viWorkerPos)
{}

Workplace::~Workplace() {}


// returns the worker position on the map
sf::Vector2f Workplace::getWorkerPos() const
{
	return sf::Vector2f(m_viTilePos * TILE_SIZE + m_viWorkerPos);
}

bool Workplace::noWorker() const
{
	return m_pWorker == nullptr;
}

void Workplace::setWorker(Worker* pWorker)
{
	m_pWorker = pWorker;
}