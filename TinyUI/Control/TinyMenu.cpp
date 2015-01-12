#include "stdafx.h"
#include "TinyMenu.h"

namespace TinyUI
{

	TinyMenu::TinyMenu(HMENU hMenu)
		:m_hMenu(hMenu)
	{

	}

	TinyMenu::~TinyMenu()
	{
		DestroyMenu();
	}

	BOOL TinyMenu::CreateMenu()
	{
		m_hMenu = ::CreateMenu();
		TinyApplication::Instance()->GetMapHMENU().AddHandle(m_hMenu, this);
		return m_hMenu != NULL;
	}
	BOOL TinyMenu::CreatePopupMenu()
	{
		m_hMenu = ::CreatePopupMenu();
		TinyApplication::Instance()->GetMapHMENU().AddHandle(m_hMenu, this);
		return m_hMenu != NULL;
	}
	TinyMenu::operator HMENU() const
	{
		ASSERT(this == NULL || m_hMenu == NULL || ::IsMenu(m_hMenu));
		return this == NULL ? NULL : m_hMenu;
	}
	BOOL TinyMenu::operator==(const TinyMenu& menu) const
	{
		return ((HMENU)menu) == m_hMenu;
	}
	BOOL TinyMenu::operator!=(const TinyMenu& menu) const
	{
		return ((HMENU)menu) != m_hMenu;
	}

