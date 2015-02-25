#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ²Ëµ¥
	/// </summary>
	class TinyMenu : public TinyHandleHMENU, public TinyObject
	{
		DECLARE_DYNAMIC(TinyMenu)
	public:
		TinyMenu(HMENU hMenu = NULL);
		virtual ~TinyMenu();

		BOOL CreateMenu();
		BOOL CreatePopupMenu();
		BOOL LoadMenu(LPCTSTR lpszResourceName);
		BOOL LoadMenu(UINT nIDResource);
		BOOL LoadMenuIndirect(const void* lpMenuTemplate);
		BOOL DestroyMenu();

		BOOL DeleteMenu(UINT nPosition, UINT nFlags);
		BOOL TrackPopupMenu(UINT nFlags, INT x, INT y, HWND pWnd, LPCRECT lpRect = 0);
		BOOL TrackPopupMenuEx(UINT fuFlags, INT x, INT y, HWND pWnd, LPTPMPARAMS lptpm);

		BOOL SetMenuInfo(LPCMENUINFO lpcmi);
		BOOL GetMenuInfo(LPMENUINFO lpcmi) const;

		BOOL AppendMenu(UINT nFlags, UINT_PTR nIDNewItem = 0, LPCTSTR lpszNewItem = NULL);
		BOOL AppendMenu(UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp);
		UINT CheckMenuItem(UINT nIDCheckItem, UINT nCheck);
		UINT EnableMenuItem(UINT nIDEnableItem, UINT nEnable);
		UINT GetMenuItemCount() const;
		UINT GetMenuItemID(INT nPos) const;
		UINT GetMenuState(UINT nID, UINT nFlags) const;
		INT GetMenuString(UINT nIDItem, LPTSTR lpString, _In_ INT nMaxCount, _In_ UINT nFlags) const;
		BOOL GetMenuItemInfo(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos = FALSE);
		BOOL SetMenuItemInfo(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos = FALSE);
		BOOL InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem = 0, LPCTSTR lpszNewItem = NULL);
		BOOL InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp);
		BOOL InsertMenuItem(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos = FALSE);
		BOOL ModifyMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem = 0, LPCTSTR lpszNewItem = NULL);
		BOOL ModifyMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp);
		BOOL RemoveMenu(UINT nPosition, UINT nFlags);
		BOOL SetMenuItemBitmaps(UINT nPosition, UINT nFlags, const HBITMAP hBmpUnchecked, const HBITMAP hBmpChecked);
		BOOL CheckMenuRadioItem(UINT nIDFirst, UINT nIDLast, UINT nIDItem, UINT nFlags);
		BOOL SetDefaultItem(UINT uItem, BOOL fByPos = FALSE);
		UINT GetDefaultItem(UINT gmdiFlags, BOOL fByPos = FALSE);
		BOOL SetMenuContextHelpId(DWORD dwContextHelpId);
		DWORD GetMenuContextHelpId() const;

		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
		virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
		virtual void OnClick(void*, INT menuID);
		Event<void(void*, INT)> EVENT_Click;
	};
}

