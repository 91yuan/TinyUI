#include "../stdafx.h"
#include "TinyView.h"

namespace TinyUI
{
	TinyView::TinyView()
	{
	}
	TinyView::~TinyView()
	{
	}
	BOOL TinyView::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	HICON TinyView::RetrieveIcon()
	{
		return NULL;
	}
	DWORD TinyView::RetrieveStyle()
	{
		return (WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MINIMIZEBOX);
	}
	DWORD TinyView::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR | WS_EX_OVERLAPPEDWINDOW | WS_EX_TOPMOST);
	}
	LPCSTR TinyView::RetrieveClassName()
	{
		return TEXT("TinyView");
	}
	LPCSTR TinyView::RetrieveTitle()
	{
		return TEXT("TinyView");
	}
	BOOL TinyView::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		if (uMsg >= WM_NCMOUSEFIRST && uMsg <= WM_NCMOUSELAST)
		{
			return TRUE;
		}
		if (uMsg == WM_NCHITTEST)
		{
			POINT pos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			ScreenToClient(m_hWND, &pos);
			return TRUE;
		}
		if (uMsg == WM_MOUSEFIRST && uMsg <= WM_MOUSELAST)
		{

		}
		return TinyControl::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult);
	}
}
