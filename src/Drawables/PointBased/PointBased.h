#pragma once

#include <array>

#include "SFML/Graphics.hpp"

class PointBased
{
public:
	PointBased(const sf::Vector2f vfMapPos);
	virtual ~PointBased();

	virtual void addVertices(std::vector<sf::Vertex>& rvVertices) const = 0;
	void move(const sf::Vector2f vfDist) { m_vfMapPos += vfDist; };

	float getDistance(const sf::Vector2f vfMapPos) const;
	sf::Vector2f getMapPos() const { return m_vfMapPos; };

protected:
	sf::Vector2f m_vfMapPos;
};
