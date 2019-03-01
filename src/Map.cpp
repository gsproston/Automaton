#include "Map.h"

#include <unordered_map>
#include <unordered_set>

#include "Constants.h"
#include "Structures/Workplace/Tree.h"
#include "Tiles/Grass.h"
#include "Utils/Utils.h"

Map::Map()
{
	// init the m_vTiles
	std::vector<std::unique_ptr<Tile>> vTmp;
	for (int i = 0; i <= WINDOW_WIDTH / TILE_SIZE; ++i)
	{
		vTmp.clear();
		for (int j = 0; j <= WINDOW_HEIGHT / TILE_SIZE; ++j)
		{
			std::unique_ptr<Tile> tmpTile(new Grass(sf::Vector2i(i, j)));
			vTmp.push_back(std::move(tmpTile));
		}
		m_vTiles.push_back(std::move(vTmp));
	}

	// init the structures
	int count = 0;
	while (count < 200)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::unique_ptr<Tree> tmpTree(new Tree(sf::Vector2i(i, j)));
		if (addStructure(std::move(tmpTree)))
			++count;
	}

	// init the workers
	count = 0;
	while (count < 100)
	{
		int i = rand() % WINDOW_WIDTH;
		int j = rand() % WINDOW_HEIGHT;
		std::unique_ptr<Worker> tmpWorker(
			new Worker(sf::Vector2f((float) i, (float) j), *this));
		m_vWorkers.push_back(std::move(tmpWorker));
		++count;
	}
}

void Map::tick()
{
	// tick all the workers
	for (int i = 0; i < m_vWorkers.size(); ++i)
	{
		m_vWorkers[i]->tick();
	}
}


void Map::addQuadVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// add tile vertices
	for (uint32_t i = 0; i < m_vTiles.size(); ++i)
	{
		for (uint32_t j = 0; j < m_vTiles[i].size(); ++j)
		{
			m_vTiles[i][j]->addQuadVertices(rvVertices);
		}
	}

	// add structure vertices
	for (uint32_t i = 0; i < m_vStructures.size(); ++i)
	{
		m_vStructures[i]->addQuadVertices(rvVertices);
	}
}

bool Map::addStructure(std::unique_ptr<Structure> pStructure)
{
	Tile* pTmpTile = getTile(pStructure->getTilePos());
	if (pTmpTile &&
		pTmpTile->m_bPassable)
	{
		pTmpTile->m_bPassable = false;
		m_vStructures.push_back(std::move(pStructure));
		return true;
	}
	return false;
}

void Map::addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// add worker vertices
	for (uint32_t i = 0; i < m_vWorkers.size(); ++i)
	{
		m_vWorkers[i]->addTriangleVertices(rvVertices);
	}
}

bool Map::assignWorkplace(Worker& rWorker, const sf::Vector2f vfMapPos) const
{
	Workplace* pWorkplace = getClosestFreeWorkplace(vfMapPos);
	if (pWorkplace)
	{
		rWorker.setWorkplace(pWorkplace);
		pWorkplace->setWorker(&rWorker);
		return true;
	}
	return false;
}

Workplace* Map::getClosestFreeWorkplace(const sf::Vector2f vfMapPos) const
{
	float fMinDist = -1;
	float fTmpDist = -1;
	Workplace* pWorkplace = nullptr;
	Workplace* pTmp = nullptr;

	// cycle over all workplaces, returning the closest one
	for (int i = 0; i < m_vStructures.size(); ++i)
	{
		pTmp = dynamic_cast<Workplace*>(m_vStructures[i].get());
		if (pTmp &&
			pTmp->noWorker())
		{
			// we have a workplace, check distance
			fTmpDist = getDistance(vfMapPos, pTmp->getCentrePos());
			if (fMinDist < 0 ||
				fMinDist > fTmpDist)
			{
				fMinDist = fTmpDist;
				pWorkplace = pTmp;
			}
		}
	}

	return pWorkplace;
}

