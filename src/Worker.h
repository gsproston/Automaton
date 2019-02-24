#pragma once

#include <SFML/Graphics.hpp>

class Map;
class Workplace;

class Worker
{
public:
	Worker(const int x, const int y, Map& rMap);

	void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const;
	void tick();

	void setWorkplace(Workplace* pWorkplace);

private:
	int m_iSpeed;
	int m_ix;
	int m_iy;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
	// non-owning reference to the map
	Map& m_rMap;
};
