#pragma once

#include <SFML/Graphics.hpp>

#include "Worker.h"

class Structure
{
public:
	Structure(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viDimensions);
	virtual ~Structure();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	sf::Vector2f getCentrePos() const;

protected:

	sf::Vector2i m_viTilePos;
	sf::Vector2i m_viTileMapPos;
	sf::Vector2i m_viDimensions;
};