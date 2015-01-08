#include "stdafx.h"
#include "TinyControl.h"

namespace TinyUI
{
	TinyControl::TinyControl()
	{
	}
	TinyControl::~TinyControl()
	{
	}
	LRESULT CALLBACK TinyControl::CbtFilterHook(INT code, WPARAM wParam, LPARAM lParam)
	{
		if (code != HCBT_CREATEWND)
			return CallNextHookEx(m_pHook, code, wParam, lParam);
		ASSERT(lParam != NULL);
		LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
		ASSERT(lpcs != NULL);
		TinyControl *_this = NULL;
		_this = (TinyControl*)(lpcs->lpCreateParams);
		if (_this != NULL)
		{
			_this->SubclassWindow((HWND)wParam);
		}
		return CallNextHookEx(m_pHook, code, wParam, lParam);
	};
	BOOL TinyControl::Create(HWND hParent, int x, int y, int cx, int cy, BOOL bHook)
	{
		BOOL bRes = FALSE;
		if (bHook)
		{
			m_pHook = SetWindowsHookEx(WH_CBT, CbtFilterHook, TinyApplication::Instance()->Handle(), GetCurrentThreadId());
			ASSERT(m_pHook != NULL);
			bRes = TinyWindow::Create(hParent, x, y, cx, cy);
			::SendMessage(m_hWND, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
			UnhookWindowsHookEx(m_pHook);
			m_pHook = NULL;
			return FALSE;
		}
		bRes = TinyWindow::Create(hParent, x, y, cx, cy);
		return FALSE;
	};
	LPCSTR TinyControl::RetrieveClassName()
	{
		return TEXT("TinyControl");
	}
	HICON TinyControl::RetrieveIcon()
	{
		return NULL;
	}
	LPCTSTR TinyControl::RetrieveTitle()
	{
		return TEXT("TinyControl");
	}
	DWORD TinyControl::RetrieveStyle()
	{
		return (WS_VISIBLE | WS_CHILD);
	}
	DWORD TinyControl::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR);
	}
	LRESULT TinyControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (lParam != NULL)
		{
			return ::SendMessage((HWND)lParam, (WM_COMMAND + WM_REFLECT), wParam, lParam);
		}
		else
		{
			bHandled = TRUE;
			//²Ëµ¥ClickÊÂ¼þ
			/*INT wID = LOWORD(wParam);
			SysMenu* menuPtr = (SysMenu*)__Module.GetMapMENUID().FromKey(wID);
			if (menuPtr != NULL)
			{
			menuPtr->OnClick(menuPtr, wID);
			}*/
			return TRUE;
		}
		return FALSE;
	}
	LRESULT TinyControl::OnCommandReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		LPNMHDR p = (LPNMHDR)lParam;
		return ::SendMessage(p->hwndFrom, (uMsg + WM_REFLECT), wParam, lParam);
	}
	LRESULT TinyControl::OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnDeleteItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnDrawItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnMeasureItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	BOOL TinyControl::ShowWindow(INT nCmdShow) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ShowWindow(m_hWND, nCmdShow);
	}
	BOOL TinyControl::UpdateWindow() throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::UpdateWindow(m_hWND);
	}
	DWORD TinyControl::GetStyle() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::GetWindowLong(m_hWND, GWL_STYLE);
	}
	DWORD TinyControl::SetStyle(LONG dwNewLong) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::SetWindowLong(m_hWND, GWL_STYLE, dwNewLong);
	}
	DWORD TinyControl::GetExStyle() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::GetWindowLong(m_hWND, GWL_EXSTYLE);
	}

	LONG TinyControl::GetWindowLong(INT nIndex) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowLong(m_hWND, nIndex);
	}

	LONG TinyControl::SetWindowLong(INT nIndex, LONG dwNewLong) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowLong(m_hWND, nIndex, dwNewLong);
	}

	WORD TinyControl::GetWindowWord(INT nIndex) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowWord(m_hWND, nIndex);
	}

	WORD TinyControl::SetWindowWord(INT nIndex, WORD wNewWord) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowWord(m_hWND, nIndex, wNewWord);
	}

	DWORD TinyControl::GetWindowStyle() throw()
	{
		return ((DWORD)GetWindowLong(GWL_STYLE));
	}

	DWORD TinyControl::GetWindowExStyle() throw()
	{
		return ((DWORD)GetWindowLong(GWL_EXSTYLE));
	}

	DWORD TinyControl::SetWindowStyle(DWORD dwNewStyle) throw()
	{
		return ((DWORD)SetWindowLong(GWL_STYLE, dwNewStyle));
	}

	DWORD TinyControl::SetWindowExStyle(DWORD dwNewStyle) throw()
	{
		return ((DWORD)SetWindowLong(GWL_EXSTYLE, dwNewStyle));
	}

	HMODULE TinyControl::GetWindowInstance()  throw()
	{
		return ((HMODULE)GetWindowLongPtr(GWLP_HINSTANCE));
	}
	BOOL TinyControl::SetWindowText(LPCTSTR lpszString) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowText(m_hWND, lpszString);
	}

	INT TinyControl::GetWindowText(_Out_z_cap_post_count_(nMaxCount, return +1) LPTSTR lpszStringBuf, INT nMaxCount) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowText(m_hWND, lpszStringBuf, nMaxCount);
	}
	INT TinyControl::GetWindowTextLength() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowTextLength(m_hWND);
	}
	void TinyControl::SetFont(HFONT hFont, BOOL bRedraw) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
	}
	void TinyControl::SetText(LPCSTR lpszText) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_SETTEXT, 0, (LPARAM)lpszText);
	}

	INT TinyControl::GetText(LPCSTR lpszText, INT cchTextMax) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, WM_GETTEXT, cchTextMax, (LPARAM)lpszText);
	}

	HFONT TinyControl::GetFont() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (HFONT)::SendMessage(m_hWND, WM_GETFONT, 0, 0);
	}
	HMENU TinyControl::GetMenu() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (HMENU)::GetMenu(m_hWND);
	}

	BOOL TinyControl::SetMenu(HMENU hMenu) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetMenu(m_hWND, hMenu);
	}
	HMENU TinyControl::GetSystemMenu(BOOL bRevert) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (HMENU)::GetSystemMenu(m_hWND, bRevert);
	}

	BOOL TinyControl::HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::HiliteMenuItem(m_hWND, hMenu, uItemHilite, uHilite);
	}
	BOOL TinyControl::IsIconic() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::IsIconic(m_hWND);
	}

	BOOL TinyControl::IsZoomed() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::IsZoomed(m_hWND);
	}

	BOOL TinyControl::MoveWindow(INT x, INT y, INT cx, INT cy, BOOL bRepaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MoveWindow(m_hWND, x, y, cx, cy, bRepaint);
	}
	INT TinyControl::MapWindowPoints(HWND hWndFrom, POINT& pos)
	{
		ASSERT(::IsWindow(m_hWND));
		return MapWindowPoints(hWndFrom, &pos, 1);
	}
	INT TinyControl::MapWindowPoints(POINT& pos)
	{
		ASSERT(::IsWindow(m_hWND));
		return MapWindowPoints(NULL, &pos, 1);
	}
	BOOL TinyControl::MoveWindow(LPCRECT lpRect, BOOL bRepaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
	}
	BOOL TinyControl::SetForegroundWindow()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetForegroundWindow(m_hWND);
	}
	BOOL TinyControl::SetWindowPos(HWND hWndInsertAfter, INT x, INT y, INT cx, INT cy, UINT nFlags) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowPos(m_hWND, hWndInsertAfter, x, y, cx, cy, nFlags);
	}

	BOOL TinyControl::SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowPos(m_hWND, hWndInsertAfter, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, nFlags);
	}

	UINT TinyControl::ArrangeIconicWindows() throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ArrangeIconicWindows(m_hWND);
	}

	BOOL TinyControl::BringWindowToTop() throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::BringWindowToTop(m_hWND);
	}

	BOOL TinyControl::GetWindowRect(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowRect(m_hWND, lpRect);
	}

	BOOL TinyControl::GetClientRect(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetClientRect(m_hWND, lpRect);
	}

	BOOL TinyControl::GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowPlacement(m_hWND, lpwndpl);
	}

	BOOL TinyControl::SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowPlacement(m_hWND, lpwndpl);
	}
	BOOL TinyControl::ClientToScreen(LPPOINT lpPoint) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ClientToScreen(m_hWND, lpPoint);
	}

	BOOL TinyControl::ClientToScreen(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		if (!::ClientToScreen(m_hWND, (LPPOINT)lpRect))
			return FALSE;
		return ::ClientToScreen(m_hWND, ((LPPOINT)lpRect) + 1);
	}

	BOOL TinyControl::ScreenToClient(LPPOINT lpPoint) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ScreenToClient(m_hWND, lpPoint);
	}

	BOOL TinyControl::ScreenToClient(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		if (!::ScreenToClient(m_hWND, (LPPOINT)lpRect))
			return FALSE;
		return ::ScreenToClient(m_hWND, ((LPPOINT)lpRect) + 1);
	}

	INT TinyControl::MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MapWindowPoints(m_hWND, hWndTo, lpPoint, nCount);
	}

	INT TinyControl::MapWindowPoints(HWND hWndTo, LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MapWindowPoints(m_hWND, hWndTo, (LPPOINT)lpRect, 2);
	}
	HDC TinyControl::BeginPaint(LPPAINTSTRUCT lpPaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::BeginPaint(m_hWND, lpPaint);
	}

	void TinyControl::EndPaint(LPPAINTSTRUCT lpPaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::EndPaint(m_hWND, lpPaint);
	}

	void TinyControl::SetRedraw(BOOL bRedraw) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_SETREDRAW, (WPARAM)bRedraw, 0);
	}
	BOOL TinyControl::RedrawWindow(LPCRECT lpRectUpdate, HRGN hRgnUpdate, UINT flags) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::RedrawWindow(m_hWND, lpRectUpdate, hRgnUpdate, flags);
	}

	LRESULT TinyControl::SendMessage(UINT message, WPARAM wParam, LPARAM lParam) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SendMessage(m_hWND, message, wParam, lParam);
	}
}
