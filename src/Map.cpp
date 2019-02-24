#include "Map.h"

#include "Constants.h"
#include "Structures/Workplace/Tree.h"

Map::Map()
{
	// init the m_vTiles
	std::vector<std::unique_ptr<Tile>> vTmp;
	for (int i = 0; i <= WINDOW_WIDTH / TILE_SIZE; i++)
	{
		vTmp.clear();
		for (int j = 0; j <= WINDOW_HEIGHT / TILE_SIZE; j++)
		{
			std::unique_ptr<Tile> tmpTile(new Tile(i, j));
			vTmp.push_back(std::move(tmpTile));
		}
		m_vTiles.push_back(std::move(vTmp));
	}

	// init the structures
	int count = 0;
	while (count < 50)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		std::unique_ptr<Tree> tmpTree(new Tree(i, j));
		m_vStructures.push_back(std::move(tmpTree));
		count++;
	}

	// init the workers
	count = 0;
	while (count < 30)
	{
		int i = rand() % WINDOW_WIDTH;
		int j = rand() % WINDOW_HEIGHT;
		std::unique_ptr<Worker> tmpWorker(new Worker(i, j, *this));
		m_vWorkers.push_back(std::move(tmpWorker));
		count++;
	}
}

void Map::draw(sf::RenderWindow& window) const
{
	// draw all the m_vTiles
	for (int i = 0; i < m_vTiles.size(); i++)
	{
		for (int j = 0; j < m_vTiles[i].size(); j++)
		{
			m_vTiles[i][j]->draw(window, 0, 0);
		}
	}

	// draw all the structures
	for (int i = 0; i < m_vStructures.size(); i++)
	{
		m_vStructures[i]->draw(window, 0, 0);
	}

	// draw all the workers
	for (int i = 0; i < m_vWorkers.size(); i++)
	{
		m_vWorkers[i]->draw(window, 0, 0);
	}
}

void Map::tick()
{
	// tick all the workers
	for (int i = 0; i < m_vWorkers.size(); i++)
	{
		m_vWorkers[i]->tick();
	}
}


bool Map::assignWorkplace(Worker& rWorker, const int x, const int y) const
{
	Workplace* pWorkplace = getClosestFreeWorkplace(x, y);
	if (pWorkplace)
	{
		rWorker.setWorkplace(pWorkplace);
		pWorkplace->setWorker(&rWorker);
		return true;
	}
	return false;
}

Workplace* Map::getClosestFreeWorkplace(const int x, const int y) const
{
	int iMinDist = -1;
	int iTmpDist = -1;
	Workplace* pWorkplace = nullptr;
	Workplace* pTmp = nullptr;

	// cycle over all workplaces, returning the closest one
	for (int i = 0; i < m_vStructures.size(); i++)
	{
		pTmp = dynamic_cast<Workplace*>(m_vStructures[i].get());
		if (pTmp &&
			pTmp->noWorker())
		{
			// we have a workplace, check distance
			iTmpDist = pTmp->getDistance(x, y);
			if (iMinDist < 0 ||
				iMinDist > iTmpDist)
			{
				iMinDist = iTmpDist;
				pWorkplace = pTmp;
			}
		}
	}

	return pWorkplace;
}