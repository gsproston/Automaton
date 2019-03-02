#pragma once

#include "SFML/Graphics.hpp"

class TileBased
{
public:
	TileBased(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viTileDims);
	virtual ~TileBased();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	sf::Vector2f getCentrePos() const;
	sf::Vector2i getTilePos() const;

protected:
	sf::Vector2i m_viTilePos;
	sf::Vector2i m_viTileMapPos;
	sf::Vector2i m_viTileDims;
};
