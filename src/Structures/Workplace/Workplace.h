#pragma once

#include "../Structure.h"

class Worker;

class Workplace: public Structure
{
public:
	Workplace(const int x, const int y) : 
		Structure(x, y),
		m_pWorker(nullptr)
	{}

	virtual void draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const = 0;
	virtual void work() = 0;

private:
	// non-owning pointer to worker
	Worker* m_pWorker;
};