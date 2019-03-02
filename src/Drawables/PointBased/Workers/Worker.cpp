#include "Worker.h"

#include "Map.h"
#include "Drawables/TileBased/Structures/Workplaces/Workplace.h"
#include "Utils/Utils.h"

Worker::Worker(const sf::Vector2f vfMapPos, 
	Map& rMap):
	PointBased(vfMapPos),
	m_fSpeed(0.25),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{
	// get a workplace
	m_rMap.assignWorkplace(*this, m_vfMapPos);
	// get a path to the workplace
	if (m_pWorkplace)
	{
		m_vvfPath = m_rMap.getPath(m_vfMapPos,
			m_pWorkplace->getCentrePos());
	}
}


void Worker::tick()
{
	if (!m_vvfPath.empty())
	{
		// we have a path, move towards it
		auto itNode = m_vvfPath.end() -1;
		float fRemainingDist = m_fSpeed;
		// check if we're in range of the next node
		float fDist = getDistance(m_vfMapPos, (*itNode));

		while (fDist < fRemainingDist)
		{
			// move to the point
			m_vfMapPos = (*itNode);
			fRemainingDist -= fDist;

			// get the next point
			m_vvfPath.erase(itNode);
			if (m_vvfPath.empty())
				// we have reached our goal
				return;

			// otherwise, get the next node
			itNode = m_vvfPath.end() - 1;
			fDist = getDistance(m_vfMapPos, (*itNode));
		}

		// move towards the position
		sf::Vector2f vfDelta((*itNode) - m_vfMapPos);
		m_vfMapPos += vfDelta * (fRemainingDist / fDist);
	}
	else if (m_pWorkplace)
	{
		// we have work, are we close to it?
		if (getDistance(m_vfMapPos, m_pWorkplace->getCentrePos()) < 5)
		{
			// we are! so we can work it
			m_pWorkplace->work();
		}
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