#include "Worker.h"

#include "Map/Map.h"
#include "Utils/Utils.h"

Worker::Worker(const sf::Vector2f vfMapPos):
	PointBased(vfMapPos),
	m_fSpeed(32)
{}


// returns true if the worker is free
bool Worker::tick(const sf::Time elapsedTime)
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

bool Worker::holdsResource(const Resource& rResource) const
{
	std::shared_ptr<Resource> pResource;
	if (!(pResource = m_pResource.lock()))
		return false;
	return (pResource.get() == &rResource);
}

void Worker::move(const sf::Vector2f vfDist)
{
	PointBased::move(vfDist);
	std::shared_ptr<Resource> pResource;
	if (pResource = m_pResource.lock())
		pResource->move(vfDist);
}

bool Worker::pickUp(std::shared_ptr<Resource> pResource)
{
	if (!pResource || holdsResource())
		return false;
	m_pResource = pResource;
	return true;
}
