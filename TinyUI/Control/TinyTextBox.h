#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyTextBox : public TinyControl
	{
	public:
		TinyTextBox();
		virtual ~TinyTextBox();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);

		BOOL CanUndo() const;
		INT GetLineCount() const;
		BOOL GetModify() const;
		void SetModify(BOOL bModified = TRUE);
		void GetRect(LPRECT lpRect) const;
		DWORD GetSel() const;
		void GetSel(INT& nStartChar, INT& nEndChar) const;
		HLOCAL GetHandle() const;
		void SetHandle(HLOCAL hBuffer);
		void SetMargins(UINT nLeft, UINT nRight);
		DWORD GetMargins() const;
		void SetLimitText(UINT nMax);
		UINT GetLimitText() const;
		TinyPoint PosFromChar(UINT nChar) const;
		INT CharFromPos(TinyPoint pt) const;
		INT GetLine(INT nIndex, LPTSTR lpszBuffer) const;
		INT GetLine(INT nIndex, LPTSTR lpszBuffer, INT nMaxLength) const;
		BOOL SetCueBanner(LPCWSTR lpszText, BOOL fDrawIfFocused = FALSE);
		BOOL GetCueBanner(LPWSTR lpszText, INT cchText) const;
		void EmptyUndoBuffer();
		BOOL FmtLines(BOOL bAddEOL);
		void LimitText(INT nChars = 0);
		INT LineFromChar(INT nIndex = -1) const;
		INT LineIndex(INT nLine = -1) const;
		INT LineLength(INT nLine = -1) const;
		void LineScroll(INT nLines, INT nChars = 0);
		void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
		void SetPasswordChar(TCHAR ch);
		void SetRect(LPCRECT lpRect);
		void SetRectNP(LPCRECT lpRect);
		void SetSel(DWORD dwSelection, BOOL bNoScroll = FALSE);
		void SetSel(INT nStartChar, INT nEndChar, BOOL bNoScroll = FALSE);
		BOOL SetTabStops(INT nTabStops, LPINT rgTabStops);
		void SetTabStops();
		BOOL SetTabStops(const INT& cxEachStop);
		BOOL Undo();
		void Clear();
		void Copy();
		void Cut();
		void Paste();
		BOOL SetReadOnly(BOOL bReadOnly = TRUE);
		INT GetFirstVisibleLine() const;
		TCHAR GetPasswordChar() const;
	private:
		DWORD dwStyle;
		DWORD dwExStyle;
	};
}