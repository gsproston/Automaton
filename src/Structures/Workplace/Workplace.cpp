#include "Workplace.h"

#include "Worker.h"

Workplace::Workplace(const int x, const int y):
	Structure(x, y),
	m_pWorker(nullptr)
{}


bool Workplace::noWorker()
{
	return m_pWorker == nullptr;
}

void Workplace::setWorker(Worker* pWorker)
{
	m_pWorker = pWorker;
}