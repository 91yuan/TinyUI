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
	LRESULT TinyVisualHWND::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_images[0].Load("E:\\SysButton\\btn_close_normal.png");
		m_images[1].Load("E:\\SysButton\\btn_close_down.png");
		m_images[2].Load("E:\\SysButton\\btn_close_highlight.png");
		m_images[3].Load("E:\\SysButton\\btn_mini_normal.png");
		m_images[4].Load("E:\\SysButton\\btn_mini_down.png");
		m_images[5].Load("E:\\SysButton\\btn_mini_highlight.png");
		return TRUE;
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

		if (m_size.cx != 0 && m_size.cy != 0)
		{
			TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
			RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
			FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));

			DrawSysButtons(memdc, 0);

			memdc.Render(paintRC, paintRC, FALSE);
		}

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
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;

		POINT pos = { LOWORD(lParam), HIWORD(lParam) };
		ScreenToClient(m_hWND, &pos);

		RECT rectangle = { 0 };
		GetPartRectangle(PART_TOPLEFT, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTTOPLEFT;

		GetPartRectangle(PART_TOP, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTTOP;

		GetPartRectangle(PART_TOPRIGHT, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTTOPRIGHT;

		GetPartRectangle(PART_LEFT, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTLEFT;

		GetPartRectangle(PART_RIGHT, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTRIGHT;

		GetPartRectangle(PART_BOTTOMLEFT, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTBOTTOMLEFT;

		GetPartRectangle(PART_BOTTOM, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTBOTTOM;

		GetPartRectangle(PART_BOTTOMRIGHT, rectangle);
		if (PtInRect(&rectangle, pos))
			return HTBOTTOMRIGHT;

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
	void TinyVisualHWND::GetPartRectangle(UINT fPart, RECT& rect)
	{
		RECT rectangle = { 0, 0, m_size.cx, m_size.cy };
		SetRectEmpty(&rect);
		switch (fPart)
		{
		case PART_CLOSE:
			SetRect(&rect, rectangle.right - TINY_CXBORDER - TINY_CXCLOSEIMIZED,
				rectangle.top + TINY_CYBORDER,
				rectangle.right - TINY_CXBORDER,
				rectangle.top + TINY_CYBORDER + TINY_CYCLOSEIMIZED);
			break;
		case PART_MAXBUTTON:
			SetRect(&rect, rectangle.right - TINY_CXBORDER - TINY_CXCLOSEIMIZED - TINY_CXMAXIMIZED,
				rectangle.top + TINY_CYBORDER,
				rectangle.right - TINY_CXBORDER - TINY_CXCLOSEIMIZED,
				rectangle.top + TINY_CYBORDER + TINY_CYMAXIMIZED);
			break;
		case PART_MINBUTTON:
			SetRect(&rect, rectangle.right - TINY_CXBORDER - TINY_CXCLOSEIMIZED - TINY_CXMAXIMIZED - TINY_CXMINIMIZED,
				rectangle.top + TINY_CYBORDER,
				rectangle.right - TINY_CXBORDER - TINY_CXCLOSEIMIZED - TINY_CXMAXIMIZED,
				rectangle.top + TINY_CYBORDER + TINY_CYMINIMIZED);
			break;
		case PART_TOPLEFT:
			SetRect(&rect, rectangle.left,
				rectangle.top,
				rectangle.left + TINY_CXBORDER,
				rectangle.top + TINY_CYBORDER);
			break;
		case PART_TOP:
			SetRect(&rect, rectangle.left + TINY_CXBORDER,
				rectangle.top,
				rectangle.right - TINY_CXBORDER,
				rectangle.top + TINY_CYBORDER);
			break;
		case PART_TOPRIGHT:
			SetRect(&rect, rectangle.right - TINY_CXBORDER,
				rectangle.top,
				rectangle.right,
				rectangle.top + TINY_CYBORDER);
			break;
		case PART_BOTTOMLEFT:
			SetRect(&rect, rectangle.left,
				rectangle.bottom - TINY_CYBORDER,
				rectangle.left + TINY_CXBORDER,
				rectangle.bottom);
			break;
		case PART_BOTTOM:
			SetRect(&rect, rectangle.left + TINY_CXBORDER,
				rectangle.bottom - TINY_CYBORDER,
				rectangle.right - TINY_CXBORDER,
				rectangle.bottom);
			break;
		case PART_BOTTOMRIGHT:
			SetRect(&rect, rectangle.right - TINY_CXBORDER,
				rectangle.bottom - TINY_CYBORDER,
				rectangle.right,
				rectangle.bottom);
			break;
		case PART_LEFT:
			SetRect(&rect, rectangle.left,
				rectangle.top + TINY_CYBORDER,
				rectangle.left + TINY_CXBORDER,
				rectangle.bottom - TINY_CYBORDER);
			break;
		case PART_RIGHT:
			SetRect(&rect, rectangle.right - TINY_CXBORDER,
				rectangle.top + TINY_CYBORDER,
				rectangle.right,
				rectangle.bottom - TINY_CYBORDER);
			break;
		}
	}
	void TinyVisualHWND::DrawSysButtons(TinyMemDC& dc, INT iPart)
	{
		INT iSaveDC = dc.SaveDC();
		INT iOldMode = dc.SetBkMode(TRANSPARENT);

		RECT rectangle = { 0 };
		TinyMemDC memdcClose(dc, m_images[0]);
		GetPartRectangle(PART_CLOSE, rectangle);
		memdcClose.Render(rectangle, m_images[0].GetRectangle(), TRUE);
		TinyMemDC memdcMin(dc, m_images[3]);
		GetPartRectangle(PART_MINBUTTON, rectangle);
		memdcMin.Render(rectangle, m_images[3].GetRectangle(), TRUE);

		dc.SetBkMode(iOldMode);
		dc.RestoreDC(iSaveDC);
	}
}
