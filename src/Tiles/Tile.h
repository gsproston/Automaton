#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(const int iTileX, const int iTileY,
		const int iTileMapX, const int iTileMapY);
	virtual ~Tile();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;

private:
	int m_iTileX;
	int m_iTileY;
	int m_iTileMapX;
	int m_iTileMapY;
};