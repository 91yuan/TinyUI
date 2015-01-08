#pragma once
#include "TinyEvent.h"
#include "TinyString.h"
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// Tab¿Ø¼þ
	/// </summary>
	class TinyTabControl : public TinyControl
	{
	public:
		TinyTabControl();
		virtual ~TinyTabControl();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);

		HIMAGELIST GetImageList() const;
		HIMAGELIST SetImageList(HIMAGELIST hImageList);
		INT GetItemCount() const;
		BOOL GetItem(INT nItem, TCITEM* pTabCtrlItem) const;
		BOOL SetItem(INT nItem, TCITEM* pTabCtrlItem);
		BOOL SetItemExtra(INT nBytes);
		BOOL GetItemRect(INT nItem, LPRECT lpRect) const;
		INT GetCurSel() const;
		INT SetCurSel(INT nItem);
		void SetCurFocus(INT nItem);
		TinySize SetItemSize(TinySize size);
		void SetPadding(TinySize size);
		INT GetRowCount() const;
		HWND GetToolTips() const;
		void SetToolTips(HWND pWndTip);
		INT GetCurFocus() const;
		INT SetMinTabWidth(INT cx);
		DWORD GetExtendedStyle() const;
		DWORD SetExtendedStyle(DWORD dwNewStyle, DWORD dwExMask = 0);
		DWORD GetItemState(INT nItem, DWORD dwMask) const;
		BOOL SetItemState(INT nItem, DWORD dwMask, DWORD dwState);
		LONG InsertItem(INT nItem, TCITEM* pTabCtrlItem);
		LONG InsertItem(INT nItem, LPCTSTR lpszItem);
		LONG InsertItem(INT nItem, LPCTSTR lpszItem, INT nImage);
		LONG InsertItem(UINT nMask, INT nItem, LPCTSTR lpszItem, INT nImage, LPARAM lParam);
		LONG InsertItem(UINT nMask, INT nItem, LPCTSTR lpszItem, INT nImage, LPARAM lParam, DWORD dwState, DWORD dwStateMask);
		BOOL DeleteItem(INT nItem);
		BOOL DeleteAllItems();
		void AdjustRect(BOOL bLarger, _Inout_ LPRECT lpRect);
		void RemoveImage(INT nImage);
		INT HitTest(TCHITTESTINFO* pHitTestInfo) const;
		void DeselectAll(BOOL fExcludeFocus);
		BOOL HighlightItem(INT idItem, BOOL fHighlight = TRUE);
		virtual HRESULT OnNotifyReflect(void* sender, UINT ctlID, LPARAM lParam, BOOL &bHandled);
		virtual void OnSelectChangingTab(void* sender, BOOL& bPrevent);
		virtual void OnSelectChangeTab(void* sender);
	private:
		Event<void(void*, BOOL&)> EVENT_SelectChangingTab;
		Event<void(void*)> EVENT_SelectChangeTab;
	};
}