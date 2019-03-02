#include "Workplace.h"

#include "Drawables/PointBased/Workers/Worker.h"

Workplace::Workplace(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viDimensions):
	Structure(viTilePos,
		viTileMapPos,
		viDimensions),
	m_pWorker(nullptr)
{}

Workplace::~Workplace() {}


bool Workplace::noWorker()
{
	return m_pWorker == nullptr;
}

void Workplace::setWorker(Worker* pWorker)
{
	m_pWorker = pWorker;
}