#include "Worker.h"

#include "Map.h"
#include "Structures/Workplace/Workplace.h"

Worker::Worker(const int iMapX, const int iMapY, 
	Map& rMap):
	m_iMapX(iMapX),
	m_iMapY(iMapY),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{}


void Worker::tick()
{
	if (m_pWorkplace)
	{
		// we have work, are we close to it?
		if (m_pWorkplace->isClose(m_iMapX, m_iMapY))
		{
			// we are! so we can work it
			m_pWorkplace->work();
		}
		else
		{
			// we aren't, move towards it
			m_iMapX += m_pWorkplace->getDirectionX(m_iMapX);
			m_iMapY += m_pWorkplace->getDirectionY(m_iMapY);
		}
	}
	else
	{
		// request workplace
		m_rMap.assignWorkplace(*this, m_iMapX, m_iMapY);
	}
}


void Worker::addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// top point
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f(m_iMapX, m_iMapY - 2)));
	// left point
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f(m_iMapX - 2, m_iMapY + 2)));
	// right point
	rvVertices.push_back(sf::Vertex(
		sf::Vector2f(m_iMapX + 2, m_iMapY + 2)));
}

void Worker::setWorkplace(Workplace* pWorkplace)
{
	m_pWorkplace = pWorkplace;
}