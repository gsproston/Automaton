#pragma once

#include "Storage.h"

class Stockpile : public Storage
{
public:
	Stockpile(const sf::Vector2i viTilePos);

private:
	const static std::vector<sf::Vector2f> m_vvfBinPos;
};