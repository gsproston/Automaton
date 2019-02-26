#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos);
	virtual ~Tile();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;

private:
	sf::Vector2i m_viTilePos;
	sf::Vector2i m_viTileMapPos;
};