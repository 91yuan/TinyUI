#include "../stdafx.h"
#include "TinyRichUI.h"

namespace TinyUI
{
	LONG HimetricXtoDX(LONG xHimetric, LONG xPerInch)
	{
		return (LONG)MulDiv(xHimetric, xPerInch, HIMETRIC_PER_INCH);
	}
	LONG HimetricYtoDY(LONG yHimetric, LONG yPerInch)
	{
		return (LONG)MulDiv(yHimetric, yPerInch, HIMETRIC_PER_INCH);
	}
	LONG DXtoHimetricX(LONG dx, LONG xPerInch)
	{
		return (LONG)MulDiv(dx, HIMETRIC_PER_INCH, xPerInch);
	}
	LONG DYtoHimetricY(LONG dy, LONG yPerInch)
	{
		return (LONG)MulDiv(dy, HIMETRIC_PER_INCH, yPerInch);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyRichUI::TinyRichUI()
		:m_cRef(1),
		m_pts(NULL),
		m_hWND(NULL)
	{

	}


	TinyRichUI::~TinyRichUI()
	{

	}
	HRESULT TinyRichUI::Create(HWND hWND)
	{
		HRESULT hRes = S_OK;
		this->m_hWND = hWND;
		IUnknown* pUnknown = NULL;
		hRes = CreateTextServices(NULL, static_cast<ITextHost*>(this), &pUnknown);
		if (hRes == S_OK)
		{
			hRes = pUnknown->QueryInterface(IID_ITextServices, (void**)&m_pts);
			pUnknown->Release();
		}
		return hRes;
	}
	HRESULT TinyRichUI::SetCharFormat(CHARFORMATW * pcf, HFONT hFont)
	{
		HWND hwnd;
		LOGFONT lf;
		HDC hdc;
		LONG yPixPerInch;
		if (!hFont)
			hFont = (HFONT)GetStockObject(SYSTEM_FONT);
		if (!GetObject(hFont, sizeof(LOGFONT), &lf))
			return E_FAIL;
		pcf->cbSize = sizeof(CHARFORMAT2);
		hwnd = GetDesktopWindow();
		hdc = GetDC(hwnd);
		yPixPerInch = GetDeviceCaps(hdc, LOGPIXELSY);
		pcf->yHeight = lf.lfHeight * LY_PER_INCH / yPixPerInch;
		ReleaseDC(hwnd, hdc);

		pcf->yOffset = 0;
		pcf->crTextColor = 0;

		pcf->dwEffects = CFM_EFFECTS | CFE_AUTOBACKCOLOR;
		pcf->dwEffects &= ~(CFE_PROTECTED | CFE_LINK);

		if (lf.lfWeight < FW_BOLD)
			pcf->dwEffects &= ~CFE_BOLD;
		if (!lf.lfItalic)
			pcf->dwEffects &= ~CFE_ITALIC;
		if (!lf.lfUnderline)
			pcf->dwEffects &= ~CFE_UNDERLINE;
		if (!lf.lfStrikeOut)
			pcf->dwEffects &= ~CFE_STRIKEOUT;

		pcf->dwMask = CFM_ALL | CFM_BACKCOLOR;
		pcf->bCharSet = lf.lfCharSet;
		pcf->bPitchAndFamily = lf.lfPitchAndFamily;
		MultiByteToWideChar(CP_ACP, 0, lf.lfFaceName, LF_FACESIZE, pcf->szFaceName, LF_FACESIZE);
		return S_OK;
	}
	HRESULT STDMETHODCALLTYPE TinyRichUI::QueryInterface(REFIID riid, void **ppvObject)
	{
		if (IsEqualIID(riid, IID_ITextHost) || IsEqualIID(riid, IID_IUnknown))
		{
			*ppvObject = this;
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
		AddRef();
		return NOERROR;
	}
	ULONG STDMETHODCALLTYPE TinyRichUI::AddRef(void)
	{
		return InterlockedIncrement(&this->m_cRef);
	}
	ULONG STDMETHODCALLTYPE TinyRichUI::Release(void)
	{
		if (InterlockedDecrement(&this->m_cRef))
		{
			return this->m_cRef;
		}
		delete this;
		return NOERROR;
	}
	HDC TinyRichUI::TxGetDC()
	{
		return ::GetDC(m_hWND);
	}

	INT TinyRichUI::TxReleaseDC(HDC hdc)
	{
		return ::ReleaseDC(m_hWND, hdc);
	}

	BOOL TinyRichUI::TxShowScrollBar(INT fnBar, BOOL fShow)
	{
		return FALSE;
	}

	BOOL TinyRichUI::TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags)
	{
		return FALSE;
	}

	BOOL TinyRichUI::TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw)
	{
		return FALSE;
	}

