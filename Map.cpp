#include "Map.h"

#define TILE_SIZE 32

Map::Map()
{
	// init the tiles
	int x = 1280;
	int y = 720;
	std::vector<Tile*> vTmp;
	Tile* newTile = nullptr;

	for (int i = 0; i <= x / TILE_SIZE; i++)
	{
		vTmp.clear();
		for (int j = 0; j <= y / TILE_SIZE; j++)
		{
			newTile = new Tile();
			vTmp.push_back(newTile);
		}
		tiles.push_back(vTmp);
	}
}

Map::~Map()
{
	// delete everything in the vector
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j])
				delete tiles[i][j];
		}
	}
}

void Map::draw(sf::RenderWindow& window)
{
	// draw all the tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			// create rect
			sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			shape.setFillColor(sf::Color::Black);
			shape.setOutlineColor(sf::Color::Green);
			shape.setOutlineThickness(1);
			shape.setPosition(sf::Vector2f(i*TILE_SIZE, j*TILE_SIZE));
			window.draw(shape);
		}
	}
}