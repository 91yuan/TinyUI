#include "../stdafx.h"
#include "TinyTabControl.h"

namespace TinyUI
{
	TinyTabControl::TinyTabControl()
	{

	}
	TinyTabControl::~TinyTabControl()
	{

	}
	LPCSTR TinyTabControl::RetrieveClassName()
	{
		return WC_TABCONTROL;
	}
	LPCSTR TinyTabControl::RetrieveTitle()
	{
		return TEXT("TinyTabControl");
	}
	DWORD TinyTabControl::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_BORDER);
	}
	DWORD TinyTabControl::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY);
	}
	BOOL TinyTabControl::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_TAB_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyTabControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	HIMAGELIST TinyTabControl::GetImageList() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HIMAGELIST)::SendMessage(m_hWND, TCM_GETIMAGELIST, 0, 0L);
	}
	HIMAGELIST TinyTabControl::SetImageList(HIMAGELIST hImageList)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HIMAGELIST)::SendMessage(m_hWND, TCM_SETIMAGELIST, 0, (LPARAM)hImageList);
	}
	INT TinyTabControl::GetItemCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_GETITEMCOUNT, 0, 0L);
	}
	BOOL TinyTabControl::GetItem(INT nItem, TCITEM* pTabCtrlItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_GETITEM, nItem, (LPARAM)pTabCtrlItem);
	}
	BOOL TinyTabControl::SetItem(INT nItem, TCITEM* pTabCtrlItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_SETITEM, nItem, (LPARAM)pTabCtrlItem);
	}
	BOOL TinyTabControl::SetItemExtra(INT nBytes)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_SETITEMEXTRA, (WPARAM)nBytes, 0);
	}
	void TinyTabControl::SetCurFocus(INT nItem)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TCM_SETCURFOCUS, (WPARAM)nItem, 0);
	}
	LONG TinyTabControl::InsertItem(INT nItem, TCITEM* pTabCtrlItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (LONG)::SendMessage(m_hWND, TCM_INSERTITEM, nItem, (LPARAM)pTabCtrlItem);
	}
	LONG TinyTabControl::InsertItem(INT nItem, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return TinyTabControl::InsertItem(TCIF_TEXT, nItem, lpszItem, 0, 0);
	}
	LONG TinyTabControl::InsertItem(UINT nMask, INT nItem, LPCTSTR lpszItem, INT nImage, LPARAM lParam)
	{
		ASSERT(::IsWindow(m_hWND));
		TCITEM item;
		item.mask = nMask;
		item.iImage = nImage;
		item.lParam = lParam;
		item.pszText = (LPTSTR)lpszItem;
		return (LONG) ::SendMessage(m_hWND, TCM_INSERTITEM, nItem, (LPARAM)&item);
	}

	LONG TinyTabControl::InsertItem(UINT nMask, INT nItem, LPCTSTR lpszItem, INT nImage, LPARAM lParam, DWORD dwState, DWORD dwStateMask)
	{
		ASSERT(::IsWindow(m_hWND));
		TCITEM item;
		item.mask = nMask;
		item.iImage = nImage;
		item.lParam = lParam;
		item.pszText = (LPTSTR)lpszItem;
		item.dwState = dwState;
		item.dwStateMask = dwStateMask;
		return (LONG) ::SendMessage(m_hWND, TCM_INSERTITEM, nItem, (LPARAM)&item);
	}
	LONG TinyTabControl::InsertItem(INT nItem, LPCTSTR lpszItem, INT nImage)
	{
		ASSERT(::IsWindow(m_hWND));
		return TinyTabControl::InsertItem(TCIF_TEXT | TCIF_IMAGE, nItem, lpszItem, nImage, 0);
	}
	BOOL TinyTabControl::DeleteItem(INT nItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_DELETEITEM, nItem, 0L);
	}
	BOOL TinyTabControl::DeleteAllItems()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_DELETEALLITEMS, 0, 0L);
	}
	BOOL TinyTabControl::GetItemRect(INT nItem, LPRECT lpRect) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_GETITEMRECT, nItem, (LPARAM)lpRect);
	}
	INT TinyTabControl::GetCurSel() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_GETCURSEL, 0, 0L);
	}
	INT TinyTabControl::SetCurSel(INT nItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_SETCURSEL, nItem, 0L);
	}
	INT TinyTabControl::HitTest(TCHITTESTINFO* pHitTestInfo) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_HITTEST, 0, (LPARAM)pHitTestInfo);
	}
	void TinyTabControl::AdjustRect(BOOL bLarger, LPRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TCM_ADJUSTRECT, bLarger, (LPARAM)lpRect);
	}
	TinySize TinyTabControl::SetItemSize(TinySize size)
	{
		ASSERT(::IsWindow(m_hWND));
		return (TinySize)DWORD(::SendMessage(m_hWND, TCM_SETITEMSIZE, 0, MAKELPARAM(size.cx, size.cy)));
	}
	void TinyTabControl::RemoveImage(INT nImage)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TCM_REMOVEIMAGE, nImage, 0L);
	}
	void TinyTabControl::SetPadding(TinySize size)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TCM_SETPADDING, 0, MAKELPARAM(size.cx, size.cy));
	}
	INT TinyTabControl::GetRowCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_GETROWCOUNT, 0, 0L);
	}
	HWND TinyTabControl::GetToolTips() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, TCM_GETTOOLTIPS, 0, 0L);
	}
	void TinyTabControl::SetToolTips(HWND pWndTip)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TCM_SETTOOLTIPS, (WPARAM)pWndTip, 0L);
	}
	INT TinyTabControl::GetCurFocus() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_GETCURFOCUS, 0, 0L);
	}
	INT TinyTabControl::SetMinTabWidth(INT cx)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, TCM_SETMINTABWIDTH, 0, (LPARAM)cx);
	}
	void TinyTabControl::DeselectAll(BOOL fExcludeFocus)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TCM_DESELECTALL, fExcludeFocus, 0);
	}
	BOOL TinyTabControl::HighlightItem(INT idItem, BOOL fHighlight /*= TRUE*/)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TCM_HIGHLIGHTITEM, idItem, MAKELPARAM(fHighlight, 0));
	}
	DWORD TinyTabControl::GetExtendedStyle() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD) ::SendMessage(m_hWND, TCM_GETEXTENDEDSTYLE, 0, 0);
	}
	DWORD TinyTabControl::SetExtendedStyle(DWORD dwNewStyle, DWORD dwExMask /*= 0*/)
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD) ::SendMessage(m_hWND, TCM_SETEXTENDEDSTYLE, dwExMask, dwNewStyle);
	}
	void TinyTabControl::OnSelectChangingTab(void* sender, BOOL& bPrevent)
	{
		EVENT_SelectChangingTab(this, bPrevent);
	}
	void TinyTabControl::OnSelectChangeTab(void* sender)
	{
		EVENT_SelectChangeTab(this);
	}
	HRESULT TinyTabControl::OnNotifyReflect(void* sender, UINT ctlID, LPARAM lParam, BOOL &bHandled)
	{
		BOOL bPrevent = FALSE;
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGING:
			OnSelectChangingTab(this, bPrevent);
			return bPrevent;
		case TCN_SELCHANGE:
			OnSelectChangeTab(this);
			break;
		}
		return FALSE;
	}

}