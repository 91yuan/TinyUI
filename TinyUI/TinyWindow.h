#pragma once
#include "TinyWindowMsg.h"
#include "TinyApplication.h"

namespace TinyUI
{
	/// <summary>
	/// 普通窗口类
	/// </summary>
	class TinyWindow : public TinyWindowMsg, public TinyMessageFilter
	{
		DECLARE_DYNAMIC(TinyWindow)
	public:
		TinyWindow();
		TinyWindow(INT x, INT y, INT cx, INT cy);
		virtual ~TinyWindow();
	public:
		operator HWND() const;
		BOOL operator==(const TinyWindow& wnd) const;
		BOOL operator!=(const TinyWindow& wnd) const;
		BOOL SubclassDlgItem(UINT nID, HWND hDlg);
		BOOL SubclassWindow(HWND hWND);
		HWND UnsubclassWindow(BOOL bForce = FALSE);
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void PreSubclassDlgItem();
		virtual void PreSubclassWindow();
		virtual void OnFinalMessage(HWND hWnd);
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual BOOL DestroyWindow();
	public:
		BOOL	ShowWindow(INT nCmdShow) throw();
		BOOL	UpdateWindow() throw();
		DWORD	GetStyle() const throw();
		DWORD	SetStyle(LONG dwNewLong) const throw();
		DWORD	GetExStyle() const throw();
		LONG	GetWindowLong(int nIndex) const throw();
		LONG	SetWindowLong(int nIndex, LONG dwNewLong) throw();
		WORD	GetWindowWord(int nIndex) const throw();
		WORD	SetWindowWord(int nIndex, WORD wNewWord) throw();
		DWORD	GetWindowStyle() throw();
		DWORD	GetWindowExStyle() throw();
		DWORD	SetWindowStyle(DWORD dwNewStyle) throw();
		DWORD	SetWindowExStyle(DWORD dwNewStyle) throw();
		HMODULE GetWindowInstance()  throw();
		BOOL	SetWindowText(LPCTSTR lpszString) throw();
		INT		GetWindowText(_Out_z_cap_post_count_(nMaxCount, return +1) LPTSTR lpszStringBuf, _In_ int nMaxCount) const throw();
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
	protected:
		HWND			m_hWND;//窗口句柄
		TinyLoopThunk	m_thunk;// Thunk类
		WNDPROC			m_hPrimaryProc;//原始的PROC
	private:
		LRESULT DefWindowProc();
		LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK BeginLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK EndLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LPCSTR RetrieveClass(LPCTSTR lpszClass);
	};
}


