#include "Worker.h"

#include "Map.h"
#include "Utils/Utils.h"

Worker::Worker(const sf::Vector2f vfMapPos):
	PointBased(vfMapPos),
	m_fSpeed(32)
{}


// returns true if the worker is free
bool Worker::tick(sf::Time elapsedTime)
{	
	if (!m_dqpTasks.empty() &&
		m_dqpTasks.front()->tick(elapsedTime, *this))
	{
		// task completed, delete the Task
		m_dqpTasks.pop_front();
		return m_dqpTasks.empty();
	}
	return false;
}


void Worker::addTaskBack(std::unique_ptr<Task> pTask)
{
	m_dqpTasks.push_back(std::move(pTask));
}

void Worker::addTaskFront(std::unique_ptr<Task> pTask)
{
	m_dqpTasks.push_front(std::move(pTask));
}

void Worker::addVertices(std::vector<sf::Vertex>& rvVertices) const
{
	static const uint8_t iSize = 2;

	// top point
	rvVertices.push_back(sf::Vertex(
		m_vfMapPos + sf::Vector2f(0, -iSize)));
	// left point
	rvVertices.push_back(sf::Vertex(
		m_vfMapPos + sf::Vector2f(-iSize, iSize)));
	// right point
	rvVertices.push_back(sf::Vertex(
		m_vfMapPos + sf::Vector2f(iSize, iSize)));
}

bool Worker::free() const
{
	return m_dqpTasks.empty();
}

float Worker::getSpeed() const
{
	return m_fSpeed;
}