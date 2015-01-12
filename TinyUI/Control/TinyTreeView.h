#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyTreeView :public TinyControl
	{
		DECLARE_DYNAMIC(TinyTreeView)
	public:
		TinyTreeView();
		virtual ~TinyTreeView();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	private:
		LRESULT		TvnExpanding(NMTREEVIEW* nmtv);
		void		TvnExpanded(NMTREEVIEW* nmtv);
		LRESULT		TvnSelecting(NMTREEVIEW* nmtv);
		void		TvnSelected(NMTREEVIEW* nmtv);
		void		TvnDeleteItem(NMTREEVIEW* nmtv);
	public:
		void		UpdateCursor(HCURSOR hNew);
		virtual void OnNodeExpanding(HTREEITEM hItem, BOOL& bCancel);
		virtual void OnNodeCollapsing(HTREEITEM hItem, BOOL& bCancel);
		virtual void OnNodeExpanded(HTREEITEM hItem);
		virtual void OnNodeCollapsed(HTREEITEM hItem);
		virtual void OnNodeSelecting(HTREEITEM hItem, BOOL& bCancel);
		virtual void OnNodeSelected(HTREEITEM hItem);
		virtual void OnNodeDelete(TVITEM& tvItem);
		Event<void(void*, HTREEITEM, BOOL&)>	EVENT_NodeExpanding;
		Event<void(void*, HTREEITEM, BOOL&)>	EVENT_NodeCollapsing;
		Event<void(void*, HTREEITEM)>			EVENT_NodeExpanded;
		Event<void(void*, HTREEITEM)>			EVENT_NodeCollapsed;
		Event<void(void*, HTREEITEM, BOOL&)>	EVENT_NodeSelecting;
		Event<void(void*, HTREEITEM)>			EVENT_NodeSelected;
		Event<void(void*, TVITEM)>				EVENT_NodeDelete;
		//////////////////////////////////////////////////////////////////////////
		BOOL GetItemRect(HTREEITEM hItem, LPRECT lpRect, BOOL bTextOnly) const;
		UINT GetCount() const;
		UINT GetIndent() const;
		void SetIndent(UINT nIndent);
		HIMAGELIST GetImageList(INT nImageList) const;
		HIMAGELIST SetImageList(HIMAGELIST hImageList, INT nImageList);
		HTREEITEM GetNextItem(HTREEITEM hItem, UINT nCode) const;
		HTREEITEM GetChildItem(HTREEITEM hItem) const;
		HTREEITEM GetNextSiblingItem(HTREEITEM hItem) const;
		HTREEITEM GetPrevSiblingItem(HTREEITEM hItem) const;
		HTREEITEM GetParentItem(HTREEITEM hItem) const;
		HTREEITEM GetFirstVisibleItem() const;
		HTREEITEM GetNextVisibleItem(HTREEITEM hItem) const;
		HTREEITEM GetPrevVisibleItem(HTREEITEM hItem) const;
		HTREEITEM GetLastVisibleItem() const;
		HTREEITEM GetSelectedItem() const;
		HTREEITEM GetDropHilightItem() const;
		HTREEITEM GetRootItem() const;
		BOOL GetItem(TVITEM* pItem) const;
		INT GetItemText(HTREEITEM hItem, CHAR* pz, INT size) const;
		BOOL GetItemImage(HTREEITEM hItem, INT& nImage, INT& nSelectedImage) const;
		UINT GetItemState(HTREEITEM hItem, UINT nStateMask) const;
		DWORD_PTR GetItemData(HTREEITEM hItem) const;
		BOOL SetItem(TVITEM* pItem);
		BOOL SetItem(HTREEITEM hItem, UINT nMask, _In_opt_z_ LPCTSTR lpszItem, INT nImage,
			INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam);
		BOOL SetItemEx(HTREEITEM hItem, UINT nMask, _In_opt_z_ LPCTSTR lpszItem, INT nImage,
			INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
			UINT uStateEx, HWND hWnd, INT iExpandedImage);
		BOOL SetItemText(HTREEITEM hItem, LPCTSTR lpszItem);
		BOOL SetItemImage(HTREEITEM hItem, INT nImage, INT nSelectedImage);
		BOOL SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask);
		BOOL SetItemData(HTREEITEM hItem, DWORD_PTR dwData);
		BOOL ItemHasChildren(HTREEITEM hItem) const;
		HWND GetEditControl() const;
		UINT GetVisibleCount() const;
		HWND GetToolTips() const;
		HWND SetToolTips(HWND pWndTip);
		COLORREF GetBkColor() const;
		COLORREF SetBkColor(COLORREF clr);
		SHORT GetItemHeight() const;
		SHORT SetItemHeight(SHORT cyHeight);
		COLORREF GetTextColor() const;
		COLORREF SetTextColor(COLORREF clr);
		BOOL SetInsertMark(HTREEITEM hItem, BOOL fAfter = TRUE);
		BOOL GetCheck(HTREEITEM hItem) const;
		BOOL SetCheck(HTREEITEM hItem, BOOL fCheck = TRUE);
		COLORREF GetInsertMarkColor() const;
		COLORREF SetInsertMarkColor(COLORREF clrNew);
		UINT SetScrollTime(UINT uScrollTime);
		UINT GetScrollTime() const;
		COLORREF GetLineColor() const;
		COLORREF SetLineColor(COLORREF clrNew = CLR_DEFAULT);
		HTREEITEM InsertItem(LPTVINSERTSTRUCT lpInsertStruct);
		HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, INT nImage, INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter);
		HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
		HTREEITEM InsertItem(LPCTSTR lpszItem, INT nImage, INT nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
		BOOL DeleteItem(HTREEITEM hItem);
		BOOL DeleteAllItems();
		BOOL Expand(HTREEITEM hItem, UINT nCode);
		BOOL Select(HTREEITEM hItem, UINT nCode);
		BOOL SelectItem(HTREEITEM hItem);
		BOOL SelectDropTarget(HTREEITEM hItem);
		BOOL SelectSetFirstVisible(HTREEITEM hItem);
		HWND EditLabel(HTREEITEM hItem);
		HTREEITEM HitTest(TinyPoint pt, UINT* pFlags = NULL) const;
		HTREEITEM HitTest(TVHITTESTINFO* pHitTestInfo) const;
		HIMAGELIST CreateDragImage(HTREEITEM hItem);
		BOOL SortChildren(HTREEITEM hItem);
		BOOL EnsureVisible(HTREEITEM hItem);
		BOOL SortChildrenCB(LPTVSORTCB pSort);
		BOOL EndEditLabelNow(BOOL fCancelWithoutSave);
		void RemoveImageList(INT nImageList);
	private:
		HCURSOR m_hCursor;
	};
}


