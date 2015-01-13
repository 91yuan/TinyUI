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
		return (WS_VISIBLE | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU);
	}

	DWORD TinyFrameUI::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING);
	}

	LRESULT TinyFrameUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		image.Load("E:\\1234.png");
		return TRUE;
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

	LRESULT TinyFrameUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;


		PAINTSTRUCT s;
		HDC hDC = BeginPaint(m_hWND, &s);
		TinySize size = image.GetSize();
		TinySize paintSize((s.rcPaint.right - s.rcPaint.left), (s.rcPaint.bottom - s.rcPaint.top));

		HDC hMenDC = CreateCompatibleDC(hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, m_cx, m_cy);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMenDC, hBitmap);
		::FillRect(hMenDC, &s.rcPaint, (HBRUSH)GetStockObject(GRAY_BRUSH));

		DeleteObject(hBitmap);
		SelectObject(hMenDC, hOldBitmap);
		DeleteDC(hMenDC);

		/*HDC hMenDC1 = CreateCompatibleDC(hDC);
		HBITMAP hBitmap1 = (HBITMAP)SelectObject(hMenDC1, image);

		::BitBlt(hMenDC, 0, 0, size.cx, size.cy, hMenDC1, 0, 0, SRCCOPY);
		::BitBlt(hDC, 0, 0, size.cx, size.cy, hMenDC, 0, 0, SRCCOPY);

		DeleteObject(hBitmap);
		DeleteDC(hMenDC1);
		DeleteDC(hMenDC);*/

		EndPaint(m_hWND, &s);
		/*HDC hMenDC = CreateCompatibleDC(hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, m_cx, m_cy);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMenDC, hBitmap);
		RECT rc = { 0, 0, m_cx, m_cy };
		::FillRect(hMenDC, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

		TRACE("OnPaint: %d,%d\n", paintSize.cx, paintSize.cy);

		BLENDFUNCTION bs = { AC_SRC_OVER, 0, 128, 1 };
		::AlphaBlend(hDC, 10, 10, size.cx, size.cy, hMenDC, 0, 0, size.cx, size.cy, bs);

		SelectObject(hMenDC, hOldBitmap);
		DeleteDC(hMenDC);*/



		return TRUE;
	}

	LRESULT TinyFrameUI::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return TRUE;
	}

	LRESULT TinyFrameUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_cx = LOWORD(lParam);
		m_cy = HIWORD(lParam);
		return FALSE;
	}

}

