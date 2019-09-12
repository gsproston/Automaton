#pragma once

#include "Task.h"

#include "Drawables/PointBased/Resources/Resource.h"
#include "Drawables/TileBased/Structures/Storage/Storage.h"
#include "Map/Map.h"

class Store : public Task
{
public:
	Store(Map& rMap,
		std::shared_ptr<Resource> pResource,
		std::shared_ptr<StorageBin> pStorageBin);

	bool tick(const sf::Time elapsedTime, Worker& rWorker);
	bool validate(Worker& rWorker);

private:
	Map& m_rMap;

	// non-owning pointer to the resource
	std::weak_ptr<Resource> m_pResource;
	// non-owning pointer to the storage bin
	std::weak_ptr<StorageBin> m_pStorageBin;
};