#pragma once

#include <array>

#include "SFML/Graphics.hpp"

class TileBased
{
public:
	TileBased(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viTileDims);
	virtual ~TileBased();

	void addVertices(std::vector<sf::Vertex>& rvVertices) const;
	sf::Vector2f getCentrePos() const;
	sf::Vector2i getTilePos() const { return m_viTilePos; };

protected:
	std::array<sf::Vertex, 4> m_aVertices;
	const sf::Vector2i m_viTilePos;
	const sf::Vector2i m_viTileDims;
};
