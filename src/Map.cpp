#include "Map.h"

Map::Map()
{
	// init the m_vTiles
	int x = 1280;
	int y = 720;
	std::vector<Tile*> vTmp;
	Tile* newTile = nullptr;

	for (int i = 0; i <= x / TILE_SIZE; i++)
	{
		vTmp.clear();
		for (int j = 0; j <= y / TILE_SIZE; j++)
		{
			newTile = new Tile(i, j);
			vTmp.push_back(newTile);
		}
		m_vTiles.push_back(vTmp);
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
}