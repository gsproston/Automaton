#include "Storage.h"

#include "Constants.h"

Storage::Storage(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims,
	const std::vector<sf::Vector2f> vvfBinPos) :
	Structure(viTilePos, viTileMapPos, viTileDims, 0)
{
	// create bins for each position given
	for (auto it = vvfBinPos.begin(); it != vvfBinPos.end(); ++it)
	{
		std::unique_ptr<StorageBin> pBin(new StorageBin((*it) * (float)TILE_SIZE + getCentrePos()));
		m_vpBins.push_back(std::move(pBin));
	}
}

Storage::~Storage() {}


std::shared_ptr<StorageBin> Storage::available() const
{
	// cycle over the storage bins, returning the first one that's free
	for (auto it = m_vpBins.begin(); it != m_vpBins.end(); ++it)
	{
		if ((*it) &&
			(*it)->available())
			return (*it);
	}
	return nullptr;
}