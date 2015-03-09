#include "../stdafx.h"
#include "TinyContextMenu.h"

namespace TinyUI
{
	TinyMenuItem::TinyMenuItem(BOOL bBreak)
		:m_fState(0),
		m_bBreak(bBreak),
		m_pChild(NULL)
	{
		memset(m_pzText, 0, 150 * sizeof(CHAR));
		m_size.cx = MENUITEM_DEFAULT_WIDTH;
		m_size.cy = bBreak ? MENUITEM_BREAK_HEIGHT : MENUITEM_DEFAULT_HEIGHT;
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
			RECT rectangle = { 0 };
			m_pOwner->Recalculate(rectangle);
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
			RECT rectangle = { 0 };
			m_pOwner->Recalculate(rectangle);
			::InvalidateRect(m_pOwner->Handle(), NULL, FALSE);
		}
	}
	void TinyMenuItem::SetChild(TinyContextMenu* ps)
	{
		m_pChild = ps;
	}
	void TinyMenuItem::SetSize(SIZE size)
	{
		m_size = size;
		if (m_pOwner != NULL)
		{
			RECT rectangle = { 0 };
			m_pOwner->Recalculate(rectangle);
			::InvalidateRect(m_pOwner->Handle(), NULL, FALSE);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	TinyContextMenu::TinyContextMenu()
		:m_bMouseTracking(FALSE),
		m_bMouseDown(FALSE),
		m_pFocusItem(NULL),
		m_pNext(NULL),
		m_pPrev(NULL)
	{

	}
	TinyContextMenu::~TinyContextMenu()
	{

	}
	DWORD TinyContextMenu::RetrieveStyle()
	{
		return  WS_POPUP;
	}
	DWORD TinyContextMenu::RetrieveExStyle()
	{
		return NULL;
	}
	LPCSTR TinyContextMenu::RetrieveClassName()
	{
		return TEXT("TinyContextMenu");
	}
	BOOL TinyContextMenu::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	LRESULT CALLBACK TinyContextMenu::MessageFilterHook(INT code, WPARAM wParam, LPARAM lParam)
	{
		if (code == HC_ACTION &&
			m_pMessageHook &&
			(INT)wParam == PM_REMOVE)
		{

		}
		return CallNextHookEx(m_pMessageHook, code, wParam, lParam);
	}
	LRESULT TinyContextMenu::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_images[0].Load("E:\\Menu\\menu_bkg.png");
		m_images[1].Load("E:\\Menu\\menu_highlight.png");
		m_images[2].Load("E:\\Menu\\menu_check.png");
		m_images[3].Load("E:\\Menu\\menu_cutling.png");
		m_images[4].Load("E:\\Menu\\menu_arrow.png");
		return FALSE;
	}
	LRESULT TinyContextMenu::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}
	LRESULT TinyContextMenu::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return TRUE;
	}
	LRESULT TinyContextMenu::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
	LRESULT TinyContextMenu::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (m_bMouseTracking)
		{
			m_bMouseTracking = FALSE;
			HDC hDC = GetDC(m_hWND);
			TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
			RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
			FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawMenu(memdc, m_pFocusItem);
			memdc.Render(paintRC, paintRC, FALSE);
			ReleaseDC(m_hWND, hDC);
		}
		return FALSE;
	}
	LRESULT TinyContextMenu::OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
				m_pFocusItem = pItem;
				if (pItem->m_pChild != NULL)
				{
					if (m_pNext != pItem->m_pChild)
					{
						if (m_pNext != NULL && m_pNext->IsPopup())
						{
							TinyContextMenu* ps = m_pNext;
							while (ps != NULL)
							{
								ps->m_pFocusItem = NULL;
								ps->Unpopup();
								ps = ps->m_pNext;
							}
						}
						m_pNext = pItem->m_pChild;
						if (m_pNext != NULL)
						{
							for (INT i = 0; i < m_pNext->m_items.GetSize(); i++)
							{
								m_pNext->m_pPrev = this;
							}
						}
					}
					if (!m_pNext->IsPopup())
					{
						RECT rect = pItem->m_rectangle;
						ClientToScreen(m_hWND, (LPPOINT)&rect);
						ClientToScreen(m_hWND, (LPPOINT)&rect + 1);
						pt.x = rect.right;
						pt.y = rect.top;
						m_pNext->Popup(pt);
					}
				}
				else
				{
					TinyContextMenu* ps = m_pNext;
					while (ps != NULL)
					{
						ps->m_pFocusItem = NULL;
						ps->Unpopup();
						ps = ps->m_pNext;
					}
				}
			}
		}
		return FALSE;
	}
	LRESULT TinyContextMenu::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		SetCapture(m_hWND);
		return FALSE;
	}
	LRESULT TinyContextMenu::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		ReleaseCapture();
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		TinyMenuItem* ps = GetAt(pt);
		if (ps != NULL)
		{
			if (ps->m_pChild == NULL)
			{
				TinyContextMenu* psm = ps->m_pOwner;
				while (psm != NULL)
				{
					psm->m_pFocusItem = NULL;
					psm->Unpopup();
					psm = psm->m_pPrev;
				}
				Click(ps);
			}
		}
		return FALSE;
	}
	LRESULT TinyContextMenu::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		//UninstallMessageHook();
		return FALSE;
	}
	LRESULT TinyContextMenu::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PAINTSTRUCT ps = { 0 };
		HDC hDC = BeginPaint(m_hWND, &ps);

		if (m_size.cx != 0 && m_size.cy != 0)
		{
			TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
			RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
			FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawMenu(memdc);
			memdc.Render(paintRC, paintRC, FALSE);
		}

		EndPaint(m_hWND, &ps);
		return FALSE;
	}
	LRESULT TinyContextMenu::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			TinyString names(256);
			::GetClassName((HWND)lParam, names.STR(), 256);
			if (!names.Compare("TinyContextMenu"))
			{
				TinyContextMenu* ps = m_pPrev == NULL ? this : m_pPrev;
				while (ps != NULL)
				{
					ps->Unpopup();
					ps = ps->m_pPrev;
				}
				ps = m_pNext == NULL ? this : m_pNext;
				while (ps != NULL)
				{
					ps->Unpopup();
					ps = ps->m_pNext;
				}
			}
		}
		return FALSE;
	}
	BOOL TinyContextMenu::AddItem(TinyMenuItem* pz)
	{
		if (m_items.Add(pz))
		{
			pz->m_pOwner = this;
			RECT rectangle = { 0 };
			Recalculate(rectangle);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyContextMenu::InsertItem(INT index, TinyMenuItem* pz)
	{
		if (m_items.Insert(index, pz))
		{
			pz->m_pOwner = this;
			RECT rectangle = { 0 };
			Recalculate(rectangle);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyContextMenu::RemoveItem(TinyMenuItem* pz)
	{
		if (m_items.Remove(pz))
		{
			RECT rectangle = { 0 };
			Recalculate(rectangle);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyContextMenu::RemoveAt(INT index)
	{
		if (m_items.RemoveAt(index))
		{
			RECT rectangle = { 0 };
			Recalculate(rectangle);
			return TRUE;
		}
		return FALSE;
	}
	void TinyContextMenu::RemoveAll()
	{
		m_items.RemoveAll();
		RedrawMenu();
	}
	void TinyContextMenu::RedrawMenu()
	{
		if (m_size.cx != 0 && m_size.cy != 0)
		{
			HDC hDC = GetDC(m_hWND);
			TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
			RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
			FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawMenu(memdc);
			memdc.Render(paintRC, paintRC, FALSE);
			ReleaseDC(m_hWND, hDC);
		}
	}

	void TinyContextMenu::Recalculate(RECT& rect)
	{
		SetRectEmpty(&rect);
		INT cy = 0;
		INT size = m_items.GetSize();
		for (INT i = 0; i < size; i++)
		{
			TinyMenuItem* ps = m_items[i];
			ps->m_rectangle.left = 0;
			ps->m_rectangle.top = cy;
			ps->m_rectangle.right = ps->m_size.cx;
			ps->m_rectangle.bottom = ps->m_rectangle.top + ps->m_size.cy;
			cy += TO_CY(ps->m_rectangle);
		}
		if (size > 0)
		{
			SetRect(&rect, 0, 0, TO_CX(m_items[0]->m_rectangle), cy);
			SetWindowPos(m_hWND,
				HWND_TOPMOST,
				0,
				0,
				TO_CX(rect),
				TO_CY(rect),
				SWP_NOACTIVATE | SWP_NOMOVE);
		}
	}
	TinyMenuItem* TinyContextMenu::GetAt(POINT& pt)
	{
		INT size = m_items.GetSize();
		for (INT i = 0; i < size; i++)
		{
			if (PtInRect(&m_items[i]->m_rectangle, pt))
				return m_items[i];
		}
		return NULL;
	}
	BOOL TinyContextMenu::InstallMessageHook()
	{
		if (m_pMessageHook == NULL)
		{
			m_pMessageHook = ::SetWindowsHookEx(WH_GETMESSAGE,
				MessageFilterHook,
				TinyApplication::Instance()->Handle(),
				GetCurrentThreadId());
			return m_pMessageHook != NULL;
		}
		return FALSE;
	}
	BOOL TinyContextMenu::UninstallMessageHook()
	{
		if (m_pMessageHook != NULL)
		{
			if (::UnhookWindowsHookEx(m_pMessageHook))
			{
				m_pMessageHook = NULL;
				return TRUE;
			}
		}
		return FALSE;
	}
	void TinyContextMenu::DrawMenu(TinyMemDC& dc, TinyMenuItem* hotItem)
	{
		DrawMenuItems(dc, hotItem);
	}
	void TinyContextMenu::DrawMenuItems(TinyMemDC& dc, TinyMenuItem* hotItem)
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
				rect.left = rect.left + 26;
				rect.right = rect.right - 3;
				imagedc.Render(rect, m_images[3].GetRectangle(), TRUE);
			}
		}
		dc.SelectObject(hOldFont);
		dc.SetBkMode(iOldMode);
		dc.RestoreDC(iSaveDC);
	}
	BOOL TinyContextMenu::Popup(POINT& pt)
	{
		RECT rectangle = { 0 };
		Recalculate(rectangle);
		if (!IsRectEmpty(&rectangle))
		{
			SetWindowPos(m_hWND,
				HWND_TOPMOST,
				pt.x,
				pt.y,
				TO_CX(rectangle),
				TO_CY(rectangle),
				SWP_SHOWWINDOW);
			UpdateWindow(m_hWND);
		}
		return FALSE;
	}
	BOOL TinyContextMenu::IsPopup()
	{
		return ::IsWindowVisible(m_hWND);
	}
	BOOL TinyContextMenu::Unpopup()
	{
		return SetWindowPos(m_hWND,
			NULL,
			0,
			0,
			0,
			0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
}