// returns a vector of coordinates to follow to get from source to sink
std::vector<sf::Vector2f> Map::getPath(
	const sf::Vector2f vfSource, const sf::Vector2f vfSink) const
{
	// set of explored nodes
	std::unordered_set<sf::Vector2f> sClosed;
	// set of nodes to be explored
	std::unordered_set<sf::Vector2f> sOpen = { vfSource };

	// nodes and their previous nodes
	std::unordered_map<sf::Vector2f, sf::Vector2f> umapCameFrom;

	// cost of going from the start node to this node
	std::unordered_map<sf::Vector2f, float> umapGScore;
	umapGScore.insert({ vfSource, 0 });
	// estimated cost of getting to the goal
	std::unordered_map<sf::Vector2f, float> umapFScore;
	umapFScore.insert({ vfSource, getHeuristic(vfSource, vfSink) });

	while (!sOpen.empty())
	{
		// get the node with the lowest score
		auto openIt = sOpen.begin();
		float minScore = umapFScore[*sOpen.begin()];
		for (auto it = sOpen.begin(); it != sOpen.end(); ++it)
		{
			float newScore = umapFScore[*it];
			if (minScore > newScore)
			{
				minScore = newScore;
				openIt = it;
			}
		}

		// check if the node is close enough to the end goal
		sf::Vector2f vfCurrentPos = *openIt;
		if (getDistance(vfCurrentPos, vfSink) <= TILE_SIZE)
		{
			std::vector<sf::Vector2f> vvfPath = { vfSink };
			vvfPath.push_back(vfCurrentPos);
			while (umapCameFrom.find(vfCurrentPos) != umapCameFrom.end())
			{
				vfCurrentPos = umapCameFrom[vfCurrentPos];
				vvfPath.push_back(vfCurrentPos);
			}
			return vvfPath;
		}

		// add the current tile to the list of evaluated tiles
		sOpen.erase(openIt);
		sClosed.insert(vfCurrentPos);

		Tile* pTmpTile = getTile(vfCurrentPos);
		if (!pTmpTile)
			continue;

		std::vector<sf::Vector2f> vfNodes = getNeighbouringNodes(pTmpTile->getTilePos());
		if (vfCurrentPos == vfSource)
			vfNodes.push_back(pTmpTile->getCentrePos());
		for (auto it = vfNodes.begin(); it != vfNodes.end(); ++it)
		{
			// ignore evaluated nodes
			if (sClosed.find(*it) != sClosed.end())
				continue;

			// get the distance from the start node
			float fTmpGScore = umapGScore[vfCurrentPos] + 
				getHeuristic(vfCurrentPos,(*it));

			if (sOpen.find(*it) == sOpen.end())
				// this node is new
				sOpen.insert(*it);
			else if (fTmpGScore >= umapGScore[*it])
				// this node has a worse score
				continue;

			// if we reach here, this node has the best score
			auto cameIt = umapCameFrom.find(*it);
			if (cameIt != umapCameFrom.end())
				(*cameIt).second = vfCurrentPos;
			else
				umapCameFrom.insert({ *it, vfCurrentPos });
			umapGScore[*it] = fTmpGScore;
			umapFScore[*it] = umapGScore[*it] + 
				getHeuristic((*it), vfSink);
		}
	}

	return {};
}

// returns a vector of all neighbouring tiles
std::vector<sf::Vector2f> Map::getNeighbouringNodes(const sf::Vector2i viTilePos) const
{
	std::vector<sf::Vector2f> vfNodes;
	Tile* pTile;

	for (int8_t i = -1; i <= 1; ++i)
	{
		for (int8_t j = -1; j <= 1; ++j)
		{
			// exclude the given tile
			if (i == 0 && j == 0 ||
				i != 0 && j != 0)
				continue;

			pTile = getTile(viTilePos + sf::Vector2i(i, j));
			if (pTile && pTile->m_bPassable)
				vfNodes.push_back(pTile->getCentrePos());
		}
	}

	return vfNodes;
}

Tile* Map::getTile(const sf::Vector2f vfMapPos) const
{
	return getTile(convertMapPosToTilePos(vfMapPos));
}

Tile* Map::getTile(const sf::Vector2i viTilePos) const
{
	if (viTilePos.x < m_vTiles.size() &&
		viTilePos.y < m_vTiles[viTilePos.x].size())
	{
		return m_vTiles[viTilePos.x][viTilePos.y].get();
	}
	return nullptr;
}

float Map::getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const
{
	// return manhattan distance
	return abs(vfSource.x - vfDest.x) + abs(vfSource.y - vfDest.y);
}