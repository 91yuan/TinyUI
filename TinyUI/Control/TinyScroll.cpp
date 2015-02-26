#include "../stdafx.h"
#include "TinyScroll.h"

namespace TinyUI
{
	TinyScroll::TinyScroll(BOOL bVert)
	{

	}


	TinyScroll::~TinyScroll()
	{
	}

	BOOL TinyScroll::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}

	LRESULT TinyScroll::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PAINTSTRUCT ps = { 0 };
		HDC hDC = BeginPaint(m_hWND, &ps);

		TinyMemDC menDC(hDC, ps.rcPaint);

		//Draw
		FillRect(menDC, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));
		TinyMemDC menDC1(menDC, m_scrollbar_hover);
		menDC1.Render(m_scrollbar_hover.GetRectangle(),TRUE);
		menDC.Render(ps.rcPaint, TRUE);

		EndPaint(m_hWND, &ps);
		return FALSE;
	}

	LRESULT TinyScroll::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		return FALSE;
	}

	LRESULT TinyScroll::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyScroll::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyScroll::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_scrollbar_groove.Load("E:\\ScrollBar\\scrollbar_groove.png");
		/*m_arrow_down_hover.Load("E:\\ScrollBar\\arrow_down_hover.png");
		m_arrow_down_normal.Load("E:\\ScrollBar\\arrow_down_normal.png");
		m_arrow_down_press.Load("E:\\ScrollBar\\arrow_down_press.png");
		m_arrow_up_hover.Load("E:\\ScrollBar\\arrow_up_hover.png");
		m_arrow_up_normal.Load("E:\\ScrollBar\\arrow_up_normal.png");
		m_arrow_up_press.Load("E:\\ScrollBar\\arrow_up_press.png");
		m_scrollbar_groove.Load("E:\ScrollBar\scrollbar_groove.png");
		m_scrollbar_hover.Load("E:\\ScrollBar\\scrollbar_hover.png");
		m_scrollbar_normal.Load("E:\\ScrollBar\\scrollbar_normal.png");*/
		return FALSE;
	}
}
