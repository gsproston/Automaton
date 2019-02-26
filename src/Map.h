#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Structures/Structure.h"
#include "Tiles/Tile.h"
#include "Worker.h"

class Map
{
public:
	Map();

	void tick();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;
	bool assignWorkplace(Worker& rWorker, const sf::Vector2f vfMapPos) const;

private:
	std::vector<std::unique_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_vTiles;
	std::vector<std::unique_ptr<Worker>> m_vWorkers;

	Workplace* getClosestFreeWorkplace(const sf::Vector2f vfMapPos) const;
};