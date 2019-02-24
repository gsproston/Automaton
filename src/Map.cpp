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
		std::unique_ptr<Worker> tmpWorker(new Worker(i, j));
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