#include "../stdafx.h"
#include "TinyScroll.h"

namespace TinyUI
{
	TinyScroll::TinyScroll()
		:m_bTracking(FALSE),
		m_bMouseTracking(FALSE),
		m_iOffsetPos(0),
		m_iTrackingCode(HTSCROLL_NONE)
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

		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));

		DrawScrollBar(memdc, HTSCROLL_NONE, FALSE);

		memdc.Render(paintRC, paintRC, FALSE);
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
				SCROLLCALC si = { 0 };
				ScrollCalculate(&si);
				ScrollTrackThumb(pt, &si);
				HDC hDC = GetDC(m_hWND);
				TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
				RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
				FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
				DrawScrollBar(memdc, HTSCROLL_THUMB, wParam & MK_LBUTTON);
				memdc.Render(paintRC, paintRC, FALSE);
				ReleaseDC(m_hWND, hDC);
				return FALSE;
			}
		}
		INT iHitTest = ScrollHitTest(pt);
		HDC hDC = GetDC(m_hWND);
		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
		DrawScrollBar(memdc, iHitTest, wParam & MK_LBUTTON);
		memdc.Render(paintRC, paintRC, FALSE);
		ReleaseDC(m_hWND, hDC);

		return FALSE;
	}

	LRESULT TinyScroll::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

		if (!m_bMouseTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWND;
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 0;
			m_bMouseTracking = _TrackMouseEvent(&tme);
		}

		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);

		INT iHitTest = ScrollHitTest(pt);
		if (iHitTest == HTSCROLL_THUMB)
		{
			m_iOffsetPos = pt.y - si.thumbRectangle.top;
		}
		m_iTrackingCode = iHitTest;
		m_bTracking = TRUE;

		HDC hDC = GetDC(m_hWND);
		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
		DrawScrollBar(memdc, iHitTest, TRUE);
		memdc.Render(paintRC, paintRC, FALSE);
		ReleaseDC(m_hWND, hDC);

		SetCapture(m_hWND);

		return FALSE;
	}

	LRESULT TinyScroll::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		m_iOffsetPos = 0;
		m_bTracking = FALSE;

		if (m_iTrackingCode == HTSCROLL_THUMB)
		{
			HDC hDC = GetDC(m_hWND);
			TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
			RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
			FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawScrollBar(memdc, HTSCROLL_NONE, FALSE);
			memdc.Render(paintRC, paintRC, FALSE);
			ReleaseDC(m_hWND, hDC);
		}

		ReleaseCapture();

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
	LRESULT TinyScroll::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		m_bMouseTracking = FALSE;

		if (m_bTracking)
			return FALSE;
		HDC hDC = GetDC(m_hWND);
		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
		DrawScrollBar(memdc, HTSCROLL_NONE, FALSE);
		memdc.Render(paintRC, paintRC, FALSE);
		ReleaseDC(m_hWND, hDC);

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
	void TinyScroll::ScrollTrackThumb(POINT& pt, SCROLLCALC* ps)
	{
		ASSERT(ps);
		INT iPos = 0;
		INT iRange = (m_si.nMax - m_si.nMin) + 1;
		INT iThumbPos = (pt.y - m_iOffsetPos) - ps->arrowRectangle[0].bottom;
		INT iThumbSize = TO_CY(ps->thumbRectangle);
		INT iGrooveSize = ps->arrowRectangle[1].top - ps->arrowRectangle[0].bottom;
		if (iThumbPos < 0)
			iThumbPos = 0;
		if (iThumbPos >(iGrooveSize - iThumbSize))
			iThumbPos = iGrooveSize - iThumbSize;
		if (iRange > 0)
			iPos = MulDiv(iThumbPos, iRange - m_si.nPage, iGrooveSize - iThumbSize);
		if (m_si.nPos != iPos)
		{
			m_si.nPos = iPos;
			TRACE("iPos:%d\n", iPos);
		}
	}
	void TinyScroll::DrawScrollBar(TinyMemDC& dc, INT iHitTest, BOOL bMouseDown)
	{
		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);
		DrawArrow(dc, &si, iHitTest, bMouseDown);
		DrawGroove(dc, &si);
		DrawThumb(dc, &si, iHitTest);
	}
	void TinyScroll::DrawArrow(TinyMemDC& dc, SCROLLCALC* ps, INT iHitTest, BOOL bMouseDown)
	{
		if (iHitTest == HTSCROLL_LINEUP)
		{
			if (bMouseDown)
			{
				TinyMemDC memdc1(dc, m_images[2]);
				memdc1.Render(ps->arrowRectangle[0], m_images[2].GetRectangle(), TRUE);
				TinyMemDC memdc2(dc, m_images[3]);
				memdc2.Render(ps->arrowRectangle[1], m_images[3].GetRectangle(), TRUE);
			}
			else
			{
				TinyMemDC memdc1(dc, m_images[1]);
				memdc1.Render(ps->arrowRectangle[0], m_images[1].GetRectangle(), TRUE);
				TinyMemDC memdc2(dc, m_images[3]);
				memdc2.Render(ps->arrowRectangle[1], m_images[3].GetRectangle(), TRUE);
			}
		}
		else if (iHitTest == HTSCROLL_LINEDOWN)
		{
			if (bMouseDown)
			{
				TinyMemDC memdc1(dc, m_images[0]);
				memdc1.Render(ps->arrowRectangle[0], m_images[0].GetRectangle(), TRUE);
				TinyMemDC memdc2(dc, m_images[5]);
				memdc2.Render(ps->arrowRectangle[1], m_images[5].GetRectangle(), TRUE);
			}
			else
			{
				TinyMemDC memdc1(dc, m_images[0]);
				memdc1.Render(ps->arrowRectangle[0], m_images[0].GetRectangle(), TRUE);
				TinyMemDC memdc2(dc, m_images[4]);
				memdc2.Render(ps->arrowRectangle[1], m_images[4].GetRectangle(), TRUE);
			}
		}
		else
		{
			TinyMemDC memdc1(dc, m_images[0]);
			memdc1.Render(ps->arrowRectangle[0], m_images[0].GetRectangle(), TRUE);
			TinyMemDC memdc2(dc, m_images[3]);
			memdc2.Render(ps->arrowRectangle[1], m_images[3].GetRectangle(), TRUE);
		}
	}
	void TinyScroll::DrawThumb(TinyMemDC& dc, SCROLLCALC* ps, INT iHitTest)
	{
		if (iHitTest == HTSCROLL_THUMB)
		{
			TinyMemDC memdc(dc, m_images[8]);
			RECT dstCenter, srcCenter;
			CopyRect(&srcCenter, &m_images[8].GetRectangle());
			srcCenter.top = srcCenter.top + 4;
			srcCenter.bottom = srcCenter.bottom - 4;
			CopyRect(&dstCenter, &ps->thumbRectangle);
			dstCenter.top = dstCenter.top + 4;
			dstCenter.bottom = dstCenter.bottom - 4;
			memdc.Render(ps->thumbRectangle, dstCenter, m_images[8].GetRectangle(), srcCenter, TRUE);
		}
		else
		{
			TinyMemDC memdc(dc, m_images[7]);
			RECT dstCenter, srcCenter;
			CopyRect(&srcCenter, &m_images[7].GetRectangle());
			srcCenter.top = srcCenter.top + 4;
			srcCenter.bottom = srcCenter.bottom - 4;
			CopyRect(&dstCenter, &ps->thumbRectangle);
			dstCenter.top = dstCenter.top + 4;
			dstCenter.bottom = dstCenter.bottom - 4;
			memdc.Render(ps->thumbRectangle, dstCenter, m_images[7].GetRectangle(), srcCenter, TRUE);
		}
	}
	void TinyScroll::DrawGroove(TinyMemDC& dc, SCROLLCALC* ps)
	{
		TinyMemDC memdc(dc, m_images[7]);
		RECT dstCenter, srcCenter;
		CopyRect(&srcCenter, &m_images[7].GetRectangle());
		srcCenter.top = srcCenter.top + 4;
		srcCenter.bottom = srcCenter.bottom - 4;
		RECT grooveRectangle;
		CopyRect(&grooveRectangle, &ps->rectangle);
		grooveRectangle.top = ps->arrowRectangle[0].bottom;
		grooveRectangle.bottom = ps->arrowRectangle[1].top;
		CopyRect(&dstCenter, &grooveRectangle);
		dstCenter.top = dstCenter.top + 4;
		dstCenter.bottom = dstCenter.bottom - 4;
		memdc.Render(grooveRectangle, dstCenter, m_images[7].GetRectangle(), srcCenter, TRUE);
	}
	BOOL TinyScroll::SetScrollInfo(INT iMin, INT iMax, INT iPage, INT iPos)
	{
		if (iMin <= iPos && iPos <= (iMax - iPage + 1))
		{
			m_si.nMin = iMin;
			m_si.nMax = iMax;
			m_si.nPage = iPage;
			m_si.nPos = iPos;
			InvalidateRect(m_hWND, NULL, FALSE);
			return TRUE;
		}
		else
		{
			m_si.nMax = m_si.nPos = m_si.nMin;
			m_si.nPage = m_si.nMax - m_si.nPos + 1;
			InvalidateRect(m_hWND, NULL, FALSE);
		}
		return FALSE;
	}
	INT	TinyScroll::ScrollHitTest(POINT& pt)
	{
		SCROLLCALC si = { 0 };
		ScrollCalculate(&si);
		if (pt.y >= si.arrowRectangle[0].top && pt.y < si.arrowRectangle[0].bottom)
			return HTSCROLL_LINEUP;
		if (pt.y >= si.pageRectangle[0].top && pt.y < si.pageRectangle[0].bottom)
			return HTSCROLL_PAGEUP;
		if (pt.y >= si.thumbRectangle.top && pt.y < si.thumbRectangle.bottom)
			return HTSCROLL_THUMB;
		if (pt.y >= si.pageRectangle[1].top && pt.y < si.pageRectangle[1].bottom)
			return HTSCROLL_PAGEDOWN;
		if (pt.y >= si.arrowRectangle[1].top && pt.y < si.arrowRectangle[1].bottom)
			return HTSCROLL_LINEDOWN;
		return HTSCROLL_NONE;
	}
}
