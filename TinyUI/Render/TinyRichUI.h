#pragma once
#include <richedit.h>
#include <textserv.h>
#include <imm.h>
#include <tom.h>

namespace TinyUI
{
	const IID IID_ITextServices = {
		0x8d33f740,
		0xcf58,
		0x11ce,
		{ 0xa8, 0x9d, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5 }
	};

	const IID IID_ITextHost = {
		0xc5bdd8d0,
		0xd26e,
		0x11ce,
		{ 0xa8, 0x9e, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5 }
	};

#define LY_PER_INCH   1440
#define HIMETRIC_PER_INCH   2540
#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)
	LONG HimetricXtoDX(LONG xHimetric, LONG xPerInch);
	LONG HimetricYtoDY(LONG yHimetric, LONG yPerInch);
	LONG DXtoHimetricX(LONG dx, LONG xPerInch);
	LONG DYtoHimetricY(LONG dy, LONG yPerInch);
	/// <summary>
	/// 无窗口富文本渲染
	/// </summary>
	class TinyRichUI :public ITextHost2
	{
	public:
		TinyRichUI();
		~TinyRichUI();
		HRESULT Create(HWND hWND);//创建接口
		HRESULT SetCharFormat(CHARFORMATW * pcf, HFONT hFont);
		/************************************************************************/
		/*ITextHost                                                             */
		/************************************************************************/
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
		virtual ULONG STDMETHODCALLTYPE AddRef(void);
		virtual ULONG STDMETHODCALLTYPE Release(void);
		virtual HDC TxGetDC();
		virtual INT TxReleaseDC(HDC hdc);
		virtual BOOL TxShowScrollBar(INT fnBar, BOOL fShow);
		virtual BOOL TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags);
		virtual BOOL TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw);
		virtual BOOL TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw);
		virtual void TxInvalidateRect(LPCRECT prc, BOOL fMode);
		virtual void TxViewChange(BOOL fUpdate);
		virtual BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight);
		virtual BOOL TxShowCaret(BOOL fShow);
		virtual BOOL TxSetCaretPos(INT x, INT y);
		virtual BOOL TxSetTimer(UINT idTimer, UINT uTimeout);
		virtual void TxKillTimer(UINT idTimer);
		virtual void TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll);
		virtual void TxSetCapture(BOOL fCapture);
		virtual void TxSetFocus();
		virtual void TxSetCursor(HCURSOR hcur, BOOL fText);
		virtual BOOL TxScreenToClient(LPPOINT lppt);
		virtual BOOL TxClientToScreen(LPPOINT lppt);
		virtual HRESULT TxActivate(LONG * plOldState);
		virtual HRESULT TxDeactivate(LONG lNewState);
		virtual HRESULT TxGetClientRect(LPRECT prc);
		virtual HRESULT TxGetViewInset(LPRECT prc);
		virtual HRESULT TxGetCharFormat(const CHARFORMATW **ppCF);
		virtual HRESULT TxGetParaFormat(const PARAFORMAT **ppPF);
		virtual COLORREF TxGetSysColor(INT nIndex);
		virtual HRESULT TxGetBackStyle(TXTBACKSTYLE *pstyle);
		virtual HRESULT TxGetMaxLength(DWORD *plength);
		virtual HRESULT TxGetScrollBars(DWORD *pdwScrollBar);
		virtual HRESULT TxGetPasswordChar( TCHAR *pch);
		virtual HRESULT TxGetAcceleratorPos(LONG *pcp);
		virtual HRESULT TxGetExtent(LPSIZEL lpExtent);
		virtual HRESULT OnTxCharFormatChange(const CHARFORMATW * pCF);
		virtual HRESULT OnTxParaFormatChange(const PARAFORMAT * pPF);
		virtual HRESULT TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits);
		virtual HRESULT TxNotify(DWORD iNotify, void *pv);
		virtual HIMC TxImmGetContext();
		virtual void TxImmReleaseContext(HIMC himc);
		virtual HRESULT TxGetSelectionBarWidth(LONG *lSelBarWidth);
		/************************************************************************/
		/*ITextHost2                                                             */
		/************************************************************************/
		virtual BOOL TxIsDoubleClickPending();
		virtual HRESULT TxGetWindow(HWND *phwnd);
		virtual HRESULT TxSetForegroundWindow();
		virtual HPALETTE TxGetPalette();
		virtual HRESULT TxGetEastAsianFlags(LONG *pFlags);
		virtual HCURSOR TxSetCursor2(HCURSOR hcur, BOOL bText);
		virtual void TxFreeTextServicesNotification();
		virtual HRESULT TxGetEditStyle(DWORD dwItem, DWORD *pdwData);
		virtual HRESULT TxGetWindowStyles(DWORD *pdwStyle, DWORD *pdwExStyle);
		virtual HRESULT TxShowDropCaret(BOOL fShow, HDC hdc, LPCRECT prc);
		virtual HRESULT TxDestroyCaret();
		virtual HRESULT TxGetHorzExtent(LONG *plHorzExtent);
	public:
		//绘制接口包括OLE实现
	private:
		LONG			m_cRef;
		ITextServices	*m_pts;//富文本接口
		DWORD			m_dwStyle;
		HWND			m_hWND;
	};
}


