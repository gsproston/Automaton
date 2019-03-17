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
	bool setStructure(std::shared_ptr<Structure> pStructure, bool bOverwrite = false);

private:
	const float m_fDefaultSpeedMod;
	float m_fSpeedMod;
	std::shared_ptr<Structure> m_pStructure;
};


struct Node
{
	Node(std::shared_ptr<Tile> pTile)
	{
		vfPos = pTile->getCentrePos();
		fSpeed = pTile->getSpeedMod();
	}

	Node(const sf::Vector2f pos, const float speed)
	{
		vfPos = pos;
		fSpeed = speed;
	}

	sf::Vector2f vfPos;
	float fSpeed;
};