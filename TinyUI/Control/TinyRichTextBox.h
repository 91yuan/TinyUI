#pragma once
#include <Richedit.h>
#include <RichOle.h>
#include "TinyControl.h"

namespace TinyUI
{
	class TinyRichTextBox :public TinyControl
	{
	public:
		TinyRichTextBox();
		virtual ~TinyRichTextBox();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	public:
		BOOL CanUndo() const;
		BOOL CanRedo() const;
		UNDONAMEID GetUndoName() const;
		UNDONAMEID GetRedoName() const;
		INT GetLineCount() const;
		BOOL GetModify() const;
		void SetModify(BOOL bModified = TRUE);
		BOOL SetTextMode(UINT fMode);
		UINT GetTextMode() const;
		void GetRect(LPRECT lpRect) const;
		TinyPoint GetCharPos(LONG lChar) const;
		UINT GetOptions() const;
		void SetOptions(WORD wOp, DWORD dwFlags);
		BOOL SetAutoURLDetect(BOOL bEnable = TRUE);
		UINT GetWordWrapMode() const;
		UINT SetWordWrapMode(UINT uFlags) const;
		BOOL GetPunctuation(UINT fType, PUNCTUATION* lpPunc) const;
		BOOL SetPunctuation(UINT fType, PUNCTUATION* lpPunc);
		INT GetLine(INT nIndex, LPTSTR lpszBuffer) const;
		INT GetLine(INT nIndex, _Out_cap_post_count_(nMaxLength, return) LPTSTR lpszBuffer, INT nMaxLength) const;

		BOOL CanPaste(UINT nFormat = 0) const;
		void GetSel(LONG& nStartChar, LONG& nEndChar) const;
		void GetSel(CHARRANGE &cr) const;
		void LimitText(LONG nChars = 0);
		LONG LineFromChar(LONG nIndex) const;
		TinyPoint PosFromChar(UINT nChar) const;
		INT CharFromPos(TinyPoint pt) const;

		void SetSel(LONG nStartChar, LONG nEndChar);
		void SetSel(CHARRANGE &cr);
		DWORD GetDefaultCharFormat(CHARFORMAT &cf) const;
		DWORD GetDefaultCharFormat(CHARFORMAT2 &cf) const;
		DWORD GetSelectionCharFormat(CHARFORMAT &cf) const;
		DWORD GetSelectionCharFormat(CHARFORMAT2 &cf) const;
		LONG GetEventMask() const;
		LONG GetLimitText() const;
		DWORD GetParaFormat(PARAFORMAT &pf) const;
		DWORD GetParaFormat(PARAFORMAT2 &pf) const;
		INT GetTextRange(INT nFirst, INT nLast, TinyString& refString) const;
		LONG GetSelText(LPSTR lpBuf) const;
		TinyString GetSelText() const;
		WORD GetSelectionType() const;
		COLORREF SetBackgroundColor(BOOL bSysColor, COLORREF cr);
		BOOL SetDefaultCharFormat(CHARFORMAT &cf);
		BOOL SetDefaultCharFormat(CHARFORMAT2 &cf);
		BOOL SetSelectionCharFormat(CHARFORMAT &cf);
		BOOL SetSelectionCharFormat(CHARFORMAT2 &cf);
		BOOL SetWordCharFormat(CHARFORMAT &cf);
		BOOL SetWordCharFormat(CHARFORMAT2 &cf);
		DWORD SetEventMask(DWORD dwEventMask);
		BOOL SetParaFormat(PARAFORMAT &pf);
		BOOL SetParaFormat(PARAFORMAT2 &pf);
		BOOL SetTargetDevice(HDC hDC, LONG lLineWidth);
		LONG GetTextLength() const;
		LONG GetTextLengthEx(DWORD dwFlags, UINT uCodePage = -1) const;
		BOOL SetReadOnly(BOOL bReadOnly = TRUE);
		INT GetFirstVisibleLine() const;

		void EmptyUndoBuffer();
		void StopGroupTyping();
		UINT SetUndoLimit(UINT nLimit);

		INT LineIndex(INT nLine = -1) const;
		INT LineLength(INT nLine = -1) const;
		void LineScroll(INT nLines, INT nChars = 0);
		void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
		void SetRect(LPCRECT lpRect);

		BOOL DisplayBand(LPRECT pDisplayRect);
		LONG FindText(DWORD dwFlags, FINDTEXTEX* pFindText) const;
		DWORD FindWordBreak(UINT nCode, DWORD nStart) const;
		LONG FormatRange(FORMATRANGE* pfr, BOOL bDisplay = TRUE);
		void HideSelection(BOOL bHide, BOOL bPerm);
		void PasteSpecial(UINT nClipFormat, DWORD dvAspect = 0, HMETAFILE hMF = 0);
		void RequestResize();
		LONG StreamIn(INT nFormat, EDITSTREAM &es);
		LONG StreamOut(INT nFormat, EDITSTREAM &es);

		BOOL Undo();
		BOOL Redo();
		void Clear();
		void Copy();
		void Cut();
		void Paste();

		IRichEditOle* GetIRichEditOle() const;
		BOOL SetOLECallback(IRichEditOleCallback* pCallback);

		BOOL InsertOLE(LPCTSTR lpszFileName);
		BOOL InsertImage(LPCTSTR pszFileName);
		BOOL InsertImage(BYTE* pData);

	private:
		HINSTANCE		m_hInstance;
	};
}