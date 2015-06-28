#include "../stdafx.h"
#include "TinySocket.h"
#include "vld.h"
#include <process.h>
#include "TinyProactorIO.h"

namespace TinyUI
{
	TinyProactorIO::TinyProactorIO()
	{

	}
	BOOL TinyProactorIO::Initialize(DWORD dwConcurrent, TaskCallback cb)
	{
		m_dwConcurrent = dwConcurrent;
		m_completionCb = cb;
		m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, m_dwConcurrent);
		for (INT i = 0; i < m_dwConcurrent; i++)
		{
			m_tasks.Add((HANDLE)_beginthreadex(NULL, 0, &DoTask, this, 0, 0));
		}
		return m_hIOCP != NULL;
	}
	TinyProactorIO::~TinyProactorIO()
	{
		Detach();
	}
	TinyProactorIO::operator HANDLE() const
	{
		return m_hIOCP;
	}
	BOOL TinyProactorIO::Attach(HANDLE handle)
	{
		ASSERT(handle);
		if (m_hIOCP == NULL) return FALSE;
		if (0 == ::CreateIoCompletionPort(handle, m_hIOCP, 0, 0))
			return FALSE;
		return TRUE;
	}
	HANDLE TinyProactorIO::Detach()
	{
		HANDLE hIocp = m_hIOCP;
		if (hIocp != NULL)
		{
			CloseHandle(hIocp);
		}
		m_hIOCP = NULL;
		return hIocp;
	}
	UINT WINAPI TinyProactorIO::DoTask(LPVOID ps)
	{
		ASSERT(ps);
		TinyProactorIO* io = static_cast<TinyProactorIO*>(ps);
		io->m_completionCb(io);
		return 0;
	}
}
