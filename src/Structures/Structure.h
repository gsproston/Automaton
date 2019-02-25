#pragma once

#include <SFML/Graphics.hpp>

#include "Worker.h"

class Structure
{
public:
	Structure(const int iTileX, const int iTileY,
		const int iTileMapX, const int iTileMapY,
		const int iHeight, const int iWidth);
	virtual ~Structure();

	void addQuadVertices(std::vector<sf::Vertex>& rvVertices) const;
	int getDirectionX(const int x) const;
	int getDirectionY(const int y) const;
	int getDistance(const int x, const int y) const;
	bool isClose(const int x, const int y) const;

protected:
	int getCentreX() const;
	int getCentreY() const;

	int m_iTileX;
	int m_iTileY;
	int m_iTileMapX;
	int m_iTileMapY;
	int m_iHeight;
	int m_iWidth;
};