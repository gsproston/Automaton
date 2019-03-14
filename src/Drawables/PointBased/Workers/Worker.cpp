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
	// preference following a path
	while (!m_vNodes.empty() ||
		!m_vPath.empty())
	{
		// do we have nodes?
		while (!m_vNodes.empty())
		{
			// we have a node, move towards it
			auto itNode = m_vNodes.begin();
			float fRemainingDist = m_fSpeed * elapsedTime.asSeconds();
			// get the distance to the next node
			float fDist = getDistance(m_vfMapPos, (*itNode).vfPos);

			if (fDist < fRemainingDist * (*itNode).fSpeed)
			{
				// we have enough speed to get to the node
				m_vfMapPos = (*itNode).vfPos;
				fRemainingDist -= fDist / (*itNode).fSpeed;
				// remove the node
				m_vNodes.erase(itNode);
			}
			else
			{
				// move towards the node
				sf::Vector2f vfDelta((*itNode).vfPos - m_vfMapPos);
				m_vfMapPos += vfDelta * (fRemainingDist / fDist) * (*itNode).fSpeed;
				return;
			}
		}

		while (!m_vPath.empty())
		{
			// we have tiles
			auto itTile = m_vPath.end() - 1;
			// is the tile passable?
			if ((*itTile)->getSpeedMod() <= 0 &&
				m_vPath.size() > 1 &&
				m_pWorkplace)
			{
				// the tile is not passable, recalculate the path
				m_vPath.clear();	// clear the tiles
				m_vNodes.clear();	// clear the nodes
				m_rMap.getPath(m_vfMapPos, m_pWorkplace->getCentrePos(), m_vPath);
				continue;
			}

			// tile is passable, generate the nodes
			if (m_vPath.size() > 1)
			{
				m_vNodes.push_back(Node(*itTile));
				m_vNodes.push_back(Node(
					((*itTile)->getCentrePos() + (*(itTile - 1))->getCentrePos()) / 2.f,
					(*itTile)->getSpeedMod()
				));
				m_vNodes.push_back(*(itTile - 1));
			}
			else if (m_pWorkplace)
			{
				// this is the last tile
				m_vNodes.push_back(Node(m_pWorkplace->getCentrePos(), 1));
			}
			m_vPath.erase(itTile);
			break;
		}
	}
	
	if (m_pWorkplace)
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