#include "../stdafx.h"
#include "TinyVisualHWND.h"

namespace TinyUI
{
	TinyVisualHWND::TinyVisualHWND()
	{
	}


	TinyVisualHWND::~TinyVisualHWND()
	{
	}

	BOOL TinyVisualHWND::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		ParseUI();
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}

	DWORD TinyVisualHWND::RetrieveStyle()
	{
		return (WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	}

	DWORD TinyVisualHWND::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR);
	}

	LPCSTR TinyVisualHWND::RetrieveClassName()
	{
		return TEXT("TinyVisualHWND");
	}

	LPCSTR TinyVisualHWND::RetrieveTitle()
	{
		return TEXT("TinyVisualHWND");
	}

	HICON TinyVisualHWND::RetrieveIcon()
	{
		return NULL;
	}


	void TinyVisualHWND::ParseUI()
	{
		m_desktop = CreateVisual(NULL);
		strcpy(m_desktop->name, "desktop");
		Visual* ps1 = m_desktop;
		for (INT i = 0; i < 100; i++)
		{
			Visual* ps = new Visual();
			TinyString str;
			str = TinyString::Format("%d-node", i);
			strcpy(m_desktop->name, str.STR());
			SetParent(ps, ps1);
			ps1 = ps;
		}
	}

	BOOL TinyVisualHWND::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			DestoryVisual(m_desktop);
			PostQuitMessage(0);//退出应用程序
			break;
		default:
			break;
		}
		return TinyControl::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult);
	}

}
