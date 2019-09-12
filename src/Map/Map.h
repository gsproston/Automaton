#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/Resources/Resource.h"
#include "Drawables/TileBased/Structures/Storage/Storage.h"
#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/TileBased/Tiles/Tile.h"
#include "Drawables/PointBased/Workers/Worker.h"
#include "Drawables/TileBased/Structures/Workplaces/Workplace.h"

class Map
{
public:
	Map();

	void loadChunk(const sf::Vector2i& viChunk);

	void tick(const sf::Time elapsedTime);

	void addVertices(std::vector<sf::Vertex>& rvTriangleVertices,
		std::vector<sf::Vertex>& rvQuadVertices) const;

	bool assignTask(std::unique_ptr<Task> pTask);

	bool addResource(std::shared_ptr<Resource> pResource);
	bool assignResource(std::shared_ptr<Resource> pResource);
	bool removeStructure(Structure& rStructure);

	// pathfinding
	std::vector<std::shared_ptr<Tile>> getPath(const sf::Vector2f vfSource,
		const sf::Vector2f vfSink) const;

private:
	sf::Vector2i m_viCurrentChunk;
	std::vector<std::shared_ptr<Structure>> m_vStructures;
	std::array<std::array<std::array<std::array<std::shared_ptr<Tile>, CHUNK_HEIGHT>, CHUNK_WIDTH>, 
		1 + CHUNK_EXTRA_HEIGHT * 2>, 1 + CHUNK_EXTRA_WIDTH * 2> m_vTiles;

	std::vector<std::shared_ptr<Resource>> m_vResources;
	std::vector<std::weak_ptr<Resource>> m_vResourcesPending;
	std::vector<std::unique_ptr<Worker>> m_vWorkersBusy;
	std::vector<std::unique_ptr<Worker>> m_vWorkersFree;

	std::vector<std::weak_ptr<Storage>> m_vStorage;

	std::vector<std::unique_ptr<Task>> m_vPendingTasks;

	bool addStorage(std::shared_ptr<Storage> pStorage);
	bool addStructure(std::shared_ptr<Structure> pStructure);
	bool addWorker(std::unique_ptr<Worker> pWorker);
	bool addWorkplace(std::shared_ptr<Workplace> pWorkplace);

	bool assignStorage(const Storage& rStorage);
	bool assignWorker(std::unique_ptr<Worker> pWorker);

	// pathfinding
	float getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const;
	std::vector<std::shared_ptr<Tile>> getNeighbouringNodes(const sf::Vector2i viTilePos) const;
	std::shared_ptr<Tile> getTile(const sf::Vector2f vfMapPos) const;
	std::shared_ptr<Tile> getTile(const sf::Vector2i viTilePos) const;
};