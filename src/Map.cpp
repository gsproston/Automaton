#include "Map.h"

#include <map>
#include <unordered_map>
#include <unordered_set>

#include "Constants.h"
#include "Utils/Utils.h"

#include "Drawables/TileBased/Structures/Road.h"
#include "Drawables/TileBased/Structures/Storage/Stockpile.h"
#include "Drawables/TileBased/Structures/Workplaces/Tree.h"
#include "Drawables/TileBased/Tiles/Grass.h"

#include "Tasks/Store.h"
#include "Tasks/Work.h"

Map::Map()
{
	//srand((unsigned int) time(0));

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

	// init the stockpiles
	count = 0;
	while (count < 5)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::shared_ptr<Stockpile> tmpStock(new Stockpile(sf::Vector2i(i, j)));
		if (addStorage(std::move(tmpStock)))
			++count;
	}

	// init the workplaces
	count = 0;
	while (count < 200)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::shared_ptr<Tree> tmpTree(new Tree(*this, sf::Vector2i(i, j)));
		if (addWorkplace(std::move(tmpTree)))
			++count;
	}
}

void Map::tick(const sf::Time elapsedTime)
{
	// cannot do this in the loop as it may make the iterators incompatible
	std::vector<std::unique_ptr<Worker>> vWorkersToAssign;
	// tick all the busy workers
	for (auto it = m_vWorkersBusy.begin(); it != m_vWorkersBusy.end();)
	{
		if ((*it)->tick(elapsedTime))
		{
			// this worker has finished working
			vWorkersToAssign.push_back(std::move(*it));
			// erase from the busy vector
			it = m_vWorkersBusy.erase(it);
		}
		else
		{
			++it;
		}
	}

	// reassign all the finished workers
	for (auto it = vWorkersToAssign.begin(); it != vWorkersToAssign.end(); ++it)
	{
		assignWorker(std::move(*it));
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

	// add resources
	for (uint32_t i = 0; i < m_vResources.size(); ++i)
	{
		m_vResources[i]->addVertices(rvVertices);
	}
}

bool Map::addResource(std::shared_ptr<Resource> pResource)
{
	if (!pResource)
		return false;
	m_vResources.push_back(pResource);
	storeResource(pResource);
	return true;
}

bool Map::storeResource(std::shared_ptr<Resource> pResource)
{
	if (!pResource)
		return false;

	if (!m_vStorage.empty())
	{
		std::shared_ptr<Storage> pStorage;
		// ordered map of tasks and their distances to the worker
		std::map<float, std::shared_ptr<Storage>> mStorage;

		// cycle over all storage locations
		for (auto it = m_vStorage.begin(); it != m_vStorage.end();)
		{
			if ((pStorage = (*it).lock()) &&
				pStorage)
			{
				// get the distance to the worker
				float dist = pResource->getDistance(pStorage->getCentrePos());
				// add it to the map
				mStorage.insert({ dist, pStorage });
				++it;
			}
			else
			{
				// no storage location here, remove it
				m_vStorage.erase(it);
			}
		}

		std::shared_ptr<StorageBin> pBin;
		// find the cloest storage location which the resource can be stored in
		for (auto it = mStorage.begin(); it != mStorage.end(); ++it)
		{
			pStorage = (*it).second;
			pBin = pStorage->available();
			if (pBin &&
				pBin->reserve())
			{
				std::unique_ptr<Store> pStore(new Store(*this, pResource, pBin));
				assignTask(std::move(pStore));
				return true;
			}
		}
	}
	// failed to allocate resource to a storage location
	m_vResourcesPending.push_back(pResource);
	return false;
}

bool Map::addStorage(std::shared_ptr<Storage> pStorage)
{
	// TODO look for pending resources
	if (addStructure(pStorage))
	{
		m_vStorage.push_back(pStorage);
		return true;
	}
	return false;
}

bool Map::addStructure(std::shared_ptr<Structure> pStructure)
{
	if (!pStructure)
		return false;

	// non-owning pointer guaranteed to be alive
	Tile* pCurrentTile = getTile(pStructure->getTilePos());
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
	if (!pWorker)
		return false;
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
	if (!pTask)
		return false;

	if (!m_vWorkersFree.empty())
	{
		// ordered map of workers and their distances to the task
		std::map<float, std::vector<std::unique_ptr<Worker>>::iterator> mWorkers;

		// cycle over all workers
		for (auto it = m_vWorkersFree.begin(); it != m_vWorkersFree.end();)
		{
			if (*it)
			{
				if ((*it)->hasNoTasks())
				{
					// get the distance to the task
					float dist = (*it)->getDistance(pTask->getMapPos());
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
			if (pTask->validate(*(*(*it).second)))
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
	if (!pWorker)
		return false;

	if (!m_vPendingTasks.empty() &&
		pWorker->hasNoTasks())
	{
		// ordered map of tasks and their distances to the worker
		std::map<float, std::vector<std::unique_ptr<Task>>::iterator> mTasks;

		// cycle over all tasks
		for (auto it = m_vPendingTasks.begin(); it != m_vPendingTasks.end();)
		{
			if (*it)
			{
				// get the distance to the worker
				float dist = pWorker->getDistance((*it)->getMapPos());
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
			if ((*(*it).second)->validate(*pWorker))
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
bool Map::removeStructure(Structure& rStructure)
{
	for (auto it = m_vStructures.begin(); it != m_vStructures.end(); ++it)
	{
		if ((*it).get() == &rStructure)
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
std::vector<Tile*> Map::getPath(const sf::Vector2f vfSource,
	const sf::Vector2f vfSink) const
{
	Tile* pSourceTile = getTile(vfSource);
	Tile* pSinkTile = getTile(vfSink);

	// set of explored nodes
	std::unordered_set<Tile*> sClosed;
	// set of nodes to be explored
	std::unordered_set<Tile*> sOpen = { pSourceTile };

	// nodes and their previous nodes
	std::unordered_map<Tile*, Tile*> umapCameFrom;

	// cost of going from the start node to this node
	std::unordered_map<Tile*, float> umapGScore;
	umapGScore.insert({ pSourceTile, 0.f });
	// estimated cost of getting to the goal
	std::unordered_map<Tile*, float> umapFScore;
	umapFScore.insert({ pSourceTile, getHeuristic(vfSource, pSinkTile->getCentrePos()) });

	while (!sOpen.empty())
	{
		// get the node with the lowest score
		auto openIt = sOpen.begin();
		float minScore = umapFScore[*openIt];
		{
			auto it = openIt;
			++it;
			for (; it != sOpen.end(); ++it)
			{
				float newScore = umapFScore[*it];
				if (minScore > newScore)
				{
					minScore = newScore;
					openIt = it;
				}
			}
		}

		Tile* pCurrentTile = *openIt;
		if (!pCurrentTile)
			continue;

		const sf::Vector2i viDiff = pCurrentTile->getTilePos() - pSinkTile->getTilePos();
		// check if the node is close enough to the end goal
		if ((viDiff.x == 0 && abs(viDiff.y) == 1) ||
			(viDiff.y == 0 && abs(viDiff.x) == 1) ||
			(viDiff.x == 0 && viDiff.y == 0))
		{
			std::vector<Tile*> vvfPath = { pSinkTile };
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

		std::vector<Tile*> vTiles = getNeighbouringNodes(pCurrentTile->getTilePos());
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
				utils::getDistance(pCurrentTile->getCentrePos(), (*it)->getCentrePos()) /	// divide by the speed mod
				((pCurrentTile->getSpeedMod() + (*it)->getSpeedMod()) / 2.f);				// take the average of the two speed mods

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
			umapFScore[*it] = fTmpGScore +
				getHeuristic((*it)->getCentrePos(), pSinkTile->getCentrePos());
		}
	}

	return {};
}

// returns a vector of all neighbouring tiles
std::vector<Tile*> Map::getNeighbouringNodes(const sf::Vector2i viTilePos) const
{
	std::vector<Tile*> vTiles;
	Tile* pTile;

	for (int8_t i = -1; i <= 1; ++i)
	{
		for (int8_t j = -1; j <= 1; ++j)
		{
			// exclude the given tile
			// and diagonal tiles
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

Tile* Map::getTile(const sf::Vector2f vfMapPos) const
{
	return getTile(utils::convertMapPosToTilePos(vfMapPos));
}

Tile* Map::getTile(const sf::Vector2i viTilePos) const
{
	if (viTilePos.x < m_vTiles.size() &&
		viTilePos.y < m_vTiles[viTilePos.x].size())
	{
		return (m_vTiles[viTilePos.x][viTilePos.y]).get();
	}
	return nullptr;
}