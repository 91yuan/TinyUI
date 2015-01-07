#include "stdafx.h"
#include "TinyListBox.h"

namespace TinyUI
{
	TinyListBox::TinyListBox()
	{

	}
	TinyListBox::~TinyListBox()
	{

	}
	LPCSTR TinyListBox::RetrieveClassName()
	{
		return WC_LISTBOX;
	}
	LPCSTR TinyListBox::RetrieveTitle()
	{
		return TEXT("TinyListBox");
	}
	DWORD TinyListBox::RetrieveStyle()
	{
		return (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	}
	DWORD TinyListBox::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY);
	}
	BOOL TinyListBox::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	INT TinyListBox::GetCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);
	}
	INT TinyListBox::GetCurSel() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	}
	INT TinyListBox::SetCurSel(INT nSelect)
	{
		return (int)SendMessage(m_hWND, LB_SETCURSEL, (WPARAM)nSelect, (LPARAM)0);
	}
	INT TinyListBox::GetHorizontalExtent() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETHORIZONTALEXTENT, (WPARAM)0, (LPARAM)0);
	}
	void TinyListBox::SetHorizontalExtent(INT cxExtent)
	{
		SendMessage(m_hWND, LB_SETHORIZONTALEXTENT, cxExtent, 0);
	}
	INT TinyListBox::GetSelCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETSELCOUNT, 0, 0);
	}
	INT TinyListBox::GetSelItems(INT nMaxItems, LPINT rgIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETSELITEMS, nMaxItems, (LPARAM)rgIndex);
	}
	INT TinyListBox::GetTopIndex() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETTOPINDEX, 0, 0);
	}
	INT TinyListBox::SetTopIndex(INT nIndex)
	{
		return (int)SendMessage(m_hWND, LB_SETTOPINDEX, nIndex, 0);
	}
	DWORD_PTR TinyListBox::GetItemData(int nIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SendMessage(m_hWND, LB_GETITEMDATA, nIndex, 0);
	}
	INT TinyListBox::SetItemData(INT nIndex, LPARAM dwItemData)
	{
		return (int)SendMessage(m_hWND, LB_SETITEMDATA, nIndex, dwItemData);
	}
	void* TinyListBox::GetItemDataPtr(INT nIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LPVOID)::SendMessage(m_hWND, LB_GETITEMDATA, nIndex, 0);
	}
	INT TinyListBox::SetItemDataPtr(INT nIndex, void* pData)
	{
		return SetItemData(nIndex, (LPARAM)pData);
	}
	INT TinyListBox::GetItemRect(INT nIndex, LPRECT lpRect) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETITEMRECT, nIndex, (LPARAM)lpRect);
	}
	INT TinyListBox::GetSel(INT nIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETSEL, nIndex, 0);
	}
	INT TinyListBox::SetSel(INT nIndex, BOOL bSelect)
	{
		return (INT)SendMessage(m_hWND, LB_SETSEL, bSelect, nIndex);
	}
	INT TinyListBox::GetText(INT nIndex, LPTSTR lpszBuffer) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETTEXT, nIndex, (LPARAM)lpszBuffer);
	}
	INT TinyListBox::GetTextLen(INT nIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETTEXTLEN, nIndex, 0);
	}
	void TinyListBox::SetColumnWidth(int cxWidth)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LB_SETCOLUMNWIDTH, cxWidth, 0);
	}
	INT TinyListBox::GetItemAt(POINT pos)
	{
		ASSERT(::IsWindow(m_hWND));
		RECT rect = { 0 };
		GetClientRect(&rect);
		if (::PtInRect(&rect, pos))
		{
			DWORD dwItem = (DWORD)::SendMessage(m_hWND, LB_ITEMFROMPOINT, NULL, MAKELPARAM(pos.x, pos.y));
			if (HIWORD(dwItem) == 0)
				return  LOWORD(dwItem);
			else
				return LB_ERR;
		}
		else
		{
			return LB_ERR;
		}
	}
	BOOL TinyListBox::SetTabStops(INT nTabStops, LPINT rgTabStops)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, LB_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
	}
	void TinyListBox::SetTabStops()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LB_SETTABSTOPS, 0, 0);
	}
	BOOL TinyListBox::SetTabStops(const INT& cxEachStop)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, LB_SETTABSTOPS, 1, (LPARAM)(LPINT)&cxEachStop);
	}
	INT TinyListBox::SetItemHeight(INT nIndex, UINT cyItemHeight)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));
	}
	INT TinyListBox::GetItemHeight(INT nIndex) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETITEMHEIGHT, nIndex, 0L);
	}
	INT TinyListBox::FindStringExact(INT nIndexStart, LPCTSTR lpszFind) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind);
	}
	INT TinyListBox::GetCaretIndex() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETCARETINDEX, 0, 0L);
	}
	INT TinyListBox::SetCaretIndex(int nIndex, BOOL bScroll)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_SETCARETINDEX, nIndex, MAKELONG(bScroll, 0));
	}
	INT TinyListBox::AddString(LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_ADDSTRING, 0, (LPARAM)lpszItem);
	}
	INT TinyListBox::DeleteString(UINT nIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_DELETESTRING, nIndex, 0);
	}
	INT TinyListBox::InsertString(INT nIndex, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_INSERTSTRING, nIndex, (LPARAM)lpszItem);
	}
	void TinyListBox::ResetContent()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LB_RESETCONTENT, 0, 0);
	}
	INT TinyListBox::Dir(UINT attr, LPCTSTR lpszWildCard)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_DIR, attr, (LPARAM)lpszWildCard);
	}
	INT TinyListBox::FindString(INT nStartAfter, LPCTSTR lpszItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_FINDSTRING, nStartAfter, (LPARAM)lpszItem);
	}
	INT TinyListBox::SelectString(INT nStartAfter, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_SELECTSTRING, nStartAfter, (LPARAM)lpszItem);
	}
	INT TinyListBox::SelItemRange(BOOL bSelect, INT nFirstItem, INT nLastItem)
	{
		ASSERT(::IsWindow(m_hWND)); return bSelect ?
			(int)::SendMessage(m_hWND, LB_SELITEMRANGEEX, nFirstItem, nLastItem) :
			(int)::SendMessage(m_hWND, LB_SELITEMRANGEEX, nLastItem, nFirstItem);
	}
	void TinyListBox::SetAnchorIndex(INT nIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LB_SETANCHORINDEX, nIndex, 0);
	}
	INT TinyListBox::GetAnchorIndex() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)::SendMessage(m_hWND, LB_GETANCHORINDEX, 0, 0);
	}
	LCID TinyListBox::GetLocale() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (LCID)::SendMessage(m_hWND, LB_GETLOCALE, 0, 0);
	}
	LCID TinyListBox::SetLocale(LCID nNewLocale)
	{
		ASSERT(::IsWindow(m_hWND));
		return (LCID)::SendMessage(m_hWND, LB_SETLOCALE, (WPARAM)nNewLocale, 0);
	}
	INT TinyListBox::InitStorage(INT nItems, UINT nBytes)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, LB_INITSTORAGE, (WPARAM)nItems, nBytes);
	}
}
