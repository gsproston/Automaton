#include "Storage.h"

Storage::Storage(const sf::Vector2i viTilePos,
	const sf::Vector2i viTileMapPos,
	const sf::Vector2i viTileDims,
	const std::vector<sf::Vector2f> vvfBinPos) :
	Structure(viTilePos, viTileMapPos, viTileDims, 0)
{
	// create bins for each position given
	for (auto it = vvfBinPos.begin(); it != vvfBinPos.end(); ++it)
	{
		std::unique_ptr<StorageBin> pBin(new StorageBin(*it));
		m_vpBins.push_back(std::move(pBin));
	}
}

Storage::~Storage() {}