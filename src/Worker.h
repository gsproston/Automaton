#pragma once

#include <SFML/Graphics.hpp>

class Workplace;

class Worker
{
public:
	Worker(const int x, const int y);

	void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const;
	void tick();

private:
	int m_iSpeed;
	int m_ix;
	int m_iy;

	// non-owning pointer to workplace
	Workplace* m_pWorkplace;
};
