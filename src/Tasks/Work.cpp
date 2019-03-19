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
	if (getDistance(rWorker.m_vfMapPos, m_pWorkplace->getWorkerPos()) < 5)
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