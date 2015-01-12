#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ListVew控件
	/// </summary>
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
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	private:
		void	LvnDeleteItem(INT iItem);
		void	LvnColumnClick(INT iSubItem);
		void	LvnDeleteAllItems();
		void	LvnInsertItem(INT iItem);
		HRESULT LvnItemChanging(NMLISTVIEW* nmlv);
		void	LvnItemChanged(NMLISTVIEW* nmlv);
		void	LvnItemActivate(NMITEMACTIVATE* nmActivate);
	public:
		void UpdateCursor(HCURSOR hNew);
		virtual LRESULT OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual void OnDeleteItem(INT iItem);
		virtual void OnDeleteAllItems();
		virtual void OnInsertItem(INT iItem);
		virtual void OnColumnClick(INT iSubItem);
		virtual void OnItemActivate(NMITEMACTIVATE* nmActivate);
		virtual void OnItemChanging(NMLISTVIEW* nmlv, BOOL& bCancel);
		virtual void OnItemChange(NMLISTVIEW* nmlv);
		Event<void(void*, NMLISTVIEW*, BOOL&)>	EVENT_ItemChanging;
		Event<void(void*, NMLISTVIEW*)>			EVENT_ItemChange;
		Event<void(void*, NMITEMACTIVATE*)>		EVENT_ItemActivate;
		Event<void(void*, INT)>					EVENT_ColumnClick;
		Event<void(void*, INT)>					EVENT_InsertItem;
		Event<void(void*, INT)>					EVENT_DeleteItem;
		Event<void(void*)>						EVENT_DeleteAllItems;
		/************************************************************************/
		/* 控件方法                                                             */
		/************************************************************************/
		HIMAGELIST GetImageList(INT nImageList) const;
		HIMAGELIST SetImageList(HIMAGELIST hImageList, INT nImageList);
		COLORREF GetBkColor() const;
		BOOL SetBkColor(COLORREF cr);
		HWND GetToolTips() const;
		HWND SetToolTips(HWND pWndTip);
		INT GetItemCount() const;
		BOOL GetItem(LVITEM* pItem) const;
		BOOL SetItem(const LVITEM* pItem);
		BOOL SetItem(INT nItem, INT nSubItem, UINT nMask, LPCTSTR lpszItem, INT nImage, UINT nState, UINT nStateMask, LPARAM lParam);
		BOOL SetItem(INT nItem, INT nSubItem, UINT nMask, LPCTSTR lpszItem, INT nImage, UINT nState, UINT nStateMask, LPARAM lParam, INT nIndent);
		UINT GetCallbackMask() const;
		BOOL SetCallbackMask(UINT nMask);
		INT GetNextItem(INT nItem, INT nFlags) const;
		INT GetFirstSelectedItemPosition() const;
		INT GetNextSelectedItem(INT& pos) const;
		BOOL GetItemRect(INT nItem, LPRECT lpRect, UINT nCode) const;
		BOOL SetItemPosition(INT nItem, POINT pt);
		BOOL GetItemPosition(INT nItem, LPPOINT lpPoint) const;
		INT GetStringWidth(LPCTSTR lpsz) const;
		HWND GetEditControl() const;
		BOOL GetColumn(INT nCol, LVCOLUMN* pColumn) const;
		BOOL SetColumn(INT nCol, const LVCOLUMN* pColumn);
		INT GetColumnWidth(INT nCol) const;
		BOOL SetColumnWidth(INT nCol, INT cx);
		BOOL GetViewRect(LPRECT lpRect) const;
		COLORREF GetTextColor() const;
		BOOL SetTextColor(COLORREF cr);
		COLORREF GetTextBkColor() const;
		BOOL SetTextBkColor(COLORREF cr);
		INT GetTopIndex() const;
		INT GetCountPerPage() const;
		BOOL GetOrigin(LPPOINT lpPoint) const;
		BOOL SetItemState(INT nItem, LVITEM* pItem);
		BOOL SetItemState(INT nItem, UINT nState, UINT nMask);
		UINT GetItemState(INT nItem, UINT nMask) const;
		INT GetItemText(INT nItem, INT nSubItem, _Out_z_cap_post_count_(nLen, return +1) LPTSTR lpszText, INT nLen) const;
		BOOL SetItemText(INT nItem, INT nSubItem, LPCTSTR lpszText);
		void SetItemCount(INT nItems);
		BOOL SetItemData(INT nItem, DWORD_PTR dwData);
		DWORD_PTR GetItemData(INT nItem) const;
		UINT GetSelectedCount() const;
		BOOL GetItemSpacing(BOOL fSmall, INT* pnHorzSpacing, INT* pnVertSpacing) const;
		BOOL SetColumnOrderArray(INT iCount, LPINT piArray);
		BOOL GetColumnOrderArray(LPINT piArray, INT iCount = -1) const;
		TinySize SetIconSpacing(TinySize size);
		TinySize SetIconSpacing(INT cx, INT cy);
		HCURSOR GetHotCursor() const;
		HCURSOR SetHotCursor(HCURSOR hc);
		BOOL GetSubItemRect(INT iItem, INT iSubItem, INT nArea, TinyRectangle& ref) const;
		INT GetHotItem() const;
		INT SetHotItem(INT iIndex);
		INT GetSelectionMark() const;
		INT SetSelectionMark(INT iIndex);
		DWORD GetExtendedStyle() const;
		DWORD SetExtendedStyle(DWORD dwNewStyle);
		INT SubItemHitTest(LPLVHITTESTINFO pInfo);
		void SetWorkAreas(INT nWorkAreas, LPRECT lpRect);
		BOOL SetItemCountEx(INT iCount, DWORD dwFlags = LVSICF_NOINVALIDATEALL);
		TinySize ApproximateViewRect(TinySize sz = TinySize(-1, -1), INT iCount = -1) const;
		BOOL GetBkImage(LVBKIMAGE* plvbkImage) const;
		DWORD GetHoverTime() const;
		void GetWorkAreas(INT nWorkAreas, LPRECT prc) const;
		BOOL SetBkImage(HBITMAP hbm, BOOL fTile = TRUE, INT xOffsetPercent = 0, INT yOffsetPercent = 0);
		BOOL SetBkImage(LPTSTR pszUrl, BOOL fTile = TRUE, INT xOffsetPercent = 0, INT yOffsetPercent = 0);
		BOOL SetBkImage(LVBKIMAGE* plvbkImage);
		DWORD SetHoverTime(DWORD dwHoverTime = (DWORD)-1);
		UINT GetNumberOfWorkAreas() const;
		BOOL GetCheck(INT nItem) const;
		BOOL SetCheck(INT nItem, BOOL fCheck = TRUE);
		INT InsertItem(UINT nMask, INT nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, INT nImage, LPARAM lParam);
		INT InsertItem(const LVITEM* pItem);
		INT InsertItem(INT nItem, LPCTSTR lpszItem);
		INT InsertItem(INT nItem, LPCTSTR lpszItem, INT nImage);
		BOOL DeleteItem(INT nItem);
		BOOL DeleteAllItems();
		INT FindItem(LVFINDINFO* pFindInfo, INT nStart = -1) const;
		INT HitTest(LVHITTESTINFO* pHitTestInfo) const;
		INT HitTest(TinyPoint pt, UINT* pFlags = NULL) const;
		BOOL EnsureVisible(INT nItem, BOOL bPartialOK);
		BOOL Scroll(TinySize size);
		BOOL RedrawItems(INT nFirst, INT nLast);
		BOOL Arrange(UINT nCode);
		HWND EditLabel(INT nItem);
		INT InsertColumn(INT nCol, const LVCOLUMN* pColumn);
		INT InsertColumn(INT nCol, LPCTSTR lpszColumnHeading, INT nFormat = LVCFMT_LEFT, INT nWidth = -1, INT nSubItem = -1);
		BOOL DeleteColumn(INT nCol);
		HIMAGELIST CreateDragImage(INT nItem, LPPOINT lpPoint);
		BOOL Update(INT nItem);
		BOOL SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);
		BOOL SortItemsEx(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);
		void SetSelectedColumn(INT iCol);
		DWORD SetView(INT iView);
		DWORD GetView() const;
		INT InsertGroup(INT index, PLVGROUP pgrp);
		INT SetGroupInfo(INT iGroupId, PLVGROUP pGroup);
		INT GetGroupInfo(INT iGroupId, PLVGROUP pgrp) const;
		INT RemoveGroup(INT iGroupId);
		void MoveGroup(INT iGroupId, INT toIndex);
		void MoveItemToGroup(INT idItemFrom, INT idGroupTo);
		void SetGroupMetrics(PLVGROUPMETRICS pGroupMetrics);
		void GetGroupMetrics(PLVGROUPMETRICS pGroupMetrics) const;
		HWND GetHeaderCtrl() const;
		INT EnableGroupView(BOOL fEnable);
		BOOL SortGroups(PFNLVGROUPCOMPARE _pfnGroupCompare, LPVOID _plv);
		void InsertGroupSorted(PLVINSERTGROUPSORTED pStructInsert);
		void RemoveAllGroups();
		BOOL HasGroup(INT iGroupId) const;
		BOOL SetTileViewInfo(PLVTILEVIEWINFO ptvi);
		BOOL GetTileViewInfo(PLVTILEVIEWINFO ptvi) const;
		BOOL SetTileInfo(PLVTILEINFO pti);
		BOOL GetTileInfo(PLVTILEINFO pti) const;
		BOOL SetInsertMark(LPLVINSERTMARK lvim);
		BOOL GetInsertMark(LPLVINSERTMARK lvim) const;
		INT InsertMarkHitTest(LPPOINT pPoint, LPLVINSERTMARK lvim) const;
		INT GetInsertMarkRect(LPRECT pRect) const;
		COLORREF SetInsertMarkColor(COLORREF color);
		COLORREF GetInsertMarkColor() const;
		BOOL SetInfoTip(PLVSETINFOTIP plvInfoTip);
		UINT GetSelectedColumn() const;
		BOOL IsGroupViewEnabled() const;
		COLORREF GetOutlineColor() const;
		COLORREF SetOutlineColor(COLORREF color);
		void CancelEditLabel();
		void RemoveImageList(INT nImageList);
	};
};

