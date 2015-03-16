#include "../stdafx.h"
#include "TinyVisualHWND.h"

namespace TinyUI
{
	TinyVisualHWND::TinyVisualHWND()
		:m_desktop(NULL)
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
		bHandled = FALSE;
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		ScreenToClient(m_hWND, &pt);

		return FALSE;
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
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWND;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 0;
		_TrackMouseEvent(&tme);

		/*POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		TinyVisual* ps = TinyVisual::FindVisual(m_desktop, pt);
		if (ps != NULL)
		{
			LPCSTR pzName = ps->GetName();
			TRACE("Name: %s\n", pzName);
		}*/
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnNCMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_desktop = TinyVisual::New(NULL, 0, 0, m_size.cx, m_size.cy);
		m_desktop->SetName("desktop");
		m_val1 = TinyVisual::New(m_desktop, 10, 10, 10, 10);
		m_val1->SetName("m_val1");
		m_val2 = TinyVisual::New(m_desktop, 20, 20, 10, 10);
		m_val2->SetName("m_val2");
		m_val3 = TinyVisual::New(m_desktop, 30, 30, 10, 10);
		m_val3->SetName("m_val3");
		m_val4 = TinyVisual::New(m_desktop, 40, 40, 10, 10);
		m_val4->SetName("m_val4");
		m_val5 = TinyVisual::New(m_desktop, 50, 50, 10, 10);
		m_val5->SetName("m_val5");
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		TinyVisual::Delete(m_desktop);
		TinyVisual::Delete(m_val1);
		TinyVisual::Delete(m_val2);
		TinyVisual::Delete(m_val3);
		TinyVisual::Delete(m_val4);
		TinyVisual::Delete(m_val5);

		return FALSE;
	}

	LRESULT TinyVisualHWND::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}
}
