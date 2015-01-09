#include "stdafx.h"
#include "TinyColumn.h"
#include "TinyRichRender.h"

namespace TinyUI
{
	TinyRichUI::TinyRichUI()
		:m_cRef(1),
		m_pts(NULL)
	{

	}


	TinyRichUI::~TinyRichUI()
	{

	}
	HRESULT TinyRichUI::Create()
	{
		HRESULT hRes = S_OK;
		IUnknown* pUnknown = NULL;
		hRes = CreateTextServices(NULL, static_cast<ITextHost*>(this), &pUnknown);
		if (hRes == S_OK)
		{
			hRes = pUnknown->QueryInterface(IID_ITextServices, (void**)&m_pts);
			pUnknown->Release();
		}
		return hRes;
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
		throw std::exception("The method or operation is not implemented.");
	}

	INT TinyRichUI::TxReleaseDC(HDC hdc)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxShowScrollBar(INT fnBar, BOOL fShow)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxInvalidateRect(LPCRECT prc, BOOL fMode)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxViewChange(BOOL fUpdate)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxShowCaret(BOOL fShow)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxSetCaretPos(INT x, INT y)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxSetTimer(UINT idTimer, UINT uTimeout)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxKillTimer(UINT idTimer)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxSetCapture(BOOL fCapture)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxSetFocus()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxSetCursor(HCURSOR hcur, BOOL fText)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxScreenToClient(LPPOINT lppt)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxClientToScreen(LPPOINT lppt)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxActivate(LONG * plOldState)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxDeactivate(LONG lNewState)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetClientRect(LPRECT prc)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetViewInset(LPRECT prc)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetCharFormat(const CHARFORMATW **ppCF)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetParaFormat(const PARAFORMAT **ppPF)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	COLORREF TinyRichUI::TxGetSysColor(int nIndex)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetBackStyle(TXTBACKSTYLE *pstyle)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetMaxLength(DWORD *plength)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetScrollBars(DWORD *pdwScrollBar)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetPasswordChar(_Out_ TCHAR *pch)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetAcceleratorPos(LONG *pcp)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetExtent(LPSIZEL lpExtent)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::OnTxCharFormatChange(const CHARFORMATW * pCF)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::OnTxParaFormatChange(const PARAFORMAT * pPF)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxNotify(DWORD iNotify, void *pv)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HIMC TinyRichUI::TxImmGetContext()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxImmReleaseContext(HIMC himc)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetSelectionBarWidth(LONG *lSelBarWidth)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	BOOL TinyRichUI::TxIsDoubleClickPending()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetWindow(HWND *phwnd)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxSetForegroundWindow()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HPALETTE TinyRichUI::TxGetPalette()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetEastAsianFlags(LONG *pFlags)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HCURSOR TinyRichUI::TxSetCursor2(HCURSOR hcur, BOOL bText)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void TinyRichUI::TxFreeTextServicesNotification()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetEditStyle(DWORD dwItem, DWORD *pdwData)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetWindowStyles(DWORD *pdwStyle, DWORD *pdwExStyle)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxShowDropCaret(BOOL fShow, HDC hdc, LPCRECT prc)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxDestroyCaret()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	HRESULT TinyRichUI::TxGetHorzExtent(LONG *plHorzExtent)
	{
		throw std::exception("The method or operation is not implemented.");
	}

}
