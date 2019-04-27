#pragma once

#include <array>

#include "SFML/Graphics.hpp"

class PointBased
{
public:
	PointBased(const sf::Vector2f vfMapPos);
	virtual ~PointBased();

	virtual void addVertices(std::vector<sf::Vertex>& rvVertices) const = 0;

	sf::Vector2f m_vfMapPos;
};
