#pragma once

#include "Map/Map.h"
#include "Task.h"

class Move : public Task
{
public:
	Move(const Map& rMap,
		const sf::Vector2f vfDestination);

	bool tick(const sf::Time elapsedTime, Worker& rWorker);
	bool validate(Worker& rWorker);

private:
	const Map& m_rMap;

	std::vector<Node> m_vNodes;
	std::vector<std::shared_ptr<Tile>> m_vPath;
	const sf::Vector2f m_vfDestination;
};
