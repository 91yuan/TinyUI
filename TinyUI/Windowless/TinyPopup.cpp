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

	LRESULT TinyVisualHWND::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);//退出应用程序
		return FALSE;
	}

	BOOL TinyVisualHWND::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	BOOL TinyVisualHWND::ShowWindow(int nCmdShow) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ShowWindow(m_hWND, nCmdShow);
	}

	BOOL TinyVisualHWND::UpdateWindow() throw()
	{
		ASSERT(m_hWND != NULL);
		return ::UpdateWindow(m_hWND);
	}
	DWORD TinyVisualHWND::RetrieveStyle()
	{
		return (WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
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

	void TinyVisualHWND::CenterWindow(HWND parent, HWND window, TinySize size) throw()
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

	void TinyVisualHWND::ParseUI()
	{

	}

	LRESULT TinyVisualHWND::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		ParseUI();
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		PAINTSTRUCT s;
		HDC hDC = BeginPaint(m_hWND, &s);

		EndPaint(m_hWND, &s);
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		//窗口大小更新的时候更新DC
		/*if (m_size.cx != LOWORD(lParam) &&
			m_size.cy != HIWORD(lParam))
		{
			if (m_canves != NULL)
			{
				ReleaseDC(m_hWND, m_canves);
			}
			m_canves = GetWindowDC(m_hWND);
			m_size.cx = LOWORD(lParam);
			m_size.cy = HIWORD(lParam);
		}*/
		return FALSE;
	}
	LRESULT TinyVisualHWND::OnNCMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		return FALSE;
	}
	LRESULT TinyVisualHWND::OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (!m_bMouseTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWND;
			tme.dwFlags = TME_LEAVE | TME_HOVER | TME_NONCLIENT;
			tme.dwHoverTime = 0;
			m_bMouseTracking = _TrackMouseEvent(&tme);
		}
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;

		return HTCAPTION;
	}

	LRESULT TinyVisualHWND::OnNCLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

}
