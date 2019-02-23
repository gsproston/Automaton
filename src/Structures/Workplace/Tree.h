#pragma once

#include "Workplace.h"

class Tree : public Workplace
{
public:
	Tree(const int x, const int y) : Workplace(x, y) {};

	void draw(sf::RenderWindow& window) const;
	void work();
};
