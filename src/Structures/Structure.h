#pragma once

#include <SFML/Graphics.hpp>

class Structure
{
public:
	Structure(const int x, const int y) :
		m_ix(x),
		m_iy(y)
	{}

	virtual void draw(sf::RenderWindow& window) const = 0;

private:
	int m_ix;
	int m_iy;
};