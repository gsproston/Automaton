#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

class Tile
{
public:
	Tile(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos);
	virtual ~Tile();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	sf::Vector2f getCentrePos() const;
	sf::Vector2i getTilePos() const;

private:
	sf::Vector2i m_viTilePos;
	sf::Vector2i m_viTileMapPos;
};