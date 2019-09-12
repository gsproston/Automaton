#pragma once

#include "Task.h"

#include "Drawables/TileBased/Structures/Workplaces/Workplace.h"
#include "Map/Map.h"

class Work : public Task
{
public:
	Work(Map& rMap,
		std::shared_ptr<Workplace> pWorkplace);

	bool tick(const sf::Time elapsedTime, Worker& rWorker);
	bool validate(Worker& rWorker);

private:
	Map& m_rMap;

	// non-owning pointer to the workplace
	std::weak_ptr<Workplace> m_pWorkplace;
};