#pragma once
#include "TinyWindow.h"
#include "TinyImageList.h"

namespace TinyUI
{
	/// <summary>
	/// ´°¿Ú¿Ø¼þÀà
	/// </summary>
	class TinyControl : public TinyWindow
	{
		DECLARE_DYNAMIC(TinyControl)
	public:
		TinyControl();
		virtual ~TinyControl();
	private:
		static HHOOK m_pHook;
		static LRESULT CALLBACK CbtFilterHook(INT code, WPARAM wParam, LPARAM lParam);
	public:
		virtual LPCSTR	RetrieveClassName();
		virtual LPCSTR	RetrieveTitle();
		virtual HICON	RetrieveIcon();
		virtual DWORD	RetrieveStyle();
		virtual DWORD	RetrieveExStyle();
		virtual BOOL	Create(HWND hParent, INT x, INT y, INT cx, INT cy, BOOL bHook = TRUE);
	public:
		BEGIN_MSG_MAP(TinyControl, TinyWindow)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_DESTROY, OnDestory)
			MESSAGE_HANDLER(WM_CLOSE, OnClose)
			MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)
			MESSAGE_HANDLER(WM_COMMANDREFLECT, OnCommandReflect)
			MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
			MESSAGE_HANDLER(WM_NOTIFYREFLECT, OnNotifyReflect)
			MESSAGE_HANDLER(WM_DRAWITEM + WM_REFLECT, OnDrawItemReflect)
			MESSAGE_HANDLER(WM_MEASUREITEM + WM_REFLECT, OnMeasureItemReflect)
			MESSAGE_HANDLER(WM_DELETEITEM + WM_REFLECT, OnDeleteItemReflect)
		END_MSG_MAP()
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCommandReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDeleteItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDrawItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMeasureItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	public:
		LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw();
		BOOL	ShowWindow(INT nCmdShow) throw();
		BOOL	UpdateWindow() throw();
		DWORD	GetStyle() const throw();
		DWORD	SetStyle(LONG dwNewLong) const throw();
		DWORD	GetExStyle() const throw();
		LONG	GetWindowLong(INT nIndex) const throw();
		LONG	SetWindowLong(INT nIndex, LONG dwNewLong) throw();
		WORD	GetWindowWord(INT nIndex) const throw();
		WORD	SetWindowWord(INT nIndex, WORD wNewWord) throw();
		DWORD	GetWindowStyle() throw();
		DWORD	GetWindowExStyle() throw();
		DWORD	SetWindowStyle(DWORD dwNewStyle) throw();
		DWORD	SetWindowExStyle(DWORD dwNewStyle) throw();
		HMODULE GetWindowInstance()  throw();
		BOOL	SetWindowText(LPCTSTR lpszString) throw();
		INT		GetWindowText(_Out_z_cap_post_count_(nMaxCount, return +1) LPTSTR lpszStringBuf, INT nMaxCount) const throw();
		INT		GetWindowTextLength() const throw();
		void	SetFont(HFONT hFont, BOOL bRedraw = TRUE) const throw();
		void	SetText(LPCSTR lpszText) const throw();
		INT		GetText(LPCSTR lpszText, INT cchTextMax) const throw();
		HFONT	GetFont() const throw();
		HMENU	GetMenu() const throw();
		BOOL	SetMenu(HMENU hMenu) const throw();
		HMENU	GetSystemMenu(BOOL bRevert) const throw();
		BOOL	HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite) const throw();
		BOOL	IsIconic() const throw();
		BOOL	IsZoomed() const throw();
		BOOL	MoveWindow(INT x, INT y, INT nWidth, INT nHeight, BOOL bRepaint = TRUE) throw();
		BOOL    MoveWindow(LPCRECT lpRect, BOOL bRepaint) throw();
		BOOL	SetForegroundWindow();
		BOOL	SetWindowPos(HWND hWndInsertAfter, INT x, INT y, INT cx, INT cy, UINT nFlags) throw();
		BOOL	SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags) throw();
		UINT	ArrangeIconicWindows() throw();
		BOOL	BringWindowToTop() throw();
		BOOL	GetWindowRect(LPRECT lpRect) const throw();
		BOOL	GetClientRect(LPRECT lpRect) const throw();
		BOOL	GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const throw();
		BOOL	SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl) throw();
		BOOL	ClientToScreen(LPPOINT lpPoint) const throw();
		BOOL	ClientToScreen(LPRECT lpRect) const throw();
		BOOL	ScreenToClient(LPPOINT lpPoint) const throw();
		BOOL	ScreenToClient(LPRECT lpRect) const throw();
		INT		MapWindowPoints(HWND hWndFrom, POINT& pos);
		INT		MapWindowPoints(POINT& pos);
		INT		MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const throw();
		INT		MapWindowPoints(HWND hWndTo, LPRECT lpRect) const throw();
		HDC		BeginPaint(LPPAINTSTRUCT lpPaint) throw();
		void	EndPaint(LPPAINTSTRUCT lpPaint) throw();
		void	SetRedraw(BOOL bRedraw = TRUE) throw();
		BOOL	RedrawWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE) throw();
	};
	__declspec(selectany) HHOOK TinyControl::m_pHook = NULL;
}


