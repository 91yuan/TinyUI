#include "../stdafx.h"
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

	BOOL TinyFrameUI::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	BOOL TinyFrameUI::ShowWindow(int nCmdShow) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ShowWindow(m_hWND, nCmdShow);
	}

	BOOL TinyFrameUI::UpdateWindow() throw()
	{
		ASSERT(m_hWND != NULL);
		return ::UpdateWindow(m_hWND);
	}
	DWORD TinyFrameUI::RetrieveStyle()
	{
		return (WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW);
	}

	DWORD TinyFrameUI::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR);
	}

	LPCSTR TinyFrameUI::RetrieveClassName()
	{
		return TEXT("FramwUI");
	}

	LPCSTR TinyFrameUI::RetrieveTitle()
	{
		return TEXT("FramwUI");
	}

	HICON TinyFrameUI::RetrieveIcon()
	{
		return NULL;
	}

	void TinyFrameUI::CenterWindow(HWND parent, HWND window, TinySize size) throw()
	{
		RECT window_bounds;
		RECT center_bounds = { 0 };
		if (parent)
		{
			::GetWindowRect(parent, &center_bounds);
		}
		else
		{
			HMONITOR monitor = MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST);
			if (monitor != NULL)
			{
				MONITORINFO mi = { 0 };
				mi.cbSize = sizeof(mi);
				GetMonitorInfo(monitor, &mi);
				center_bounds = mi.rcWork;
			}
		}
		window_bounds.left = center_bounds.left + (center_bounds.right - center_bounds.left - size.cx) / 2;
		window_bounds.right = window_bounds.left + size.cx;
		window_bounds.top = center_bounds.top + (center_bounds.bottom - center_bounds.top - size.cy) / 2;
		window_bounds.bottom = window_bounds.top + size.cy;
		if (::GetWindowLong(window, GWL_STYLE) & WS_CHILD)
		{
			POINT topleft = { window_bounds.left, window_bounds.top };
			::MapWindowPoints(HWND_DESKTOP, parent, &topleft, 1);
			window_bounds.left = topleft.x;
			window_bounds.top = topleft.y;
			window_bounds.right = window_bounds.left + size.cx;
			window_bounds.bottom = window_bounds.top + size.cy;
		}
		WINDOWINFO win_info = { 0 };
		win_info.cbSize = sizeof(WINDOWINFO);
		GetWindowInfo(window, &win_info);
		if (AdjustWindowRectEx(&window_bounds, win_info.dwStyle, FALSE, win_info.dwExStyle))
		{
			SetWindowPos(window, 0, window_bounds.left, window_bounds.top,
				window_bounds.right - window_bounds.left,
				window_bounds.bottom - window_bounds.top,
				SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}
	LRESULT TinyFrameUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_scroll.Create(m_hWND, 10, 10, 12, 350);
		m_scroll.SetScrollInfo(0, 100, 10, 0);
		m_fs_PosChange.BindDelegate(this, &TinyFrameUI::PosChanges);
		m_scroll.PosChange += &m_fs_PosChange;
		return TRUE;
	}
	LRESULT TinyFrameUI::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_scroll.PosChange -= &m_fs_PosChange;
		return FALSE;
	}

	LRESULT TinyFrameUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		PAINTSTRUCT s;
		HDC hDC = BeginPaint(m_hWND, &s);
		EndPaint(m_hWND, &s);

		return FALSE;
	}

	LRESULT TinyFrameUI::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyFrameUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}
	void TinyFrameUI::PosChanges(INT oldPos, INT newPos)
	{
		TRACE("OldPos:%d,NewPos:%d\n", oldPos, newPos);
	}

	
}

