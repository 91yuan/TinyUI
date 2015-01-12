#include "../stdafx.h"
#include "TinyCommonDialog.h"

namespace TinyUI
{
	extern "C"
	{
		static CLSID CLSID_FileOpenDialog_MFC = { 0xDC1C5A9C, 0xE88A, 0x4DDE, { 0xA5, 0xA1, 0x60, 0xF8, 0x2A, 0x20, 0xAE, 0xF7 } };
		static CLSID CLSID_FileSaveDialog_MFC = { 0xC0B4E2F3, 0xBA21, 0x4773, { 0x8D, 0xBA, 0x33, 0x5E, 0xC9, 0x46, 0xEB, 0x8B } };

		static IID IID_IFileDialogEvents_MFC = { 0x973510DB, 0x7D7F, 0x452B, { 0x89, 0x75, 0x74, 0xA8, 0x58, 0x28, 0xD3, 0x54 } };
		static IID IID_IFileDialogControlEvents_MFC = { 0x36116642, 0xD713, 0x4B97, { 0x9B, 0x83, 0x74, 0x84, 0xA9, 0xD0, 0x04, 0x33 } };
	}
	/************************************************************************/
	/* TinyFontDialog                                                        */
	/************************************************************************/
	TinyFontDialog::TinyFontDialog(const CHARFORMAT& charformat, DWORD dwFlags /* = CF_SCREENFONTS */, HDC hDCPrinter /* = NULL */, HWND pParentWnd /* = NULL */)
	{
		memset(&m_cf, 0, sizeof(m_cf));
		memset(&m_lf, 0, sizeof(m_lf));
		memset(&m_szStyleName, 0, sizeof(m_szStyleName));

		m_cf.lStructSize = sizeof(m_cf);
		m_cf.lpszStyle = (LPTSTR)&m_szStyleName;
		m_cf.Flags = dwFlags | CF_INITTOLOGFONTSTRUCT;
		m_cf.Flags |= FillInLogFont(charformat);

		m_cf.lpLogFont = &m_lf;

		if (hDCPrinter)
		{
			ASSERT(hDCPrinter != NULL);
			m_cf.hDC = hDCPrinter;
			m_cf.Flags |= CF_PRINTERFONTS;
		}
		if (charformat.dwMask & CFM_COLOR)
		{
			m_cf.rgbColors = charformat.crTextColor;
		}
	}
	TinyFontDialog::TinyFontDialog(LPLOGFONT lplfInitial /* = NULL */, DWORD dwFlags /* = CF_EFFECTS | CF_SCREENFONTS */, HDC hDCPrinter /* = NULL */, HWND pParentWnd /* = NULL */)
	{
		memset(&m_cf, 0, sizeof(m_cf));
		memset(&m_lf, 0, sizeof(m_lf));
		memset(&m_szStyleName, 0, sizeof(m_szStyleName));

		m_cf.lStructSize = sizeof(m_cf);
		m_cf.lpszStyle = (LPTSTR)&m_szStyleName;
		m_cf.Flags = dwFlags;

		if (lplfInitial)
		{
			m_cf.lpLogFont = lplfInitial;
			m_cf.Flags |= CF_INITTOLOGFONTSTRUCT;
			memcpy_s(&m_lf, sizeof(LOGFONT), m_cf.lpLogFont, sizeof(LOGFONT));
		}
		else
		{
			m_cf.lpLogFont = &m_lf;
		}

		if (hDCPrinter)
		{
			ASSERT(hDCPrinter != NULL);
			m_cf.hDC = hDCPrinter;
			m_cf.Flags |= CF_PRINTERFONTS;
		}
	}
	TinyString TinyFontDialog::GetFaceName() const
	{
		return (LPCTSTR)m_cf.lpLogFont->lfFaceName;
	}
	TinyString TinyFontDialog::GetStyleName() const
	{
		return m_cf.lpszStyle;
	}
	INT TinyFontDialog::GetSize() const
	{
		return m_cf.iPointSize;
	}
	INT TinyFontDialog::GetWeight() const
	{
		return (INT)m_cf.lpLogFont->lfWeight;
	}
	BOOL TinyFontDialog::IsItalic() const
	{
		return m_cf.lpLogFont->lfItalic ? TRUE : FALSE;
	}
	BOOL TinyFontDialog::IsStrikeOut() const
	{
		return m_cf.lpLogFont->lfStrikeOut ? TRUE : FALSE;
	}
	BOOL TinyFontDialog::IsBold() const
	{
		return m_cf.lpLogFont->lfWeight == FW_BOLD ? TRUE : FALSE;
	}
	BOOL TinyFontDialog::IsUnderline() const
	{
		return m_cf.lpLogFont->lfUnderline ? TRUE : FALSE;
	}
	COLORREF TinyFontDialog::GetColor() const
	{
		return m_cf.rgbColors;
	}
	INT_PTR TinyFontDialog::DoModal(HWND hParent)
	{
		m_cf.hwndOwner = hParent;
		INT_PTR nResult = ::ChooseFont(&m_cf);
		if (nResult == IDOK)
		{
			memcpy_s(&m_lf, sizeof(LOGFONT), m_cf.lpLogFont, sizeof(LOGFONT));
			return IDOK;
		}
		return nResult ? nResult : IDCANCEL;
	}
	void TinyFontDialog::GetCurrentFont(LPLOGFONT lplf)
	{
		ASSERT(lplf != NULL);
		if (m_hWND != NULL)
			::SendMessage(m_hWND, WM_CHOOSEFONT_GETLOGFONT, 0, (LPARAM)(LPVOID)lplf);
		else
			*lplf = m_lf;
	}
	void TinyFontDialog::GetCharFormat(CHARFORMAT& cf) const
	{
		cf.dwEffects = 0;
		cf.dwMask = 0;
		if ((m_cf.Flags & CF_NOSTYLESEL) == 0)
		{
			cf.dwMask |= CFM_BOLD | CFM_ITALIC;
			cf.dwEffects |= (IsBold()) ? CFE_BOLD : 0;
			cf.dwEffects |= (IsItalic()) ? CFE_ITALIC : 0;
		}
		if ((m_cf.Flags & CF_NOSIZESEL) == 0)
		{
			cf.dwMask |= CFM_SIZE;
			cf.yHeight = GetSize() * 2;
		}

		if ((m_cf.Flags & CF_NOFACESEL) == 0)
		{
			cf.dwMask |= CFM_FACE;
			cf.bPitchAndFamily = m_cf.lpLogFont->lfPitchAndFamily;
			_tcsncpy_s(cf.szFaceName, _countof(cf.szFaceName), m_cf.lpLogFont->lfFaceName, _TRUNCATE);
		}

		if (m_cf.Flags & CF_EFFECTS)
		{
			cf.dwMask |= CFM_UNDERLINE | CFM_STRIKEOUT | CFM_COLOR;
			cf.dwEffects |= (IsUnderline()) ? CFE_UNDERLINE : 0;
			cf.dwEffects |= (IsStrikeOut()) ? CFE_STRIKEOUT : 0;
			cf.crTextColor = GetColor();
		}
		if ((m_cf.Flags & CF_NOSCRIPTSEL) == 0)
		{
			cf.bCharSet = m_cf.lpLogFont->lfCharSet;
			cf.dwMask |= CFM_CHARSET;
		}
		cf.yOffset = 0;
	}
	DWORD TinyFontDialog::FillInLogFont(const CHARFORMAT& cf)
	{
		DWORD dwFlags = 0;
		BOOL bIsFormat2 = (cf.cbSize >= sizeof(CHARFORMAT2));

		if (cf.dwMask & CFM_SIZE)
		{
			HDC hDC = NULL;
			hDC = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
			LONG yPerInch = ::GetDeviceCaps(hDC, LOGPIXELSY);
			m_lf.lfHeight = -(INT)((cf.yHeight * yPerInch) / 1440);
		}
		else
		{
			m_lf.lfHeight = 0;
		}

		m_lf.lfWidth = 0;
		m_lf.lfEscapement = 0;
		m_lf.lfOrientation = 0;

		if ((cf.dwMask & (CFM_ITALIC | CFM_BOLD)) == (CFM_ITALIC | CFM_BOLD))
		{
			m_lf.lfWeight = (cf.dwEffects & CFE_BOLD) ? FW_BOLD : FW_NORMAL;
			m_lf.lfItalic = (BYTE)((cf.dwEffects & CFE_ITALIC) ? TRUE : FALSE);
		}
		else
		{
			dwFlags |= CF_NOSTYLESEL;
			m_lf.lfWeight = FW_DONTCARE;
			m_lf.lfItalic = FALSE;
		}

		if ((cf.dwMask & (CFM_UNDERLINE | CFM_STRIKEOUT | CFM_COLOR)) ==
			(CFM_UNDERLINE | CFM_STRIKEOUT | CFM_COLOR))
		{
			dwFlags |= CF_EFFECTS;
			m_lf.lfUnderline = (BYTE)((cf.dwEffects & CFE_UNDERLINE) ? TRUE : FALSE);
			m_lf.lfStrikeOut = (BYTE)((cf.dwEffects & CFE_STRIKEOUT) ? TRUE : FALSE);
		}
		else
		{
			m_lf.lfUnderline = (BYTE)FALSE;
			m_lf.lfStrikeOut = (BYTE)FALSE;
		}

		if (cf.dwMask & CFM_CHARSET)
			m_lf.lfCharSet = cf.bCharSet;
		else
			dwFlags |= CF_NOSCRIPTSEL;
		m_lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
		m_lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		m_lf.lfQuality = DEFAULT_QUALITY;

		if (bIsFormat2)
		{
			const CHARFORMAT2* pCF2 = (const CHARFORMAT2*)&cf;
			if (pCF2->dwMask & CFM_WEIGHT)
				m_lf.lfWeight = pCF2->wWeight;
			if (cf.dwMask & CFM_FACE)
			{
				m_lf.lfPitchAndFamily = pCF2->bPitchAndFamily;
				_tcscpy_s(m_lf.lfFaceName, _countof(m_lf.lfFaceName), (LPTSTR)pCF2->szFaceName);
			}
		}
		else
		{
			m_lf.lfPitchAndFamily = cf.bPitchAndFamily;
			_tcsncpy_s(m_lf.lfFaceName, _countof(m_lf.lfFaceName), cf.szFaceName, _TRUNCATE);
		}

		if (!(cf.dwMask & CFM_FACE))
		{
			m_lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
			m_lf.lfFaceName[0] = (TCHAR)0;
		}

		return dwFlags;
	}
	/************************************************************************/
	/* TinyFileDialog                                                        */
	/************************************************************************/
	BOOL TinyFileDialog::IsReadOnly() const
	{
		return m_ofn.Flags & OFN_READONLY ? TRUE : FALSE;
	}
	void TinyFileDialog::SetFilterText(LPCSTR pzFilter)
	{
		TinyString str(pzFilter);
		LPSTR ps = str.STR();
		while ((ps = _tcschr(ps, '|')) != NULL)
			*ps++ = '\0';
		m_ofn.lpstrFilter = ps;
	}
	TinyFileDialog::TinyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt /* = NULL */, LPCTSTR lpszFileName /* = NULL */, DWORD dwFlags /* = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT */, LPCTSTR lpszFilter /* = NULL */, DWORD dwSize /* = 0 */, BOOL bVistaStyle /* = TRUE */)
	{
		if (dwSize == 0)
		{
			dwSize = sizeof(OPENFILENAME);
		}
		ASSERT(dwSize >= sizeof(OPENFILENAME));
		memset(&m_ofn, 0, dwSize);
		m_szFileName[0] = '\0';
		m_szFileTitle[0] = '\0';
		m_bOpenFileDialog = bOpenFileDialog;
		m_ofn.lStructSize = dwSize;
		m_ofn.lpstrFile = m_szFileName;
		m_ofn.nMaxFile = _countof(m_szFileName);
		m_ofn.lpstrDefExt = lpszDefExt;
		m_ofn.lpstrFileTitle = (LPTSTR)m_szFileTitle;
		m_ofn.nMaxFileTitle = _countof(m_szFileTitle);
		m_ofn.Flags |= dwFlags | OFN_EXPLORER | OFN_ENABLEHOOK;
		if (dwFlags & OFN_ENABLETEMPLATE)
			m_ofn.Flags &= ~OFN_ENABLESIZING;
		m_ofn.hInstance = TinyApplication::Instance()->Handle();
		if (lpszFileName != NULL)
			_tcsncpy_s(m_szFileName, _countof(m_szFileName), lpszFileName, _TRUNCATE);
		if (lpszFilter != NULL)
		{
			TinyString str(lpszFilter);
			LPTSTR ps = str.STR();
			while ((ps = _tcschr(ps, '|')) != NULL)
				*ps++ = '\0';
			m_ofn.lpstrFilter = ps;
		}
	}
	TinyFileDialog::~TinyFileDialog()
	{
	}
	INT_PTR TinyFileDialog::DoModal(HWND hParent)
	{
		DWORD nOffset = lstrlen(m_ofn.lpstrFile) + 1;
		ASSERT(nOffset <= m_ofn.nMaxFile);
		memset(m_ofn.lpstrFile + nOffset, 0, (m_ofn.nMaxFile - nOffset)*sizeof(TCHAR));
		HWND hWndFocus = ::GetFocus();
		BOOL bEnableParent = FALSE;
		m_ofn.hwndOwner = hParent;
		if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
		{
			bEnableParent = TRUE;
			::EnableWindow(m_ofn.hwndOwner, FALSE);
		}
		INT_PTR nResult = 0;
		if (m_bOpenFileDialog)
			nResult = ::GetOpenFileName(&m_ofn);
		else
			nResult = ::GetSaveFileName(&m_ofn);
		if (bEnableParent)
			::EnableWindow(m_ofn.hwndOwner, TRUE);
		if (::IsWindow(hWndFocus))
			::SetFocus(hWndFocus);
		return nResult ? nResult : IDCANCEL;
	}
	TinyString TinyFileDialog::GetPathName() const
	{
		return m_ofn.lpstrFile;
	}
	TinyString TinyFileDialog::GetFileName() const
	{
		return m_ofn.lpstrFileTitle;
	}
	TinyString TinyFileDialog::GetFileExt() const
	{
		return m_ofn.lpstrFile + m_ofn.nFileExtension;
	}
	TinyString TinyFileDialog::GetFileTitle() const
	{
		LPSTR pz = m_ofn.lpstrFileTitle;
		::PathRemoveExtension(pz);
		return TinyString(pz);
	}
}
