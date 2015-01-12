#pragma once
#include "TinyObject.h"

/// <summary>
/// 信号量对象
/// </summary>
namespace TinyUI
{
	/// <summary>
	/// 临界区
	/// </summary>
	class TinyCriticalSection : public TinyObject
	{
		DECLARE_DYNAMIC(TinyCriticalSection);
	public:
		TinyCriticalSection() throw();
		~TinyCriticalSection();
		HRESULT Lock() throw();
		HRESULT Unlock() throw();
		HRESULT Initialize() throw();
		HRESULT Uninitialize() throw();
	private:
		CRITICAL_SECTION section;
	};
	/// <summary>
	/// 事件
	/// </summary>
	class TinyEvent : public TinyObject
	{
		DECLARE_DYNAMIC(TinyEvent);
	public:
		TinyEvent(BOOL bInitiallyOwn = FALSE, BOOL bManualReset = FALSE, LPCTSTR lpszNAme = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
		~TinyEvent();
		operator HANDLE() const;
		HANDLE Handle();
		BOOL CreateEvent(BOOL bInitiallyOwn = FALSE, BOOL bManualReset = FALSE, LPCTSTR lpszNAme = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
		BOOL OpenEvent(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName);
		BOOL SetEvent();
		BOOL PulseEvent();
		BOOL ResetEvent();
		BOOL Lock(DWORD dwTimeout = INFINITE);
		BOOL Unlock();
	private:
		HANDLE  m_hEvent;
	};
	/// <summary>
	/// 互斥量
	/// </summary>
	class TinyMutex : public TinyObject
	{
		DECLARE_DYNAMIC(TinyMutex);
	public:
		TinyMutex(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
		~TinyMutex();
		BOOL Open(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName);
		operator HANDLE() const;
		HANDLE Handle();
		BOOL Lock(DWORD dwTimeout = INFINITE);
		BOOL Unlock();
	private:
		HANDLE  m_hMutex;
	};
};

