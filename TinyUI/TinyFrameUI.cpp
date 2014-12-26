#include "stdafx.h"
#include "TinyFrameUI.h"

namespace TinyUI
{
	TinyFrameUI::TinyFrameUI()
	{
	}


	TinyFrameUI::~TinyFrameUI()
	{
	}

	LRESULT TinyFrameUI::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);//退出应用程序
		return FALSE;
	}

	BOOL TinyFrameUI::Create(HWND hParent, int x, int y, int cx, int cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}

	DWORD TinyFrameUI::RetrieveStyle()
	{
		return (WS_VISIBLE | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU);
	}

	DWORD TinyFrameUI::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING);
	}

	LRESULT TinyFrameUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		btn.Create(m_hWND, 10, 10, 200, 23);
		return TRUE;
	}

}

