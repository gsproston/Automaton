#pragma once

#include "Workplace.h"

class Tree : public Workplace
{
public:
	Tree(const sf::Vector2i viTIlePos);

	bool work(const sf::Time elapsedTime);

private:
	float m_fHealth; // number of seconds to destroy
};
