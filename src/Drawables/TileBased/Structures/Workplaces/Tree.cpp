#include "Tree.h"

#include "Constants.h"
#include "Drawables/PointBased/Resources/Wood.h"

Tree::Tree(std::vector<std::unique_ptr<Resource>>& rvResources,
	const sf::Vector2i viTilePos) :
	Workplace(rvResources,
		viTilePos,
		sf::Vector2i(0, 1),
		sf::Vector2i(1, 1),
		sf::Vector2f(1.f/8, 7.f/8)),
	m_fHealth(5.f)
{}


bool Tree::work(const sf::Time elapsedTime) 
{
	m_fHealth -= elapsedTime.asSeconds();
	if (m_fHealth <= 0)
	{
		std::unique_ptr<Wood> pWood(new Wood(getCentrePos()));
		m_rvResources.push_back(std::move(pWood));
		return true;
	}
	return false;
}