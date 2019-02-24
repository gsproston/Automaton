#pragma once

#include <SFML/Graphics.hpp>

class Structure
{
public:
	Structure(const int x, const int y) :
		m_ix(x),
		m_iy(y)
	{}

	virtual void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const = 0;

protected:
	int m_ix;
	int m_iy;
};