	BOOL TinyRichUI::TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw)
	{
		return FALSE;
	}

	void TinyRichUI::TxInvalidateRect(LPCRECT prc, BOOL fMode)
	{

	}

	void TinyRichUI::TxViewChange(BOOL fUpdate)
	{

	}

	BOOL TinyRichUI::TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight)
	{
		return ::CreateCaret(m_hWND, hbmp, xWidth, yHeight);
	}

	BOOL TinyRichUI::TxShowCaret(BOOL fShow)
	{
		if (fShow)
			return ::ShowCaret(m_hWND);
		return ::HideCaret(m_hWND);
	}

	BOOL TinyRichUI::TxSetCaretPos(INT x, INT y)
	{
		return ::SetCaretPos(x, y);
	}

	BOOL TinyRichUI::TxSetTimer(UINT idTimer, UINT uTimeout)
	{
		return FALSE;
	}

	void TinyRichUI::TxKillTimer(UINT idTimer)
	{

	}

	void TinyRichUI::TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll)
	{

	}

	void TinyRichUI::TxSetCapture(BOOL fCapture)
	{
	}

	void TinyRichUI::TxSetFocus()
	{

	}

	void TinyRichUI::TxSetCursor(HCURSOR hcur, BOOL fText)
	{

	}

	BOOL TinyRichUI::TxScreenToClient(LPPOINT lppt)
	{
		return FALSE;
	}

	BOOL TinyRichUI::TxClientToScreen(LPPOINT lppt)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxActivate(LONG * plOldState)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxDeactivate(LONG lNewState)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetClientRect(LPRECT prc)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetViewInset(LPRECT prc)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetCharFormat(const CHARFORMATW **ppCF)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetParaFormat(const PARAFORMAT **ppPF)
	{
		return FALSE;
	}

	COLORREF TinyRichUI::TxGetSysColor(INT nIndex)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetBackStyle(TXTBACKSTYLE *pstyle)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetMaxLength(DWORD *plength)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetScrollBars(DWORD *pdwScrollBar)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetPasswordChar(TCHAR *pch)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetAcceleratorPos(LONG *pcp)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetExtent(LPSIZEL lpExtent)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::OnTxCharFormatChange(const CHARFORMATW * pCF)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::OnTxParaFormatChange(const PARAFORMAT * pPF)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxNotify(DWORD iNotify, void *pv)
	{
		return FALSE;
	}

	HIMC TinyRichUI::TxImmGetContext()
	{
		return NULL;
	}

	void TinyRichUI::TxImmReleaseContext(HIMC himc)
	{

	}

	HRESULT TinyRichUI::TxGetSelectionBarWidth(LONG *lSelBarWidth)
	{
		return FALSE;
	}

	BOOL TinyRichUI::TxIsDoubleClickPending()
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetWindow(HWND *phwnd)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxSetForegroundWindow()
	{
		return FALSE;
	}

	HPALETTE TinyRichUI::TxGetPalette()
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetEastAsianFlags(LONG *pFlags)
	{
		return FALSE;
	}

	HCURSOR TinyRichUI::TxSetCursor2(HCURSOR hcur, BOOL bText)
	{
		return FALSE;
	}

	void TinyRichUI::TxFreeTextServicesNotification()
	{

	}

	HRESULT TinyRichUI::TxGetEditStyle(DWORD dwItem, DWORD *pdwData)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetWindowStyles(DWORD *pdwStyle, DWORD *pdwExStyle)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxShowDropCaret(BOOL fShow, HDC hdc, LPCRECT prc)
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxDestroyCaret()
	{
		return FALSE;
	}

	HRESULT TinyRichUI::TxGetHorzExtent(LONG *plHorzExtent)
	{
		return FALSE;
	}

}
