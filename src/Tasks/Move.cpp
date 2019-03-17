#include "Move.h"

#include "Utils/Utils.h"

Move::Move(const Map& rMap,
	std::vector<std::shared_ptr<Tile>> vPath,
	const sf::Vector2f vfDestination) :
	Task(vfDestination),
	m_rMap(rMap),
	m_vPath(vPath),
	m_vfDestination(vfDestination)
{}


bool Move::tick(const sf::Time elapsedTime, Worker& rWorker)
{
	float fRemainingDist = rWorker.getSpeed() * elapsedTime.asSeconds();

	while (!m_vNodes.empty() ||
		!m_vPath.empty())
	{
		// do we have nodes?
		while (!m_vNodes.empty())
		{
			// we have a node, move towards it
			auto itNode = m_vNodes.begin();
			// get the distance to the next node
			float fDist = getDistance(rWorker.m_vfMapPos, (*itNode).vfPos);

			if (fDist < fRemainingDist * (*itNode).fSpeed)
			{
				// we have enough speed to get to the node
				rWorker.m_vfMapPos = (*itNode).vfPos;
				fRemainingDist -= fDist / (*itNode).fSpeed;
				// remove the node
				m_vNodes.erase(itNode);
			}
			else
			{
				// move towards the node
				sf::Vector2f vfDelta((*itNode).vfPos - rWorker.m_vfMapPos);
				rWorker.m_vfMapPos += vfDelta * (fRemainingDist / fDist) * (*itNode).fSpeed;
				return false;
			}
		}

		while (!m_vPath.empty())
		{
			// we have tiles
			auto itTile = m_vPath.end() - 1;
			// is the tile passable?
			if ((*itTile)->getSpeedMod() <= 0 &&
				m_vPath.size() > 1)
			{
				// the tile is not passable, recalculate the path
				m_vPath.clear();	// clear the tiles
				m_vNodes.clear();	// clear the nodes
				m_vPath = m_rMap.getPath(rWorker.m_vfMapPos, m_vfDestination);
				continue;
			}

			// tile is passable, generate the nodes
			if (m_vPath.size() > 2)
			{
				// many tiles left before the goal
				m_vNodes.push_back(Node(*itTile));
				m_vNodes.push_back(Node(
					((*itTile)->getCentrePos() + (*(itTile - 1))->getCentrePos()) / 2.f,
					(*itTile)->getSpeedMod()
				));
				m_vNodes.push_back(*(itTile - 1));
			}
			else if (m_vPath.size() > 1)
			{
				// two tiles left before the goal
				m_vNodes.push_back(Node(*itTile));
				m_vNodes.push_back(Node(
					((*itTile)->getCentrePos() + (*(itTile - 1))->getCentrePos()) / 2.f,
					(*itTile)->getSpeedMod()
				));
			}
			else
			{
				// this tile is the goal
				m_vNodes.push_back(Node(m_vfDestination, 1));
			}
			m_vPath.erase(itTile);
			break;
		}
	}

	// if we reach here, we have reached the goal
	return true;
}