#include "../stdafx.h"
#include "TinyColumn.h"

namespace TinyUI
{
	TinyColumn::TinyColumn()
	{
	}

	TinyColumn::~TinyColumn()
	{
	}
	LPCSTR TinyColumn::RetrieveClassName()
	{
		return WC_HEADER;
	}
	LPCSTR TinyColumn::RetrieveTitle()
	{
		return TEXT("TinyColumn");
	}
	DWORD TinyColumn::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING);
	}
	DWORD TinyColumn::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | HDS_BUTTONS | HDS_HOTTRACK | HDS_OVERFLOW);
	}
	BOOL TinyColumn::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	BOOL TinyColumn::SetOrderArray(INT iCount, LPINT piArray)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, HDM_SETORDERARRAY,
			(WPARAM)iCount, (LPARAM)piArray);
	}

	BOOL TinyColumn::GetOrderArray(LPINT piArray, INT iCount) const
	{
		ASSERT(::IsWindow(m_hWND));
		INT nCount = iCount;
		if (nCount < 0)
		{
			ASSERT(FALSE);
			return FALSE;
		}
		return (BOOL) ::SendMessage(m_hWND, HDM_GETORDERARRAY, (WPARAM)nCount, (LPARAM)piArray);
	}
	INT TinyColumn::GetItemCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, HDM_GETITEMCOUNT, 0, 0L);
	}
	INT TinyColumn::InsertItem(INT nPos, HDITEM* phdi)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_INSERTITEM, nPos, (LPARAM)phdi);
	}
	BOOL TinyColumn::DeleteItem(INT nPos)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, HDM_DELETEITEM, nPos, 0L);
	}
	BOOL TinyColumn::GetItem(INT nPos, HDITEM* pHeaderItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, HDM_GETITEM, nPos, (LPARAM)pHeaderItem);
	}
	BOOL TinyColumn::SetItem(INT nPos, HDITEM* pHeaderItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, HDM_SETITEM, nPos, (LPARAM)pHeaderItem);
	}

	BOOL TinyColumn::Layout(HDLAYOUT* pHeaderLayout)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, HDM_LAYOUT, 0, (LPARAM)pHeaderLayout);
	}

	INT TinyColumn::HitTest(LPHDHITTESTINFO pHeaderHitTestInfo)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, HDM_HITTEST, 0, (LPARAM)pHeaderHitTestInfo);
	}

	BOOL TinyColumn::GetItemRect(INT nIndex, LPRECT lpRect) const
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT(lpRect != NULL);
		return (BOOL)::SendMessage(m_hWND, HDM_GETITEMRECT, nIndex, (LPARAM)lpRect);
	}
	INT TinyColumn::OrderToIndex(INT nOrder) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_ORDERTOINDEX, nOrder, 0);
	}
	INT TinyColumn::SetHotDivider(TinyPoint pt)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_SETHOTDIVIDER, TRUE, MAKELPARAM(pt.x, pt.y));
	}
	INT TinyColumn::SetHotDivider(INT nIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_SETHOTDIVIDER, FALSE, nIndex);
	}
	HIMAGELIST TinyColumn::CreateDragImage(INT nIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HIMAGELIST) ::SendMessage(m_hWND, HDM_CREATEDRAGIMAGE, nIndex, 0L);
	}

	INT TinyColumn::GetBitmapMargin() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_GETBITMAPMARGIN, 0, 0L);
	}
	INT TinyColumn::SetBitmapMargin(INT nWidth)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_SETBITMAPMARGIN, nWidth, 0L);
	}
	INT TinyColumn::SetFilterChangeTimeout(DWORD dwTimeOut)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_SETFILTERCHANGETIMEOUT, 0, dwTimeOut);
	}
	INT TinyColumn::EditFilter(INT nColumn, BOOL bDiscardChanges)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, HDM_EDITFILTER, nColumn, MAKELPARAM(bDiscardChanges, 0));
	}
	BOOL TinyColumn::ClearFilter(INT nColumn)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, HDM_CLEARFILTER, nColumn, 0L);
	}
	BOOL TinyColumn::ClearAllFilters()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, HDM_CLEARFILTER, (WPARAM)-1, 0L);
	}
}

