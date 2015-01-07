#pragma once
#include "TinyControl.h"
#include "TinyGraphics.h"
#include "TinyEvent.h"

namespace TinyUI
{
	class TinyListView : public TinyControl
	{
		DECLARE_DYNAMIC(TinyListView)
	public:
		TinyListView();
		virtual ~TinyListView();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveExStyle();
		virtual DWORD RetrieveStyle();
		virtual BOOL Create(HWND hParent, int x, int y, int cx, int cy);
		//////////////////////////////////////////////////////////////////////////
		virtual HRESULT OnCreate(void* sender, LPCREATESTRUCT lpCreateStruct, BOOL& bHandled);
		virtual HRESULT OnNotify(void* sender, UINT ctlID, LPARAM lParam, BOOL& bHandled);
		virtual HRESULT OnRButtonUp(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled);
		virtual HRESULT OnRButtonDown(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled);
		virtual HRESULT OnLButtonDown(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled);
		virtual HRESULT OnLButtonUp(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled);
		virtual HRESULT OnMButtonDown(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled);
		virtual HRESULT OnMButtonUp(void* sender, UINT nFlags, TinyPoint pos, BOOL& bHandled);
	private:
		void LvnDeleteItem(INT iItem);
		void LvnColumnClick(INT iSubItem);
		void LvnDeleteAllItems();
		void LvnInsertItem(INT iItem);
		HRESULT LvnItemChanging(NMLISTVIEW* nmlv);
		void LvnItemChanged(NMLISTVIEW* nmlv);
		void LvnItemActivate(NMITEMACTIVATE* nmActivate);
	public:
		void UpdateCursor(HCURSOR hNew);
		virtual void OnDeleteItem(INT iItem);
		virtual void OnDeleteAllItems();
		virtual void OnInsertItem(INT iItem);
		virtual void OnColumnClick(INT iSubItem);
		virtual void OnItemActivate(NMITEMACTIVATE* nmActivate);
		virtual void OnItemChanging(NMLISTVIEW* nmlv, BOOL& bCancel);
		virtual void OnItemChange(NMLISTVIEW* nmlv);
		Event<void(void*, NMLISTVIEW*, BOOL&)> EVENT_ItemChanging;
		Event<void(void*, NMLISTVIEW*)> EVENT_ItemChange;
		Event<void(void*, NMITEMACTIVATE*)> EVENT_ItemActivate;
		Event<void(void*, INT)> EVENT_ColumnClick;
		Event<void(void*, INT)> EVENT_InsertItem;
		Event<void(void*, INT)> EVENT_DeleteItem;
		Event<void(void*)> EVENT_DeleteAllItems;
		//////////////////////////////////////////////////////////////////////////
		COLORREF GetBkColor() const;
		BOOL SetBkColor(_In_ COLORREF cr);
		HWND GetToolTips() const;
		HWND SetToolTips(_In_ HWND pWndTip);
		int GetItemCount() const;
		BOOL GetItem(_Out_ LVITEM* pItem) const;
		BOOL SetItem(_In_ const LVITEM* pItem);
		BOOL SetItem(_In_ int nItem, _In_ int nSubItem, _In_ UINT nMask, _In_opt_z_ LPCTSTR lpszItem,
			_In_ int nImage, _In_ UINT nState, _In_ UINT nStateMask, _In_ LPARAM lParam);
		BOOL SetItem(_In_ int nItem, _In_ int nSubItem, _In_ UINT nMask, _In_opt_z_ LPCTSTR lpszItem,
			_In_ int nImage, _In_ UINT nState, _In_ UINT nStateMask, _In_ LPARAM lParam, _In_ int nIndent);
		UINT GetCallbackMask() const;
		BOOL SetCallbackMask(_In_ UINT nMask);
		INT GetNextItem(_In_ int nItem, _In_ int nFlags) const;
		POSITION GetFirstSelectedItemPosition() const;
		INT GetNextSelectedItem(_Inout_ POSITION& pos) const;
		BOOL GetItemRect(_In_ int nItem, _Out_ LPRECT lpRect, _In_ UINT nCode) const;
		BOOL SetItemPosition(_In_ int nItem, _In_ POINT pt);
		BOOL GetItemPosition(_In_ int nItem, _Out_ LPPOINT lpPoint) const;
		INT GetStringWidth(_In_z_ LPCTSTR lpsz) const;
		HWND GetEditControl() const;
		BOOL GetColumn(_In_ int nCol, _Out_ LVCOLUMN* pColumn) const;
		BOOL SetColumn(_In_ int nCol, _In_ const LVCOLUMN* pColumn);
		INT GetColumnWidth(_In_ int nCol) const;
		BOOL SetColumnWidth(_In_ int nCol, _In_ int cx);
		BOOL GetViewRect(_Out_ LPRECT lpRect) const;
		COLORREF GetTextColor() const;
		BOOL SetTextColor(_In_ COLORREF cr);
		COLORREF GetTextBkColor() const;
		BOOL SetTextBkColor(_In_ COLORREF cr);
		INT GetTopIndex() const;
		INT GetCountPerPage() const;
		BOOL GetOrigin(_Out_ LPPOINT lpPoint) const;
		BOOL SetItemState(_In_ int nItem, _In_ LVITEM* pItem);
		BOOL SetItemState(_In_ int nItem, _In_ UINT nState, _In_ UINT nMask);
		UINT GetItemState(_In_ int nItem, _In_ UINT nMask) const;
		SysString GetItemText(_In_ int nItem, _In_ int nSubItem) const;
		INT GetItemText(_In_ int nItem, _In_ int nSubItem, _Out_z_cap_post_count_(nLen, return +1) LPTSTR lpszText, _In_ int nLen) const;
		BOOL SetItemText(_In_ int nItem, _In_ int nSubItem, _In_z_ LPCTSTR lpszText);
		void SetItemCount(_In_ int nItems);
		BOOL SetItemData(_In_ int nItem, _In_ DWORD_PTR dwData);
		DWORD_PTR GetItemData(_In_ int nItem) const;
		UINT GetSelectedCount() const;
		BOOL GetItemSpacing(_In_ BOOL fSmall, _Out_ int* pnHorzSpacing, _Out_ int* pnVertSpacing) const;
		BOOL SetColumnOrderArray(_In_ int iCount, _In_ LPINT piArray);
		BOOL GetColumnOrderArray(_Out_ LPINT piArray, _In_ int iCount = -1) const;
		TinySize SetIconSpacing(_In_ TinySize size);
		TinySize SetIconSpacing(_In_ int cx, _In_ int cy);
		HCURSOR GetHotCursor() const;
		HCURSOR SetHotCursor(_In_ HCURSOR hc);
		BOOL GetSubItemRect(_In_ int iItem, _In_ int iSubItem, _In_ int nArea, _Out_ TinyRect& ref) const;
		INT GetHotItem() const;
		INT SetHotItem(_In_ int iIndex);
		INT GetSelectionMark() const;
		INT SetSelectionMark(_In_ int iIndex);
		DWORD GetExtendedStyle() const;
		DWORD SetExtendedStyle(_In_ DWORD dwNewStyle);
		INT SubItemHitTest(_In_ LPLVHITTESTINFO pInfo);
		void SetWorkAreas(_In_ int nWorkAreas, _In_ LPRECT lpRect);
		BOOL SetItemCountEx(_In_ int iCount, _In_ DWORD dwFlags = LVSICF_NOINVALIDATEALL);
		TinySize ApproximateViewRect(_In_ TinySize sz = TinySize(-1, -1), int iCount = -1) const;
		BOOL GetBkImage(_Out_ LVBKIMAGE* plvbkImage) const;
		DWORD GetHoverTime() const;
		void GetWorkAreas(_In_ int nWorkAreas, _Out_ LPRECT prc) const;
		BOOL SetBkImage(_In_ HBITMAP hbm, _In_ BOOL fTile = TRUE, _In_ int xOffsetPercent = 0, _In_ int yOffsetPercent = 0);
		BOOL SetBkImage(_In_z_ LPTSTR pszUrl, _In_ BOOL fTile = TRUE, _In_ int xOffsetPercent = 0, _In_ int yOffsetPercent = 0);
		BOOL SetBkImage(_In_ LVBKIMAGE* plvbkImage);
		DWORD SetHoverTime(_In_ DWORD dwHoverTime = (DWORD)-1);
		UINT GetNumberOfWorkAreas() const;
		BOOL GetCheck(_In_ int nItem) const;
		BOOL SetCheck(_In_ int nItem, _In_ BOOL fCheck = TRUE);
		INT InsertItem(_In_ UINT nMask, _In_ int nItem, _In_z_ LPCTSTR lpszItem, _In_ UINT nState, _In_ UINT nStateMask, _In_ int nImage, _In_ LPARAM lParam);
		INT InsertItem(_In_ const LVITEM* pItem);
		INT InsertItem(_In_ int nItem, _In_z_ LPCTSTR lpszItem);
		INT InsertItem(_In_ int nItem, _In_z_ LPCTSTR lpszItem, _In_ int nImage);
		BOOL DeleteItem(_In_ int nItem);
		BOOL DeleteAllItems();
		INT FindItem(_In_ LVFINDINFO* pFindInfo, _In_ int nStart = -1) const;
		INT HitTest(_In_ LVHITTESTINFO* pHitTestInfo) const;
		INT HitTest(_In_ TinyPoint pt, _In_opt_ UINT* pFlags = NULL) const;
		BOOL EnsureVisible(_In_ int nItem, _In_ BOOL bPartialOK);
		BOOL Scroll(_In_ TinySize size);
		BOOL RedrawItems(_In_ int nFirst, _In_ int nLast);
		BOOL Arrange(_In_ UINT nCode);
		HWND EditLabel(_In_ int nItem);
		INT InsertColumn(_In_ int nCol, _In_ const LVCOLUMN* pColumn);
		INT InsertColumn(_In_ int nCol, _In_z_ LPCTSTR lpszColumnHeading, _In_ int nFormat = LVCFMT_LEFT, _In_ int nWidth = -1, _In_ int nSubItem = -1);
		BOOL DeleteColumn(_In_ int nCol);
		SysImageList* CreateDragImage(_In_ int nItem, _In_ LPPOINT lpPoint);
		BOOL Update(_In_ int nItem);
		BOOL SortItems(_In_ PFNLVCOMPARE pfnCompare, _In_ DWORD_PTR dwData);
		BOOL SortItemsEx(_In_ PFNLVCOMPARE pfnCompare, _In_ DWORD_PTR dwData);
		void SetSelectedColumn(_In_ int iCol);
		DWORD SetView(_In_ int iView);
		DWORD GetView() const;
		INT InsertGroup(_In_ int index, _In_ PLVGROUP pgrp);
		INT SetGroupInfo(_In_ int iGroupId, _In_ PLVGROUP pGroup);
		INT GetGroupInfo(_In_ int iGroupId, _Out_ PLVGROUP pgrp) const;
		INT RemoveGroup(_In_ int iGroupId);
		void MoveGroup(_In_ int iGroupId, _In_ int toIndex);
		void MoveItemToGroup(_In_ int idItemFrom, _In_ int idGroupTo);
		void SetGroupMetrics(_In_ PLVGROUPMETRICS pGroupMetrics);
		void GetGroupMetrics(_Out_ PLVGROUPMETRICS pGroupMetrics) const;
		HWND GetHeaderCtrl() const;
		INT EnableGroupView(_In_ BOOL fEnable);
		BOOL SortGroups(_In_ PFNLVGROUPCOMPARE _pfnGroupCompare, _In_ LPVOID _plv);
		void InsertGroupSorted(_In_ PLVINSERTGROUPSORTED pStructInsert);
		void RemoveAllGroups();
		BOOL HasGroup(_In_ int iGroupId) const;
		BOOL SetTileViewInfo(_In_ PLVTILEVIEWINFO ptvi);
		BOOL GetTileViewInfo(_Out_ PLVTILEVIEWINFO ptvi) const;
		BOOL SetTileInfo(_In_ PLVTILEINFO pti);
		BOOL GetTileInfo(_Out_ PLVTILEINFO pti) const;
		BOOL SetInsertMark(_In_ LPLVINSERTMARK lvim);
		BOOL GetInsertMark(_Out_ LPLVINSERTMARK lvim) const;
		INT InsertMarkHitTest(_In_ LPPOINT pPoint, _In_ LPLVINSERTMARK lvim) const;
		INT GetInsertMarkRect(_Out_ LPRECT pRect) const;
		COLORREF SetInsertMarkColor(_In_ COLORREF color);
		COLORREF GetInsertMarkColor() const;
		BOOL SetInfoTip(_In_ PLVSETINFOTIP plvInfoTip);
		UINT GetSelectedColumn() const;
		BOOL IsGroupViewEnabled() const;
		COLORREF GetOutlineColor() const;
		COLORREF SetOutlineColor(_In_ COLORREF color);
		void CancelEditLabel();
		void RemoveImageList(_In_ int nImageList);
	}
}

