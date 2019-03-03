#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/TileBased/Tiles/Tile.h"
#include "Drawables/PointBased/Workers/Worker.h"

namespace std {
	template <>
	struct hash<sf::Vector2f>
	{
		std::size_t operator()(const sf::Vector2f& k) const
		{
			using std::hash;
			return ((hash<float>()(k.x)
				^ (hash<float>()(k.y) << 1)) >> 1);
		}
	};

	template<>
	struct hash<Node>
	{
		std::size_t operator()(const Node& k) const
		{
			using std::hash;
			return hash<sf::Vector2f>()(k.vfMapPos);
		}
	};
}

class Map
{
public:
	Map();

	void tick(sf::Time elapsedTime);

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;
	bool assignWorkplace(Worker& rWorker, 
		const sf::Vector2f vfMapPos, 
		std::vector<Node>& rvPath) const;

	float getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const;
	bool getPath(const sf::Vector2f vfSource, 
		const sf::Vector2f vfSink, 
		std::vector<Node>& rvPath) const;

private:
	std::vector<std::unique_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_vTiles;
	std::vector<std::unique_ptr<Worker>> m_vWorkers;

	bool addStructure(std::unique_ptr<Structure> pStructure);
	Workplace* getClosestFreeWorkplace(const sf::Vector2f vfMapPos,
		std::vector<Node>& rvPath) const;
	std::vector<Node> getNeighbouringNodes(const sf::Vector2i viTilePos) const;
	Tile* getTile(const sf::Vector2f vfMapPos) const;
	Tile* getTile(const sf::Vector2i viTilePos) const;
};