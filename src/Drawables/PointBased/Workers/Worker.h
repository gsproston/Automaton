#pragma once

#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/PointBased.h"

class Map;
class Tile;
class Workplace;

class Worker : public PointBased
{
public:
	Worker(const sf::Vector2f vfMapPos, 
		Map& rMap);

	void tick(sf::Time elapsedTime);

	void addVertices(std::vector<sf::Vertex>& rvVertices) const;
	void setWorkplace(Workplace* pWorkplace);

private:
	float m_fSpeed; // pixels per second
	std::vector<std::shared_ptr<Tile>> m_vPath;
	sf::Vector2f vfDestination;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
	// non-owning reference to the map
	Map& m_rMap;
};
