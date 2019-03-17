#include "Map.h"

#include <map>
#include <unordered_map>
#include <unordered_set>

#include "Constants.h"
#include "Utils/Utils.h"

#include "Drawables/TileBased/Structures/Road.h"
#include "Drawables/TileBased/Structures/Workplaces/Tree.h"
#include "Drawables/TileBased/Tiles/Grass.h"

#include "Tasks/Work.h"

Map::Map()
{
	// init the m_vTiles
	std::vector<std::shared_ptr<Tile>> vTmp;
	for (int i = 0; i <= WINDOW_WIDTH / TILE_SIZE; ++i)
	{
		vTmp.clear();
		for (int j = 0; j <= WINDOW_HEIGHT / TILE_SIZE; ++j)
		{
			std::shared_ptr<Tile> tmpTile(new Grass(sf::Vector2i(i, j)));
			vTmp.push_back(tmpTile);
		}
		m_vTiles.push_back(vTmp);
	}

	// put in roads
	for (int i = 0; i <= WINDOW_WIDTH / TILE_SIZE; ++i)
	{
		const static int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::shared_ptr<Road> tmpRoad(new Road(sf::Vector2i(i, j)));
		addStructure(std::move(tmpRoad));
	}

	// init the workers
	int count = 0;
	while (count < 200)
	{
		int i = rand() % WINDOW_WIDTH;
		int j = rand() % WINDOW_HEIGHT;
		std::unique_ptr<Worker> tmpWorker(new Worker(sf::Vector2f((float)i, (float)j)));
		m_vWorkers.push_back(std::move(tmpWorker));
		++count;
	}

	// init the structures
	count = 0;
	while (count < 200)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::shared_ptr<Tree> tmpTree(new Tree(sf::Vector2i(i, j)));
		if (addStructure(tmpTree))
		{
			++count;
			// create task to work this
			std::unique_ptr<Work> pTask(new Work(*this, tmpTree));
			addTask(std::move(pTask));
		}
	}
}

void Map::tick(const sf::Time elapsedTime)
{
	// tick all the workers
	for (int i = 0; i < m_vWorkers.size(); ++i)
	{
		m_vWorkers[i]->tick(elapsedTime);
	}
}


void Map::addQuadVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// add tile vertices
	for (uint32_t i = 0; i < m_vTiles.size(); ++i)
	{
		for (uint32_t j = 0; j < m_vTiles[i].size(); ++j)
		{
			m_vTiles[i][j]->addVertices(rvVertices);
		}
	}

	// add structure vertices
	for (uint32_t i = 0; i < m_vStructures.size(); ++i)
	{
		m_vStructures[i]->addVertices(rvVertices);
	}
}

void Map::addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const
{
	// add worker vertices
	for (uint32_t i = 0; i < m_vWorkers.size(); ++i)
	{
		m_vWorkers[i]->addVertices(rvVertices);
	}
}

bool Map::addStructure(std::shared_ptr<Structure> pStructure)
{
	std::shared_ptr<Tile> pCurrentTile = getTile(pStructure->getTilePos());
	if (pCurrentTile &&
		pCurrentTile->setStructure(pStructure))
	{
		m_vStructures.push_back(std::move(pStructure));
		return true;
	}
	return false;
}

bool Map::addTask(std::unique_ptr<Task> pTask)
{
	// attempt to assign to the closest free worker
	float dist = -1.f;
	Worker* pWorker = nullptr;
	// cycle over all workers
	for (auto it = m_vWorkers.begin(); it != m_vWorkers.end(); ++it)
	{
		if ((*it) && (*it)->free() &&
			(dist < 0 || getDistance((*it)->m_vfMapPos, pTask->getMapPos()) < dist))
		{
			dist = getDistance((*it)->m_vfMapPos, pTask->getMapPos());
			pWorker = (*it).get();
		}
	}

	if (pWorker)
	{
		pWorker->addTaskBack(std::move(pTask));
		return true;
	}
	else
	{
		// add to the vector
		m_vPendingTasks.push_back(std::move(pTask));
		return false;
	}
}


// pathfinding

// heuristic must be admissable - never overestimates the path to the goal
float Map::getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const
{
	// return manhattan distance, devided by the best speed modifier
	return (abs(vfSource.x - vfDest.x) + abs(vfSource.y - vfDest.y)) / BEST_SPEED_MOD;
}

