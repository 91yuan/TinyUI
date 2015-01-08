#include "stdafx.h"
#include "TinyTreeView.h"

namespace TinyUI
{
	TinyTreeView::TinyTreeView()
		:m_hCursor(NULL)
	{

	}
	TinyTreeView::~TinyTreeView()
	{

	}
	LPCSTR TinyTreeView::RetrieveClassName()
	{
		return WC_TREEVIEW;
	}
	LPCSTR TinyTreeView::RetrieveTitle()
	{
		return _T("TinyTreeView");
	}
	DWORD TinyTreeView::RetrieveStyle()
	{
		return (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_HASLINES);
	}
	DWORD TinyTreeView::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY);
	}
	BOOL TinyTreeView::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_TREEVIEW_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	LRESULT TinyTreeView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		::SendMessage(m_hWND, TVM_SETEXTENDEDSTYLE, TVS_EX_MULTISELECT, (LPARAM)TVS_EX_MULTISELECT);
		return FALSE;
	}
	LRESULT TinyTreeView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		::SetCursor(m_hCursor);
		return FALSE;
	}
	LRESULT TinyTreeView::OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		LRESULT lRes = 0;
		NMTREEVIEW* nmtv = (NMTREEVIEW*)lParam;
		if (nmtv != NULL)
		{
			switch (nmtv->hdr.code)
			{
			case TVN_ITEMEXPANDING:
				lRes = TvnExpanding(nmtv);
				break;
			case TVN_ITEMEXPANDED:
				TvnExpanded(nmtv);
				break;
			case TVN_SELCHANGING:
				lRes = TvnSelecting(nmtv);
				break;
			case TVN_SELCHANGED:
				TvnSelected(nmtv);
				break;
			case TVN_DELETEITEM:
				TvnDeleteItem(nmtv);
				break;
			}
		}
		return lRes;
	}
	void TinyTreeView::TvnDeleteItem(NMTREEVIEW* nmtv)
	{
		TVITEM tvItem = nmtv->itemOld;
		if (tvItem.hItem == NULL) return;
		OnNodeDelete(tvItem);
	}
	LRESULT TinyTreeView::TvnExpanding(NMTREEVIEW* nmtv)
	{
		TV_ITEM item = nmtv->itemNew;
		if (item.hItem == NULL) return FALSE;
		BOOL bCancel = FALSE;
		if ((item.state & TVIS_EXPANDED) == 0)//展开
			OnNodeExpanding(item.hItem, bCancel);
		else
			OnNodeCollapsing(item.hItem, bCancel);
		return (LRESULT)bCancel;
	}
	void TinyTreeView::TvnExpanded(NMTREEVIEW* nmtv)
	{
		TV_ITEM item = nmtv->itemNew;
		if (item.hItem == NULL) return;
		if ((item.state & TVIS_EXPANDED) == 0)//展开
			OnNodeExpanded(item.hItem);
		else
			OnNodeCollapsed(item.hItem);
	}
	LRESULT TinyTreeView::TvnSelecting(NMTREEVIEW* nmtv)
	{
		TV_ITEM item = nmtv->itemNew;
		if (item.hItem == NULL) return FALSE;
		BOOL bCancel = FALSE;
		OnNodeSelecting(item.hItem, bCancel);
		return (LRESULT)bCancel;
	}
	void TinyTreeView::TvnSelected(NMTREEVIEW* nmtv)
	{
		TV_ITEM item = nmtv->itemNew;
		if (item.hItem == NULL) return;
		OnNodeSelected(item.hItem);
		RECT rect = { 0 };
		if (nmtv->itemOld.hItem != NULL)
		{
			if ((INT)SendMessage(TVM_GETITEMRECT, 1, (LPARAM)&rect) != 0)
			{
				InvalidateRect(m_hWND, &rect, TRUE);
			}
		}
	}
	void TinyTreeView::UpdateCursor(HCURSOR hNew)
	{
		m_hCursor = hNew;
		::SetCursor(m_hCursor);
	}
	void TinyTreeView::OnNodeDelete(TVITEM& tvItem)
	{
		EVENT_NodeDelete(this, tvItem);
	}
	void TinyTreeView::OnNodeExpanding(HTREEITEM hItem, BOOL& bCancel)
	{
		EVENT_NodeExpanding(this, hItem, bCancel);
	}
	void TinyTreeView::OnNodeCollapsing(HTREEITEM hItem, BOOL& bCancel)
	{
		EVENT_NodeCollapsing(this, hItem, bCancel);
	}
	void TinyTreeView::OnNodeExpanded(HTREEITEM hItem)
	{
		EVENT_NodeExpanded(this, hItem);
	}
	void TinyTreeView::OnNodeCollapsed(HTREEITEM hItem)
	{
		EVENT_NodeCollapsed(this, hItem);
	}
	void TinyTreeView::OnNodeSelecting(HTREEITEM hItem, BOOL& bCancel)
	{
		EVENT_NodeSelecting(this, hItem, bCancel);
	}
	void TinyTreeView::OnNodeSelected(HTREEITEM hItem)
	{
		EVENT_NodeSelected(this, hItem);
	}
	HTREEITEM TinyTreeView::InsertItem(LPTVINSERTSTRUCT lpInsertStruct)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_INSERTITEM, 0, (LPARAM)lpInsertStruct);
	}
	HTREEITEM TinyTreeView::InsertItem(LPCTSTR lpszItem, INT nImage, INT nSelectedImage, HTREEITEM hParent, HTREEITEM hInsertAfter)
	{
		ASSERT(::IsWindow(m_hWND));
		return InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE, lpszItem, nImage, nSelectedImage, 0, 0, 0, hParent, hInsertAfter);
	}
	HTREEITEM TinyTreeView::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
	{
		ASSERT(::IsWindow(m_hWND));
		return InsertItem(TVIF_TEXT, lpszItem, 0, 0, 0, 0, 0, hParent, hInsertAfter);
	}
	BOOL TinyTreeView::DeleteItem(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_DELETEITEM, 0, (LPARAM)hItem);
	}
	BOOL TinyTreeView::DeleteAllItems()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
	}
	BOOL TinyTreeView::Expand(HTREEITEM hItem, UINT nCode)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_EXPAND, nCode, (LPARAM)hItem);
	}
	UINT TinyTreeView::GetCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT)::SendMessage(m_hWND, TVM_GETCOUNT, 0, 0);
	}
	UINT TinyTreeView::GetIndent() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT)::SendMessage(m_hWND, TVM_GETINDENT, 0, 0);
	}
	void TinyTreeView::SetIndent(UINT nIndent)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, TVM_SETINDENT, nIndent, 0);
	}
	HIMAGELIST TinyTreeView::GetImageList(INT nImageList) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HIMAGELIST)::SendMessage(m_hWND, TVM_GETIMAGELIST, (WPARAM)nImageList, 0);
	}
	HIMAGELIST TinyTreeView::SetImageList(HIMAGELIST hImageList, INT nImageList)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HIMAGELIST)::SendMessage(m_hWND, TVM_SETIMAGELIST, (WPARAM)nImageList, (LPARAM)hImageList);
	}
	UINT TinyTreeView::SetScrollTime(UINT uScrollTime)
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, TVM_SETSCROLLTIME, (WPARAM)uScrollTime, 0);
	}
	HTREEITEM TinyTreeView::GetNextItem(HTREEITEM hItem, UINT nCode) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, nCode, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetChildItem(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetNextSiblingItem(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetPrevSiblingItem(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_PREVIOUS, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetParentItem(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetFirstVisibleItem() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_FIRSTVISIBLE, 0);
	}
	HTREEITEM TinyTreeView::GetNextVisibleItem(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_NEXTVISIBLE, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetPrevVisibleItem(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_PREVIOUSVISIBLE, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::GetLastVisibleItem() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_LASTVISIBLE, 0);
	}
	HTREEITEM TinyTreeView::GetSelectedItem() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_CARET, 0);
	}
	UINT TinyTreeView::GetScrollTime() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, TVM_GETSCROLLTIME, 0, 0);
	}
	HTREEITEM TinyTreeView::GetDropHilightItem() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_DROPHILITE, 0);
	}
	HTREEITEM TinyTreeView::GetRootItem() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_GETNEXTITEM, TVGN_ROOT, 0);
	}
	BOOL TinyTreeView::Select(HTREEITEM hItem, UINT nCode)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_SELECTITEM, nCode, (LPARAM)hItem);
	}
	BOOL TinyTreeView::SelectItem(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem);
	}
	BOOL TinyTreeView::SelectDropTarget(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, TVM_SELECTITEM, TVGN_DROPHILITE, (LPARAM)hItem);
	}
	BOOL TinyTreeView::SelectSetFirstVisible(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, TVM_SELECTITEM, TVGN_FIRSTVISIBLE, (LPARAM)hItem);
	}
	BOOL TinyTreeView::GetItem(TVITEM* pItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_GETITEM, 0, (LPARAM)pItem);
	}
	BOOL TinyTreeView::SetItem(TVITEM* pItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_SETITEM, 0, (LPARAM)pItem);
	}
	BOOL TinyTreeView::SetItemText(HTREEITEM hItem, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return SetItem(hItem, TVIF_TEXT, lpszItem, 0, 0, 0, 0, NULL);
	}
	BOOL TinyTreeView::SetItemImage(HTREEITEM hItem, INT nImage, INT nSelectedImage)
	{
		ASSERT(::IsWindow(m_hWND));
		return SetItem(hItem, TVIF_IMAGE | TVIF_SELECTEDIMAGE, NULL, nImage, nSelectedImage, 0, 0, NULL);
	}
	BOOL TinyTreeView::SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask)
	{
		ASSERT(::IsWindow(m_hWND));
		return SetItem(hItem, TVIF_STATE, NULL, 0, 0, nState, nStateMask, NULL);
	}
	BOOL TinyTreeView::SetItemData(HTREEITEM hItem, DWORD_PTR dwData)
	{
		ASSERT(::IsWindow(m_hWND));
		return SetItem(hItem, TVIF_PARAM, NULL, 0, 0, 0, 0, (LPARAM)dwData);
	}
	HWND TinyTreeView::EditLabel(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, TVM_EDITLABEL, 0, (LPARAM)hItem);
	}
	HTREEITEM TinyTreeView::HitTest(TVHITTESTINFO* pHitTestInfo) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HTREEITEM)::SendMessage(m_hWND, TVM_HITTEST, 0, (LPARAM)pHitTestInfo);
	}
	HWND TinyTreeView::GetEditControl() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, TVM_GETEDITCONTROL, 0, 0);
	}
	UINT TinyTreeView::GetVisibleCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT)::SendMessage(m_hWND, TVM_GETVISIBLECOUNT, 0, 0);
	}
	BOOL TinyTreeView::SortChildren(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_SORTCHILDREN, 0, (LPARAM)hItem);
	}
	BOOL TinyTreeView::EnsureVisible(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_ENSUREVISIBLE, 0, (LPARAM)hItem);
	}
	BOOL TinyTreeView::SortChildrenCB(LPTVSORTCB pSort)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, TVM_SORTCHILDRENCB, 0, (LPARAM)pSort);
	}
	HWND TinyTreeView::GetToolTips() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, TVM_GETTOOLTIPS, 0, 0L);
	}
	HWND TinyTreeView::SetToolTips(HWND pWndTip)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, TVM_SETTOOLTIPS, (WPARAM)pWndTip, 0L);
	}
	COLORREF TinyTreeView::GetBkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, TVM_GETBKCOLOR, 0, 0L);
	}
	COLORREF TinyTreeView::SetBkColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, TVM_SETBKCOLOR, 0, (LPARAM)clr);
	}
	SHORT TinyTreeView::GetItemHeight() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (SHORT) ::SendMessage(m_hWND, TVM_GETITEMHEIGHT, 0, 0L);
	}
	SHORT TinyTreeView::SetItemHeight(SHORT cyHeight)
	{
		ASSERT(::IsWindow(m_hWND));
		return (SHORT)::SendMessage(m_hWND, TVM_SETITEMHEIGHT, cyHeight, 0L);
	}
	COLORREF TinyTreeView::GetTextColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, TVM_GETTEXTCOLOR, 0, 0L);
	}
	COLORREF TinyTreeView::SetTextColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, TVM_SETTEXTCOLOR, 0, (LPARAM)clr);
	}
	BOOL TinyTreeView::SetInsertMark(HTREEITEM hItem, BOOL fAfter)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, TVM_SETINSERTMARK, fAfter, (LPARAM)hItem);
	}
	COLORREF TinyTreeView::GetInsertMarkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, TVM_GETINSERTMARKCOLOR, 0, 0L);
	}
	COLORREF TinyTreeView::SetInsertMarkColor(COLORREF clrNew)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, TVM_SETINSERTMARKCOLOR, 0, (LPARAM)clrNew);
	}
	BOOL TinyTreeView::EndEditLabelNow(BOOL fCancelWithoutSave)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, TVM_ENDEDITLABELNOW, (WPARAM)fCancelWithoutSave, 0);
	}

	COLORREF TinyTreeView::GetLineColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF)::SendMessage(m_hWND, TVM_GETLINECOLOR, 0, 0L);
	}
	COLORREF TinyTreeView::SetLineColor(COLORREF clrNew /*= CLR_DEFAULT*/)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF)::SendMessage(m_hWND, TVM_SETLINECOLOR, 0, (LPARAM)clrNew);
	}
	BOOL TinyTreeView::GetItemRect(HTREEITEM hItem, LPRECT lpRect, BOOL bTextOnly) const
	{
		ASSERT(::IsWindow(m_hWND));
		*(HTREEITEM*)lpRect = hItem;
		return (BOOL)::SendMessage(m_hWND, TVM_GETITEMRECT, (WPARAM)bTextOnly, (LPARAM)lpRect);
	}

	INT TinyTreeView::GetItemText(HTREEITEM hItem, CHAR* pz, INT size) const
	{
		ASSERT(::IsWindow(m_hWND));
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_TEXT;
		item.pszText = pz;
		item.cchTextMax = size;
		return (INT)::SendMessage(m_hWND, TVM_GETITEM, 0, (LPARAM)&item);
	}

	BOOL TinyTreeView::GetItemImage(HTREEITEM hItem, INT& nImage, INT& nSelectedImage) const
	{
		ASSERT(::IsWindow(m_hWND));
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		BOOL bRes = (BOOL)::SendMessage(m_hWND, TVM_GETITEM, 0, (LPARAM)&item);
		if (bRes)
		{
			nImage = item.iImage;
			nSelectedImage = item.iSelectedImage;
		}
		return bRes;
	}

	UINT TinyTreeView::GetItemState(HTREEITEM hItem, UINT nStateMask) const
	{
		ASSERT(::IsWindow(m_hWND));
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_STATE;
		item.stateMask = nStateMask;
		item.state = 0;
		::SendMessage(m_hWND, TVM_GETITEM, 0, (LPARAM)&item);
		return item.state;
	}

	DWORD_PTR TinyTreeView::GetItemData(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT(hItem != NULL);
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_PARAM;
		::SendMessage(m_hWND, TVM_GETITEM, 0, (LPARAM)&item);
		return item.lParam;
	}

	BOOL TinyTreeView::ItemHasChildren(HTREEITEM hItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_CHILDREN;
		::SendMessage(m_hWND, TVM_GETITEM, 0, (LPARAM)&item);
		return item.cChildren;
	}

	BOOL TinyTreeView::SetItem(HTREEITEM hItem, UINT nMask, LPCTSTR lpszItem, INT nImage,
		INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam)
	{
		ASSERT(::IsWindow(m_hWND));
		TVITEM item;
		item.hItem = hItem;
		item.mask = nMask;
		item.pszText = (LPTSTR)lpszItem;
		item.iImage = nImage;
		item.iSelectedImage = nSelectedImage;
		item.state = nState;
		item.stateMask = nStateMask;
		item.lParam = lParam;
		return (BOOL)::SendMessage(m_hWND, TVM_SETITEM, 0, (LPARAM)&item);
	}
	BOOL TinyTreeView::SetItemEx(HTREEITEM hItem, UINT nMask, LPCTSTR lpszItem, INT nImage,
		INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
		UINT uStateEx, HWND hWnd, INT iExpandedImage)
	{
		ASSERT(::IsWindow(m_hWND));
		TVITEMEX item;
		item.hItem = hItem;
		item.mask = nMask;
		item.pszText = (LPTSTR)lpszItem;
		item.iImage = nImage;
		item.iSelectedImage = nSelectedImage;
		item.state = nState;
		item.stateMask = nStateMask;
		item.lParam = lParam;
		item.uStateEx = uStateEx;
		item.hwnd = hWnd;
		item.iExpandedImage = iExpandedImage;
		return (BOOL)::SendMessage(m_hWND, TVM_SETITEM, 0, (LPARAM)&item);
	}

	HTREEITEM TinyTreeView::InsertItem(UINT nMask, LPCTSTR lpszItem, INT nImage,
		INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
		HTREEITEM hParent, HTREEITEM hInsertAfter)
	{
		ASSERT(::IsWindow(m_hWND));
		TVINSERTSTRUCT tvis;
		tvis.hParent = hParent;
		tvis.hInsertAfter = hInsertAfter;
		tvis.item.mask = nMask;
		tvis.item.pszText = (LPTSTR)lpszItem;
		tvis.item.iImage = nImage;
		tvis.item.iSelectedImage = nSelectedImage;
		tvis.item.state = nState;
		tvis.item.stateMask = nStateMask;
		tvis.item.lParam = lParam;
		return (HTREEITEM)::SendMessage(m_hWND, TVM_INSERTITEM, 0, (LPARAM)&tvis);
	}

	HTREEITEM TinyTreeView::HitTest(TinyPoint pt, UINT* pFlags) const
	{
		ASSERT(::IsWindow(m_hWND));
		TVHITTESTINFO hti;
		hti.pt = pt;
		HTREEITEM h = (HTREEITEM)::SendMessage(m_hWND, TVM_HITTEST, 0, (LPARAM)&hti);
		if (pFlags != NULL)
		{
			*pFlags = hti.flags;
		}
		return h;
	}

	void TinyTreeView::RemoveImageList(INT nImageList)
	{
		HIMAGELIST h = (HIMAGELIST)SendMessage(TVM_GETIMAGELIST, (WPARAM)nImageList, NULL);
		if (h != NULL)
		{
			SendMessage(TVM_SETIMAGELIST, (WPARAM)h, NULL);
		}
	}

	HIMAGELIST TinyTreeView::CreateDragImage(HTREEITEM hItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HIMAGELIST)::SendMessage(m_hWND, TVM_CREATEDRAGIMAGE, 0, (LPARAM)hItem);
	}
}
