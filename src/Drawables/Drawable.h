#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class Drawable
{
public: 
	virtual ~Drawable();

	virtual void addVertices(std::vector<sf::Vertex>& rvVertices) const = 0;
};
