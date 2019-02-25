#pragma once

#include <SFML/Graphics.hpp>

class Map;
class Workplace;

class Worker
{
public:
	Worker(const int iMapX, const int iMapY, 
		Map& rMap);

	void tick();

	void addTriangleVertices(std::vector<sf::Vertex>& rvVertices) const;
	void setWorkplace(Workplace* pWorkplace);

private:
	int m_iMapX;
	int m_iMapY;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
	// non-owning reference to the map
	Map& m_rMap;
};
