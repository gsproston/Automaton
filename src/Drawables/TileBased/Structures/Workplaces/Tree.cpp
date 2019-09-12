#include "Tree.h"

#include "Constants.h"
#include "Drawables/PointBased/Resources/Wood.h"
#include "Map/Map.h"

Tree::Tree(Map& rMap,
	const sf::Vector2i viTilePos) :
	Workplace(rMap,
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
		std::shared_ptr<Wood> pWood(new Wood(getCentrePos()));
		m_rMap.addResource(std::move(pWood));
		m_rMap.removeStructure(*this);
		return true;
	}
	return false;
}