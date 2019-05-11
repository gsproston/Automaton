#include "Work.h"

#include "Move.h"
#include "Utils/Utils.h"

Work::Work(Map& rMap,
	std::shared_ptr<Workplace> pWorkplace) :
	Task(pWorkplace->getCentrePos()),
	m_rMap(rMap),
	m_pWorkplace(pWorkplace)
{}


bool Work::tick(const sf::Time elapsedTime, Worker& rWorker)
{
	std::shared_ptr<Workplace> pWorkplace;
	if (!(pWorkplace = m_pWorkplace.lock()))
		return true;

	// we have work, are we close to it?
	if (rWorker.getMapPos() == pWorkplace->getWorkerPos())
		// we are! so we can work it
		return pWorkplace->work(elapsedTime);

	// create a task to move to this place
	std::vector<Tile*> vpPath = 
		m_rMap.getPath(rWorker.getMapPos(), pWorkplace->getWorkerPos());

	if (vpPath.empty())
	{
		// cannot find a path, assign someone else to work this place
		std::unique_ptr<Work> pWorkTask(new Work(m_rMap, pWorkplace));
		m_rMap.assignTask(std::move(pWorkTask));
		return true;
	}

	// otherwise, move to the workplace
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, vpPath, pWorkplace->getWorkerPos()));
	rWorker.addTaskFront(std::move(pMoveTask));
	return false;
}

// returns true if the worker can work the workplace
bool Work::validate(Worker* pWorker)
{
	std::shared_ptr<Workplace> pWorkplace;
	// must have a workplace and a worker
	if (!(pWorkplace = m_pWorkplace.lock()) || !pWorker)
		return false;
	// fine if the worker is at the workplace
	if (pWorker->getMapPos() == pWorkplace->getWorkerPos())
		return true;

	// calculate the path to the workplace
	std::vector<Tile*> vpPath =
		m_rMap.getPath(pWorker->getMapPos(), pWorkplace->getWorkerPos());
	if (vpPath.empty())
		// can't find a path, so can't work this
		return false;
	// otherwise, we have a path to the workplace
	std::unique_ptr<Move> moveTask(new Move(m_rMap, vpPath, pWorkplace->getWorkerPos()));
	pWorker->addTaskFront(std::move(moveTask));
	return true;
}