// returns a vector of coordinates to follow to get from source to sink
// if no path is found, returns an empty vector
std::vector<std::shared_ptr<Tile>> Map::getPath(const sf::Vector2f vfSource,
	const sf::Vector2f vfSink) const
{
	std::shared_ptr<Tile> pSourceTile = getTile(vfSource);
	std::shared_ptr<Tile> pSinkTile = getTile(vfSink);

	// set of explored nodes
	std::unordered_set<std::shared_ptr<Tile>> sClosed;
	// set of nodes to be explored
	std::unordered_set<std::shared_ptr<Tile>> sOpen = { pSourceTile };

	// nodes and their previous nodes
	std::unordered_map<std::shared_ptr<Tile>, std::shared_ptr<Tile>> umapCameFrom;

	// cost of going from the start node to this node
	std::unordered_map<std::shared_ptr<Tile>, float> umapGScore;
	umapGScore.insert({ pSourceTile, 0 });
	// estimated cost of getting to the goal
	std::unordered_map<std::shared_ptr<Tile>, float> umapFScore;
	umapFScore.insert({ pSourceTile, getHeuristic(vfSource, pSinkTile->getCentrePos()) });

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

		std::shared_ptr<Tile> pCurrentTile = *openIt;
		if (!pCurrentTile)
			continue;

		// check if the node is close enough to the end goal
		if (getDistance(pCurrentTile->getCentrePos(), pSinkTile->getCentrePos()) <= TILE_SIZE)
		{
			std::vector<std::shared_ptr<Tile>> vvfPath = { pSinkTile };
			if (pSinkTile != pCurrentTile &&
				pSourceTile != pCurrentTile)
				vvfPath.push_back(pCurrentTile);
			while (umapCameFrom.find(pCurrentTile) != umapCameFrom.end())
			{
				pCurrentTile = umapCameFrom[pCurrentTile];
				vvfPath.push_back(pCurrentTile);
			}
			return vvfPath;
		}

		// add the current tile to the list of evaluated tiles
		sOpen.erase(openIt);
		sClosed.insert(pCurrentTile);

		std::vector<std::shared_ptr<Tile>> vTiles = getNeighbouringNodes(pCurrentTile->getTilePos());
		if (pCurrentTile == pSourceTile &&
			pCurrentTile->getSpeedMod() > 0)
			vTiles.push_back(pCurrentTile);
		for (auto it = vTiles.begin(); it != vTiles.end(); ++it)
		{
			// ignore evaluated nodes
			if (sClosed.find(*it) != sClosed.end())
				continue;

			// get the distance from the start node
			float fTmpGScore = umapGScore[pCurrentTile] + 
				getDistance(pCurrentTile->getCentrePos(), (*it)->getCentrePos()) /	// divide by the speed mod
				((pCurrentTile->getSpeedMod() + (*it)->getSpeedMod()) / 2.f);		// take the average of the two speed mods

			if (sOpen.find(*it) == sOpen.end())
				// this node is new
				sOpen.insert(*it);
			else if (fTmpGScore >= umapGScore[*it])
				// this node has a worse score
				continue;

			// if we reach here, this node has the best score
			auto cameIt = umapCameFrom.find(*it);
			if (cameIt != umapCameFrom.end())
				(*cameIt).second = pCurrentTile;
			else if (pCurrentTile->getSpeedMod() > 0)
				umapCameFrom.insert({ *it, pCurrentTile });
			umapGScore[*it] = fTmpGScore;
			umapFScore[*it] = umapGScore[*it] + 
				getHeuristic((*it)->getCentrePos(), pSinkTile->getCentrePos());
		}
	}

	return {};
}

// returns a vector of all neighbouring tiles
std::vector<std::shared_ptr<Tile>> Map::getNeighbouringNodes(const sf::Vector2i viTilePos) const
{
	std::vector<std::shared_ptr<Tile>> vTiles;
	std::shared_ptr<Tile> pTile;

	for (int8_t i = -1; i <= 1; ++i)
	{
		for (int8_t j = -1; j <= 1; ++j)
		{
			// exclude the given tile
			if (i == 0 && j == 0 ||
				i != 0 && j != 0)
				continue;

			pTile = getTile(viTilePos + sf::Vector2i(i, j));
			if (pTile && pTile->getSpeedMod() > 0)
				vTiles.push_back(pTile);
		}
	}

	return vTiles;
}

std::shared_ptr<Tile> Map::getTile(const sf::Vector2f vfMapPos) const
{
	return getTile(convertMapPosToTilePos(vfMapPos));
}

std::shared_ptr<Tile> Map::getTile(const sf::Vector2i viTilePos) const
{
	if (viTilePos.x < m_vTiles.size() &&
		viTilePos.y < m_vTiles[viTilePos.x].size())
	{
		return m_vTiles[viTilePos.x][viTilePos.y];
	}
	return nullptr;
}