#pragma once

#include "Task.h"

#include "Drawables/PointBased/Resources/Resource.h"
#include "Map/Map.h"

class PickUp : public Task
{
public:
	PickUp(Map& rMap,
		std::shared_ptr<Resource> pResource);

	bool tick(const sf::Time elapsedTime, Worker& rWorker);
	bool validate(Worker& rWorker);

private:
	Map& m_rMap;

	// non-owning pointer to the resource
	std::weak_ptr<Resource> m_pResource;
};