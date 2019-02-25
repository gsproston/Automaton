#pragma once

#include "../Structure.h"

class Worker;

class Workplace: public Structure
{
public:
	Workplace(const int iTileX, const int iTileY,
		const int iTileMapX, const int iTileMapY,
		const int iHeight, const int iWidth);

	virtual void work() = 0;

	bool noWorker();
	void setWorker(Worker* pWorker);

private:
	// non-owning pointer to worker
	Worker* m_pWorker;
};