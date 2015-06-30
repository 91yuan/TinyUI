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
	BOOL TinyProactorIO::Open(DWORD dwConcurrent, TaskCallback cb)
	{
		m_dwConcurrent = dwConcurrent;
		m_completionCb = cb;
		m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, m_dwConcurrent);
		for (DWORD i = 0; i < m_dwConcurrent; i++)
		{
			m_tasks.Add((HANDLE)_beginthreadex(NULL, 0, &DoTask, this, 0, 0));
		}
		return m_hIOCP != NULL;
	}
	BOOL TinyProactorIO::Cancel()
	{
		if (m_hIOCP != NULL)
		{
			if (FARPROC CancelIoExPtr = ::GetProcAddress(
				::GetModuleHandleA("KERNEL32"), "CancelIoEx"))
			{
				typedef BOOL(WINAPI* CancelIoEx)(HANDLE, LPOVERLAPPED);
				CancelIoEx cancelIoEx = (CancelIoEx)CancelIoExPtr;
				return cancelIoEx(m_hIOCP, NULL);
			}
		}
		return FALSE;
	}
	void TinyProactorIO::Close()
	{
		if (m_hIOCP != NULL)
		{
			CloseHandle(m_hIOCP);
			m_hIOCP = NULL;
		}
	}
	TinyProactorIO::~TinyProactorIO()
	{
		Detach();
	}
	TinyProactorIO::operator HANDLE() const
	{
		return m_hIOCP;
	}
	HANDLE	TinyProactorIO::Handle() const
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
		io->m_completionCb(*io);
		return 0;
	}
	//////////////////////////////////////////////////////////////////////////
	IOCPOperation::IOCPOperation()
	{
		Reset();
	}
	IOCPOperation::~IOCPOperation()
	{

	}
	void IOCPOperation::Complete(TinyProactorIO& owner, const DWORD dwError, DWORD dwBytestransferred)
	{
		if (!CompleteCallback.IsNull())
		{
			CompleteCallback(owner, dwError, dwBytestransferred);
		}
	}
	void IOCPOperation::Pending(TinyProactorIO& owner, const DWORD dwError, DWORD dwBytestransferred)
	{
		if (!PendingCallback.IsNull())
		{
			PendingCallback(owner, dwError, dwBytestransferred);
		}
	}
	void IOCPOperation::Reset()
	{
		Internal = 0;
		InternalHigh = 0;
		Offset = 0;
		OffsetHigh = 0;
		hEvent = 0;
	}
	CHAR* IOCPOperation::Alloc(size_t size)
	{
		try
		{
			CHAR* buffer = new CHAR[size];
			m_buffer.Reset(new CHAR[size]);
			return buffer;
		}
		catch (exception& e)
		{
			TRACE(e.what());
			TRACE("\n");
		}
		return NULL;
	}
}
