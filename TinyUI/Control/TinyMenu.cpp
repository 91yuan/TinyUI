#include "../stdafx.h"
#include "TinyMenu.h"

namespace TinyUI
{
	TinyMenu::TinyMenu(HMENU hMENU)
	{
		m_hMENU = hMENU;
	}

	TinyMenu::~TinyMenu()
	{
		DestroyMenu();
	}

	BOOL TinyMenu::CreateMenu()
	{
		return Attach(::CreateMenu());
	}
	BOOL TinyMenu::CreatePopupMenu()
	{
		return Attach(::CreatePopupMenu());
	}

	BOOL TinyMenu::DeleteMenu(UINT nPosition, UINT nFlags)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::DeleteMenu(Detach(), nPosition, nFlags);
	}
	BOOL TinyMenu::AppendMenu(UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::AppendMenu(m_hMENU, nFlags, nIDNewItem, lpszNewItem);
	}
	BOOL TinyMenu::AppendMenu(UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::AppendMenu(m_hMENU, nFlags | MF_BITMAP, nIDNewItem, (LPCTSTR)hBmp);
	}
	UINT TinyMenu::CheckMenuItem(UINT nIDCheckItem, UINT nCheck)
	{
		ASSERT(::IsMenu(m_hMENU));
		return (UINT)::CheckMenuItem(m_hMENU, nIDCheckItem, nCheck);
	}
	UINT TinyMenu::EnableMenuItem(UINT nIDEnableItem, UINT nEnable)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::EnableMenuItem(m_hMENU, nIDEnableItem, nEnable);
	}
	BOOL TinyMenu::SetDefaultItem(UINT uItem, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::SetMenuDefaultItem(m_hMENU, uItem, fByPos);
	}
	UINT TinyMenu::GetDefaultItem(UINT gmdiFlags, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::GetMenuDefaultItem(m_hMENU, fByPos, gmdiFlags);
	}
	UINT TinyMenu::GetMenuItemCount() const
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::GetMenuItemCount(m_hMENU);
	}
	UINT TinyMenu::GetMenuItemID(INT nPos) const
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::GetMenuItemID(m_hMENU, nPos);
	}
	UINT TinyMenu::GetMenuState(UINT nID, UINT nFlags) const
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::GetMenuState(m_hMENU, nID, nFlags);
	}
	INT TinyMenu::GetMenuString(_In_ UINT nIDItem, _Out_z_cap_(nMaxCount) LPTSTR lpString, _In_ INT nMaxCount, _In_ UINT nFlags) const
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::GetMenuString(m_hMENU, nIDItem, lpString, nMaxCount, nFlags);
	}
	BOOL TinyMenu::GetMenuItemInfo(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::GetMenuItemInfo(m_hMENU, uItem, fByPos, lpMenuItemInfo);
	}
	BOOL TinyMenu::SetMenuItemInfo(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::SetMenuItemInfo(m_hMENU, uItem, fByPos, lpMenuItemInfo);
	}
	BOOL TinyMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::InsertMenu(m_hMENU, nPosition, nFlags, nIDNewItem, lpszNewItem);
	}
	BOOL TinyMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::InsertMenu(m_hMENU, nPosition, nFlags | MF_BITMAP, nIDNewItem, (LPCTSTR)hBmp);
	}
	BOOL TinyMenu::InsertMenuItem(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::InsertMenuItem(m_hMENU, uItem, fByPos, lpMenuItemInfo);
	}
	BOOL TinyMenu::ModifyMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::ModifyMenu(m_hMENU, nPosition, nFlags, nIDNewItem, lpszNewItem);
	}
	BOOL TinyMenu::ModifyMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::ModifyMenu(m_hMENU, nPosition, nFlags | MF_BITMAP, nIDNewItem, (LPCSTR)hBmp);
	}
	BOOL TinyMenu::RemoveMenu(UINT nPosition, UINT nFlags)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::RemoveMenu(m_hMENU, nPosition, nFlags);
	}
	BOOL TinyMenu::SetMenuItemBitmaps(UINT nPosition, UINT nFlags, const HBITMAP hBmpUnchecked, const HBITMAP hBmpChecked)
	{
		ASSERT(::IsMenu(m_hMENU));
		return ::SetMenuItemBitmaps(m_hMENU, nPosition, nFlags, hBmpUnchecked, hBmpChecked);
	}
	BOOL TinyMenu::LoadMenu(LPCTSTR lpszResourceName)
	{
		return Attach(::LoadMenu((HINSTANCE)::FindResource(TinyApplication::GetInstance()->Handle(), lpszResourceName, RT_MENU), lpszResourceName));
	}
	BOOL TinyMenu::LoadMenu(UINT nIDResource)
	{
		return Attach(::LoadMenu((HINSTANCE)::FindResource(TinyApplication::GetInstance()->Handle(), MAKEINTRESOURCE(nIDResource), RT_MENU), MAKEINTRESOURCE(nIDResource)));
	}
	BOOL TinyMenu::LoadMenuIndirect(const void* lpMenuTemplate)
	{
		return Attach(::LoadMenuIndirect(lpMenuTemplate));
	}

	BOOL TinyMenu::SetMenuContextHelpId(DWORD dwContextHelpId)
	{
		ASSERT(m_hMENU != NULL);
		return ::SetMenuContextHelpId(m_hMENU, dwContextHelpId);
	}
	DWORD TinyMenu::GetMenuContextHelpId() const
	{
		ASSERT(m_hMENU != NULL);
		return ::GetMenuContextHelpId(m_hMENU);
	}
	BOOL TinyMenu::CheckMenuRadioItem(UINT nIDFirst, UINT nIDLast, UINT nIDItem, UINT nFlags)
	{
		ASSERT(m_hMENU != NULL);
		return ::CheckMenuRadioItem(m_hMENU, nIDFirst, nIDLast, nIDItem, nFlags);
	}
	BOOL TinyMenu::TrackPopupMenu(UINT nFlags, INT x, INT y, HWND pWnd, LPCRECT lpRect /* = 0 */)
	{
		ASSERT(m_hMENU != NULL);
		return  ::TrackPopupMenu(m_hMENU, nFlags, x, y, 0, pWnd, lpRect);
	}
	BOOL TinyMenu::TrackPopupMenuEx(UINT fuFlags, INT x, INT y, HWND pWnd, LPTPMPARAMS lptpm)
	{
		ASSERT(m_hMENU != NULL);
		return ::TrackPopupMenuEx(m_hMENU, fuFlags, x, y, pWnd, lptpm);
	}
	BOOL TinyMenu::DestroyMenu()
	{
		return ::DestroyMenu(Detach());
	}

	void TinyMenu::DrawItem(LPDRAWITEMSTRUCT /*pdis*/)
	{

	}

	void TinyMenu::MeasureItem(LPMEASUREITEMSTRUCT /*pmis*/)
	{

	}

	void TinyMenu::OnClick(void* ps, INT menuID)
	{
		EVENT_Click(ps, menuID);
	}
}

