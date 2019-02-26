#include "Worker.h"

#include "Map.h"
#include "Structures/Workplace/Workplace.h"

Worker::Worker(const sf::Vector2f vfMapPos, 
	Map& rMap):
	m_vfMapPos(vfMapPos),
	m_fSpeed(0.25),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{}


void Worker::tick()
{
	if (m_pWorkplace)
	{
		// we have work, are we close to it?
		if (m_pWorkplace->isClose(m_vfMapPos))
		{
			// we are! so we can work it
			m_pWorkplace->work();
		}
		else
		{
			// we aren't, move towards it
			m_vfMapPos += sf::Vector2f(m_pWorkplace->getDirection(m_vfMapPos)) * m_fSpeed;
		}
	}
	else
	{
		// request workplace
		m_rMap.assignWorkplace(*this, m_vfMapPos);
	}
}


void Worker::addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const
{
	static const uint8_t iSize = 2;

	// top point
	rvVertices.push_back(sf::Vertex(
		m_vfMapPos + sf::Vector2f(0, -iSize)));
	// left point
	rvVertices.push_back(sf::Vertex(
		m_vfMapPos + sf::Vector2f(-iSize, iSize)));
	// right point
	rvVertices.push_back(sf::Vertex(
		m_vfMapPos + sf::Vector2f(iSize, iSize)));
}

void Worker::setWorkplace(Workplace* pWorkplace)
{
	m_pWorkplace = pWorkplace;
}