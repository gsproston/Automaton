#include "Worker.h"

#include "Map.h"
#include "Drawables/TileBased/Structures/Workplaces/Workplace.h"
#include "Utils/Utils.h"

Worker::Worker(const sf::Vector2f vfMapPos, 
	Map& rMap):
	PointBased(vfMapPos),
	m_fSpeed(32),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{
	// get a workplace
	m_rMap.assignWorkplace(*this, m_vfMapPos, m_vPath);
}


void Worker::tick(sf::Time elapsedTime)
{
	if (!m_vPath.empty())
	{
		// we have a path, move towards it
		auto itNode = m_vPath.end() -1;
		float fRemainingDist = m_fSpeed * elapsedTime.asSeconds();
		// get the distance to the next node
		float fDist = getDistance(m_vfMapPos, (*itNode).vfMapPos);
		
		while (fDist < fRemainingDist * (*itNode).fSpeedMod)
		{
			// move to the point
			m_vfMapPos = (*itNode).vfMapPos;
			fRemainingDist -= fDist / (*itNode).fSpeedMod;

			// get the next point
			m_vPath.erase(itNode);
			if (m_vPath.empty())
				// we have reached our goal
				return;

			// otherwise, get the next node
			itNode = m_vPath.end() - 1;
			fDist = getDistance(m_vfMapPos, (*itNode).vfMapPos);
		}

		// move towards the position
		sf::Vector2f vfDelta((*itNode).vfMapPos - m_vfMapPos);
		m_vfMapPos += vfDelta * (fRemainingDist / fDist) * (*itNode).fSpeedMod;
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


void Worker::addVertices(std::vector<sf::Vertex>& rvVertices) const
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