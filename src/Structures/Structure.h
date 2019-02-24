#pragma once

#include <SFML/Graphics.hpp>

#include "Worker.h"

class Structure
{
public:
	Structure(const int x, const int y);

	virtual void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const = 0;

	int getDirectionX(const int x) const;
	int getDirectionY(const int y) const;
	int getDistance(const int x, const int y) const;
	bool isClose(const int x, const int y) const;

protected:
	int getCentreX() const;
	int getCentreY() const;

	int m_ix;
	int m_iy;
};