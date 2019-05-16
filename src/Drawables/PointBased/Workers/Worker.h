#pragma once

#include <deque>
#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/PointBased.h"
#include "Drawables/PointBased/Resources/Resource.h"
#include "Tasks/Task.h"

class Worker : public PointBased
{
public:
	Worker(const sf::Vector2f vfMapPos);

	bool tick(const sf::Time elapsedTime);

	void addTaskBack(std::unique_ptr<Task> pTask);
	void addTaskFront(std::unique_ptr<Task> pTask);
	void addVertices(std::vector<sf::Vertex>& rvVertices) const;

	void dropResrouce() { m_pResource.reset(); };
	bool hasNoTasks() const { return m_dqpTasks.empty(); };
	bool holdsResource() const { return !m_pResource.expired(); };
	bool holdsResource(const Resource& rResource) const;
	float getSpeed() const { return m_fSpeed; };
	void move(const sf::Vector2f vfDist);
	bool pickUp(std::shared_ptr<Resource> pResource);

private:
	const float m_fSpeed; // pixels per second
	std::deque<std::unique_ptr<Task>> m_dqpTasks;
	std::weak_ptr<Resource> m_pResource;
};
