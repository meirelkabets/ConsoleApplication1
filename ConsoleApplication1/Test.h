#pragma once

#include <thread>

class CTest
{

public:
	CTest(void);
	~CTest(void);

	void Initialize();

private:
	std::thread *m_pTask;
	bool m_tskStarted;

public:
	void Task();

};

