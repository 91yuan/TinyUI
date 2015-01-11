#include "stdafx.h"
#include <comdef.h>
#include "TinyRichTextBox.h"

namespace TinyUI
{
	TinyRichTextBox::TinyRichTextBox()
		:m_hInstance(NULL)
	{

	}
	TinyRichTextBox::~TinyRichTextBox()
	{
		if (m_hInstance != NULL)
		{
			FreeLibrary(m_hInstance);
			m_hInstance = NULL;
		}
	}
	LPCSTR TinyRichTextBox::RetrieveClassName()
	{
		return TEXT("RichEdit50W");
	}
	LPCSTR TinyRichTextBox::RetrieveTitle()
	{
		return TEXT("");
	}
	BOOL TinyRichTextBox::PreCreateWindow(CREATESTRUCT& cs)
	{
		m_hInstance = LoadLibrary(TEXT("Msftedit.dll"));
		return TRUE;
	}
	DWORD TinyRichTextBox::RetrieveStyle()
	{
		return (ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_TABSTOP);
	}
	DWORD TinyRichTextBox::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING);
	}
	BOOL TinyRichTextBox::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}

	BOOL TinyRichTextBox::CanUndo() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_CANUNDO, 0, 0);
	}
	BOOL TinyRichTextBox::CanRedo() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_CANREDO, 0, 0);
	}
	UNDONAMEID TinyRichTextBox::GetUndoName() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UNDONAMEID) ::SendMessage(m_hWND, EM_GETUNDONAME, 0, 0);
	}
	UNDONAMEID TinyRichTextBox::GetRedoName() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UNDONAMEID) ::SendMessage(m_hWND, EM_GETREDONAME, 0, 0);
	}
	INT TinyRichTextBox::GetLineCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_GETLINECOUNT, 0, 0);
	}
	BOOL TinyRichTextBox::GetModify() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_GETMODIFY, 0, 0);
	}
	void TinyRichTextBox::SetModify(BOOL bModified /* = TRUE */)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETMODIFY, bModified, 0);
	}
	BOOL TinyRichTextBox::SetTextMode(UINT fMode)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, EM_SETTEXTMODE, (WPARAM)fMode, 0);
	}
	UINT TinyRichTextBox::GetTextMode() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, EM_GETTEXTMODE, 0, 0);
	}
	void TinyRichTextBox::GetRect(LPRECT lpRect) const
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_GETRECT, 0, (LPARAM)lpRect);
	}
	TinyPoint TinyRichTextBox::GetCharPos(LONG lChar) const
	{
		ASSERT(::IsWindow(m_hWND));
		TinyPoint pt;
		::SendMessage(m_hWND, EM_POSFROMCHAR, (WPARAM)&pt, (LPARAM)lChar);
		return pt;
	}
	UINT TinyRichTextBox::GetOptions() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, EM_GETOPTIONS, 0, 0);
	}
	void TinyRichTextBox::SetOptions(WORD wOp, DWORD dwFlags)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETOPTIONS, (WPARAM)wOp, (LPARAM)dwFlags);
	}
	BOOL TinyRichTextBox::SetAutoURLDetect(BOOL bEnable /* = TRUE */)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, EM_AUTOURLDETECT, (WPARAM)bEnable, 0);
	}
	void TinyRichTextBox::EmptyUndoBuffer()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_EMPTYUNDOBUFFER, 0, 0);
	}
	UINT TinyRichTextBox::SetUndoLimit(UINT nLimit)
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, EM_SETUNDOLIMIT, (WPARAM)nLimit, 0);
	}
	void TinyRichTextBox::ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText);
	}
	void TinyRichTextBox::SetRect(LPCRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_SETRECT, 0, (LPARAM)lpRect);
	}
	void TinyRichTextBox::StopGroupTyping()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_STOPGROUPTYPING, 0, 0);
	}
	BOOL TinyRichTextBox::Redo()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, EM_REDO, 0, 0);
	}
	BOOL TinyRichTextBox::Undo()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_UNDO, 0, 0);
	}
	void TinyRichTextBox::Clear()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_CLEAR, 0, 0);
	}
	void TinyRichTextBox::Copy()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_COPY, 0, 0);
	}
	void TinyRichTextBox::Cut()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_CUT, 0, 0);
	}
	void TinyRichTextBox::Paste()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_PASTE, 0, 0);
	}
	BOOL TinyRichTextBox::SetReadOnly(BOOL bReadOnly /* = TRUE */)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_SETREADONLY, bReadOnly, 0L);
	}
	INT TinyRichTextBox::GetFirstVisibleLine() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_GETFIRSTVISIBLELINE, 0, 0L);
	}
	BOOL TinyRichTextBox::DisplayBand(LPRECT pDisplayRect)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_DISPLAYBAND, 0, (LPARAM)pDisplayRect);
	}
	void TinyRichTextBox::GetSel(CHARRANGE &cr) const
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_EXGETSEL, 0, (LPARAM)&cr);
	}
	BOOL TinyRichTextBox::GetPunctuation(UINT fType, PUNCTUATION* lpPunc) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, EM_GETPUNCTUATION, (WPARAM)fType, (LPARAM)lpPunc);
	}
	BOOL TinyRichTextBox::SetPunctuation(UINT fType, PUNCTUATION* lpPunc)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, EM_SETPUNCTUATION, (WPARAM)fType, (LPARAM)lpPunc);
	}
	void TinyRichTextBox::LimitText(LONG nChars)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_EXLIMITTEXT, 0, nChars);
	}
	LONG TinyRichTextBox::LineFromChar(LONG nIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_EXLINEFROMCHAR, 0, nIndex);
	}
	TinyPoint TinyRichTextBox::PosFromChar(UINT nChar) const
	{
		ASSERT(::IsWindow(m_hWND));
		POINTL pt;
		::SendMessage(m_hWND, EM_POSFROMCHAR, (WPARAM)&pt, nChar);
		return TinyPoint(pt.x, pt.y);
	}
	INT TinyRichTextBox::CharFromPos(TinyPoint pt) const
	{
		ASSERT(::IsWindow(m_hWND));
		POINTL ptl = { pt.x, pt.y };
		return (INT)::SendMessage(m_hWND, EM_CHARFROMPOS, 0, (LPARAM)&ptl);
	}
	void TinyRichTextBox::SetSel(CHARRANGE &cr)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_EXSETSEL, 0, (LPARAM)&cr);
	}
	DWORD TinyRichTextBox::FindWordBreak(UINT nCode, DWORD nStart) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::SendMessage(m_hWND, EM_FINDWORDBREAK, (WPARAM)nCode, (LPARAM)nStart);
	}

	LONG TinyRichTextBox::FindText(DWORD dwFlags, FINDTEXTEX* pFindText) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_FINDTEXTEX, dwFlags, (LPARAM)pFindText);
	}

	LONG TinyRichTextBox::FormatRange(FORMATRANGE* pfr, BOOL bDisplay)
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_FORMATRANGE, (WPARAM)bDisplay, (LPARAM)pfr);
	}

	LONG TinyRichTextBox::GetEventMask() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_GETEVENTMASK, 0, 0L);
	}

	LONG TinyRichTextBox::GetLimitText() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_GETLIMITTEXT, 0, 0L);
	}

	LONG TinyRichTextBox::GetSelText(LPSTR lpBuf) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_GETSELTEXT, 0, (LPARAM)lpBuf);
	}

	void TinyRichTextBox::HideSelection(BOOL bHide, BOOL bPerm)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_HIDESELECTION, bHide, bPerm);
	}

	void TinyRichTextBox::RequestResize()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_REQUESTRESIZE, 0, 0L);
	}

	WORD TinyRichTextBox::GetSelectionType() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (WORD)::SendMessage(m_hWND, EM_SELECTIONTYPE, 0, 0L);
	}

	UINT TinyRichTextBox::GetWordWrapMode() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, EM_GETWORDWRAPMODE, 0, 0);
	}

	UINT TinyRichTextBox::SetWordWrapMode(UINT uFlags) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, EM_SETWORDWRAPMODE, (WPARAM)uFlags, 0);
	}

	COLORREF TinyRichTextBox::SetBackgroundColor(BOOL bSysColor, COLORREF cr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF)::SendMessage(m_hWND, EM_SETBKGNDCOLOR, bSysColor, cr);
	}

	DWORD TinyRichTextBox::SetEventMask(DWORD dwEventMask)
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::SendMessage(m_hWND, EM_SETEVENTMASK, 0, dwEventMask);
	}

	BOOL TinyRichTextBox::SetOLECallback(IRichEditOleCallback* pCallback)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_SETOLECALLBACK, 0, (LPARAM)pCallback);
	}

	BOOL TinyRichTextBox::SetTargetDevice(HDC hDC, LONG lLineWidth)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, EM_SETTARGETDEVICE, (WPARAM)hDC, lLineWidth);
	}

	LONG TinyRichTextBox::StreamIn(INT nFormat, EDITSTREAM &es)
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_STREAMIN, nFormat, (LPARAM)&es);
	}

	LONG TinyRichTextBox::StreamOut(INT nFormat, EDITSTREAM &es)
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, EM_STREAMOUT, nFormat, (LPARAM)&es);
	}

	LONG TinyRichTextBox::GetTextLength() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, WM_GETTEXTLENGTH, NULL, NULL);
	}

	INT TinyRichTextBox::GetLine(INT nIndex, LPTSTR lpszBuffer) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	INT TinyRichTextBox::LineIndex(INT nLine /* = -1 */) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_LINEINDEX, nLine, 0);
	}

	INT TinyRichTextBox::LineLength(INT nLine /* = -1 */) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, EM_LINELENGTH, nLine, 0);
	}

	void TinyRichTextBox::LineScroll(INT nLines, INT nChars /* = 0 */)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, EM_LINESCROLL, nChars, nLines);
	}

	void TinyRichTextBox::SetSel(LONG nStartChar, LONG nEndChar)
	{
		ASSERT(::IsWindow(m_hWND));
		CHARRANGE cr;
		cr.cpMin = nStartChar;
		cr.cpMax = nEndChar;
		::SendMessage(m_hWND, EM_EXSETSEL, 0, (LPARAM)&cr);
	}

	BOOL TinyRichTextBox::CanPaste(UINT nFormat) const
	{
		ASSERT(::IsWindow(m_hWND));
		BOOL b = (BOOL)::SendMessage(m_hWND, EM_CANPASTE, nFormat, 0L);
		return b;
	}

	void TinyRichTextBox::PasteSpecial(UINT nClipFormat, DWORD dvAspect, HMETAFILE hMF)
	{
		ASSERT(::IsWindow(m_hWND));
		REPASTESPECIAL reps;
		reps.dwAspect = dvAspect;
		reps.dwParam = (DWORD_PTR)hMF;
		::SendMessage(m_hWND, EM_PASTESPECIAL, nClipFormat, (LPARAM)&reps);
	}

	INT TinyRichTextBox::GetLine(INT nIndex, _Out_cap_post_count_(nMaxLength, return) LPTSTR lpszBuffer, INT nMaxLength) const
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT(sizeof(nMaxLength) <= nMaxLength*sizeof(TCHAR) && nMaxLength > 0);
		*(LPINT)lpszBuffer = nMaxLength;
		return (INT)::SendMessage(m_hWND, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	void TinyRichTextBox::GetSel(LONG& nStartChar, LONG& nEndChar) const
	{
		ASSERT(::IsWindow(m_hWND));
		CHARRANGE cr;
		::SendMessage(m_hWND, EM_EXGETSEL, 0, (LPARAM)&cr);
		nStartChar = cr.cpMin;
		nEndChar = cr.cpMax;
	}

	TinyString TinyRichTextBox::GetSelText() const
	{
		ASSERT(::IsWindow(m_hWND));
		CHARRANGE cr;
		cr.cpMin = cr.cpMax = 0;
		::SendMessage(m_hWND, EM_EXGETSEL, 0, (LPARAM)&cr);
		TinyString strText(cr.cpMax - cr.cpMin + 1);
		::SendMessage(m_hWND, EM_GETSELTEXT, 0, (LPARAM)strText.STR());
		return TinyString(strText);
	}

	IRichEditOle* TinyRichTextBox::GetIRichEditOle() const
	{
		ASSERT(::IsWindow(m_hWND));
		IRichEditOle *pRichItem = NULL;
		::SendMessage(m_hWND, EM_GETOLEINTERFACE, 0, (LPARAM)&pRichItem);
		return pRichItem;
	}

	LONG TinyRichTextBox::GetTextLengthEx(DWORD dwFlags, UINT nCodePage) const
	{
		ASSERT(::IsWindow(m_hWND));
		GETTEXTLENGTHEX textLenEx;
		textLenEx.flags = dwFlags;

		if (nCodePage == -1)
		{
#ifdef _UNICODE
			textLenEx.codepage = 1200;
#else
			textLenEx.codepage = CP_ACP;
#endif
		}
		else
			textLenEx.codepage = nCodePage;

		return (LONG) ::SendMessage(m_hWND, EM_GETTEXTLENGTHEX,
			(WPARAM)&textLenEx, 0);
	}

	INT TinyRichTextBox::GetTextRange(INT nFirst, INT nLast, TinyString& refString) const
	{
		ASSERT(::IsWindow(m_hWND));

		TEXTRANGE textRange;
		textRange.chrg.cpMin = nFirst;
		textRange.chrg.cpMax = nLast;

		INT nLength = INT(nLast - nFirst + 1);
		ASSERT(nLength > 0);


		textRange.lpstrText = refString.Substring(nFirst, nLength).STR();
		nLength = (INT)::SendMessage(m_hWND, EM_GETTEXTRANGE, 0, (LPARAM)&textRange);
		return (INT)nLength;
	}

	BOOL TinyRichTextBox::SetDefaultCharFormat(CHARFORMAT &cf)
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)::SendMessage(m_hWND, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}

	BOOL TinyRichTextBox::SetDefaultCharFormat(CHARFORMAT2 &cf)
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)::SendMessage(m_hWND, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}

	BOOL TinyRichTextBox::SetSelectionCharFormat(CHARFORMAT &cf)
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)::SendMessage(m_hWND, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	BOOL TinyRichTextBox::SetSelectionCharFormat(CHARFORMAT2 &cf)
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)::SendMessage(m_hWND, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	BOOL TinyRichTextBox::SetWordCharFormat(CHARFORMAT &cf)
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)::SendMessage(m_hWND, EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
	}

	BOOL TinyRichTextBox::SetWordCharFormat(CHARFORMAT2 &cf)
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)::SendMessage(m_hWND, EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
	}

	DWORD TinyRichTextBox::GetDefaultCharFormat(CHARFORMAT &cf) const
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT);
		return (DWORD)::SendMessage(m_hWND, EM_GETCHARFORMAT, 0, (LPARAM)&cf);
	}

	DWORD TinyRichTextBox::GetDefaultCharFormat(CHARFORMAT2 &cf) const
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT2);
		return (DWORD)::SendMessage(m_hWND, EM_GETCHARFORMAT, 0, (LPARAM)&cf);
	}

	DWORD TinyRichTextBox::GetSelectionCharFormat(CHARFORMAT &cf) const
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT);
		return (DWORD)::SendMessage(m_hWND, EM_GETCHARFORMAT, 1, (LPARAM)&cf);
	}

	DWORD TinyRichTextBox::GetSelectionCharFormat(CHARFORMAT2 &cf) const
	{
		ASSERT(::IsWindow(m_hWND));
		cf.cbSize = sizeof(CHARFORMAT2);
		return (DWORD)::SendMessage(m_hWND, EM_GETCHARFORMAT, 1, (LPARAM)&cf);
	}

	DWORD TinyRichTextBox::GetParaFormat(PARAFORMAT &pf) const
	{
		ASSERT(::IsWindow(m_hWND));
		pf.cbSize = sizeof(PARAFORMAT);
		return (DWORD)::SendMessage(m_hWND, EM_GETPARAFORMAT, 0, (LPARAM)&pf);
	}

	DWORD TinyRichTextBox::GetParaFormat(PARAFORMAT2 &pf) const
	{
		ASSERT(::IsWindow(m_hWND));
		pf.cbSize = sizeof(PARAFORMAT2);
		return (DWORD)::SendMessage(m_hWND, EM_GETPARAFORMAT, 0, (LPARAM)&pf);
	}

	BOOL TinyRichTextBox::SetParaFormat(PARAFORMAT &pf)
	{
		ASSERT(::IsWindow(m_hWND));
		pf.cbSize = sizeof(PARAFORMAT);
		return (BOOL)::SendMessage(m_hWND, EM_SETPARAFORMAT, 0, (LPARAM)&pf);
	}

	BOOL TinyRichTextBox::SetParaFormat(PARAFORMAT2 &pf)
	{
		ASSERT(::IsWindow(m_hWND));
		pf.cbSize = sizeof(PARAFORMAT2);
		return (BOOL)::SendMessage(m_hWND, EM_SETPARAFORMAT, 0, (LPARAM)&pf);
	}
	/************************************************************************/
	/* http://msdn.microsoft.com/en-us/library/dd387916(VS.85).aspx         */
	/************************************************************************/
	BOOL TinyRichTextBox::InsertOLE(LPCTSTR pszFileName)
	{
		HRESULT hRes = S_OK;
		LPRICHEDITOLE pRichEditOle = NULL;
		SendMessage(m_hWND, EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle);
		if (pRichEditOle == NULL)
		{
			return FALSE;
		}
		LPLOCKBYTES pLockBytes = NULL;
		hRes = CreateILockBytesOnHGlobal(NULL, TRUE, &pLockBytes);
		if (FAILED(hRes))
		{
			pRichEditOle->Release();
			pRichEditOle = NULL;
			return FALSE;
		}
		LPSTORAGE pStorage = NULL;
		hRes = StgCreateDocfileOnILockBytes(pLockBytes, STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);
		if (FAILED(hRes))
		{
			pLockBytes->Release();
			pLockBytes = NULL;
			pRichEditOle->Release();
			pRichEditOle = NULL;
			return FALSE;
		}
		FORMATETC formatEtc;
		formatEtc.cfFormat = 0;
		formatEtc.ptd = NULL;
		formatEtc.dwAspect = DVASPECT_CONTENT;
		formatEtc.lindex = -1;
		formatEtc.tymed = TYMED_NULL;
		LPOLECLIENTSITE	pClientSite = NULL;
		hRes = pRichEditOle->GetClientSite(&pClientSite);
		if (FAILED(hRes))
		{
			pStorage->Release();
			pStorage = NULL;
			pLockBytes->Release();
			pLockBytes = NULL;
			pRichEditOle->Release();
			pRichEditOle = NULL;
			return FALSE;
		}
		LPUNKNOWN pUnk = NULL;
		CLSID clsid = CLSID_NULL;
		//多字节转Unicode
		INT size = ::MultiByteToWideChar(CP_UTF8, 0, pszFileName, -1, NULL, 0);
		wchar_t*  pUnicode = new  wchar_t[size + 1];
		::MultiByteToWideChar(CP_UTF8, 0, pszFileName, -1, (LPWSTR)pUnicode, size);
		//多字节转Unicode
		hRes = OleCreateFromFile(clsid, pUnicode, IID_IUnknown, OLERENDER_DRAW, &formatEtc, pClientSite, pStorage, (void**)&pUnk);
		delete[]  pUnicode;
		if (FAILED(hRes))
		{
			pStorage->Release();
			pStorage = NULL;
			pLockBytes->Release();
			pLockBytes = NULL;
			pRichEditOle->Release();
			pRichEditOle = NULL;
			return FALSE;
		}
		LPOLEOBJECT pObject = NULL;
		hRes = pUnk->QueryInterface(IID_IOleObject, (void**)&pObject);
		pUnk->Release();
		if (FAILED(hRes))
		{
			pStorage->Release();
			pStorage = NULL;
			pLockBytes->Release();
			pLockBytes = NULL;
			pRichEditOle->Release();
			pRichEditOle = NULL;
			return FALSE;
		}
		OleSetContainedObject(pObject, TRUE);
		REOBJECT reobject = { sizeof(REOBJECT) };
		hRes = pObject->GetUserClassID(&clsid);
		if (FAILED(hRes))
		{
			pObject->Release();
			pObject = NULL;
			pStorage->Release();
			pStorage = NULL;
			pLockBytes->Release();
			pLockBytes = NULL;
			pRichEditOle->Release();
			pRichEditOle = NULL;
			return FALSE;
		}
		reobject.clsid = clsid;
		reobject.cp = REO_CP_SELECTION;
		reobject.dvaspect = DVASPECT_CONTENT;
		reobject.dwFlags = REO_RESIZABLE | REO_BELOWBASELINE;
		reobject.dwUser = 0;
		reobject.poleobj = pObject;
		reobject.polesite = pClientSite;
		reobject.pstg = pStorage;
		SIZEL sizel = { 0 };
		reobject.sizel = sizel;
		SendMessage(m_hWND, EM_SETSEL, 0, -1);
		DWORD dwStart, dwEnd;
		SendMessage(m_hWND, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		SendMessage(m_hWND, EM_SETSEL, dwEnd + 1, dwEnd + 1);
		SendMessage(m_hWND, EM_REPLACESEL, TRUE, (WPARAM)L"\n");
		hRes = pRichEditOle->InsertObject(&reobject);
		pObject->Release();
		pObject = NULL;
		pClientSite->Release();
		pClientSite = NULL;
		pStorage->Release();
		pStorage = NULL;
		pLockBytes->Release();
		pLockBytes = NULL;
		pRichEditOle->Release();
		pRichEditOle = NULL;
		if (FAILED(hRes))
		{
			return FALSE;
		}
		return TRUE;
	}
	BOOL TinyRichTextBox::InsertImage(LPCTSTR pszFileName)
	{
		return TRUE;
	}
	BOOL TinyRichTextBox::InsertImage(BYTE* pData)
	{
		return TRUE;
	}
}