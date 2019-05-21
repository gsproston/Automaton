#include "Work.h"

#include "Move.h"
#include "Utils/Utils.h"

Work::Work(Map& rMap,
	std::shared_ptr<Workplace> pWorkplace) :
	Task(pWorkplace->getWorkerPos()),
	m_rMap(rMap),
	m_pWorkplace(pWorkplace)
{}


bool Work::tick(const sf::Time elapsedTime, Worker& rWorker)
{
	std::shared_ptr<Workplace> pWorkplace;
	if (!(pWorkplace = m_pWorkplace.lock()))
		return true;

	// we have work, are we close to it?
	if (rWorker.getMapPos() == m_vfMapPos)
		// we are! so we can work it
		return pWorkplace->work(elapsedTime);

	// create a task to move to this place
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, m_vfMapPos));
	if (!pMoveTask->validate(rWorker))
	{
		// cannot find a path, assign someone else to work this place
		std::unique_ptr<Work> pWorkTask(new Work(m_rMap, pWorkplace));
		m_rMap.assignTask(std::move(pWorkTask));
		return true;
	}
	rWorker.addTaskFront(std::move(pMoveTask));
	return false;
}

// returns true if the worker can work the workplace
bool Work::validate(Worker& rWorker)
{
	std::shared_ptr<Workplace> pWorkplace;
	// must have a workplace and a worker
	if (!(pWorkplace = m_pWorkplace.lock()))
		return false;
	// fine if the worker is at the workplace
	if (rWorker.getMapPos() == m_vfMapPos)
		return true;

	// calculate the path to the workplace
	std::unique_ptr<Move> pMoveTask(new Move(m_rMap, m_vfMapPos));
	return pMoveTask->validate(rWorker);
}