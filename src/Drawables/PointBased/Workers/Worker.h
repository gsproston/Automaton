#pragma once

#include <deque>
#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/PointBased.h"
#include "Tasks/Task.h"

class Map;

class Worker : public PointBased
{
public:
	Worker(const sf::Vector2f vfMapPos);

	bool tick(sf::Time elapsedTime);

	void addTaskBack(std::unique_ptr<Task> pTask);
	void addTaskFront(std::unique_ptr<Task> pTask);
	void addVertices(std::vector<sf::Vertex>& rvVertices) const;

	bool free() const;
	float getSpeed() const;

private:
	const float m_fSpeed; // pixels per second
	std::deque<std::unique_ptr<Task>> m_dqpTasks;
};
