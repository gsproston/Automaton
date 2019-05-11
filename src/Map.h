#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/Resources/Resource.h"
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

	bool assignTask(std::unique_ptr<Task> pTask);

	bool addResource(std::unique_ptr<Resource> pResource);
	bool removeStructure(Structure& rStructure);

	// pathfinding
	std::vector<Tile*> getPath(const sf::Vector2f vfSource,
		const sf::Vector2f vfSink) const;

private:
	std::vector<std::unique_ptr<Resource>> m_vResources;
	std::vector<std::shared_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_vTiles;
	std::vector<std::unique_ptr<Worker>> m_vWorkersBusy;
	std::vector<std::unique_ptr<Worker>> m_vWorkersFree;

	std::vector<std::unique_ptr<Task>> m_vPendingTasks;

	bool addStructure(std::shared_ptr<Structure> pStructure);
	bool addWorker(std::unique_ptr<Worker> pWorker);
	bool addWorkplace(std::shared_ptr<Workplace> pWorkplace);

	bool assignWorker(std::unique_ptr<Worker> pWorker);

	// pathfinding
	float getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const;
	std::vector<Tile*> getNeighbouringNodes(const sf::Vector2i viTilePos) const;
	Tile* getTile(const sf::Vector2f vfMapPos) const;
	Tile* getTile(const sf::Vector2i viTilePos) const;
};