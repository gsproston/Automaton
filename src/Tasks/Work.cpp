#include "Work.h"

#include "Move.h"
#include "Utils/Utils.h"

Work::Work(const Map& rMap,
	std::shared_ptr<Workplace> pWorkplace) :
	Task(pWorkplace->getCentrePos()),
	m_rMap(rMap),
	m_pWorkplace(pWorkplace)
{}


bool Work::tick(sf::Time elapsedTime, Worker& rWorker)
{
	if (!m_pWorkplace)
		return true;

	// we have work, are we close to it?
	if (rWorker.m_vfMapPos == m_pWorkplace->getWorkerPos())
	{
		// we are! so we can work it
		m_pWorkplace->work();
	}
	else
	{
		// create a task to move to this place
		std::vector<std::shared_ptr<Tile>> vpPath = 
			m_rMap.getPath(rWorker.m_vfMapPos, m_pWorkplace->getWorkerPos());
		std::unique_ptr<Move> moveTask(new Move(m_rMap, vpPath, m_pWorkplace->getWorkerPos()));
		rWorker.addTaskFront(std::move(moveTask));
	}
	return false;
}

bool Work::validate(Worker* pWorker)
{
	// must have a workplace and a worker
	if (!m_pWorkplace || !pWorker)
		return false;
	// fine if the worker is at the workplace
	if (pWorker->m_vfMapPos == m_pWorkplace->getWorkerPos())
		return true;

	// calculate the path to the workplace
	std::vector<std::shared_ptr<Tile>> vpPath =
		m_rMap.getPath(pWorker->m_vfMapPos, m_pWorkplace->getWorkerPos());
	if (!vpPath.empty())
	{
		// we have a path to the workplace
		std::unique_ptr<Move> moveTask(new Move(m_rMap, vpPath, m_pWorkplace->getWorkerPos()));
		pWorker->addTaskFront(std::move(moveTask));
		return true;
	}
	// otherwise, we can't reach the workplace, so can't work it
	return false;
}