	BOOL TinyMenu::DeleteMenu(UINT nPosition, UINT nFlags)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::DeleteMenu(m_hMenu, nPosition, nFlags);
	}
	BOOL TinyMenu::AppendMenu(UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::AppendMenu(m_hMenu, nFlags, nIDNewItem, lpszNewItem);
	}
	BOOL TinyMenu::AppendMenu(UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::AppendMenu(m_hMenu, nFlags | MF_BITMAP, nIDNewItem, (LPCTSTR)hBmp);
	}
	UINT TinyMenu::CheckMenuItem(UINT nIDCheckItem, UINT nCheck)
	{
		ASSERT(::IsMenu(m_hMenu));
		return (UINT)::CheckMenuItem(m_hMenu, nIDCheckItem, nCheck);
	}
	UINT TinyMenu::EnableMenuItem(UINT nIDEnableItem, UINT nEnable)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::EnableMenuItem(m_hMenu, nIDEnableItem, nEnable);
	}
	BOOL TinyMenu::SetDefaultItem(UINT uItem, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::SetMenuDefaultItem(m_hMenu, uItem, fByPos);
	}
	UINT TinyMenu::GetDefaultItem(UINT gmdiFlags, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuDefaultItem(m_hMenu, fByPos, gmdiFlags);
	}
	UINT TinyMenu::GetMenuItemCount() const
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuItemCount(m_hMenu);
	}
	UINT TinyMenu::GetMenuItemID(INT nPos) const
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuItemID(m_hMenu, nPos);
	}
	UINT TinyMenu::GetMenuState(UINT nID, UINT nFlags) const
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuState(m_hMenu, nID, nFlags);
	}
	INT TinyMenu::GetMenuString(_In_ UINT nIDItem, _Out_z_cap_(nMaxCount) LPTSTR lpString, _In_ INT nMaxCount, _In_ UINT nFlags) const
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuString(m_hMenu, nIDItem, lpString, nMaxCount, nFlags);
	}
	BOOL TinyMenu::GetMenuItemInfo(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuItemInfo(m_hMenu, uItem, fByPos, lpMenuItemInfo);
	}
	BOOL TinyMenu::SetMenuItemInfo(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::SetMenuItemInfo(m_hMenu, uItem, fByPos, lpMenuItemInfo);
	}
	BOOL TinyMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::InsertMenu(m_hMenu, nPosition, nFlags, nIDNewItem, lpszNewItem);
	}
	BOOL TinyMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::InsertMenu(m_hMenu, nPosition, nFlags | MF_BITMAP, nIDNewItem, (LPCTSTR)hBmp);
	}
	BOOL TinyMenu::InsertMenuItem(UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::InsertMenuItem(m_hMenu, uItem, fByPos, lpMenuItemInfo);
	}
	BOOL TinyMenu::ModifyMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::ModifyMenu(m_hMenu, nPosition, nFlags, nIDNewItem, lpszNewItem);
	}
	BOOL TinyMenu::ModifyMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem, const HBITMAP hBmp)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::ModifyMenu(m_hMenu, nPosition, nFlags | MF_BITMAP, nIDNewItem, (LPCSTR)hBmp);
	}
	BOOL TinyMenu::RemoveMenu(UINT nPosition, UINT nFlags)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::RemoveMenu(m_hMenu, nPosition, nFlags);
	}
	BOOL TinyMenu::SetMenuItemBitmaps(UINT nPosition, UINT nFlags, const HBITMAP hBmpUnchecked, const HBITMAP hBmpChecked)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::SetMenuItemBitmaps(m_hMenu, nPosition, nFlags, hBmpUnchecked, hBmpChecked);
	}
	BOOL TinyMenu::LoadMenu(LPCTSTR lpszResourceName)
	{
		m_hMenu = ::LoadMenu((HINSTANCE)::FindResource(TinyApplication::Instance()->Handle(), lpszResourceName, RT_MENU), lpszResourceName);
		TinyApplication::Instance()->GetMapHMENU().AddHandle(m_hMenu, this);
		return m_hMenu != NULL;
	}
	BOOL TinyMenu::LoadMenu(UINT nIDResource)
	{
		m_hMenu = ::LoadMenu((HINSTANCE)::FindResource(TinyApplication::Instance()->Handle(), MAKEINTRESOURCE(nIDResource), RT_MENU), MAKEINTRESOURCE(nIDResource));
		TinyApplication::Instance()->GetMapHMENU().AddHandle(m_hMenu, this);
		return m_hMenu != NULL;
	}
	BOOL TinyMenu::LoadMenuIndirect(const void* lpMenuTemplate)
	{
		m_hMenu = ::LoadMenuIndirect(lpMenuTemplate);
		TinyApplication::Instance()->GetMapHMENU().AddHandle(m_hMenu, this);
		return m_hMenu != NULL;
	}

	BOOL TinyMenu::SetMenuContextHelpId(DWORD dwContextHelpId)
	{
		return ::SetMenuContextHelpId(m_hMenu, dwContextHelpId);
	}
	DWORD TinyMenu::GetMenuContextHelpId() const
	{
		return ::GetMenuContextHelpId(m_hMenu);
	}
	BOOL TinyMenu::CheckMenuRadioItem(UINT nIDFirst, UINT nIDLast, UINT nIDItem, UINT nFlags)
	{
		return ::CheckMenuRadioItem(m_hMenu, nIDFirst, nIDLast, nIDItem, nFlags);
	}
	BOOL TinyMenu::TrackPopupMenu(UINT nFlags, INT x, INT y, HWND pWnd, LPCRECT lpRect /* = 0 */)
	{
		ASSERT(m_hMenu != NULL);
		return  ::TrackPopupMenu(m_hMenu, nFlags, x, y, 0, pWnd, lpRect);
	}
	BOOL TinyMenu::TrackPopupMenuEx(UINT fuFlags, INT x, INT y, HWND pWnd, LPTPMPARAMS lptpm)
	{
		ASSERT(m_hMenu != NULL);
		return ::TrackPopupMenuEx(m_hMenu, fuFlags, x, y, pWnd, lptpm);
	}
	BOOL TinyMenu::DestroyMenu()
	{
		if (m_hMenu == NULL)
		{
			return FALSE;
		}
		TinyApplication::Instance()->GetMapHMENU().RemoveHandle(m_hMenu);
		return ::DestroyMenu(m_hMenu);
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

