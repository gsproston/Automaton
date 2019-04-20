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
	while (count < 100)
	{
		int i = rand() % WINDOW_WIDTH;
		int j = rand() % WINDOW_HEIGHT;
		std::unique_ptr<Worker> tmpWorker(new Worker(sf::Vector2f((float)i, (float)j)));
		addWorker(std::move(tmpWorker));
		++count;
	}

	// init the workplaces
	count = 0;
	while (count < 200)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::shared_ptr<Tree> tmpTree(new Tree(sf::Vector2i(i, j)));
		if (addWorkplace(std::move(tmpTree)))
			++count;
	}
}

void Map::tick(const sf::Time elapsedTime)
{
	// tick all the busy workers
	for (auto it = m_vWorkersBusy.begin(); it != m_vWorkersBusy.end();)
	{
		if ((*it)->tick(elapsedTime))
		{
			// this worker has finished working
			std::unique_ptr<Worker> pWorker = std::move(*it);
			// see if we have any tasks for our newly freed worker
			assignWorker(std::move(pWorker));
			// erase from the busy vector
			it = m_vWorkersBusy.erase(it);
		}
		else
		{
			++it;
		}
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
	for (uint32_t i = 0; i < m_vWorkersBusy.size(); ++i)
	{
		m_vWorkersBusy[i]->addVertices(rvVertices);
	}
	for (uint32_t i = 0; i < m_vWorkersFree.size(); ++i)
	{
		m_vWorkersFree[i]->addVertices(rvVertices);
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

bool Map::addWorker(std::unique_ptr<Worker> pWorker)
{
	assignWorker(std::move(pWorker));
	return true;
}

bool Map::addWorkplace(std::shared_ptr<Workplace> pWorkplace)
{
	if (!addStructure(pWorkplace))
		return false;

	// add a work task for this workplace
	std::unique_ptr<Work> pTask(new Work(*this, pWorkplace));
	assignTask(std::move(pTask));
	return true;
}

bool Map::assignTask(std::unique_ptr<Task> pTask)
{
	if (!m_vWorkersFree.empty())
	{
		// ordered map of workers and their distances to the task
		std::map<float, std::vector<std::unique_ptr<Worker>>::iterator> mWorkers;

		// cycle over all workers
		for (auto it = m_vWorkersFree.begin(); it != m_vWorkersFree.end();)
		{
			if (*it)
			{
				if ((*it)->free())
				{
					// get the distance to the task
					float dist = getDistance((*it)->m_vfMapPos, pTask->getMapPos());
					// add it to the map
					mWorkers.insert({ dist, it });
					++it;
				}
				else
				{
					// move to the busy vector
					m_vWorkersBusy.push_back(std::move(*it));
					m_vWorkersFree.erase(it);
				}
			}
			else
			{
				// no worker here, remove it
				m_vWorkersFree.erase(it);
			}
		}

		// now, cycle over our map, returning the first worker who can reach the task
		for (auto it = mWorkers.begin(); it != mWorkers.end(); ++it)
		{
			if (pTask->validate((*(*it).second).get()))
			{
				// assign the task to the worker
				(*(*it).second)->addTaskBack(std::move(pTask));
				// move the worker to the busy vector
				m_vWorkersBusy.push_back(std::move((*(*it).second)));
				// erase it from the free vector
				m_vWorkersFree.erase((*it).second);

				return true;
			}
		}
	}

	// we didn't find a free worker for this task, add to the vector
	m_vPendingTasks.push_back(std::move(pTask));
	return false;
}

bool Map::assignWorker(std::unique_ptr<Worker> pWorker)
{
	if (!m_vPendingTasks.empty() &&
		pWorker->free())
	{
		// ordered map of tasks and their distances to the worker
		std::map<float, std::vector<std::unique_ptr<Task>>::iterator> mTasks;

		// cycle over all tasks
		for (auto it = m_vPendingTasks.begin(); it != m_vPendingTasks.end();)
		{
			if (*it)
			{
				// get the distance to the worker
				float dist = getDistance((*it)->getMapPos(), pWorker->m_vfMapPos);
				// add it to the map
				mTasks.insert({ dist, it });
				++it;
			}
			else
			{
				// no task here, remove it
				m_vPendingTasks.erase(it);
			}
		}

		// now, cycle over our map, returning the first tasks which the worker can reach
		for (auto it = mTasks.begin(); it != mTasks.end(); ++it)
		{
			if ((*(*it).second)->validate(pWorker.get()))
			{
				// assign the task to the worker
				pWorker->addTaskBack(std::move(*(*it).second));
				// erase the task from the vector
				m_vPendingTasks.erase((*it).second);
				// move the worker to the busy vector
				m_vWorkersBusy.push_back(std::move(pWorker));
				return true;
			}
		}
	}

	// we didn't find a task for this worker, add to the free vector
	m_vWorkersFree.push_back(std::move(pWorker));
	return false;
}

// returns true if we were able to delete the structure
bool Map::removeStructure(const std::shared_ptr<Structure> pStructure)
{
	if (!pStructure)
		return false;

	for (auto it = m_vStructures.begin(); it != m_vStructures.end(); ++it)
	{
		if (*it &&
			*it == pStructure)
		{
			m_vStructures.erase(it);
			return true;
		}
	}
	return false;
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