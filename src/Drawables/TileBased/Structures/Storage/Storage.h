#pragma once

#include <SFML/Graphics.hpp>

#include "Drawables/TileBased/Structures/Structure.h"
#include "Drawables/PointBased/Resources/Resource.h"

class Storage : public Structure
{
public:
	Storage(const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viTileDims,
		const std::vector<sf::Vector2f> vvfBinPos);
	virtual ~Storage();

private:
	struct StorageBin
	{
	public:
		StorageBin(const sf::Vector2f vfPos) :
			bReserved(false),
			vfPos(vfPos)
		{};

		bool isAvailable() const
		{
			return (!bReserved && pResource == nullptr);
		};

	private:
		const sf::Vector2f vfPos;
		bool bReserved;
		std::unique_ptr<Resource> pResource;
	};

	std::vector<std::unique_ptr<StorageBin>> m_vpBins;
};