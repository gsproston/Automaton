#pragma once

#include "../Structure.h"

class Worker;

class Workplace: public Structure
{
public:
	Workplace(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viDimensions,
		const sf::Vector2i viWorkerPos);
	virtual ~Workplace();

	virtual void work() = 0;

	sf::Vector2f getWorkerPos() const;
	bool noWorker() const;
	void setWorker(Worker* pWorker);

private:
	// non-owning pointer to worker
	Worker* m_pWorker;
	// pixel offset to where the worker should go
	const sf::Vector2i m_viWorkerPos;
};