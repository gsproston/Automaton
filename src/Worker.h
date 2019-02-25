#pragma once

#include <SFML/Graphics.hpp>

class Map;
class Workplace;

class Worker
{
public:
	Worker(const float fMapX, const float fMapY, 
		Map& rMap);

	void tick();

	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;
	void setWorkplace(Workplace* pWorkplace);

private:
	float m_fMapX;
	float m_fMapY;
	float m_fSpeed;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
	// non-owning reference to the map
	Map& m_rMap;
};
