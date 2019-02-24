#include "Worker.h"

#include "Map.h"
#include "Structures/Workplace/Workplace.h"

Worker::Worker(const int x, const int y, Map& rMap):
	m_iSpeed(10),
	m_ix(x),
	m_iy(y),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{}


void Worker::draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const
{
	sf::CircleShape circle;
	circle.setRadius(2);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1);
	circle.setPosition((float) m_ix + iOffsetX, (float) m_iy + iOffsetY);
	window.draw(circle);
}

void Worker::tick()
{
	if (m_pWorkplace)
	{
		// we have work, are we close to it?
		if (m_pWorkplace->isClose(m_ix, m_iy))
		{
			// we are! so we can work it
			m_pWorkplace->work();
		}
		else
		{
			// we aren't, move towards it
			m_ix += m_pWorkplace->getDirectionX(m_ix);
			m_iy += m_pWorkplace->getDirectionY(m_iy);
		}
	}
	else
	{
		// request workplace
		m_rMap.assignWorkplace(*this, m_ix, m_iy);
	}
}


void Worker::setWorkplace(Workplace* pWorkplace)
{
	m_pWorkplace = pWorkplace;
}