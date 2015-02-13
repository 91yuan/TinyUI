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
		return (WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MINIMIZEBOX);
	}

	DWORD TinyFrameUI::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR | WS_EX_OVERLAPPEDWINDOW | WS_EX_TOPMOST);
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
		btn1.Create(m_hWND, 10, 10, 200, 30);
		RECT rect = { 0 };
		GetClientRect(btn1, &rect);
		HRGN hRgn = CreateRoundRectRgn(rect.left + 3, rect.top + 3, rect.right - 3, rect.bottom - 3, 5, 5);
		SetWindowRgn(btn1, hRgn, TRUE);
		DeleteObject(hRgn);
		RECT rect1 = { 0 };
		RECT rect2 = { 0 };
		GetClientRect(btn1, &rect1);
		GetWindowRect(btn1, &rect2);
		//intersect_rect(&rect, &rect2, &rect1);
		BOOL a = IntersectRect1(&rect, &rect2, &rect1);
		return TRUE;
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
		bHandled = TRUE;
		return TRUE;
	}

	LRESULT TinyFrameUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnSize\n");
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	LRESULT TinyFrameUI::OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		POINT pos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		ScreenToClient(m_hWND, &pos);
		//窗口缩放
		if (pos.x <= CLIENT_MARGIN_LEFT && pos.y <= CLIENT_MARGIN_TOP)
		{
			return HTTOPLEFT;
		}
		if (pos.x >= CLIENT_MARGIN_LEFT && pos.x <= (m_size.cx - CLIENT_MARGIN_RIGHT) && pos.y <= CLIENT_MARGIN_TOP)
		{
			return HTTOP;
		}
		if (pos.x >= (m_size.cx - CLIENT_MARGIN_RIGHT) && pos.x <= m_size.cx && pos.y <= CLIENT_MARGIN_TOP)
		{
			return HTTOPRIGHT;
		}
		if (pos.x <= CLIENT_MARGIN_LEFT && pos.y >= (m_size.cy - CLIENT_MARGIN_BOTTOM) && pos.y <= m_size.cy)
		{
			return HTBOTTOMLEFT;
		}
		if (pos.x >= CLIENT_MARGIN_LEFT && pos.x <= (m_size.cx - CLIENT_MARGIN_RIGHT) && pos.y >= (m_size.cy - CLIENT_MARGIN_TOP))
		{
			return HTBOTTOM;
		}
		if (pos.x >= (m_size.cx - CLIENT_MARGIN_RIGHT) && pos.y >= (m_size.cy - CLIENT_MARGIN_BOTTOM) && pos.y <= m_size.cy)
		{
			return HTBOTTOMRIGHT;
		}
		if (pos.x <= CLIENT_MARGIN_LEFT && pos.y >= CLIENT_MARGIN_TOP && pos.y <= (m_size.cy - CLIENT_MARGIN_BOTTOM))
		{
			return HTLEFT;
		}
		if (pos.x >= (m_size.cx - CLIENT_MARGIN_RIGHT) && pos.x <= m_size.cx && pos.y >= CLIENT_MARGIN_TOP && pos.y <= (m_size.cy - CLIENT_MARGIN_BOTTOM))
		{
			return HTRIGHT;
		}
		//标题栏
		if (pos.y <= CAPTION_HEIGHT)
		{
			return HTCAPTION;
		}
		return HTCLIENT;
	}

	LRESULT TinyFrameUI::OnNCLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCLButtonDown\n");
		return FALSE;
	}

	LRESULT TinyFrameUI::OnNCLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCLButtonUp\n");
		return FALSE;
	}

	LRESULT TinyFrameUI::OnNCLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCLButtonDBClick\n");
		return FALSE;
	}

	LRESULT TinyFrameUI::OnNCRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCRButtonDown\n");
		return FALSE;
	}

	LRESULT TinyFrameUI::OnNCRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCRButtonUp\n");
		return FALSE;
	}

	LRESULT TinyFrameUI::OnNCRButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCRButtonDBClick\n");
		return FALSE;
	}

}

