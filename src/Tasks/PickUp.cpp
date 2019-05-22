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

	// if we reach here, we're not close to the resource
	// create a task to move to this resource
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, m_vfMapPos));
	if (!pMoveTask->validate(rWorker))
	{
		// cannot find a path, have the map drop the resource
		m_rMap.storeResource(pResource);
		return true;
	}
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

	// see if we can reach the resource
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, m_vfMapPos));
	return pMoveTask->validate(rWorker);
}