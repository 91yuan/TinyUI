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
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
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

	LRESULT TinyVisualHWND::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PostQuitMessage(0);//退出应用程序
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		ScreenToClient(m_hWND, &pt);

		RECT rect = { 50, 50, 100, 100 };
		if (PtInRect(&rect, pt))
		{
			return HTCLIENT;
		}

		return HTCAPTION;
	}

	LRESULT TinyVisualHWND::OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWND;
		tme.dwFlags = TME_LEAVE | TME_NONCLIENT;
		tme.dwHoverTime = 0;
		_TrackMouseEvent(&tme);
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnMouseMove\n");
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWND;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 0;
		_TrackMouseEvent(&tme);
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnNCMouseLeave\n");
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		TRACE("OnMouseLeave\n");
		return FALSE;
	}

}
