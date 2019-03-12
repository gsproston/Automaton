#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/TileBased/TileBased.h"

class Tile : public TileBased
{
public:
	Tile(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const float fSpeedMod);
	virtual ~Tile();

	float getSpeedMod() const;
	bool setStructure(Structure* pStructure, bool bOverwrite = false);

private:
	const float m_fDefaultSpeedMod;
	float m_fSpeedMod;
	Structure* m_pStructure;
};


struct Node
{
	Node(std::shared_ptr<Tile> pTile)
	{
		vfPos = pTile->getCentrePos();
		fSpeed = pTile->getSpeedMod();
	}

	Node(sf::Vector2f pos, float speed)
	{
		vfPos = pos;
		fSpeed = speed;
	}

	sf::Vector2f vfPos;
	float fSpeed;
};