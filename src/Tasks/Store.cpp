#include "Store.h"

#include "Tasks/Move.h"
#include "Tasks/PickUp.h"

Store::Store(Map& rMap,
	std::shared_ptr<Resource> pResource,
	std::shared_ptr<StorageBin> pStorageBin) :
	Task(pResource->getMapPos()),
	m_rMap(rMap),
	m_pResource(pResource),
	m_pStorageBin(pStorageBin)
{}


bool Store::tick(const sf::Time elapsedTime, Worker& rWorker)
{
	std::shared_ptr<Resource> pResource;
	std::shared_ptr<StorageBin> pStorageBin;
	if (!(pResource = m_pResource.lock()) ||
		!(pStorageBin = m_pStorageBin.lock()))
		return true;

	// check that the worker holds the resource
	if (!rWorker.holdsResource(*pResource))
	{
		// create a task to pick it up
		std::unique_ptr<PickUp> pPickUp(new PickUp(m_rMap, pResource));
		if (pPickUp->validate(rWorker))
		{
			// we can pick it up
			rWorker.addTaskFront(std::move(pPickUp));
			return false;
		}
		// we cannot pick it up
		return true;
	}

	// the worker holds the resource, are we close to the bin?
	if (rWorker.getMapPos() == pStorageBin->getMapPos())
	{
		// we are! put the resource in the bin
		pStorageBin->store(pResource);
		rWorker.dropResrouce();
		return true;
	}

	// create a task to move to this place
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, pStorageBin->getMapPos()));
	if (!pMoveTask->validate(rWorker))
	{
		// cannot find a path, drop the resource
		rWorker.dropResrouce();
		m_rMap.storeResource(pResource);
		return true;
	}
	// otherwise, move to the workplace
	rWorker.addTaskFront(std::move(pMoveTask));
	return false;
}

bool Store::validate(Worker& rWorker)
{
	std::shared_ptr<Resource> pResource;
	std::shared_ptr<StorageBin> pStorageBin;
	// must have a workplace and a worker
	if (!(pResource = m_pResource.lock()) ||
		!(pStorageBin = m_pStorageBin.lock()))
		return false;

	// fine if the worker is at the storage bin
	if (rWorker.getMapPos() != pStorageBin->getMapPos())
	{
		// see if we can move to it
		std::unique_ptr<Move> pMove(new Move(m_rMap, pStorageBin->getMapPos()));
		if (!pMove->validate(rWorker))
			return false;
	}

	// check that the worker holds the resource
	if (!rWorker.holdsResource(*pResource))
	{
		// see if we can pick it up
		std::unique_ptr<PickUp> pPickUp(new PickUp(m_rMap, pResource));
		if (!pPickUp->validate(rWorker))
			return false;
	}
	return true;
}