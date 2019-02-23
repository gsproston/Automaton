#pragma once

#include "../Structure.h"

class Workplace: public Structure
{
public:
	Workplace(const int x, const int y) : Structure(x, y) {}

	virtual void draw(sf::RenderWindow& window) const = 0;
	virtual void work() = 0;

private:
	// TODO pointer to worker
};