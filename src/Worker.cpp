#include "Worker.h"

#include "Structures/Workplace/Workplace.h"

Worker::Worker(const int x, const int y):
	m_iSpeed(50),
	m_ix(x),
	m_iy(y),
	m_pWorkplace(nullptr)
{}


void Worker::draw(sf::RenderWindow& window, const int iOffsetX, const int iOffsetY) const
{
	sf::CircleShape circle;
	circle.setRadius(2);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1);
	circle.setPosition((float) m_ix + iOffsetX, (float) m_iy + iOffsetY);
	window.draw(circle);
}

void Worker::tick()
{

}