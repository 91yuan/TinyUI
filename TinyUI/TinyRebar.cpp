#include "stdafx.h"
#include "TinyRebar.h"

namespace TinyUI
{
	TinyRebar::TinyRebar()
	{

	}
	TinyRebar::~TinyRebar()
	{

	}
	LPCSTR TinyRebar::RetrieveClassName()
	{
		return REBARCLASSNAME;
	}
	LPCSTR TinyRebar::RetrieveTitle()
	{
		return TEXT("SysRebar");
	}
	DWORD TinyRebar::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | RBS_AUTOSIZE | RBS_VARHEIGHT | CCS_NORESIZE | RBS_BANDBORDERS);
	}
	DWORD TinyRebar::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY);
	}

	BOOL TinyRebar::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_COOL_CLASSES | ICC_BAR_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy, TRUE);
		}
		return FALSE;
	}

	UINT TinyRebar::GetBandCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, RB_GETBANDCOUNT, 0, 0L);
	}
	BOOL TinyRebar::GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_GETBANDINFO, uBand, (LPARAM)prbbi);
	}
	UINT TinyRebar::GetBarHeight() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, RB_GETBARHEIGHT, 0, 0L);
	}
	BOOL TinyRebar::GetBarInfo(REBARINFO* prbi) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_GETBARINFO, 0, (LPARAM)prbi);
	}
	COLORREF TinyRebar::GetBkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, RB_GETBKCOLOR, 0, 0L);
	}
	IDropTarget* TinyRebar::GetDropTarget() const
	{
		ASSERT(::IsWindow(m_hWND));
		IDropTarget* pdt; ::SendMessage(m_hWND, RB_GETDROPTARGET, 0, (LPARAM)&pdt); return pdt;
	}
	BOOL TinyRebar::GetRect(UINT uBand, LPRECT prc) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_GETRECT, uBand, (LPARAM)prc);
	}
	UINT TinyRebar::GetRowCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, RB_GETROWCOUNT, 0, 0L);
	}
	UINT TinyRebar::GetRowHeight(UINT uRow) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, RB_GETROWHEIGHT, uRow, 0L);
	}
	COLORREF TinyRebar::GetTextColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, RB_GETTEXTCOLOR, 0, 0L);
	}
	HWND TinyRebar::GetToolTips() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, RB_GETTOOLTIPS, 0, 0L);
	}
	INT TinyRebar::IDToIndex(UINT uBandID) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, RB_IDTOINDEX, uBandID, 0L);
	}
	BOOL TinyRebar::SetBandInfo(UINT uBand, REBARBANDINFO* prbbi)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_SETBANDINFO, uBand, (LPARAM)prbbi);
	}
	BOOL TinyRebar::SetBarInfo(REBARINFO* prbi)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_SETBARINFO, 0, (LPARAM)prbi);
	}
	COLORREF TinyRebar::SetBkColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, RB_SETBKCOLOR, 0, (LPARAM)clr);
	}
	HWND TinyRebar::SetOwner(HWND pWnd)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, RB_SETPARENT, (WPARAM)pWnd, 0L);
	}
	COLORREF TinyRebar::SetTextColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, RB_SETTEXTCOLOR, 0, (LPARAM)clr);
	}
	void TinyRebar::SetToolTips(HWND pTip)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_SETTOOLTIPS, (WPARAM)pTip, 0L);
	}
	void TinyRebar::BeginDrag(UINT uBand, DWORD dwPos)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_BEGINDRAG, uBand, dwPos);
	}
	BOOL TinyRebar::DeleteBand(UINT uBand)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_DELETEBAND, uBand, 0L);
	}
	void TinyRebar::DragMove(DWORD dwPos)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_DRAGMOVE, 0, dwPos);
	}
	void TinyRebar::EndDrag()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_ENDDRAG, 0, 0L);
	}
	INT TinyRebar::HitTest(RBHITTESTINFO* prbht)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, RB_HITTEST, 0, (LPARAM)prbht);
	}
	BOOL TinyRebar::InsertBand(UINT uIndex, REBARBANDINFO* prbbi)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_INSERTBAND, uIndex, (LPARAM)prbbi);
	}
	void TinyRebar::MaximizeBand(UINT uBand)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_MAXIMIZEBAND, uBand, 0L);
	}
	void TinyRebar::MinimizeBand(UINT uBand)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_MINIMIZEBAND, uBand, 0L);
	}
	void TinyRebar::RestoreBand(UINT uBand)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_MAXIMIZEBAND, uBand, 1L);
	}
	BOOL TinyRebar::SizeToRect(TinyRectangle& rect)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_SIZETORECT, 0, (LPARAM)&rect);
	}
	BOOL TinyRebar::ShowBand(UINT uBand, BOOL fShow /*= TRUE*/)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_SHOWBAND, uBand, fShow);
	}
	void TinyRebar::GetBandBorders(UINT uBand, LPRECT prc) const
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_GETBANDBORDERS, uBand, (LPARAM)prc);
	}
	HPALETTE TinyRebar::GetPalette() const
	{
		ASSERT(::IsWindow(m_hWND));
		return(HPALETTE)::SendMessage(m_hWND, RB_GETPALETTE, 0, 0L);
	}
	HPALETTE TinyRebar::SetPalette(HPALETTE hPal)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HPALETTE)::SendMessage(m_hWND, RB_SETPALETTE, 0, (LPARAM)hPal);
	}
	BOOL TinyRebar::MoveBand(UINT uFrom, UINT uTo)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, RB_MOVEBAND, uFrom, uTo);
	}
	void TinyRebar::PushChevron(UINT uBand, LPARAM lAppValue)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, RB_PUSHCHEVRON, uBand, lAppValue);
	}
}

