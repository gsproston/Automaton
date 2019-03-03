#pragma once

#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/PointBased.h"

class Map;
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
	float m_fSpeed;
	std::vector<sf::Vector2f> m_vvfPath;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
	// non-owning reference to the map
	Map& m_rMap;
};
