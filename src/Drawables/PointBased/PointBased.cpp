#include "PointBased.h"

#include "Utils/Utils.h"

PointBased::PointBased(const sf::Vector2f vfMapPos):
	m_vfMapPos(vfMapPos)
{}

PointBased::~PointBased() {}


float PointBased::getDistance(const sf::Vector2f vfMapPos) const
{
	return utils::getDistance(vfMapPos, m_vfMapPos);
}