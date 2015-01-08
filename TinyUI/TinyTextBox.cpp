#include "stdafx.h"
#include "TinyTextBox.h"

namespace TinyUI
{
	TinyTextBox::TinyTextBox()
	{

	}
	TinyTextBox::~TinyTextBox()
	{

	}
	LPCSTR TinyTextBox::RetrieveClassName()
	{
		return WC_EDIT;
	}
	LPCSTR TinyTextBox::RetrieveTitle()
	{
		return TEXT("TinyTextBox");
	}
	DWORD TinyTextBox::RetrieveStyle()
	{
		return (WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);
	}
	DWORD TinyTextBox::RetrieveExStyle()
	{
		return (WS_EX_LEFT|WS_EX_CLIENTEDGE|WS_EX_NOPARENTNOTIFY);
	}
	BOOL TinyTextBox::Create(HWND hParent, INT x, INT y,INT cx,INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls={sizeof(INITCOMMONCONTROLSEX),ICC_STANDARD_CLASSES};
		if(InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	BOOL TinyTextBox::CanUndo() const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (BOOL)::SendMessage(m_hWND, EM_CANUNDO, 0, 0); 
	}
	INT TinyTextBox::GetLineCount() const
	{ 
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_GETLINECOUNT, 0, 0);
	}
	BOOL TinyTextBox::GetModify() const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (BOOL)::SendMessage(m_hWND, EM_GETMODIFY, 0, 0); 
	}
	void TinyTextBox::SetModify(BOOL bModified)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETMODIFY, bModified, 0);
	}
	void TinyTextBox::GetRect(LPRECT lpRect) const
	{
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_GETRECT, 0, (LPARAM)lpRect);
	}
	void TinyTextBox::GetSel(INT& nStartChar, INT& nEndChar) const
	{ 
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_GETSEL, (WPARAM)&nStartChar,(LPARAM)&nEndChar); 
	}
	DWORD TinyTextBox::GetSel() const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return DWORD(::SendMessage(m_hWND, EM_GETSEL, 0, 0)); 
	}
	HLOCAL TinyTextBox::GetHandle() const
	{ 
		ASSERT(::IsWindow(m_hWND));
		return (HLOCAL)::SendMessage(m_hWND, EM_GETHANDLE, 0, 0); 
	}
	void TinyTextBox::SetHandle(HLOCAL hBuffer)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETHANDLE, (WPARAM)hBuffer, 0); 
	}
	INT TinyTextBox::GetLine( INT nIndex,  LPTSTR lpszBuffer) const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (INT)::SendMessage(m_hWND, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}
	INT TinyTextBox::GetLine( INT nIndex, _Out_cap_post_count_(nMaxLength, return) LPTSTR lpszBuffer,  INT nMaxLength) const
	{
		ASSERT(::IsWindow(m_hWND));
		*(LPWORD)lpszBuffer = (WORD)nMaxLength;
		return (INT)::SendMessage(m_hWND, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}
	void TinyTextBox::EmptyUndoBuffer()
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_EMPTYUNDOBUFFER, 0, 0); 
	}
	BOOL TinyTextBox::FmtLines(BOOL bAddEOL)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_FMTLINES, bAddEOL, 0);
	}
	void TinyTextBox::LimitText(INT nChars)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_LIMITTEXT, nChars, 0);
	}
	INT TinyTextBox::LineFromChar(INT nIndex) const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (INT)::SendMessage(m_hWND, EM_LINEFROMCHAR, nIndex, 0);
	}
	INT TinyTextBox::LineIndex(INT nLine) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_LINEINDEX, nLine, 0);
	}
	INT TinyTextBox::LineLength(INT nLine) const
	{ 
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_LINELENGTH, nLine, 0); 
	}
	void TinyTextBox::LineScroll(INT nLines, INT nChars)
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_LINESCROLL, nChars, nLines);
	}
	void TinyTextBox::ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo)
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
	}
	void TinyTextBox::SetPasswordChar(TCHAR ch)
	{ 
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETPASSWORDCHAR, ch, 0); 
	}
	void TinyTextBox::SetRect(LPCRECT lpRect)
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_SETRECT, 0, (LPARAM)lpRect);
	}
	void TinyTextBox::SetRectNP(LPCRECT lpRect)
	{ 
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETRECTNP, 0, (LPARAM)lpRect);
	}
	void TinyTextBox::SetSel(DWORD dwSelection, BOOL bNoScroll)
	{
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_SETSEL,LOWORD(dwSelection), HIWORD(dwSelection));
		if (!bNoScroll)
		{
			::SendMessage(m_hWND, EM_SCROLLCARET, 0, 0);
		}
	}
	void TinyTextBox::SetSel(INT nStartChar, INT nEndChar, BOOL bNoScroll)
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, EM_SETSEL, nStartChar, nEndChar);
		if (!bNoScroll)
		{
			::SendMessage(m_hWND, EM_SCROLLCARET, 0, 0);
		} 
	}
	BOOL TinyTextBox::SetTabStops(INT nTabStops, LPINT rgTabStops)
	{ 
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_SETTABSTOPS, nTabStops,(LPARAM)rgTabStops); 
	}
	void TinyTextBox::SetTabStops()
	{ 
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETTABSTOPS, 0, 0);
	}
	BOOL TinyTextBox::SetTabStops(const INT& cxEachStop)
	{
		ASSERT(::IsWindow(m_hWND)); 
		return (BOOL)::SendMessage(m_hWND, EM_SETTABSTOPS,1, (LPARAM)(LPINT)&cxEachStop);
	}
	BOOL TinyTextBox::Undo()
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (BOOL)::SendMessage(m_hWND, EM_UNDO, 0, 0); 
	}
	void TinyTextBox::Clear()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_CLEAR, 0, 0);
	}
	void TinyTextBox::Copy()
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, WM_COPY, 0, 0); 
	}
	void TinyTextBox::Cut()
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		::SendMessage(m_hWND, WM_CUT, 0, 0); 
	}
	void TinyTextBox::Paste()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_PASTE, 0, 0);
	}
	BOOL TinyTextBox::SetReadOnly(BOOL bReadOnly )
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (BOOL)::SendMessage(m_hWND, EM_SETREADONLY, bReadOnly, 0L); 
	}
	INT TinyTextBox::GetFirstVisibleLine() const
	{
		ASSERT(::IsWindow(m_hWND)); 
		return (INT)::SendMessage(m_hWND, EM_GETFIRSTVISIBLELINE, 0, 0L);
	}
	TCHAR TinyTextBox::GetPasswordChar() const
	{
		ASSERT(::IsWindow(m_hWND)); 
		return (TCHAR)::SendMessage(m_hWND, EM_GETPASSWORDCHAR, 0, 0L);
	}
	void TinyTextBox::SetMargins(UINT nLeft, UINT nRight)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETMARGINS, EC_LEFTMARGIN|EC_RIGHTMARGIN, MAKELONG(nLeft, nRight));
	}
	DWORD TinyTextBox::GetMargins() const
	{ 
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::SendMessage(m_hWND, EM_GETMARGINS, 0, 0);
	}
	void TinyTextBox::SetLimitText(UINT nMax)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETLIMITTEXT, nMax, 0); 
	}
	UINT TinyTextBox::GetLimitText() const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (UINT)::SendMessage(m_hWND, EM_GETLIMITTEXT, 0, 0); 
	}
	TinyPoint TinyTextBox::PosFromChar(UINT nChar) const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return TinyPoint((DWORD)::SendMessage(m_hWND, EM_POSFROMCHAR, nChar, 0));
	}
	INT TinyTextBox::CharFromPos(TinyPoint pt) const
	{ 
		ASSERT(::IsWindow(m_hWND)); 
		return (INT)::SendMessage(m_hWND, EM_CHARFROMPOS, 0, MAKELPARAM(pt.x, pt.y));
	}
}