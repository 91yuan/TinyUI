#include "../stdafx.h"
#include <process.h>
#include "TinyIOCP.h"

namespace TinyUI
{
	namespace IO
	{
		TinyIOCP::TinyIOCP(DWORD dwConcurrent)
			:m_hFileHandle(NULL),
			m_hIOCP(NULL),
			m_dwConcurrent(dwConcurrent)
		{
			m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, m_dwConcurrent);
			if (m_hIOCP == NULL)
			{
				throw error_code(GetLastError(), system_category());
			}
		}
		BOOL TinyIOCP::Cancel()
		{
			if (m_hIOCP != NULL)
			{
				if (FARPROC CancelIoExPtr = ::GetProcAddress(
					::GetModuleHandleA("KERNEL32"), "CancelIoEx"))
				{
					CancelIoEx cancelIoEx = (CancelIoEx)CancelIoExPtr;
					return cancelIoEx(m_hIOCP, NULL);
				}
			}
			return FALSE;
		}
		void TinyIOCP::Close()
		{
			if (m_hIOCP != NULL)
			{
				CloseHandle(m_hIOCP);
				m_hIOCP = NULL;
			}
		}
		TinyIOCP::~TinyIOCP()
		{
			Close();
		}
		TinyIOCP::operator HANDLE() const
		{
			return m_hIOCP;
		}
		HANDLE	TinyIOCP::Handle() const
		{
			return m_hIOCP;
		}
		BOOL TinyIOCP::Register(HANDLE hFileHandle, ULONG_PTR completionKey)
		{
			if (m_hIOCP == NULL || hFileHandle == NULL)
			{
				return FALSE;
			}
			if (hFileHandle != m_hFileHandle)
			{
				hFileHandle = m_hFileHandle;
				return ::CreateIoCompletionPort(hFileHandle, m_hIOCP, completionKey, 0) != NULL;
			}
			return FALSE;
		}
		HANDLE	TinyIOCP::GetFileHandle() const
		{
			return m_hFileHandle;
		}
		ULONG_PTR TinyIOCP::GetCompletionKey() const
		{
			return m_completionKey;
		}
	}
}
