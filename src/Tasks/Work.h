#pragma once

#include "Drawables/TileBased/Structures/Workplaces/Workplace.h"
#include "Map.h"
#include "Task.h"

class Work : public Task
{
public:
	Work(const Map& rMap,
		std::shared_ptr<Workplace> pWorkplace);

	bool tick(sf::Time elapsedTime, Worker& rWorker);

private:
	const Map& m_rMap;

	// non-owning pointer to the workplace
	std::shared_ptr<Workplace> m_pWorkplace;
};