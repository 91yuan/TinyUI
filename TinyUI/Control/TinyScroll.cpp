#include "../stdafx.h"
#include "TinyScroll.h"

namespace TinyUI
{
	TinyScroll::TinyScroll()
		:m_bTracking(FALSE),
		m_iTrackingCode(0),
		m_iOffsetPos(0),
		m_iLastCode(0)
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

		DrawScrollBar(memdc, 0);

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
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		if (m_bTracking && (wParam & MK_LBUTTON))
		{
			if (m_iTrackingCode == HTSCROLL_THUMB)
			{
				ScrollTrackThumb(pt);
				return FALSE;
			}
		}
		return FALSE;
	}

	LRESULT TinyScroll::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		INT iHitTest = ScrollHitTest(pt);
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

	void TinyScroll::ScrollCalculate(SCROLLCALC* ps)
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
	void TinyScroll::ScrollTrackThumb(POINT& pt)
	{
		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);
		INT iPos = 0;
		INT iRange = (m_si.nMax - m_si.nMin) + 1;
		INT iThumbPos = (pt.y - m_iOffsetPos) - si.arrowRectangle[0].bottom;
		INT iThumbSize = TO_CY(si.thumbRectangle);
		INT iGrooveSize = si.arrowRectangle[1].top - si.arrowRectangle[0].bottom;
		if (iThumbPos < 0)
			iThumbPos = 0;
		if (iThumbPos >(iGrooveSize - iThumbSize))
			iThumbPos = iGrooveSize - iThumbSize;
		if (iRange > 0)
			iPos = MulDiv(iThumbPos, iRange - m_si.nPage, iGrooveSize - iThumbSize);
		if (m_si.nPos != iPos)
		{
			m_si.nTrackPos = iPos;
			TRACE("当前位置iPos: %d\n" + iPos);
		}
	}
	void TinyScroll::DrawScrollBar(TinyMemDC& dc, INT iHitTest)
	{
		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);

		DrawArrow(dc, &si);
		DrawGroove(dc, &si);
		DrawThumb(dc, &si);

	}
	void TinyScroll::DrawArrow(TinyMemDC& dc, SCROLLCALC* ps)
	{
		TinyMemDC memdc1(dc, m_images[0]);
		memdc1.Render(ps->arrowRectangle[0], m_images[0].GetRectangle(), TRUE);
		TinyMemDC memdc2(dc, m_images[3]);
		memdc2.Render(ps->arrowRectangle[1], m_images[3].GetRectangle(), TRUE);
	}
	void TinyScroll::DrawThumb(TinyMemDC& dc, SCROLLCALC* ps)
	{
		TinyMemDC memdc(dc, m_images[8]);
		RECT dstCenter, srcCenter;
		CopyRect(&srcCenter, &m_images[8].GetRectangle());
		srcCenter.top = srcCenter.top + 3;
		srcCenter.bottom = srcCenter.bottom - 3;
		CopyRect(&dstCenter, &ps->thumbRectangle);
		dstCenter.top = dstCenter.top + 3;
		dstCenter.bottom = dstCenter.bottom - 3;
		memdc.Render(ps->thumbRectangle, dstCenter, m_images[8].GetRectangle(), srcCenter, TRUE);
	}
	void TinyScroll::DrawGroove(TinyMemDC& dc, SCROLLCALC* ps)
	{
		TinyMemDC memdc(dc, m_images[7]);
		RECT dstCenter, srcCenter;
		CopyRect(&srcCenter, &m_images[7].GetRectangle());
		srcCenter.top = srcCenter.top + 3;
		srcCenter.bottom = srcCenter.bottom - 3;
		RECT grooveRectangle;
		CopyRect(&grooveRectangle, &ps->rectangle);
		grooveRectangle.top = ps->arrowRectangle[0].bottom;
		grooveRectangle.bottom = ps->arrowRectangle[1].top;
		CopyRect(&dstCenter, &grooveRectangle);
		dstCenter.top = dstCenter.top + 3;
		dstCenter.bottom = dstCenter.bottom - 3;
		memdc.Render(grooveRectangle, dstCenter, m_images[7].GetRectangle(), srcCenter, TRUE);
	}
	void TinyScroll::SetScrollInfo(INT iMax, INT iMin, INT iPage, INT iPos)
	{
		m_si.nMax = iMax;
		m_si.nMin = iMin;
		m_si.nPage = iPage;
		m_si.nPos = iPos;
	}
	INT	TinyScroll::ScrollHitTest(POINT& pt)
	{
		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);
		if (!PtInRect(&si.rectangle, pt))
			return HTSCROLL_NONE;
		if (pt.y >= si.arrowRectangle[0].top && pt.y < si.arrowRectangle[0].bottom)
			return HTSCROLL_LINEUP;
		if (pt.y >= si.pageRectangle[0].top && pt.y < si.pageRectangle[0].bottom)
			return HTSCROLL_PAGEUP;
		if (pt.y >= si.thumbRectangle.top && pt.y <= si.thumbRectangle.bottom)
			return HTSCROLL_THUMB;
		if (pt.y > si.pageRectangle[1].top && pt.y < si.pageRectangle[1].bottom)
			return HTSCROLL_PAGEDOWN;
		if (pt.y >= si.arrowRectangle[1].top && pt.y < si.arrowRectangle[1].bottom)
			return HTSCROLL_LINEDOWN;
		return HTSCROLL_NONE;
	}
}
