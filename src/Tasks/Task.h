#pragma once

#include <SFML/Graphics.hpp>

class Worker;

class Task
{
public:
	Task(const sf::Vector2f vfMapPos);
	virtual ~Task();

	// returns true when the task is to be deleted
	virtual bool tick(const sf::Time elapsedTime, Worker& rWorker) = 0;
	// returns true if the worker can take this task
	virtual bool validate(Worker& rWorker) = 0;

	sf::Vector2f getMapPos() const { return m_vfMapPos; };

protected:
	const sf::Vector2f m_vfMapPos;
};
