#pragma once

#include <SFML/Graphics.hpp>

#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/PointBased/Resources/Resource.h"

struct StorageBin
{
public:
	StorageBin(const sf::Vector2f vfMapPos) :
		bAvailable(true),
		vfMapPos(vfMapPos)
	{};

	bool available() const
	{
		return bAvailable;
	}

	sf::Vector2f getMapPos() const 
	{
		return vfMapPos;
	}

	bool reserve()
	{
		if (!bAvailable)
			return false;
		bAvailable = false;
		return true;
	}

	bool store(std::shared_ptr<Resource> pResource)
	{
		if (!pResource)
			return false;
		this->pResource = pResource;
		bAvailable = false;
		return true;
	}

private:
	const sf::Vector2f vfMapPos;
	bool bAvailable;
	std::weak_ptr<Resource> pResource;
};

class Storage : public Structure
{
public:
	Storage(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viTileDims,
		const std::vector<sf::Vector2f> vvfBinPos);
	virtual ~Storage();

	std::shared_ptr<StorageBin> available() const;

private:
	std::vector<std::shared_ptr<StorageBin>> m_vpBins;
};