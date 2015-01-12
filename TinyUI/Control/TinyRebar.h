#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	typedef struct _MARGIN
	{
		INT cxLeftWidth;
		INT cxRightWidth;
		INT cyTopHeight;
		INT cyBottomHeight;
	} MARGIN, *PMARGIN;

	class TinyRebar : public TinyControl
	{
		DECLARE_DYNAMIC(TinyRebar)
	public:
		TinyRebar();
		virtual ~TinyRebar();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		UINT GetBandCount() const;
		BOOL GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const;
		UINT GetBarHeight() const;
		BOOL GetBarInfo(REBARINFO* prbi) const;
		COLORREF GetBkColor() const;
		IDropTarget* GetDropTarget() const;
		BOOL GetRect(UINT uBand, LPRECT prc) const;
		UINT GetRowCount() const;
		UINT GetRowHeight(UINT uRow) const;
		COLORREF GetTextColor() const;
		HWND GetToolTips() const;
		INT IDToIndex(UINT uBandID) const;
		BOOL SetBandInfo(UINT uBand, REBARBANDINFO* prbbi);
		BOOL SetBarInfo(REBARINFO* prbi);
		COLORREF SetBkColor(COLORREF clr);
		HWND SetOwner(HWND pWnd);
		COLORREF SetTextColor(COLORREF clr);
		void SetToolTips(HWND pToolTip);
		void GetBandBorders(UINT uBand, LPRECT prc) const;
		HPALETTE GetPalette() const;
		HPALETTE SetPalette(HPALETTE hPal);
		BOOL GetColorScheme(COLORSCHEME* lpcs) const;
		void SetColorScheme(const COLORSCHEME* lpcs);
		void GetBandMargins(PMARGIN pMargins) const;
		HRESULT SetWindowTheme(LPCWSTR pszSubAppName);
		void BeginDrag(UINT uBand, DWORD dwPos = (DWORD)-1);
		BOOL DeleteBand(UINT uBand);
		void DragMove(DWORD dwPos = (DWORD)-1);
		void EndDrag();
		INT HitTest(RBHITTESTINFO* prbht);
		BOOL InsertBand(UINT uIndex, REBARBANDINFO* prbbi);
		void MaximizeBand(UINT uBand);
		void MinimizeBand(UINT uBand);
		void RestoreBand(UINT uBand);
		BOOL ShowBand(UINT uBand, BOOL fShow = TRUE);
		BOOL SizeToRect(TinyRectangle& rect);
		BOOL MoveBand(UINT uFrom, UINT uTo);
		void PushChevron(UINT uBand, LPARAM lAppValue);
	};
}



