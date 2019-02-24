#include "Map.h"

#include "Constants.h"
#include "Structures/Workplace/Tree.h"

Map::Map()
{
	// init the m_vTiles
	std::vector<Tile*> vTmp;
	Tile* newTile = nullptr;

	for (int i = 0; i <= WINDOW_WIDTH / TILE_SIZE; i++)
	{
		vTmp.clear();
		for (int j = 0; j <= WINDOW_HEIGHT / TILE_SIZE; j++)
		{
			newTile = new Tile(i, j);
			vTmp.push_back(newTile);
		}
		m_vTiles.push_back(vTmp);
	}

	// init the structures
	int count = 0;
	while (count < 50)
	{
		int i = rand() % (WINDOW_WIDTH / TILE_SIZE);
		int j = rand() % (WINDOW_HEIGHT / TILE_SIZE);
		Tree* tmpTree = new Tree(i, j);
		m_vStructures.push_back(tmpTree);
		count++;
	}
}

Map::~Map()
{
	// delete everything in the vector
	for (int i = 0; i < m_vTiles.size(); i++)
	{
		for (int j = 0; j < m_vTiles[i].size(); j++)
		{
			if (m_vTiles[i][j])
				delete m_vTiles[i][j];
		}
	}

	// delete everything in the vector
	for (int i = 0; i < m_vStructures.size(); i++)
	{
		if (m_vStructures[i])
			delete m_vStructures[i];
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
}