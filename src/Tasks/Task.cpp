#include "Task.h"

Task::Task(const sf::Vector2f vfMapPos) :
	m_vfMapPos(vfMapPos)
{}

Task::~Task() {}


sf::Vector2f Task::getMapPos() const
{
	return m_vfMapPos;
}