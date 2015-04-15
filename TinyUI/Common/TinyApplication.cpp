#include "../stdafx.h"
#include "TinyApplication.h"

namespace TinyUI
{
	TinyApplication::TinyApplication()
		:m_hInstance(NULL),
		m_hCmdLine(NULL),
		m_hAccTable(NULL),
		m_iCmdShow(-1)
	{
	}
	TinyApplication* TinyApplication::GetInstance() throw()
	{
		TinyCriticalSection section;
		section.Initialize();
		if (m_pInstance == NULL)
		{
			section.Lock();
			if (m_pInstance == NULL)
			{
				m_pInstance = new TinyApplication();
			}
			section.Unlock();
		}
		section.Uninitialize();
		return m_pInstance;
	}
	HINSTANCE TinyApplication::Handle() throw()
	{
		return m_hInstance;
	}
	BOOL TinyApplication::AddMessageLoop(TinyMessageLoop* pMsgLoop)
	{
		TinyCriticalSection section;
		section.Initialize();
		if (FAILED(section.Lock()))
		{
			TRACE(_T("ERROR : Unable to lock critical section in AddMessageLoop.\n"));
			ASSERT(FALSE);
			return FALSE;
		}
		ASSERT(pMsgLoop != NULL);
		ASSERT(m_msgLoops.Lookup(::GetCurrentThreadId()) == NULL);
		BOOL bRet = m_msgLoops.Add(::GetCurrentThreadId(), pMsgLoop);
		section.Unlock();
		return bRet;
	}
	BOOL TinyApplication::RemoveMessageLoop()
	{
		TinyCriticalSection section;
		section.Initialize();
		if (FAILED(section.Lock()))
		{
			TRACE(_T("ERROR : Unable to lock critical section in RemoveMessageLoop.\n"));
			ASSERT(FALSE);
			return FALSE;
		}
		BOOL bRet = m_msgLoops.Remove(::GetCurrentThreadId());
		section.Unlock();
		section.Uninitialize();
		return bRet;
	}
	TinyMessageLoop* TinyApplication::GetMessageLoop(DWORD dwThreadID) const
	{
		TinyCriticalSection section;
		section.Initialize();
		if (FAILED(section.Lock()))
		{
			TRACE(_T("ERROR : Unable to lock critical section in SysMessageLoop::GetMessageLoop.\n"));
			ASSERT(FALSE);
			return NULL;
		}
		TinyMessageLoop* ps = m_msgLoops.Lookup(dwThreadID);
		section.Unlock();
		section.Uninitialize();
		return ps;
	}
	BOOL TinyApplication::Initialize(HINSTANCE m_hInstance, LPTSTR m_lpCmdLine, INT m_nCmdShow, LPCTSTR lpTableName)
	{
		this->m_hCmdLine = m_lpCmdLine;
		this->m_hInstance = m_hInstance;
		this->m_iCmdShow = m_nCmdShow;
		this->m_hAccTable = LoadAccelerators(m_hInstance, lpTableName);
		if (m_gdiplusToken == 0)
		{
			GdiplusStartupInput input;
			GdiplusStartupOutput output;
			Status status = GdiplusStartup(&m_gdiplusToken, &input, &output);
			return (status != Ok);
		}
		return TRUE;
	}
	BOOL TinyApplication::Uninitialize()
	{
		m_hInstance = NULL;
		m_hCmdLine = NULL;
		if (m_gdiplusToken != 0)
		{
			GdiplusShutdown(m_gdiplusToken);
			m_gdiplusToken = 0;
		}
		//ÊÍ·Åµ¥Àý
		if (m_pInstance != NULL)
		{
			SAFE_DELETE(m_pInstance);
		}
		return TRUE;
	}

	TinyHandleMap<HWND, TinyHandleHWND*>& TinyApplication::GetMapHWND()
	{
		return m_MapHWND;
	}
	TinyHandleMap<HMENU, TinyHandleHMENU*>& TinyApplication::GetMapHMENU()
	{
		return m_MapHMENU;
	}
	TinyHandleMap<HDC, TinyHandleHDC*>&	TinyApplication::GetMapHDC()
	{
		return m_MapHDC;
	}
	TinyHandleMap<HBITMAP, TinyHandleHBITMAP*>&	TinyApplication::GetMapHBITMAP()
	{
		return m_MapHBITMAP;
	}
	TinyHandleMap<HFONT, TinyHandleHFONT*>&	TinyApplication::GetMapHFONT()
	{
		return m_MapHFONT;
	}
	TinyHandleMap<HPEN, TinyHandleHPEN*>& TinyApplication::GetMapHPEN()
	{
		return m_MapHPEN;
	}
	TinyHandleMap<HBRUSH, TinyHandleHBRUSH*>& TinyApplication::GetMapHBRUSH()
	{
		return m_MapHBRUSH;
	}
	TinyHandleMap<HPALETTE, TinyHandleHPALETTE*>& TinyApplication::GetMapHPALETTE()
	{
		return m_MapHPALETTE;
	}
	TinyHandleMap<HRGN, TinyHandleHRGN*>& TinyApplication::GetMapHRGN()
	{
		return m_MapHRGN;
	}
	TinyHandleMap<HIMAGELIST, TinyHandleHIMAGELIST*>& TinyApplication::GetMapHIMAGELIST()
	{
		return m_MapHIMAGELIST;
	}
	TinyApplication::~TinyApplication()
	{

	}
}
