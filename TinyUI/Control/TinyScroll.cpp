#include "../stdafx.h"
#include "TinyScroll.h"

namespace TinyUI
{
	TinyScroll::TinyScroll()
		:m_bTracking(FALSE)
	{
		memset(&m_si, 0, sizeof(SCROLLINFO));
		m_si.cbSize = sizeof(SCROLLINFO);
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
		TinyMemDC memdc(hDC, TO_CX(ps.rcPaint), TO_CY(ps.rcPaint));
		FillRect(memdc, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));



		memdc.Render(ps.rcPaint, ps.rcPaint, FALSE);
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
		//上箭头
		m_images[0].Load("E:\\ScrollBar\\1_arrow_up_normal.png");
		m_images[1].Load("E:\\ScrollBar\\2_arrow_up_hover.png");
		m_images[2].Load("E:\\ScrollBar\\3_arrow_up_press.png");
		//下箭头
		m_images[3].Load("E:\\ScrollBar\\4_arrow_down_normal.png");
		m_images[4].Load("E:\\ScrollBar\\5_arrow_down_hover.png");
		m_images[5].Load("E:\\ScrollBar\\6_arrow_down_press.png");
		//划块
		m_images[6].Load("E:\\ScrollBar\\7_scrollbar_groove.png");
		m_images[7].Load("E:\\ScrollBar\\8_scrollbar_normal.png");
		m_images[8].Load("E:\\ScrollBar\\9_scrollbar_hover.png");

		return FALSE;
	}

	LRESULT TinyScroll::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	BOOL TinyScroll::ScrollCalculate(SCROLLCALC* ps)
	{
		ASSERT(ps);
		SetRect(&ps->rectangle,
			TINY_SCROLL_MARGIN_LEFT,
			TINY_SCROLL_MARGIN_TOP,
			m_size.cx - TINY_SCROLL_MARGIN_RIGHT,
			m_size.cy - TINY_SCROLL_MARGIN_BOTTOM);
		SetRect(&ps->arrowRectangle[0],
			ps->rectangle.left,
			ps->rectangle.top,
			ps->rectangle.right,
			ps->rectangle.top + TINY_SM_CYSCROLL);//上箭头的高度
		SetRect(&ps->arrowRectangle[1],
			ps->rectangle.left,
			ps->rectangle.bottom - TINY_SM_CYSCROLL,
			ps->rectangle.right,
			ps->rectangle.bottom);//下箭头的大小
		INT iRange = (m_si.nMax - m_si.nMin) + 1;
		INT iGrooveSize = ps->arrowRectangle[1].top - ps->arrowRectangle[0].bottom;//划块的槽
		BOOL bFlag = (m_si.nPage > (UINT)m_si.nMax || m_si.nMax <= m_si.nMin || m_si.nMax == 0);
		if (iRange > 0 && !bFlag)
		{
			//计算划块的大小
			INT iThumbPos = 0;
			INT iThumbSize = MulDiv(m_si.nPage, iGrooveSize, iRange);
			if (iThumbSize < TINY_SCROLL_MINTHUMB_SIZE)
				iThumbSize = TINY_SCROLL_MINTHUMB_SIZE;
			//计算Page
			INT iPageSize = max(1, m_si.nPage);
			iThumbPos = MulDiv(m_si.nPos - m_si.nMin, iGrooveSize - iThumbSize, iRange - iPageSize);
			if (iThumbPos < 0)
				iThumbPos = 0;
			if (iThumbPos >= (iGrooveSize - iThumbSize))
				iThumbPos = iGrooveSize - iThumbSize;
			iThumbPos += ps->rectangle.top + TO_CY(ps->arrowRectangle[0]);
			SetRect(&ps->thumbRectangle,
				ps->rectangle.left,
				iThumbPos,
				ps->rectangle.right,
				iThumbPos + iThumbSize);
			SetRect(&ps->pageRectangle[0],
				ps->rectangle.top,
				ps->arrowRectangle[0].bottom,
				ps->rectangle.right,
				ps->thumbRectangle.top);
			SetRect(&ps->pageRectangle[1],
				ps->rectangle.top,
				ps->thumbRectangle.top,
				ps->rectangle.right,
				ps->arrowRectangle[1].top);
		}
		else
		{
			SetRect(&ps->thumbRectangle,
				ps->rectangle.left,
				0,
				ps->rectangle.right,
				0);
			SetRect(&ps->pageRectangle[0],
				ps->rectangle.top,
				ps->arrowRectangle[0].bottom,
				ps->rectangle.right,
				ps->arrowRectangle[1].top);
			SetRect(&ps->pageRectangle[1],
				ps->rectangle.top,
				ps->arrowRectangle[0].bottom,
				ps->rectangle.right,
				ps->arrowRectangle[1].top);
		}
	}
	void TinyScroll::SetScrollInfo(INT iMax, INT iMin, INT iPage, INT iPos)
	{
		m_si.nMax = iMax;
		m_si.nMin = iMin;
		m_si.nPage = iPage;
		m_si.nPos = iPos;
	}
	INT	TinyScroll::ScrollHitTest(POINT pt)
	{
		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);
		if (!PtInRect(&si.rectangle, pt))
			return HTSCROLL_NONE;
		if (pt.y >= si.arrowRectangle[0].top && pt.y < si.arrowRectangle[0].bottom)
			return HTSCROLL_LINEUP;
		if (pt.y >= si.thumbRectangle.top && pt.y <= si.thumbRectangle.bottom)
			return HTSCROLL_THUMB;
		if (pt.y >= si.arrowRectangle[1].top && pt.y < si.arrowRectangle[1].bottom)
			return HTSCROLL_LINEDOWN;
		return HTSCROLL_NONE;
	}
}
