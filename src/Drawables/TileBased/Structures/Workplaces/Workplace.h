#pragma once

#include "../Structure.h"

class Worker;

class Workplace: public Structure
{
public:
	Workplace(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viDimensions);

	virtual void work() = 0;

	bool noWorker();
	void setWorker(Worker* pWorker);

private:
	// non-owning pointer to worker
	Worker* m_pWorker;
};