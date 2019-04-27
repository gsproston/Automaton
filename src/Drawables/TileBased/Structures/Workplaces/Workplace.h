#pragma once

#include "Drawables/PointBased/Resources/Resource.h"
#include "Drawables/TileBased/Structures/Structure.h"

class Workplace: public Structure
{
public:
	Workplace(std::vector<std::unique_ptr<Resource>>& rvResources,
		const sf::Vector2i viTilePos,
		const sf::Vector2i viTileMapPos,
		const sf::Vector2i viDimensions,
		const sf::Vector2f vfWorkerPos);
	virtual ~Workplace();

	virtual bool work(const sf::Time elapsedTime) = 0;

	sf::Vector2f getWorkerPos() const;

protected:
	// reference to the resource vector owned by Map
	std::vector<std::unique_ptr<Resource>>& m_rvResources;

private:
	// percent offset to where the worker should go
	const sf::Vector2f m_vfWorkerPos;
};