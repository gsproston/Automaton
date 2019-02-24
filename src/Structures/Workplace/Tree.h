#pragma once

#include "Workplace.h"

class Tree : public Workplace
{
public:
	Tree(const int x, const int y);

	void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const;
	void work();
};
