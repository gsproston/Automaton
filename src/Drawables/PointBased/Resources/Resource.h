#pragma once

#include <SFML/Graphics.hpp>

#include "Drawables/PointBased/PointBased.h"

class Resource : public PointBased
{
public:
	enum typeEnum { wood };

	Resource(const sf::Vector2f vfMapPos, 
		const sf::Color colour,
		const typeEnum type);
	virtual ~Resource();

	void addVertices(std::vector<sf::Vertex>& rvVertices) const;
	void move(const sf::Vector2f vfDist);

private:
	std::array<sf::Vertex, 6> m_aVertices;
	typeEnum m_type;
};
