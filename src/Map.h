#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/TileBased/Tiles/Tile.h"
#include "Drawables/PointBased/Workers/Worker.h"
#include "Drawables/TileBased/Structures/Workplaces/Workplace.h"

class Map
{
public:
	Map();

	void tick(const sf::Time elapsedTime);

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;

	// pathfinding
	std::vector<std::shared_ptr<Tile>> getPath(const sf::Vector2f vfSource,
		const sf::Vector2f vfSink) const;

private:
	std::vector<std::shared_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_vTiles;
	std::vector<std::unique_ptr<Worker>> m_vWorkersBusy;
	std::vector<std::unique_ptr<Worker>> m_vWorkersFree;

	std::vector<std::unique_ptr<Task>> m_vPendingTasks;

	bool addStructure(std::shared_ptr<Structure> pStructure);
	bool addWorker(std::unique_ptr<Worker> pWorker);
	bool addWorkplace(std::shared_ptr<Workplace> pWorkplace);

	bool assignTask();

	// pathfinding
	float getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const;
	std::vector<std::shared_ptr<Tile>> getNeighbouringNodes(const sf::Vector2i viTilePos) const;
	std::shared_ptr<Tile> getTile(const sf::Vector2f vfMapPos) const;
	std::shared_ptr<Tile> getTile(const sf::Vector2i viTilePos) const;
};