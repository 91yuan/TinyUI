#include "../stdafx.h"
#include "TinyMenuBox.h"

namespace TinyUI
{
	TinyMenuItem::TinyMenuItem(BOOL bBreak)
		:m_fState(0),
		m_bBreak(bBreak),
		m_pChild(NULL),
		m_cy(MENUITEM_DEFAULT_HEIGHT)
	{
		memset(m_pzText, 0, 150 * sizeof(CHAR));
	}
	TinyMenuItem::~TinyMenuItem()
	{

	}
	void TinyMenuItem::SetText(LPCSTR pzText)
	{
		ASSERT(pzText);
		strcpy_s(m_pzText, 150, pzText);
	}
	LPCSTR TinyMenuItem::GetText() const
	{
		return m_pzText;
	}
	void TinyMenuItem::SetCheck(BOOL bFlag)
	{
		m_fState = bFlag ? (m_fState |= STATE_CHECKED) : (m_fState &= ~STATE_CHECKED);
		if (m_pOwner != NULL)
		{
			m_pOwner->Recalculate();
			::InvalidateRect(m_pOwner->Handle(), NULL, FALSE);
		}
	}
	BOOL TinyMenuItem::IsChecked()
	{
		return m_fState & STATE_CHECKED;
	}
	BOOL TinyMenuItem::IsDisabled()
	{
		return m_fState & STATE_DISABLED;
	}
	void TinyMenuItem::SetDisable(BOOL bFlag)
	{
		m_fState = bFlag ? (m_fState |= STATE_DISABLED) : (m_fState &= ~STATE_DISABLED);
		if (m_pOwner != NULL)
		{
			m_pOwner->Recalculate();
			::InvalidateRect(m_pOwner->Handle(), NULL, FALSE);
		}
	}
	void TinyMenuItem::SetChild(TinyMenuBox* ps)
	{
		m_pChild = ps;
	}
	//////////////////////////////////////////////////////////////////////////
	TinyMenuBox::TinyMenuBox()
		:m_bMouseTracking(FALSE),
		m_bMouseDown(FALSE),
		m_pParent(NULL),
		m_pChild(NULL),
		m_pHoverItem(NULL)
	{

	}
	TinyMenuBox::~TinyMenuBox()
	{

	}
	BOOL TinyMenuBox::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	DWORD TinyMenuBox::RetrieveStyle()
	{
		return WS_VISIBLE | WS_POPUP;
	}
	DWORD TinyMenuBox::RetrieveExStyle()
	{
		return WS_EX_LEFT | WS_EX_LTRREADING;
	}
	LRESULT TinyMenuBox::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_images[0].Load("D:\\Menu\\menu_bkg.png");
		m_images[1].Load("D:\\Menu\\menu_highlight.png");
		m_images[2].Load("D:\\Menu\\menu_check.png");
		m_images[3].Load("D:\\Menu\\menu_cutling.png");
		m_images[4].Load("D:\\Menu\\menu_arrow.png");
		return FALSE;
	}

	LRESULT TinyMenuBox::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	LRESULT TinyMenuBox::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return TRUE;
	}

	LRESULT TinyMenuBox::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		if (!m_bMouseTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWND;
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 10;
			m_bMouseTracking = _TrackMouseEvent(&tme);
		}

		HDC hDC = GetDC(m_hWND);
		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		DrawMenu(memdc, GetAt(pt));
		memdc.Render(paintRC, paintRC, FALSE);
		ReleaseDC(m_hWND, hDC);
		return FALSE;
	}

	LRESULT TinyMenuBox::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (m_bMouseTracking)
		{
			m_bMouseTracking = FALSE;
			HDC hDC = GetDC(m_hWND);
			TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
			RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
			FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawMenu(memdc, m_pHoverItem);
			memdc.Render(paintRC, paintRC, FALSE);
			ReleaseDC(m_hWND, hDC);
		}
		return FALSE;
	}

	LRESULT TinyMenuBox::OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (m_bMouseTracking)
		{
			m_bMouseTracking = FALSE;
			DWORD dwPos = GetMessagePos();
			POINT pt = { GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos) };
			ScreenToClient(m_hWND, &pt);
			TinyMenuItem* pItem = GetAt(pt);
			if (pItem != NULL)
			{
				m_pHoverItem = pItem;
				if (pItem->m_pChild != NULL)
				{
					if (m_pChild != pItem->m_pChild)
					{
						if (m_pChild != NULL && m_pChild->IsPopup())
						{
							TinyMenuBox* ps = m_pChild;
							while (ps != NULL)
							{
								ps->m_pHoverItem = NULL;
								ps->DestroyWindow();
								ps = ps->m_pChild;
							}
						}
						m_pChild = pItem->m_pChild;
						for (INT i = 0; i < m_pChild->m_items.GetSize(); i++)
						{
							m_pChild->m_pParent = this;
						}
					}
					if (!m_pChild->IsPopup())
					{
						RECT rect = pItem->m_rectangle;
						ClientToScreen(m_hWND, (LPPOINT)&rect);
						ClientToScreen(m_hWND, (LPPOINT)&rect + 1);
						pt.x = rect.right;
						pt.y = rect.top;
						m_pChild->Popup(pt);
					}
				}
				else
				{
					TinyMenuBox* ps = m_pChild;
					while (ps != NULL)
					{
						ps->m_pHoverItem = NULL;
						ps->DestroyWindow();
						ps = ps->m_pChild;
					}
				}
			}
		}
		return FALSE;
	}

	LRESULT TinyMenuBox::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyMenuBox::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		TinyMenuItem* pItem = GetAt(pt);
		if (pItem != NULL)
		{
			if (pItem->m_pChild == NULL)
			{
				TinyMenuBox* pMenu = pItem->m_pOwner;
				while (pMenu != NULL)
				{
					pMenu->m_pHoverItem = NULL;
					pMenu->DestroyWindow();
					pMenu = pMenu->m_pParent;
				}
				Click(pItem);
			}
		}
		return FALSE;
	}
	LRESULT TinyMenuBox::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyMenuBox::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PAINTSTRUCT ps = { 0 };
		HDC hDC = BeginPaint(m_hWND, &ps);

		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));

		DrawMenu(memdc);

		memdc.Render(paintRC, paintRC, FALSE);
		EndPaint(m_hWND, &ps);
		return FALSE;
	}
	LRESULT TinyMenuBox::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			TRACE("WA_INACTIVE\n");
			DestroyWindow();
		}
		if (LOWORD(wParam) == WA_ACTIVE)
		{
			TRACE("WA_ACTIVE\n");
		}
		return FALSE;
	}
	BOOL TinyMenuBox::AddItem(TinyMenuItem* pz)
	{
		if (m_items.Add(pz))
		{
			pz->m_pOwner = this;
			Recalculate();
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyMenuBox::InsertItem(INT index, TinyMenuItem* pz)
	{
		if (m_items.Insert(index, pz))
		{
			pz->m_pOwner = this;
			Recalculate();
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyMenuBox::RemoveItem(TinyMenuItem* pz)
	{
		if (m_items.Remove(pz))
		{
			Recalculate();
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyMenuBox::RemoveAt(INT index)
	{
		if (m_items.RemoveAt(index))
		{
			Recalculate();
			return TRUE;
		}
		return FALSE;
	}
	void TinyMenuBox::RemoveAll()
	{
		m_items.RemoveAll();
		RedrawMenu();
	}
	void TinyMenuBox::RedrawMenu()
	{
		HDC hDC = GetDC(m_hWND);

		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
		DrawMenu(memdc);
		memdc.Render(paintRC, paintRC, FALSE);

		ReleaseDC(m_hWND, hDC);
	}
	void TinyMenuBox::Recalculate()
	{
		RECT rectangle = { 0, 0, m_size.cx, m_size.cy };
		INT cy = 0;
		INT size = m_items.GetSize();
		for (INT i = 0; i < size; i++)
		{
			TinyMenuItem* ps = m_items[i];
			if (ps->m_bBreak)
			{
				ps->m_rectangle.left = rectangle.left;
				ps->m_rectangle.top = cy;
				ps->m_rectangle.right = rectangle.right;
				ps->m_rectangle.bottom = ps->m_rectangle.top + MENUITEM_BREAK_HEIGHT;
			}
			else
			{
				ps->m_rectangle.left = rectangle.left;
				ps->m_rectangle.top = cy;
				ps->m_rectangle.right = rectangle.right;
				ps->m_rectangle.bottom = ps->m_rectangle.top + ps->m_cy;
			}
			cy += TO_CY(ps->m_rectangle);
		}
	}
	TinyMenuItem* TinyMenuBox::GetAt(POINT& pt)
	{
		INT size = m_items.GetSize();
		for (INT i = 0; i < size; i++)
		{
			if (PtInRect(&m_items[i]->m_rectangle, pt))
				return m_items[i];
		}
		return NULL;
	}
	void TinyMenuBox::DrawMenu(TinyMemDC& dc, TinyMenuItem* hotItem)
	{
		DrawMenuItems(dc, hotItem);
	}
	void TinyMenuBox::DrawMenuItems(TinyMemDC& dc, TinyMenuItem* hotItem)
	{
		INT iSaveDC = dc.SaveDC();
		INT iOldMode = dc.SetBkMode(TRANSPARENT);
		TinyMemDC memdc(dc, m_images[0]);
		//绘制背景
		RECT dstPaint = { 0, 0, m_size.cx, m_size.cy };
		RECT srcPaint = m_images[0].GetRectangle();
		srcPaint.left += 5;
		srcPaint.top += 5;
		srcPaint.right -= 5;
		srcPaint.bottom -= 5;
		RECT srcCenter = { srcPaint.left + 4, srcPaint.top + 4, srcPaint.right - 4, srcPaint.bottom - 4 };
		memdc.Render(dstPaint, srcPaint, srcCenter, TRUE);
		HFONT hOldFont = (HFONT)dc.SelectObject((HPEN)GetStockObject(DEFAULT_GUI_FONT));
		//绘制文字和分隔符
		INT size = m_items.GetSize();
		for (INT i = 0; i < size; i++)
		{
			TinyMenuItem* ps = m_items[i];
			LPCSTR pzText = ps->GetText();
			if (!ps->m_bBreak)
			{
				if (hotItem != NULL && hotItem == ps)//高亮
				{
					RECT rect = ps->m_rectangle;
					RECT rcPaint = { rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2 };
					TinyMemDC imagedc1(dc, m_images[1]);
					imagedc1.Render(rcPaint, m_images[1].GetRectangle(), TRUE);
					if (hotItem->IsChecked())
					{
						RECT imageRect = m_images[2].GetRectangle();
						SetRect(&rcPaint, imageRect.left, imageRect.top, imageRect.right, imageRect.bottom);
						OffsetRect(&rcPaint, rect.left + 8, rect.top + (MENUITEM_DEFAULT_HEIGHT - TO_CY(imageRect)) / 2);
						TinyMemDC imagedc2(dc, m_images[2]);
						imagedc2.Render(rcPaint, imageRect, TRUE);
					}
					if (ps->m_pChild != NULL)
					{
						RECT imageRect = m_images[4].GetRectangle();
						SetRect(&rcPaint, imageRect.left, imageRect.top, imageRect.right, imageRect.bottom);
						OffsetRect(&rcPaint, rect.right - TO_CX(imageRect) - 8, rect.top + (MENUITEM_DEFAULT_HEIGHT - TO_CY(imageRect)) / 2);
						TinyMemDC imagedc3(dc, m_images[4]);
						imagedc3.Render(rcPaint, imageRect, TRUE);
					}
					::SetTextColor(dc, RGB(255, 255, 255));
					rect.left = rect.left + 45;
					rect.top = rect.top + 8;
					dc.DrawText(pzText, strlen(pzText), &rect, DT_SINGLELINE);
				}
				else
				{
					RECT rect = ps->m_rectangle;
					if (ps->IsChecked())
					{
						RECT imageRect = m_images[2].GetRectangle();
						RECT rcPaint = { 0 };
						SetRect(&rcPaint, imageRect.left, imageRect.top, imageRect.right, imageRect.bottom);
						OffsetRect(&rcPaint, rect.left + 8, rect.top + (MENUITEM_DEFAULT_HEIGHT - TO_CY(imageRect)) / 2);
						TinyMemDC imagedc1(dc, m_images[2]);
						imagedc1.Render(rcPaint, imageRect, TRUE);
					}
					if (ps->m_pChild != NULL)
					{
						RECT imageRect = m_images[4].GetRectangle();
						RECT rcPaint = { 0 };
						SetRect(&rcPaint, imageRect.left, imageRect.top, imageRect.right, imageRect.bottom);
						OffsetRect(&rcPaint, rect.right - TO_CX(imageRect) - 8, rect.top + (MENUITEM_DEFAULT_HEIGHT - TO_CY(imageRect)) / 2);
						TinyMemDC imagedc2(dc, m_images[4]);
						imagedc2.Render(rcPaint, imageRect, TRUE);
					}
					::SetTextColor(dc, RGB(0, 0, 0));
					rect.left = rect.left + 45;
					rect.top = rect.top + 8;
					dc.DrawText(pzText, strlen(pzText), &rect, DT_SINGLELINE);
				}
			}
			else
			{
				TinyMemDC imagedc(dc, m_images[3]);
				RECT rect = ps->m_rectangle;
				rect.left = rect.left + 35;
				rect.right = rect.right - 3;
				imagedc.Render(rect, m_images[3].GetRectangle(), TRUE);
			}
		}
		dc.SelectObject(hOldFont);
		dc.SetBkMode(iOldMode);
		dc.RestoreDC(iSaveDC);
	}
	BOOL TinyMenuBox::Popup(POINT& pt)
	{
		INT size = m_items.GetSize();
		if (size > 0)
		{
			SetWindowPos(m_hWND,
				NULL,
				pt.x,
				pt.y,
				TO_CX(m_items[size - 1]->m_rectangle),
				m_items[size - 1]->m_rectangle.bottom,
				SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER);
			UpdateWindow(m_hWND);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyMenuBox::IsPopup()
	{
		return ::IsWindowVisible(m_hWND);
	}
}