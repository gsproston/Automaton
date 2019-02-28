#include "Worker.h"

#include "Map.h"
#include "Structures/Workplace/Workplace.h"
#include "Utils/Utils.h"

Worker::Worker(const sf::Vector2f vfMapPos, 
	Map& rMap):
	m_fSpeed(0.25),
	m_vfMapPos(vfMapPos),
	m_pWorkplace(nullptr),
	m_rMap(rMap)
{}


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

		sf::Vector2f vfDelta((*itNode) - m_vfMapPos);
		vfDelta.x = vfDelta.x < 0 ? -1.f : 1.f;
		vfDelta.y = vfDelta.y < 0 ? -1.f : 1.f;



		m_vfMapPos += vfDelta * m_fSpeed;
	}
	else if (m_pWorkplace)
	{
		// we have work, are we close to it?
		if (getDistance(m_vfMapPos, m_pWorkplace->getCentrePos()) < 5)
		{
			// we are! so we can work it
			m_pWorkplace->work();
		}
		else
		{
			// we aren't, and we don't have a path, request one
			m_vvfPath = m_rMap.getPath(m_vfMapPos, 
				sf::Vector2f(m_pWorkplace->getCentrePos()));
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