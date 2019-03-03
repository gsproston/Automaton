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
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<float>()(k.x)
				^ (hash<float>()(k.y) << 1)) >> 1);
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
	bool assignWorkplace(Worker& rWorker, const sf::Vector2f vfMapPos) const;

	float getHeuristic(const sf::Vector2f vfSource, const sf::Vector2f vfDest) const;
	std::vector<sf::Vector2f> getPath(const sf::Vector2f vfSource, const sf::Vector2f vfSink) const;

private:
	std::vector<std::unique_ptr<Structure>> m_vStructures;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_vTiles;
	std::vector<std::unique_ptr<Worker>> m_vWorkers;

	bool addStructure(std::unique_ptr<Structure> pStructure);
	Workplace* getClosestFreeWorkplace(const sf::Vector2f vfMapPos) const;
	std::vector<sf::Vector2f> getNeighbouringNodes(const sf::Vector2i viTilePos) const;
	Tile* getTile(const sf::Vector2f vfMapPos) const;
	Tile* getTile(const sf::Vector2i viTilePos) const;
};