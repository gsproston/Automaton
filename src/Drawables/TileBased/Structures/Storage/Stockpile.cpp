#include "Stockpile.h"

Stockpile::Stockpile(const sf::Vector2i viTilePos) :
	Storage(viTilePos,
		sf::Vector2i(2, 1),
		sf::Vector2i(1, 1),
		m_vvfBinPos)
{}

std::vector<sf::Vector2f> createBins()
{
	std::vector<sf::Vector2f> vvfBinPos;
	for (int x = -2; x < 2; ++x)
	{
		for (int y = -2; y < 2; ++y)
		{
			vvfBinPos.push_back(sf::Vector2f(x/8.f, y/8.f));
		}
	}
	return vvfBinPos;
}

const std::vector<sf::Vector2f> Stockpile::m_vvfBinPos = createBins();