#ifndef INCLUDE_CRITICALSECTION
#define INCLUDE_CRITICALSECTION

#include <windows.h>

/************************************************************************/
/* CCriticalSection                                                     */
/************************************************************************/
class CCriticalSection
{
public:
	CCriticalSection() { InitializeCriticalSection(&m_CriticalSection); }
	~CCriticalSection() { DeleteCriticalSection(&m_CriticalSection); }

public:
	void Enter() { EnterCriticalSection(&m_CriticalSection); }	//�����ٽ���
	void Leave() { LeaveCriticalSection(&m_CriticalSection); }	//�뿪�ٽ���

protected:
	CRITICAL_SECTION m_CriticalSection;
};

#endif
