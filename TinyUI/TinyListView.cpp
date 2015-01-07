#include "stdafx.h"
#include "TinyListView.h"

namespace TinyUI
{
	TinyListView::TinyListView()
	{
	}
	TinyListView::~TinyListView()
	{

	}
	LPCSTR TinyListView::RetrieveClassName()
	{
		return WC_LISTVIEW;
	}
	LPCSTR TinyListView::RetrieveTitle()
	{
		return TEXT("TinyListView");
	}
	DWORD TinyListView::RetrieveStyle()
	{
		return (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT);
	}
	DWORD TinyListView::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY);
	}
	BOOL TinyListView::Create(HWND hParent, int x, int y, int cx, int cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	HRESULT TinyListView::OnNotify(void* sender, UINT ctlID, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = 0;
		NMLISTVIEW* nmlv = (NMLISTVIEW*)lParam;
		if (nmlv != NULL)
		{
			switch (nmlv->hdr.code)
			{
			case LVN_DELETEITEM:
				LvnDeleteItem(nmlv->iItem);
				break;
			case LVN_DELETEALLITEMS:
				LvnDeleteAllItems();
				lRes = FALSE;
				break;
			case LVN_COLUMNCLICK:
				LvnColumnClick(nmlv->iSubItem);
				break;
			case LVN_INSERTITEM:
				LvnInsertItem(nmlv->iItem);
				break;
			case LVN_ITEMCHANGING:
				lRes = LvnItemChanging(nmlv);
				break;
			case LVN_ITEMCHANGED:
				LvnItemChanged(nmlv);
				break;
			case LVN_ITEMACTIVATE:
			{
									 NMITEMACTIVATE* nmActivate = (NMITEMACTIVATE*)lParam;
									 LvnItemActivate(nmActivate);
									 lRes = FALSE;
			}
				break;
			case NM_CLICK:
			{
							 TinyPoint pos;
							 GetCursorPos(&pos);
							 ::MapWindowPoints(NULL, m_hWND, &pos, 1);
							 OnLButtonUp(this, MK_LBUTTON, pos, bHandled);
			}
				break;
			case NM_RCLICK:
			{
							  TinyPoint pos;
							  GetCursorPos(&pos);
							  ::MapWindowPoints(NULL, m_hWND, &pos, 1);
							  OnRButtonUp(this, MK_RBUTTON, pos, bHandled);
			}
				break;
			case NM_DBLCLK:
				break;
			case NM_RDBLCLK:
				break;
			}
		}
		return lRes;
	}
	void TinyListView::LvnDeleteItem(INT iItem)
	{
		OnDeleteItem(iItem);
	}
	void TinyListView::LvnDeleteAllItems()
	{
		OnDeleteAllItems();
	}
	void TinyListView::LvnColumnClick(INT iSubItem)
	{
		OnColumnClick(iSubItem);
	}
	void TinyListView::LvnInsertItem(INT iItem)
	{
		OnInsertItem(iItem);
	}
	HRESULT TinyListView::LvnItemChanging(NMLISTVIEW* nmlv)
	{
		BOOL bCancel = FALSE;
		OnItemChanging(nmlv, bCancel);
		return (LRESULT)bCancel;
	}
	void TinyListView::LvnItemChanged(NMLISTVIEW* nmlv)
	{
		OnItemChange(nmlv);
	}
	void TinyListView::LvnItemActivate(NMITEMACTIVATE* nmActivate)
	{
		OnItemActivate(nmActivate);
	}
	//////////////////////////////////////////////////////////////////////////
	void TinyListView::UpdateCursor(HCURSOR hNew)
	{
		::SetCursor(hNew);
	}

	HRESULT TinyListView::OnCreate(void* sender, LPCREATESTRUCT lpCreateStruct, BOOL& bHandled)
	{
		return TinyControl::OnCreate(sender, lpCreateStruct, bHandled);
	}
	HRESULT TinyListView::OnRButtonDown(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	HRESULT TinyListView::OnRButtonUp(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled)
	{
		bHandled = FALSE;
		/*if (m_contextMenu != NULL)
		{
		TinyRectangle client;
		GetClientRect(&client);
		if (client.PtInRect(pos))
		{
		MapWindowPoints(NULL, &pos, 1);
		SetForegroundWindow();
		TrackPopupMenuEx(m_contextMenu->Handle(), TPM_VERTICAL | TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, m_hWND, NULL);
		PostMessage(0x0000, NULL, NULL);
		}
		}*/
		return FALSE;
	}
	HRESULT TinyListView::OnLButtonDown(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	HRESULT TinyListView::OnLButtonUp(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	HRESULT TinyListView::OnMButtonDown(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	HRESULT TinyListView::OnMButtonUp(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	void TinyListView::OnDeleteItem(INT iItem)
	{
		EVENT_DeleteItem(this, iItem);
	}
	void TinyListView::OnDeleteAllItems()
	{
		EVENT_DeleteAllItems(this);
	}
	void TinyListView::OnInsertItem(INT iItem)
	{
		EVENT_InsertItem(this, iItem);
	}
	void TinyListView::OnColumnClick(INT iSubItem)
	{
		EVENT_ColumnClick(this, iSubItem);
	}
	void TinyListView::OnItemActivate(NMITEMACTIVATE* nmActivate)
	{
		EVENT_ItemActivate(this, nmActivate);
	}
	void TinyListView::OnItemChanging(NMLISTVIEW* nmlv, BOOL& bCancel)
	{
		EVENT_ItemChanging(this, nmlv, bCancel);
	}
	void TinyListView::OnItemChange(NMLISTVIEW* nmlv)
	{
		EVENT_ItemChange(this, nmlv);
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyListView::GetItemRect(int nItem, LPRECT lpRect, UINT nCode) const
	{
		ASSERT(::IsWindow(m_hWND));
		lpRect->left = nCode;
		return (BOOL) ::SendMessage(m_hWND, LVM_GETITEMRECT, (WPARAM)nItem, (LPARAM)lpRect);
	}
	DWORD TinyListView::SetExtendedStyle(DWORD dwNewStyle)
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD) ::SendMessage(m_hWND, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwNewStyle);
	}
	HCURSOR TinyListView::SetHotCursor(HCURSOR hc)
	{
		ASSERT(::IsWindow(m_hWND) && hc != NULL);
		return (HCURSOR) ::SendMessage(m_hWND, LVM_SETHOTCURSOR, 0, (LPARAM)hc);
	}
	INT TinyListView::SetHotItem(int iIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_SETHOTITEM, (WPARAM)iIndex, 0);
	}
	void TinyListView::SetWorkAreas(int nWorkAreas, LPRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LVM_SETWORKAREAS, nWorkAreas, (LPARAM)lpRect);
	}
	INT TinyListView::SubItemHitTest(LPLVHITTESTINFO pInfo)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_SUBITEMHITTEST, 0, (LPARAM)pInfo);
	}
	HCURSOR TinyListView::GetHotCursor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HCURSOR) ::SendMessage(m_hWND, LVM_GETHOTCURSOR, 0, 0);
	}
	INT TinyListView::GetHotItem() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETHOTITEM, 0, 0);
	}
	DWORD TinyListView::GetExtendedStyle() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD) ::SendMessage(m_hWND, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
	}
	TinySize TinyListView::ApproximateViewRect(TinySize sz, int iCount) const
	{
		ASSERT(::IsWindow(m_hWND));
		return TinySize((DWORD) ::SendMessage(m_hWND, LVM_APPROXIMATEVIEWRECT, iCount, MAKELPARAM(sz.cx, sz.cy)));
	}
	BOOL TinyListView::GetBkImage(LVBKIMAGE* plvbkImage) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_GETBKIMAGE, 0, (LPARAM)plvbkImage);
	}
	DWORD TinyListView::GetHoverTime() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD) ::SendMessage(m_hWND, LVM_GETHOVERTIME, 0, 0);
	}
	void TinyListView::GetWorkAreas(int nWorkAreas, LPRECT prc) const
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LVM_GETWORKAREAS, nWorkAreas, (LPARAM)prc);
	}
	BOOL TinyListView::SetBkImage(LVBKIMAGE* plvbkImage)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, LVM_SETBKIMAGE, 0, (LPARAM)plvbkImage);
	}
	DWORD TinyListView::SetHoverTime(DWORD dwHoverTime)
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::SendMessage(m_hWND, LVM_SETHOVERTIME, 0, dwHoverTime);
	}
	UINT TinyListView::GetNumberOfWorkAreas() const
	{
		ASSERT(::IsWindow(m_hWND));
		UINT nWorkAreas;
		::SendMessage(m_hWND, LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)&nWorkAreas);
		return nWorkAreas;
	}
	BOOL TinyListView::GetCheck(INT nItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		INT nState = (int)::SendMessage(m_hWND, LVM_GETITEMSTATE, (WPARAM)nItem, (LPARAM)LVIS_STATEIMAGEMASK);
		return ((BOOL)(nState >> 12) - 1);
	}

	BOOL TinyListView::SetCheck(INT nItem, BOOL fCheck)
	{
		ASSERT(::IsWindow(m_hWND));
		LVITEM lvi;
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK((fCheck ? 2 : 1));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
	}
	INT TinyListView::SetSelectionMark(int iIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, LVM_SETSELECTIONMARK, 0, (LPARAM)iIndex);
	}
	INT TinyListView::GetSelectionMark() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, LVM_GETSELECTIONMARK, 0, 0);
	}
	BOOL TinyListView::SetItemCountEx(int iCount, DWORD dwFlags /* = LVSICF_NOINVALIDATEALL */)
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT(dwFlags == 0 || (GetStyle() & LVS_OWNERDATA));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEMCOUNT, (WPARAM)iCount, (LPARAM)dwFlags);
	}
	TinySize TinyListView::SetIconSpacing(int cx, int cy)
	{
		ASSERT(::IsWindow(m_hWND));
		DWORD dwRet = (DWORD) ::SendMessage(m_hWND, LVM_SETICONSPACING, 0, (LPARAM)MAKELONG(cx, cy));
		return TinySize(dwRet);
	}
	TinySize TinyListView::SetIconSpacing(TinySize size)
	{
		ASSERT(::IsWindow(m_hWND));
		DWORD dwRet = (DWORD) ::SendMessage(m_hWND, LVM_SETICONSPACING, 0, (LPARAM)MAKELONG(size.cx, size.cy));
		return TinySize(dwRet);
	}
	BOOL TinyListView::GetSubItemRect(int iItem, int iSubItem, int nArea, TinyRectangle& ref) const
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT(nArea == LVIR_BOUNDS || nArea == LVIR_ICON || nArea == LVIR_LABEL || nArea == LVIR_SELECTBOUNDS);

		RECT rect;
		rect.top = iSubItem;
		rect.left = nArea;
		BOOL bRet = (BOOL) ::SendMessage(m_hWND, LVM_GETSUBITEMRECT, iItem, (LPARAM)&rect);
		if (bRet)
			ref = rect;
		return bRet;
	}

	int TinyListView::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth, int nSubItem)
	{
		LVCOLUMN column;
		column.mask = LVCF_TEXT | LVCF_FMT;
		column.pszText = (LPTSTR)lpszColumnHeading;
		column.fmt = nFormat;
		if (nWidth != -1)
		{
			column.mask |= LVCF_WIDTH;
			column.cx = nWidth;
		}
		if (nSubItem != -1)
		{
			column.mask |= LVCF_SUBITEM;
			column.iSubItem = nSubItem;
		}
		return TinyListView::InsertColumn(nCol, &column);
	}

	int TinyListView::InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask,
		int nImage, LPARAM lParam)
	{
		ASSERT(::IsWindow(m_hWND));
		LVITEM item;
		item.mask = nMask;
		item.iItem = nItem;
		item.iSubItem = 0;
		item.pszText = (LPTSTR)lpszItem;
		item.state = nState;
		item.stateMask = nStateMask;
		item.iImage = nImage;
		item.lParam = lParam;
		return TinyListView::InsertItem(&item);
	}

	int TinyListView::HitTest(TinyPoint pt, UINT* pFlags) const
	{
		ASSERT(::IsWindow(m_hWND));
		LVHITTESTINFO hti;
		hti.pt = pt;
		int nRes = (int) ::SendMessage(m_hWND, LVM_HITTEST, 0, (LPARAM)&hti);
		if (pFlags != NULL)
			*pFlags = hti.flags;
		return nRes;
	}

	BOOL TinyListView::SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
		int nImage, UINT nState, UINT nStateMask, LPARAM lParam)
	{
		ASSERT((nMask & LVIF_INDENT) == 0);
		return SetItem(nItem, nSubItem, nMask, lpszItem, nImage, nState, nStateMask, lParam, 0);
	}

	BOOL TinyListView::SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
		int nImage, UINT nState, UINT nStateMask, LPARAM lParam, int nIndent)
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT((GetStyle() & LVS_OWNERDATA) == 0);
		LVITEM lvi;
		lvi.mask = nMask;
		lvi.iItem = nItem;
		lvi.iSubItem = nSubItem;
		lvi.stateMask = nStateMask;
		lvi.state = nState;
		lvi.pszText = (LPTSTR)lpszItem;
		lvi.iImage = nImage;
		lvi.lParam = lParam;
		lvi.iIndent = nIndent;

		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEM, 0, (LPARAM)&lvi);
	}

	BOOL TinyListView::SetItemState(int nItem, UINT nState, UINT nStateMask)
	{
		ASSERT(::IsWindow(m_hWND));
		LVITEM lvi;
		lvi.stateMask = nStateMask;
		lvi.state = nState;
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
	}

	BOOL TinyListView::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT((GetStyle() & LVS_OWNERDATA) == 0);
		LVITEM lvi;
		lvi.iSubItem = nSubItem;
		lvi.pszText = (LPTSTR)lpszText;
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEMTEXT, nItem, (LPARAM)&lvi);
	}

	SysString TinyListView::GetItemText(int nItem, int nSubItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		LVITEM lvi;
		memset(&lvi, 0, sizeof(LVITEM));
		lvi.iSubItem = nSubItem;
		SysString str;
		int nLen = 128;
		int nRes;
		do
		{
			nLen *= 2;
			lvi.cchTextMax = nLen;
			lvi.pszText = str.GetBuffer(nLen);
			nRes = (int)::SendMessage(m_hWND, LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
		} while (nRes >= nLen - 1);
		str.ReleaseBuffer();
		return str;
	}

	int TinyListView::GetItemText(_In_ int nItem, _In_ int nSubItem, _Out_z_cap_post_count_(nLen, return +1) LPTSTR lpszText, _In_ int nLen) const
	{
		ASSERT(::IsWindow(m_hWND));
		LVITEM lvi;
		memset(&lvi, 0, sizeof(LVITEM));
		lvi.iSubItem = nSubItem;
		lvi.cchTextMax = nLen;
		lvi.pszText = lpszText;
		return (int)::SendMessage(m_hWND, LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
	}

	DWORD_PTR TinyListView::GetItemData(int nItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		LVITEM lvi;
		memset(&lvi, 0, sizeof(LVITEM));
		lvi.iItem = nItem;
		lvi.mask = LVIF_PARAM;
		::SendMessage(m_hWND, LVM_GETITEM, 0, (LPARAM)&lvi);
		return lvi.lParam;
	}
	void TinyListView::RemoveImageList(int nImageList)
	{
		HIMAGELIST h = (HIMAGELIST)SendMessage(LVM_GETIMAGELIST, (WPARAM)nImageList);
		SendMessage(LVM_SETIMAGELIST, (WPARAM)h, NULL);
	}
	SysImageList* TinyListView::CreateDragImage(int nItem, LPPOINT lpPoint)
	{
		ASSERT(::IsWindow(m_hWND));

		HIMAGELIST hImageList = (HIMAGELIST)::SendMessage(m_hWND, LVM_CREATEDRAGIMAGE, nItem, (LPARAM)lpPoint);
		if (hImageList == NULL)
			return NULL;
		SysImageList* pImageList = new SysImageList();
		pImageList->Attach(hImageList);
		return pImageList;
	}
	HWND TinyListView::GetToolTips() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, LVM_GETTOOLTIPS, 0, 0L);
	}
	HWND TinyListView::SetToolTips(HWND pTip)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, LVM_SETTOOLTIPS, 0, (LPARAM)pTip);
	}
	COLORREF TinyListView::GetBkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, LVM_GETBKCOLOR, 0, 0L);
	}
	BOOL TinyListView::SetBkColor(COLORREF cr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETBKCOLOR, 0, cr);
	}
	int TinyListView::GetItemCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETITEMCOUNT, 0, 0L);
	}
	BOOL TinyListView::GetItem(LVITEM* pItem) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_GETITEM, 0, (LPARAM)pItem);
	}
	BOOL TinyListView::SetItem(const LVITEM* pItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEM, 0, (LPARAM)pItem);
	}
	BOOL TinyListView::SetItemData(int nItem, DWORD_PTR dwData)
	{
		ASSERT(::IsWindow(m_hWND));
		return SetItem(nItem, 0, LVIF_PARAM, NULL, 0, 0, 0, (LPARAM)dwData);
	}
	int TinyListView::InsertItem(const LVITEM* pItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_INSERTITEM, 0, (LPARAM)pItem);
	}
	int TinyListView::InsertItem(int nItem, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return InsertItem(LVIF_TEXT, nItem, lpszItem, 0, 0, 0, 0);
	}
	int TinyListView::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
	{
		ASSERT(::IsWindow(m_hWND));
		return InsertItem(LVIF_TEXT | LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, 0);
	}
	BOOL TinyListView::DeleteItem(int nItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_DELETEITEM, nItem, 0L);
	}
	BOOL TinyListView::DeleteAllItems()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_DELETEALLITEMS, 0, 0L);
	}
	UINT TinyListView::GetCallbackMask() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, LVM_GETCALLBACKMASK, 0, 0);
	}
	BOOL TinyListView::SetCallbackMask(UINT nMask)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETCALLBACKMASK, nMask, 0);
	}
	int TinyListView::GetNextItem(int nItem, int nFlags) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETNEXTITEM, nItem, MAKELPARAM(nFlags, 0));
	}
	INT TinyListView::GetFirstSelectedItemPosition() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (1 + GetNextItem(-1, LVIS_SELECTED));
	}
	INT TinyListView::GetNextSelectedItem(INT& pos) const
	{
		ASSERT(::IsWindow(m_hWND));
		DWORD_PTR nOldPos = (DWORD_PTR)pos - 1;
		pos = (1 + GetNextItem((UINT)nOldPos, LVIS_SELECTED));
		return (UINT)nOldPos;
	}
	INT TinyListView::FindItem(LVFINDINFO* pFindInfo, int nStart) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, LVM_FINDITEM, nStart, (LPARAM)pFindInfo);
	}
	INT TinyListView::HitTest(LVHITTESTINFO* pHitTestInfo) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, LVM_HITTEST, 0, (LPARAM)pHitTestInfo);
	}
	BOOL TinyListView::SetItemPosition(int nItem, POINT pt)
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT((GetStyle() & LVS_OWNERDATA) == 0);
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEMPOSITION32, nItem, (LPARAM)&pt);
	}
	BOOL TinyListView::GetItemPosition(int nItem, LPPOINT lpPoint) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_GETITEMPOSITION, nItem, (LPARAM)lpPoint);
	}
	int TinyListView::GetStringWidth(LPCTSTR lpsz) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETSTRINGWIDTH, 0, (LPARAM)lpsz);
	}
	BOOL TinyListView::EnsureVisible(int nItem, BOOL bPartialOK)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_ENSUREVISIBLE, nItem, MAKELPARAM(bPartialOK, 0));
	}
	BOOL TinyListView::Scroll(TinySize size)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SCROLL, size.cx, size.cy);
	}
	BOOL TinyListView::RedrawItems(int nFirst, int nLast)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_REDRAWITEMS, nFirst, nLast);
	}
	BOOL TinyListView::Arrange(UINT nCode)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_ARRANGE, nCode, 0L);
	}
	HWND TinyListView::EditLabel(int nItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, LVM_EDITLABEL, nItem, 0L);
	}
	HWND TinyListView::GetEditControl() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND)::SendMessage(m_hWND, LVM_GETEDITCONTROL, 0, 0L);
	}
	BOOL TinyListView::GetColumn(int nCol, LVCOLUMN* pColumn) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_GETCOLUMN, nCol, (LPARAM)pColumn);
	}
	BOOL TinyListView::SetColumn(int nCol, const LVCOLUMN* pColumn)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETCOLUMN, nCol, (LPARAM)pColumn);
	}
	int TinyListView::InsertColumn(int nCol, const LVCOLUMN* pColumn)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_INSERTCOLUMN, nCol, (LPARAM)pColumn);
	}
	BOOL TinyListView::DeleteColumn(int nCol)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_DELETECOLUMN, nCol, 0);
	}
	int TinyListView::GetColumnWidth(int nCol) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETCOLUMNWIDTH, nCol, 0);
	}
	BOOL TinyListView::SetColumnWidth(int nCol, int cx)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETCOLUMNWIDTH, nCol, MAKELPARAM(cx, 0));
	}
	BOOL TinyListView::GetViewRect(LPRECT lpRect) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_GETVIEWRECT, 0, (LPARAM)lpRect);
	}
	COLORREF TinyListView::GetTextColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, LVM_GETTEXTCOLOR, 0, 0L);
	}
	BOOL TinyListView::SetTextColor(COLORREF cr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETTEXTCOLOR, 0, cr);
	}
	COLORREF TinyListView::GetTextBkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, LVM_GETTEXTBKCOLOR, 0, 0L);
	}
	BOOL TinyListView::SetTextBkColor(COLORREF cr)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETTEXTBKCOLOR, 0, cr);
	}
	int TinyListView::GetTopIndex() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETTOPINDEX, 0, 0);
	}
	int TinyListView::GetCountPerPage() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, LVM_GETCOUNTPERPAGE, 0, 0);
	}
	BOOL TinyListView::GetOrigin(LPPOINT lpPoint) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_GETORIGIN, 0, (LPARAM)lpPoint);
	}
	BOOL TinyListView::Update(int nItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_UPDATE, nItem, 0L);
	}
	BOOL TinyListView::SetItemState(int nItem, LVITEM* pItem)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, LVM_SETITEMSTATE, nItem, (LPARAM)pItem);
	}
	UINT TinyListView::GetItemState(int nItem, UINT nMask) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, LVM_GETITEMSTATE, nItem, nMask);
	}
	void TinyListView::SetItemCount(int nItems)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, LVM_SETITEMCOUNT, nItems, 0);
	}
	BOOL TinyListView::SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData)
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT((GetStyle() & LVS_OWNERDATA) == 0);
		return (BOOL) ::SendMessage(m_hWND, LVM_SORTITEMS, dwData, (LPARAM)pfnCompare);
	}
	BOOL TinyListView::SortItemsEx(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData)
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT((GetStyle() & LVS_OWNERDATA) == 0);
		return (BOOL) ::SendMessage(m_hWND, LVM_SORTITEMSEX, dwData, (LPARAM)pfnCompare);
	}
	UINT TinyListView::GetSelectedCount() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (UINT) ::SendMessage(m_hWND, LVM_GETSELECTEDCOUNT, 0, 0L);
	}
	BOOL TinyListView::GetItemSpacing(BOOL fSmall, int* pnHorzSpacing, int* pnVertSpacing) const
	{
		ASSERT(::IsWindow(m_hWND));
		ASSERT(pnHorzSpacing != NULL);
		ASSERT(pnVertSpacing != NULL);
		if (pnHorzSpacing == NULL || pnVertSpacing == NULL)
		{
			return FALSE;
		}
		DWORD dwSpacing = (DWORD)::SendMessage(m_hWND, LVM_GETITEMSPACING, (WPARAM)fSmall, 0L);
		*pnHorzSpacing = (int)LOWORD(dwSpacing);
		*pnVertSpacing = (int)HIWORD(dwSpacing);
		return TRUE;
	}
	HWND TinyListView::GetHeaderCtrl() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (HWND) ::SendMessage(m_hWND, LVM_GETHEADER, 0, 0);
	}
	void TinyListView::SetSelectedColumn(int iCol)
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_SetSelectedColumn(m_hWND, iCol); // LVM_SETSELECTEDCOLUMN
	}
	DWORD TinyListView::SetView(int iView)
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_SetView(m_hWND, iView); // LVM_SETVIEW
	}
	DWORD TinyListView::GetView() const
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_GetView(m_hWND); // LVM_GETVIEW
	}
	int TinyListView::InsertGroup(int index, PLVGROUP pgrp)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_InsertGroup(m_hWND, index, pgrp); // LVM_INSERTGROUP
	}
	int TinyListView::SetGroupInfo(int iGroupId, PLVGROUP pGroup)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_SetGroupInfo(m_hWND, iGroupId, pGroup); // LVM_SETGROUPINFO
	}
	int TinyListView::GetGroupInfo(int iGroupId, PLVGROUP pgrp) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_GetGroupInfo(m_hWND, iGroupId, pgrp); // LVM_GETGROUPINFO
	}
	int TinyListView::RemoveGroup(int iGroupId)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_RemoveGroup(m_hWND, iGroupId); // LVM_REMOVEGROUP
	}
	void TinyListView::MoveGroup(int iGroupId, int toIndex)
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_MoveGroup(m_hWND, iGroupId, toIndex); // LVM_MOVEGROUP
	}
	void TinyListView::MoveItemToGroup(int idItemFrom, int idGroupTo)
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_MoveItemToGroup(m_hWND, idItemFrom, idGroupTo); // LVM_MOVEITEMTOGROUP
	}
	void TinyListView::SetGroupMetrics(PLVGROUPMETRICS pGroupMetrics)
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_SetGroupMetrics(m_hWND, pGroupMetrics); // LVM_SETGROUPMETRICS
	}
	void TinyListView::GetGroupMetrics(PLVGROUPMETRICS pGroupMetrics) const
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_GetGroupMetrics(m_hWND, pGroupMetrics); // LVM_GETGROUPMETRICS
	}
	int TinyListView::EnableGroupView(BOOL fEnable)
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_EnableGroupView(m_hWND, fEnable); // LVM_ENABLEGROUPVIEW
	}
	BOOL TinyListView::SortGroups(PFNLVGROUPCOMPARE _pfnGroupCompare, LPVOID _plv)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, LVM_SORTGROUPS, (WPARAM)(LPARAM)_plv, (LPARAM)_pfnGroupCompare);
	}
	void TinyListView::InsertGroupSorted(PLVINSERTGROUPSORTED pStructInsert)
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_InsertGroupSorted(m_hWND, pStructInsert); // LVM_INSERTGROUPSORTED
	}
	void TinyListView::RemoveAllGroups()
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_RemoveAllGroups(m_hWND); // LVM_REMOVEALLGROUPS
	}
	BOOL TinyListView::HasGroup(int iGroupId) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_HasGroup(m_hWND, iGroupId); // LVM_HASGROUP
	}
	BOOL TinyListView::SetTileViewInfo(PLVTILEVIEWINFO ptvi)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_SetTileViewInfo(m_hWND, ptvi); // LVM_SETTILEVIEWINFO
	}
	BOOL TinyListView::GetTileViewInfo(PLVTILEVIEWINFO ptvi) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_GetTileViewInfo(m_hWND, ptvi); // LVM_GETTILEVIEWINFO
	}
	BOOL TinyListView::SetTileInfo(PLVTILEINFO pti)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_SetTileInfo(m_hWND, pti); // LVM_SETTILEINFO
	}
	BOOL TinyListView::GetTileInfo(PLVTILEINFO pti) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_GetTileInfo(m_hWND, pti); // LVM_GETTILEINFO
	}
	BOOL TinyListView::SetInsertMark(LPLVINSERTMARK lvim)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_SetInsertMark(m_hWND, lvim); // LVM_SETINSERTMARK
	}
	BOOL TinyListView::GetInsertMark(LPLVINSERTMARK lvim) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)ListView_GetInsertMark(m_hWND, lvim); // LVM_GETINSERTMARK
	}
	int TinyListView::InsertMarkHitTest(LPPOINT pPoint, LPLVINSERTMARK lvim) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_InsertMarkHitTest(m_hWND, pPoint, lvim); // LVM_INSERTMARKHITTEST
	}
	int TinyListView::GetInsertMarkRect(LPRECT pRect) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int)ListView_GetInsertMarkRect(m_hWND, pRect); // LVM_GETINSERTMARKRECT
	}
	COLORREF TinyListView::SetInsertMarkColor(COLORREF color)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF)ListView_SetInsertMarkColor(m_hWND, color); // LVM_SETINSERTMARKCOLOR
	}
	COLORREF TinyListView::GetInsertMarkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_GetInsertMarkColor(m_hWND); // LVM_GETINSERTMARKCOLOR
	}
	BOOL TinyListView::SetInfoTip(PLVSETINFOTIP plvInfoTip)
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_SetInfoTip(m_hWND, plvInfoTip); // LVM_SETINFOTIP
	}
	UINT TinyListView::GetSelectedColumn() const
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_GetSelectedColumn(m_hWND); // LVM_GETSELECTEDCOLUMN
	}
	BOOL TinyListView::IsGroupViewEnabled() const
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_IsGroupViewEnabled(m_hWND); // LVM_ISGROUPVIEWENABLED
	}
	COLORREF TinyListView::GetOutlineColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_GetOutlineColor(m_hWND); // LVM_GETOUTLINECOLOR
	}
	COLORREF TinyListView::SetOutlineColor(COLORREF color)
	{
		ASSERT(::IsWindow(m_hWND));
		return ListView_SetOutlineColor(m_hWND, color); // LVM_SETOUTLINECOLOR
	}
	void TinyListView::CancelEditLabel()
	{
		ASSERT(::IsWindow(m_hWND));
		ListView_CancelEditLabel(m_hWND); // LVM_CANCELEDITLABEL
	}
}

