#pragma once
#include "TinyMsg.h"
#include "TinySingle.h"
#include "TinyHandleMap.h"
#include "TinyCollection.h"

namespace TinyUI
{
	/// <summary>
	/// TinyUI的应用实例
	/// </summary>
	class TinyApplication
	{
	public:
		TinyApplication();
		~TinyApplication();
	private:
		INT					m_iCmdShow;
		HINSTANCE			m_hInstance;
		LPTSTR				m_hCmdLine;
		HACCEL				m_hAccTable;
		ULONG_PTR			m_gdiplusToken;
		//单例
		static TinyApplication*	m_pInstance;
		//句柄映射
		TinyHandleMap<HDC>			m_MapHDC;
		TinyHandleMap<HWND>			m_MapHWND;
		TinyHandleMap<HPEN>			m_MapHPEN;
		TinyHandleMap<HRGN>			m_MapHRGN;
		TinyHandleMap<HBRUSH>		m_MapHBRUSH;
		TinyHandleMap<HBITMAP>		m_MapHBITMAP;
		TinyHandleMap<HPALETTE>		m_MapHPALETTE;
		TinyHandleMap<HIMAGELIST>	m_MapHIMAGELIST;
	public:
		//单例模式
		static TinyApplication* Instance() throw();
		//分静态成员
		HINSTANCE Handle() throw();
		BOOL AddMessageLoop(TinyMessageLoop* pMsgLoop);
		BOOL RemoveMessageLoop();
		TinyMessageLoop* GetMessageLoop(DWORD dwThreadID = ::GetCurrentThreadId()) const;
		BOOL Initialize(HINSTANCE m_hInstance, LPTSTR m_lpCmdLine, INT m_nCmdShow, LPCTSTR lpTableName);
		BOOL Uninitialize();
		//Map成员
		TinyHandleMap<HDC>&			GetMapHDC();
		TinyHandleMap<HRGN>&		GetMapHRGN();
		TinyHandleMap<HWND>&		GetMapHWND();
		TinyHandleMap<HPEN>&		GetMapHPEN();
		TinyHandleMap<HBRUSH>&		GetMapHBRUSH();
		TinyHandleMap<HBITMAP>&		GetMapHBITMAP();
		TinyHandleMap<HPALETTE>&	GetMapHPALETTE();
		TinyHandleMap<HIMAGELIST>&	GetMapHIMAGELIST();
	private:
		TinyMap<DWORD, TinyMessageLoop*> m_msgLoops;
	};

	__declspec(selectany) TinyApplication* TinyApplication::m_pInstance = NULL;
}


