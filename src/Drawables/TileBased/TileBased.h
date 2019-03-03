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
	sf::Vector2i getTilePos() const;

protected:
	std::array<sf::Vertex, 4> m_aVertices;
	sf::Vector2i m_viTilePos;
	sf::Vector2i m_viTileDims;
};

struct Node
{
	Node() {}
	Node(const sf::Vector2f vfMapPos,
		const float fSpeedMod) :
		vfMapPos(vfMapPos),
		fSpeedMod(fSpeedMod)
	{}

	bool operator==(const Node& rhs) const
	{
		return (vfMapPos == rhs.vfMapPos);
	}

	sf::Vector2f vfMapPos;
	float fSpeedMod;
};
