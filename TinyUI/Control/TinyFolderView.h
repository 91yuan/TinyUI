#pragma once
#include "../Common/TinyTime.h"
#include "../Common/TinyShell.h"
#include "TinyTreeView.h"

namespace TinyUI
{
	class TinyFolderView :public TinyTreeView
	{
		DECLARE_DYNAMIC(TinyFolderView)
	private:
		void InitializeFolderView();
	public:
		TinyFolderView();
		virtual ~TinyFolderView();
		virtual TinyString	OnGetItemText(LPSHELLITEMINFO pItem);
		virtual INT			OnGetItemIcon(LPSHELLITEMINFO pItem, BOOL bSelected);
		virtual void		OnNodeExpanding(HTREEITEM hItem, BOOL& bCancel);
		virtual void		OnNodeCollapsing(HTREEITEM hItem, BOOL& bCancel);
		virtual void		OnNodeDelete(TVITEM& tvItem);
		virtual LRESULT		OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		BOOL				GetItemPath(TinyString& strPath, HTREEITEM hTreeItem) const;
		BOOL				SelectPath(LPCITEMIDLIST newPIDL);
	protected:
		BOOL GetDesktopItems();
		BOOL EnumChildItems(HTREEITEM hParentItem);
		virtual HRESULT EnumObjects(HTREEITEM hParentItem, LPSHELLFOLDER pParentFolder, LPITEMIDLIST pidlParent);
		void OnShowContextMenu(TinyPoint point);
		static INT CALLBACK CompareProc(LPARAM, LPARAM, LPARAM);
		static IContextMenu2*	m_pContextMenu2;
		BOOL	m_bContextMenu;
		HWND	m_hwndRelatedList;
		BOOL	m_bNoNotify;
		DWORD	m_dwFlags;
	private:
		TinyShellManager* m_pShellManager;
	};
}


