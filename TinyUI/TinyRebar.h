#pragma once
#include "TinyControl.h"
#include "TinyImageList.h"

namespace TinyUI
{
	typedef struct _MARGIN
	{
		int cxLeftWidth;
		int cxRightWidth;
		int cyTopHeight;
		int cyBottomHeight;
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
		BOOL GetBandInfo(_In_ UINT uBand, _Out_ REBARBANDINFO* prbbi) const;
		UINT GetBarHeight() const;
		BOOL GetBarInfo(_Out_ REBARINFO* prbi) const;
		COLORREF GetBkColor() const;
		IDropTarget* GetDropTarget() const;
		BOOL GetRect(_In_ UINT uBand, _Out_ LPRECT prc) const;
		UINT GetRowCount() const;
		UINT GetRowHeight(_In_ UINT uRow) const;
		COLORREF GetTextColor() const;
		HWND GetToolTips() const;
		int IDToIndex(_In_ UINT uBandID) const;
		BOOL SetBandInfo(_In_ UINT uBand, _In_ REBARBANDINFO* prbbi);
		BOOL SetBarInfo(_In_ REBARINFO* prbi);
		COLORREF SetBkColor(_In_ COLORREF clr);
		HWND SetOwner(_In_ HWND pWnd);
		COLORREF SetTextColor(_In_ COLORREF clr);
		void SetToolTips(_In_ HWND pToolTip);
		TinyImageList* GetImageList() const;
		BOOL SetImageList(_In_ TinyImageList* pImageList);
		void GetBandBorders(_In_ UINT uBand, _Out_ LPRECT prc) const;
		HPALETTE GetPalette() const;
		HPALETTE SetPalette(_In_ HPALETTE hPal);
		BOOL GetColorScheme(_Out_ COLORSCHEME* lpcs) const;
		void SetColorScheme(_In_ const COLORSCHEME* lpcs);
		void GetBandMargins(_Out_ PMARGIN pMargins) const;
		HRESULT SetWindowTheme(_In_z_ LPCWSTR pszSubAppName);
		void BeginDrag(_In_ UINT uBand, _In_ DWORD dwPos = (DWORD)-1);
		BOOL DeleteBand(_In_ UINT uBand);
		void DragMove(_In_ DWORD dwPos = (DWORD)-1);
		void EndDrag();
		int HitTest(_In_ RBHITTESTINFO* prbht);
		BOOL InsertBand(_In_ UINT uIndex, _In_ REBARBANDINFO* prbbi);
		void MaximizeBand(_In_ UINT uBand);
		void MinimizeBand(_In_ UINT uBand);
		void RestoreBand(_In_ UINT uBand);
		BOOL ShowBand(_In_ UINT uBand, _In_ BOOL fShow = TRUE);
		BOOL SizeToRect(_Out_ TinyRectangle& rect);
		BOOL MoveBand(_In_ UINT uFrom, _In_ UINT uTo);
		void PushChevron(_In_ UINT uBand, _In_ LPARAM lAppValue);
	};
}



