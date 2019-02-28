#pragma once

#include <SFML/Graphics.hpp>

class Map;
class Workplace;

class Worker
{
public:
	Worker(const sf::Vector2f vfMapPos, 
		Map& rMap);

	void tick();

	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;
	void setWorkplace(Workplace* pWorkplace);

private:
	float m_fSpeed;
	sf::Vector2f m_vfMapPos;
	std::vector<sf::Vector2f> m_vvfPath;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
	// non-owning reference to the map
	Map& m_rMap;
};
