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
		return (WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW);
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
		return TEXT("FramwUI");
	}
	HICON TinyVisualHWND::RetrieveIcon()
	{
		return NULL;
	}
	LRESULT TinyVisualHWND::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PAINTSTRUCT ps = { 0 };
		HDC hDC = BeginPaint(m_hWND, &ps);

		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx,m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));

		DrawImage(memdc,m_image);

		memdc.Render(paintRC, paintRC, FALSE);

		EndPaint(m_hWND, &ps);
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

	LRESULT TinyVisualHWND::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);//退出应用程序
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_image.Load("D:\\bee_10_working.png");
		return FALSE;
	}

	void TinyVisualHWND::DrawImage(TinyDC& dc, TinyImage& image)
	{
		TinyMemDC memdc1(dc, image);
		memdc1.Render(image.GetRectangle(), image.GetRectangle(), TRUE);
	}
}
