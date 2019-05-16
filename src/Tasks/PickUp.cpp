#include "PickUp.h"

#include "Tasks/Move.h"

PickUp::PickUp(Map& rMap,
	std::shared_ptr<Resource> pResource):
	Task(pResource->getMapPos()),
	m_rMap(rMap),
	m_pResource(pResource)
{}


bool PickUp::tick(const sf::Time elapsedTime, Worker& rWorker)
{
	std::shared_ptr<Resource> pResource;
	if (!(pResource = m_pResource.lock()) ||
		rWorker.holdsResource(*pResource))
		return true;

	// check if we're in pickup range
	if (rWorker.getMapPos() == m_vfMapPos)
		// we are! so pick it up
		return rWorker.pickUp(pResource);

	// create a task to move to this place
	std::vector<Tile*> vpPath =
		m_rMap.getPath(rWorker.getMapPos(), m_vfMapPos);

	if (vpPath.empty())
	{
		// cannot find a path, drop the resource
		m_rMap.dropResource(pResource);
		return true;
	}

	// otherwise, move to the resource
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, vpPath, m_vfMapPos));
	rWorker.addTaskFront(std::move(pMoveTask));
	return false;
}

bool PickUp::validate(Worker& rWorker)
{
	std::shared_ptr<Resource> pResource;
	// we must have a resource
	if (!(pResource = m_pResource.lock()))
		return false;
	// fine if the worker is at the resource
	// or the worker already holds the resource
	if (rWorker.getMapPos() == m_vfMapPos ||
		rWorker.holdsResource(*pResource))
		return true;

	// calculate the path to the workplace
	std::vector<Tile*> vpPath =
		m_rMap.getPath(rWorker.getMapPos(), m_vfMapPos);
	if (vpPath.empty())
		// can't find a path, so can't work this
		return false;
	// otherwise, we have a path to the workplace
	std::unique_ptr<Move> moveTask(new Move(m_rMap, vpPath, m_vfMapPos));
	rWorker.addTaskFront(std::move(moveTask));
	return true;
}