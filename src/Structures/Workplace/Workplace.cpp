#include "Workplace.h"

#include "Worker.h"

Workplace::Workplace(const int iTileX, const int iTileY,
	const int iTileMapX, const int iTileMapY,
	const int iHeight, const int iWidth):
	Structure(iTileX, iTileY,
		iTileMapX, iTileMapY, 
		iHeight, iWidth),
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