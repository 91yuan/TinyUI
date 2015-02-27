#include "../stdafx.h"
#include "TinyScroll.h"

namespace TinyUI
{
	TinyScroll::TinyScroll()
		:m_iTrackingCode(0),
		m_bTracking(FALSE)
	{
		memset(&m_si, 0, sizeof(SCROLLINFO));
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

		TinyMemDC memdc(hDC, ps.rcPaint);

		DrawArrow(memdc, m_iLastingCode, FALSE);
		DrawThumb(memdc, m_iLastingCode, FALSE);
		DrawGroove(memdc);

		memdc.Render(ps.rcPaint, FALSE);

		EndPaint(m_hWND, &ps);
		return FALSE;
	}

	LRESULT TinyScroll::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return TRUE;
	}

	LRESULT TinyScroll::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		//POINT ps = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		//INT code = ScrollHitTest(ps);
		//if (code != m_iLastCode)
		//{
		//	m_iLastCode = code;

		//	SCROLLCALC sc = { 0 };
		//	ScrollCalculate(&sc);

		//	HDC hDC = GetDC(m_hWND);
		//	TinyMemDC mendc(hDC, sc.rectangle);

		//	//绘制上箭头
		//	TinyMemDC mendc1(mendc, m_arrow_up_normal, m_arrow_up_normal.GetRectangle());
		//	mendc1.Render(m_arrow_up_normal.GetRectangle(), TRUE);
		//	//绘制槽
		//	TinyMemDC mendc2(mendc, m_scrollbar_groove, m_scrollbar_groove.GetRectangle());
		//	mendc1.Render(m_scrollbar_groove.GetRectangle(), TRUE);
		//	//绘制滑块
		//	TinyMemDC mendc2(mendc, m_scrollbar_groove, m_scrollbar_groove.GetRectangle());
		//	mendc1.Render(m_scrollbar_groove.GetRectangle(), TRUE);
		//	//绘制下箭头

		//	mendc.Render(sc.rectangle, FALSE);

		//	ReleaseDC(m_hWND, hDC);
		//}

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
		//加载图片
		m_arrow_down_hover.Load("E:\\ScrollBar\\arrow_down_hover.png");
		m_arrow_down_normal.Load("E:\\ScrollBar\\arrow_down_normal.png");
		m_arrow_down_press.Load("E:\\ScrollBar\\arrow_down_press.png");
		m_arrow_up_hover.Load("E:\\ScrollBar\\arrow_up_hover.png");
		m_arrow_up_normal.Load("E:\\ScrollBar\\arrow_up_normal.png");
		m_arrow_up_press.Load("E:\\ScrollBar\\arrow_up_press.png");
		m_scrollbar_groove.Load("E:\\ScrollBar\\scrollbar_groove.png");
		m_scrollbar_hover.Load("E:\\ScrollBar\\scrollbar_hover.png");
		m_scrollbar_normal.Load("E:\\ScrollBar\\scrollbar_normal.png");
		return FALSE;
	}

	LRESULT TinyScroll::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}
	void TinyScroll::ScrollCalculate(LPSCROLLCALC ps)
	{
		ASSERT(ps);
		SetRect(&ps->rectangle, 0, 0, m_size.cx, m_size.cy);
		INT arrow_size = SM_CYVSCROLL;
		INT groove_size = TO_CY(ps->rectangle) - 2 * arrow_size;//获得滚动条槽的大小
		INT thumb_size = 0;
		INT thumb_pos = 0;
		ps->arrow[0] = ps->rectangle.top + arrow_size;
		ps->arrow[1] = ps->rectangle.bottom - arrow_size;
		INT range = (m_si.nMax - m_si.nMin) + 1;
		if (range > 0 && (m_si.nPage > (UINT)m_si.nMax || m_si.nMax <= m_si.nMin || m_si.nMax == 0))
		{
			thumb_size = MulDiv(m_si.nPage, groove_size, range);
			thumb_pos = MulDiv(m_si.nPos - m_si.nMin, groove_size - thumb_size, range - max(1, m_si.nPage));
			if (thumb_pos < 0)
				thumb_pos = 0;
			if (thumb_pos >= (groove_size - thumb_size))
				thumb_pos = groove_size - thumb_size;
			thumb_pos += ps->rectangle.top + arrow_size;
			ps->thumb[0] = thumb_pos;
			ps->thumb[1] = thumb_pos + thumb_size;
		}
		else
		{
			ps->thumb[0] = ps->thumb[1] = 0;
		}
	}
	INT  TinyScroll::ScrollHitTest(POINT ps)
	{
		SCROLLCALC sc = { 0 };
		ScrollCalculate(&sc);
		if (!PtInRect(&sc.rectangle, ps)) return HTSCROLL_NONE;
		if (ps.y < sc.arrow[0]) return HTSCROLL_LINEUP;
		if (ps.y > sc.arrow[0] && ps.y < sc.arrow[1]) return HTSCROLL_PAGEUP;
		if ((ps.y >= sc.thumb[0] && ps.y <= sc.thumb[1])
			&& (sc.thumb[0] > 0 && (sc.thumb[1] > sc.thumb[0]))) return HTSCROLL_THUMB;
		if (ps.y > sc.thumb[1] && ps.y < sc.arrow[1]) return HTSCROLL_PAGEDOWN;
		if (ps.y >= sc.arrow[1]) return HTSCROLL_LINEDOWN;
		return HTSCROLL_NONE;
	}
	void TinyScroll::SetScrollInfo(SCROLLINFO si)
	{
		m_si = si;
		InvalidateRect(m_hWND, NULL, FALSE);
	}
	void TinyScroll::DrawArrow(HDC hDC, INT code, BOOL bMouseDown)
	{
		ASSERT(hDC);
		SCROLLCALC sc = { 0 };
		ScrollCalculate(&sc);
		if (code == HTSCROLL_NONE)
		{
			RECT rcPaint1 = { sc.rectangle.left, sc.rectangle.top, sc.rectangle.right, sc.arrow[0] };
			TinyMemDC dc1(hDC, m_arrow_up_normal, m_arrow_up_normal.GetRectangle());
			dc1.Render(rcPaint1, TRUE);

			RECT rcPaint2 = { sc.rectangle.left, sc.arrow[1], sc.rectangle.right, sc.rectangle.bottom };
			TinyMemDC dc2(hDC, m_arrow_down_normal, m_arrow_down_normal.GetRectangle());
			dc2.Render(rcPaint2, TRUE);
		}
		if (code == HTSCROLL_LINEUP)
		{
			if (bMouseDown)
			{
				RECT rcPaint1 = { sc.rectangle.left, sc.rectangle.top, sc.rectangle.right, sc.arrow[0] };
				TinyMemDC dc1(hDC, m_arrow_up_press, m_arrow_up_press.GetRectangle());
				dc1.Render(rcPaint1, TRUE);
			}
			else
			{
				RECT rcPaint1 = { sc.rectangle.left, sc.rectangle.top, sc.rectangle.right, sc.arrow[0] };
				TinyMemDC dc1(hDC, m_arrow_up_hover, m_arrow_up_hover.GetRectangle());
				dc1.Render(rcPaint1, TRUE);
			}

			RECT rcPaint2 = { sc.rectangle.left, sc.arrow[1], sc.rectangle.right, sc.rectangle.bottom };
			TinyMemDC dc2(hDC, m_arrow_down_normal, m_arrow_down_normal.GetRectangle());
			dc2.Render(rcPaint2, TRUE);
		}
		if (code == HTSCROLL_LINEDOWN)
		{
			RECT rcPaint1 = { sc.rectangle.left, sc.rectangle.top, sc.rectangle.right, sc.arrow[0] };
			TinyMemDC dc1(hDC, m_arrow_up_normal, m_arrow_up_normal.GetRectangle());
			dc1.Render(rcPaint1, TRUE);

			if (bMouseDown)
			{
				RECT rcPaint2 = { sc.rectangle.left, sc.arrow[1], sc.rectangle.right, sc.rectangle.bottom };
				TinyMemDC dc2(hDC, m_arrow_down_press, m_arrow_down_press.GetRectangle());
				dc2.Render(rcPaint2, TRUE);
			}
			else
			{
				RECT rcPaint2 = { sc.rectangle.left, sc.arrow[1], sc.rectangle.right, sc.rectangle.bottom };
				TinyMemDC dc2(hDC, m_arrow_down_hover, m_arrow_down_hover.GetRectangle());
				dc2.Render(rcPaint2, TRUE);
			}
		}
	}
	void TinyScroll::DrawThumb(HDC hDC, INT code, BOOL bMouseDown)
	{
		ASSERT(hDC);
		SCROLLCALC sc = { 0 };
		ScrollCalculate(&sc);
		if (code == HTSCROLL_NONE)
		{
			RECT rcPaint = { sc.rectangle.left, sc.thumb[0], sc.rectangle.right, sc.thumb[1] };
			TinyMemDC dc(hDC, m_scrollbar_normal, m_scrollbar_normal.GetRectangle());
			dc.Render(rcPaint, TRUE);
		}
		if (code == HTSCROLL_THUMB)
		{
			RECT rcPaint = { sc.rectangle.left, sc.thumb[0], sc.rectangle.right, sc.thumb[1] };
			TinyMemDC dc(hDC, m_scrollbar_hover, m_scrollbar_hover.GetRectangle());
			dc.Render(rcPaint, TRUE);
		}
	}
	void TinyScroll::DrawGroove(HDC hDC)
	{
		ASSERT(hDC);
		SCROLLCALC sc = { 0 };
		ScrollCalculate(&sc);
		RECT rcPaint = { sc.rectangle.left, sc.arrow[0], sc.rectangle.right, sc.thumb[1] };
		TinyMemDC dc(hDC, m_scrollbar_groove, m_scrollbar_groove.GetRectangle());
		dc.Render(rcPaint, TRUE);
	}

}
