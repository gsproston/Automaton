#include "Worker.h"

#include "Map.h"
#include "Structures/Workplace/Workplace.h"

Worker::Worker(const float fMapX, const float fMapY, 
	Map& rMap):
	m_fMapX(fMapX),
	m_fMapY(fMapY),
	m_fSpeed(0.25),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{}


void Worker::tick()
{
	if (m_pWorkplace)
	{
		// we have work, are we close to it?
		if (m_pWorkplace->isClose(m_fMapX, m_fMapY))
		{
			// we are! so we can work it
			m_pWorkplace->work();
		}
		else
		{
			// we aren't, move towards it
			m_fMapX += m_pWorkplace->getDirectionX(m_fMapX) * m_fSpeed;
			m_fMapY += m_pWorkplace->getDirectionY(m_fMapY) * m_fSpeed;
		}
	}
	else
	{
		// request workplace
		m_rMap.assignWorkplace(*this, m_fMapX, m_fMapY);
	}
}


void Worker::addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// top point
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f(m_fMapX, m_fMapY - 2)));
	// left point
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f(m_fMapX - 2, m_fMapY + 2)));
	// right point
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f(m_fMapX + 2, m_fMapY + 2)));
}

void Worker::setWorkplace(Workplace* pWorkplace)
{
	m_pWorkplace = pWorkplace;
}