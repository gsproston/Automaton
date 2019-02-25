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
	int getDirectionX(const float x) const;
	int getDirectionY(const float y) const;
	float getDistance(const float x, const float y) const;
	bool isClose(const float x, const float y) const;

protected:
	float getCentreX() const;
	float getCentreY() const;

	int m_iTileX;
	int m_iTileY;
	int m_iTileMapX;
	int m_iTileMapY;
	int m_iHeight;
	int m_iWidth;
};