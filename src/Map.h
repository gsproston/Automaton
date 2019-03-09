#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/TileBased/Tiles/Tile.h"
#include "Drawables/PointBased/Workers/Worker.h"

class Map
{
public:
	Map();

	void tick(sf::Time elapsedTime);

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;
	bool assignWorkplace(Worker& rWorker, 
		const sf::Vector2f vfMapPos, 
		std::vector<std::shared_ptr<Tile>>& rvPath) const;

	float getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const;
	bool getPath(const sf::Vector2f vfSource, 
		const sf::Vector2f vfSink, 
		std::vector<std::shared_ptr<Tile>>& rvPath) const;

private:
	std::vector<std::unique_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_vTiles;
	std::vector<std::unique_ptr<Worker>> m_vWorkers;

	bool addStructure(std::unique_ptr<Structure> pStructure);
	Workplace* getClosestFreeWorkplace(const sf::Vector2f vfMapPos,
		std::vector<std::shared_ptr<Tile>>& rvPath) const;
	std::vector<std::shared_ptr<Tile>> getNeighbouringNodes(const sf::Vector2i viTilePos) const;
	std::shared_ptr<Tile> getTile(const sf::Vector2f vfMapPos) const;
	std::shared_ptr<Tile> getTile(const sf::Vector2i viTilePos) const;
};