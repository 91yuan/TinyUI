#include "../stdafx.h"
#include "TinyVisualHWND.h"

namespace TinyUI
{
	TinyVisualHWND::TinyVisualHWND()
		:m_pCapture(NULL),
		m_pFocus(NULL),
		m_pDesktop(NULL)
	{
		SetRectEmpty(&m_windowRectangle);
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

	BOOL TinyVisualHWND::ProcessWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = FALSE;
		if (msg == WM_CREATE)
		{
			m_pDesktop = new TinyVisual(this);
		}
		if (msg == WM_CLOSE)
		{
			PostQuitMessage(0);
		}
		if (msg == WM_DESTROY)
		{
			ReleaseDC(m_hWND, m_canvas.Detach());
			SAFE_DELETE(m_pDesktop);
		}
		if (msg == WM_PAINT)
		{
			PAINTSTRUCT ps = { 0 };
			BeginPaint(m_hWND, &ps);

			TinyMemDC memdc(m_canvas, TO_CX(m_windowRectangle), TO_CY(m_windowRectangle));
			//»æÖÆ

			memdc.Render(m_windowRectangle, m_windowRectangle, FALSE);

			EndPaint(m_hWND, &ps);
		}
		if (msg == WM_SIZE)
		{
			INT cx = LOWORD(lParam);
			INT cy = HIWORD(lParam);
			SetRect(&m_windowRectangle, 0, 0, cx, cy);
			if (m_canvas != NULL)
			{
				ReleaseDC(m_hWND, m_canvas.Detach());
				m_canvas.Attach(GetWindowDC(hWnd));
			}
		}
		if (msg == WM_NCHITTEST)
		{

		}
		return FALSE;
	}
}
