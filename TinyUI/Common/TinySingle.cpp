#include "../stdafx.h"
#include "TinySingle.h"

namespace TinyUI
{
	/////////////////////////////////////////////////////////////////////////
	TinyCriticalSection::TinyCriticalSection() throw()
	{
		memset(&section, 0, sizeof(CRITICAL_SECTION));
	}
	TinyCriticalSection::~TinyCriticalSection()
	{
	}
	HRESULT TinyCriticalSection::Lock() throw()
	{
		EnterCriticalSection(&section);
		return S_OK;
	}
	BOOL TinyCriticalSection::Try() throw()
	{
		return ::TryEnterCriticalSection(&section);
	}
	HRESULT TinyCriticalSection::Unlock() throw()
	{
		LeaveCriticalSection(&section);
		return S_OK;
	}
	HRESULT TinyCriticalSection::Initialize() throw()
	{
		InitializeCriticalSection(&section);
		return S_OK;
	}
	HRESULT TinyCriticalSection::Uninitialize() throw()
	{
		DeleteCriticalSection(&section);
		return S_OK;
	}
	/////////////////////////////////////////////////////////////////////////
	TinyEvent::TinyEvent(BOOL bInitiallyOwn, BOOL bManualReset, LPCTSTR pstrName, LPSECURITY_ATTRIBUTES lpsaAttribute)
		:m_hEvent(NULL)
	{
		m_hEvent = ::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, pstrName);
	}
	TinyEvent::~TinyEvent()
	{
		if (m_hEvent != NULL)
		{
			::CloseHandle(m_hEvent);
			m_hEvent = NULL;
		}
	}
	TinyEvent::operator HANDLE() const
	{
		return (HANDLE)(this == NULL ? NULL : m_hEvent);
	}
	HANDLE TinyEvent::Handle()
	{
		return m_hEvent;
	}
	BOOL TinyEvent::CreateEvent(BOOL bInitiallyOwn, BOOL bManualReset, LPCTSTR lpszNAme, LPSECURITY_ATTRIBUTES lpsaAttribute)
	{
		m_hEvent = ::CreateEvent(lpsaAttribute, bManualReset,
			bInitiallyOwn, lpszNAme);
		return m_hEvent == NULL ? FALSE : TRUE;
	}
	BOOL TinyEvent::OpenEvent(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
	{
		m_hEvent = ::OpenEvent(dwDesiredAccess, bInheritHandle, lpName);
		return m_hEvent == NULL ? FALSE : TRUE;
	}
	BOOL TinyEvent::SetEvent()
	{
		ASSERT(m_hEvent != NULL);
		return ::SetEvent(m_hEvent);
	}
	BOOL TinyEvent::PulseEvent()
	{
		ASSERT(m_hEvent != NULL);
		return ::PulseEvent(m_hEvent);
	}
	BOOL TinyEvent::ResetEvent()
	{
		ASSERT(m_hEvent != NULL);
		return ::ResetEvent(m_hEvent);
	}
	BOOL TinyEvent::Lock(DWORD dwTimeout)
	{
		ASSERT(m_hEvent != NULL);
		DWORD dwRet = ::WaitForSingleObject(m_hEvent, dwTimeout);
		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return TRUE;
		else
			return FALSE;
	}
	BOOL TinyEvent::Unlock()
	{
		return TRUE;
	}
	/////////////////////////////////////////////////////////////////////////
	TinyMutex::TinyMutex(BOOL bInitiallyOwn, LPCTSTR lpszName, LPSECURITY_ATTRIBUTES lpsaAttribute)
		:m_hMutex(NULL)
	{
		m_hMutex = ::CreateMutex(lpsaAttribute, bInitiallyOwn, lpszName);
	}
	TinyMutex::~TinyMutex()
	{
		if (m_hMutex != NULL)
		{
			::CloseHandle(m_hMutex);
			m_hMutex = NULL;
		}
	}
	BOOL TinyMutex::Open(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
	{
		m_hMutex = ::OpenMutex(dwDesiredAccess, bInheritHandle, lpName);
		return m_hMutex == NULL ? FALSE : TRUE;
	}
	TinyMutex::operator HANDLE() const
	{
		return (HANDLE)(this == NULL ? NULL : m_hMutex);
	}
	HANDLE TinyMutex::Handle()
	{
		return m_hMutex;
	}
	BOOL TinyMutex::Lock(DWORD dwTimeout)
	{
		ASSERT(m_hMutex != NULL);
		DWORD dwRet = ::WaitForSingleObject(m_hMutex, dwTimeout);
		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return TRUE;
		else
			return FALSE;
	}
	BOOL TinyMutex::Unlock()
	{
		ASSERT(m_hMutex != NULL);
		return ::ReleaseMutex(m_hMutex);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyLock::TinyLock()
	{
		m_section.Initialize();
	}
	TinyLock::~TinyLock()
	{
		m_section.Uninitialize();
	}
	void TinyLock::Acquire()
	{
		m_section.Lock();
	}
	void TinyLock::Release()
	{
		m_section.Unlock();
	}
	BOOL TinyLock::Try()
	{
		return m_section.Try();
	}
	//////////////////////////////////////////////////////////////////////////
	TinyAutoLock::TinyAutoLock(TinyLock& lock) : m_lock(lock)
	{
		m_lock.Acquire();
	}
	TinyAutoLock::~TinyAutoLock()
	{
		m_lock.Release();
	}
};
