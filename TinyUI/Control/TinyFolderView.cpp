#include "../stdafx.h"
#include "TinyFolderView.h"

namespace TinyUI
{
	TinyFolderView::TinyFolderView()
		:m_dwFlags(SHCONTF_FOLDERS)
	{
		m_pShellManager = new TinyShellManager();
	}
	TinyFolderView::~TinyFolderView()
	{
		SAFE_DELETE_ARRAY(m_pShellManager);
	}

	LRESULT TinyFolderView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		InitializeFolderView();
		return TinyTreeView::OnCreate(uMsg, wParam, lParam, bHandled);
	}

	BOOL TinyFolderView::GetDesktopItems()
	{
		//获得桌面的绝对的PIDl
		LPITEMIDLIST deskPIDL;
		if (FAILED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &deskPIDL)))
		{
			return FALSE;
		}
		//获得桌面的ShellFolder
		LPSHELLFOLDER pDesktop;
		if (FAILED(SHGetDesktopFolder(&pDesktop)))
		{
			return FALSE;
		}
		TVITEM	tvItem = { 0 };
		tvItem.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
		LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)GlobalAlloc(GPTR, sizeof(SHELLITEMINFO));
		ASSERT(shellItemPtr != NULL);
		shellItemPtr->relativePIDL = deskPIDL;
		shellItemPtr->absolutePIDL = m_pShellManager->Clone(deskPIDL);
		shellItemPtr->pParentFolder = NULL;
		tvItem.lParam = (LPARAM)shellItemPtr;
		TinyString strItem = OnGetItemText(shellItemPtr);
		tvItem.pszText = strItem.STR();
		tvItem.cchTextMax = MAX_PATH;
		tvItem.iImage = OnGetItemIcon(shellItemPtr, FALSE);
		tvItem.iSelectedImage = OnGetItemIcon(shellItemPtr, TRUE);
		tvItem.cChildren = TRUE;

		TVINSERTSTRUCT tvInsert = { 0 };
		tvInsert.item = tvItem;
		tvInsert.hInsertAfter = TVI_LAST;
		tvInsert.hParent = TVI_ROOT;
		HTREEITEM hParentItem = InsertItem(&tvInsert);
		Expand(hParentItem, TVE_EXPAND);
		pDesktop->Release();
		return TRUE;
	}
	BOOL TinyFolderView::EnumChildItems(HTREEITEM hParentItem)
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(tvItem));
		tvItem.mask = TVIF_PARAM;
		tvItem.hItem = hParentItem;
		if (!GetItem(&tvItem))
		{
			return FALSE;
		}
		SendMessage(m_hWND, WM_SETREDRAW, (WPARAM)FALSE, 0);
		LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)tvItem.lParam;
		ASSERT(shellItemPtr != NULL);
		LPSHELLFOLDER pParentFolder = NULL;
		HRESULT	hRes;
		if (shellItemPtr->pParentFolder == NULL)
		{
			hRes = SHGetDesktopFolder(&pParentFolder);
		}
		else
		{

			hRes = shellItemPtr->pParentFolder->BindToObject(
				shellItemPtr->relativePIDL,
				NULL, IID_IShellFolder,
				(LPVOID*)&pParentFolder);
		}
		if (FAILED(hRes))
		{
			SendMessage(m_hWND, WM_SETREDRAW, (WPARAM)TRUE, 0);
			return FALSE;
		}
		EnumObjects(hParentItem, pParentFolder, shellItemPtr->absolutePIDL);
		TV_SORTCB tvSort;
		tvSort.hParent = hParentItem;
		tvSort.lpfnCompare = CompareProc;
		tvSort.lParam = 0;
		SortChildrenCB(&tvSort);
		SendMessage(m_hWND, WM_SETREDRAW, (WPARAM)TRUE, 0);
		RedrawWindow(m_hWND, NULL, NULL, RDW_INVALIDATE);
		pParentFolder->Release();
		return TRUE;
	}
	TinyString TinyFolderView::OnGetItemText(LPSHELLITEMINFO pItem)
	{
		ASSERT(pItem != NULL);
		SHFILEINFO sfi;
		if (SHGetFileInfo((LPCTSTR)pItem->absolutePIDL, 0, &sfi, sizeof(SHFILEINFO),
			SHGFI_PIDL | SHGFI_DISPLAYNAME))
		{
			return sfi.szDisplayName;
		}
		return _T("错误");
	}
	INT TinyFolderView::OnGetItemIcon(LPSHELLITEMINFO pItem, BOOL bSelected)
	{
		ASSERT(pItem != NULL);
		SHFILEINFO sfi;
		UINT uiFlags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON;
		if (bSelected)
		{
			uiFlags |= SHGFI_OPENICON;
		}
		else
		{
			uiFlags |= SHGFI_LINKOVERLAY;
		}
		if (SHGetFileInfo((LPCTSTR)pItem->absolutePIDL, 0, &sfi, sizeof(SHFILEINFO), uiFlags))
		{
			return sfi.iIcon;
		}
		return -1;
	}

	HRESULT TinyFolderView::EnumObjects(HTREEITEM	hParentItem, LPSHELLFOLDER	pParentFolder, LPITEMIDLIST parentPIDL)
	{
		LPENUMIDLIST ps;
		HRESULT hRes = pParentFolder->EnumObjects(NULL, m_dwFlags, &ps);
		if (FAILED(hRes) || !ps)
		{
			return hRes;
		}
		LPITEMIDLIST		pidlTemp;
		DWORD				dwFetched = 1;
		while (SUCCEEDED(ps->Next(1, &pidlTemp, &dwFetched)) && dwFetched)
		{
			TVITEM tvItem;
			ZeroMemory(&tvItem, sizeof(tvItem));
			tvItem.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
			pParentFolder->AddRef();
			LPSHELLITEMINFO pItem = (LPSHELLITEMINFO)GlobalAlloc(GPTR, sizeof(SHELLITEMINFO));
			ASSERT(pItem != NULL);
			pItem->relativePIDL = pidlTemp;
			pItem->absolutePIDL = m_pShellManager->Combine(parentPIDL, pidlTemp);
			pItem->pParentFolder = pParentFolder;
			tvItem.lParam = (LPARAM)pItem;
			TinyString strItem = OnGetItemText(pItem);
			tvItem.pszText = strItem.STR();
			tvItem.cchTextMax = MAX_PATH;
			tvItem.iImage = OnGetItemIcon(pItem, FALSE);
			tvItem.iSelectedImage = OnGetItemIcon(pItem, TRUE);
			DWORD dwAttribs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER |
				SFGAO_DISPLAYATTRMASK | SFGAO_CANRENAME;
			pParentFolder->GetAttributesOf(1, (LPCITEMIDLIST*)&pidlTemp, &dwAttribs);
			tvItem.cChildren = (dwAttribs & SFGAO_HASSUBFOLDER);
			if (dwAttribs & SFGAO_SHARE)
			{
				tvItem.mask |= TVIF_STATE;
				tvItem.stateMask |= TVIS_OVERLAYMASK;
				tvItem.state |= INDEXTOOVERLAYMASK(1);
			}
			TVINSERTSTRUCT tvInsert;
			tvInsert.item = tvItem;
			tvInsert.hInsertAfter = TVI_LAST;
			tvInsert.hParent = hParentItem;
			InsertItem(&tvInsert);
			dwFetched = 0;
		}
		ps->Release();
		return S_OK;
	}
	void TinyFolderView::InitializeFolderView()
	{
		TCHAR szWinDir[MAX_PATH + 1];
		if (GetWindowsDirectory(szWinDir, MAX_PATH) > 0)
		{
			SHFILEINFO sfi;
			SetImageList((HIMAGELIST)SHGetFileInfo(
				szWinDir,
				0,
				&sfi,
				sizeof(SHFILEINFO),
				SHGFI_SYSICONINDEX | SHGFI_SMALLICON), TVSIL_NORMAL);
		}
		DeleteAllItems();
		GetDesktopItems();
	}
	void TinyFolderView::OnNodeExpanding(HTREEITEM hItem, BOOL& bCancel)
	{
		TinyTreeView::OnNodeExpanding(hItem, bCancel);
		UpdateCursor(LoadCursor(NULL, IDC_WAIT));
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(tvItem));
		tvItem.hItem = hItem;
		tvItem.mask = TVIF_PARAM;
		if (GetItem(&tvItem))
		{
			LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)tvItem.lParam;
			if (shellItemPtr && !shellItemPtr->bEnumFlag)
			{
				EnumChildItems(hItem);
				if (GetChildItem(hItem) == NULL)
				{
					TV_ITEM tvItem;
					ZeroMemory(&tvItem, sizeof(tvItem));
					tvItem.hItem = hItem;
					tvItem.mask = TVIF_CHILDREN;
					SetItem(&tvItem);
				}
				shellItemPtr->bEnumFlag = TRUE;
			}
		}
		UpdateCursor(LoadCursor(NULL, IDC_ARROW));
	}
	void TinyFolderView::OnNodeCollapsing(HTREEITEM hItem, BOOL& bCancel)
	{
		TinyTreeView::OnNodeCollapsing(hItem, bCancel);
	}
	void TinyFolderView::OnNodeDelete(TVITEM& tvItem)
	{
		LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)tvItem.lParam;
		if (shellItemPtr != NULL)
		{
			if (shellItemPtr->relativePIDL)
			{
				CoTaskMemFree(shellItemPtr->relativePIDL);
				shellItemPtr->relativePIDL = NULL;
			}
			if (shellItemPtr->absolutePIDL)
			{
				CoTaskMemFree(shellItemPtr->absolutePIDL);
				shellItemPtr->absolutePIDL = NULL;
			}
			if (shellItemPtr->pParentFolder != NULL)
			{
				shellItemPtr->pParentFolder->Release();
				shellItemPtr->pParentFolder = NULL;
			}
			GlobalFree((HGLOBAL)shellItemPtr);
			shellItemPtr = NULL;
		}
	}
	INT CALLBACK TinyFolderView::CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		LPSHELLITEMINFO shellItemPtr1 = (LPSHELLITEMINFO)lParam1;
		LPSHELLITEMINFO shellItemPtr2 = (LPSHELLITEMINFO)lParam2;

		HRESULT hRes = shellItemPtr1->pParentFolder->CompareIDs(0,
			shellItemPtr1->relativePIDL,
			shellItemPtr2->relativePIDL);
		if (FAILED(hRes))
		{
			return 0;
		}
		return (short)SCODE_CODE(GetScode(hRes));
	}
	BOOL TinyFolderView::SelectPath(LPCITEMIDLIST newPIDL)
	{
		BOOL bRes = FALSE;
		if (newPIDL == NULL)
		{
			ASSERT(FALSE);
			return FALSE;
		}
		HTREEITEM hTreeItem = GetRootItem();
		SendMessage(m_hWND, WM_SETREDRAW, (WPARAM)FALSE, 0);
		if (GetPIDLSize(newPIDL) != 0)//不是桌面
		{
			LPCITEMIDLIST currentPIDL = newPIDL;
			LPITEMIDLIST parentPIDL = NULL;

			/*TinyList<LPITEMIDLIST, LPITEMIDLIST> lstItems;
			lstItems.AddHead(pShellManager->Clone(newPIDL));

			while (pShellManager->GetParent(currentPIDL, parentPIDL) > 0)
			{
			lstItems.AddHead(parentPIDL);
			currentPIDL = parentPIDL;
			}
			for (POSITION pos = lstItems.GetHeadPosition(); pos != NULL;)
			{
			LPITEMIDLIST nextPIDL = lstItems.GetNext(pos);
			if (hTreeItem != NULL)
			{
			if (GetChildItem(hTreeItem) == NULL)
			{
			Expand(hTreeItem, TVE_EXPAND);
			}
			BOOL bFound = FALSE;
			for (HTREEITEM hTreeChild = GetChildItem(hTreeItem); !bFound && hTreeChild != NULL; hTreeChild = GetNextSiblingItem(hTreeChild))
			{
			LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)GetItemData(hTreeChild);
			if (shellItemPtr == NULL)
			{
			continue;
			}
			SHFILEINFO sfi1;
			SHFILEINFO sfi2;
			if (SHGetFileInfo((LPCTSTR)shellItemPtr->absolutePIDL, 0, &sfi1, sizeof(sfi1), SHGFI_PIDL | SHGFI_DISPLAYNAME) &&
			SHGetFileInfo((LPCTSTR)nextPIDL, 0, &sfi2, sizeof(sfi2), SHGFI_PIDL | SHGFI_DISPLAYNAME) && lstrcmp(sfi1.szDisplayName, sfi2.szDisplayName) == 0)
			{
			bFound = TRUE;
			hTreeItem = hTreeChild;
			}
			}
			if (!bFound)
			{
			hTreeItem = NULL;
			}
			}
			CoTaskMemFree(nextPIDL);
			}*/
		}
		if (hTreeItem != NULL)
		{
			m_bNoNotify = TRUE;
			SelectItem(hTreeItem);
			if (GetChildItem(hTreeItem) == NULL)
			{
				Expand(hTreeItem, TVE_EXPAND);
			}
			EnsureVisible(hTreeItem);
			m_bNoNotify = FALSE;
			bRes = TRUE;
		}
		SendMessage(m_hWND, WM_SETREDRAW, (WPARAM)TRUE, 0);
		RedrawWindow(m_hWND, NULL, NULL, RDW_INVALIDATE);
		return bRes;
	}

	BOOL TinyFolderView::GetItemPath(TinyString& strPath, HTREEITEM hTreeItem) const
	{
		BOOL bRes = FALSE;
		strPath.Erase(0);
		if (hTreeItem == NULL)
		{
			hTreeItem = GetSelectedItem();
		}
		if (hTreeItem == NULL)
		{
			return FALSE;
		}

		LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)GetItemData(hTreeItem);
		if (shellItemPtr == NULL || shellItemPtr->relativePIDL == NULL || shellItemPtr->absolutePIDL == NULL)
		{
			return FALSE;
		}

		LPSHELLFOLDER lpShellFolder = NULL;
		HRESULT hRes;
		if (shellItemPtr->pParentFolder == NULL)
		{
			hRes = SHGetDesktopFolder(&lpShellFolder);
		}
		else
		{
			hRes = shellItemPtr->pParentFolder->BindToObject(shellItemPtr->relativePIDL, 0, IID_IShellFolder, (LPVOID*)&lpShellFolder);
		}

		if (FAILED(hRes))
		{
			return FALSE;
		}

		ULONG uAttribs = SFGAO_FILESYSTEM;
		if (shellItemPtr->pParentFolder != NULL)
		{
			shellItemPtr->pParentFolder->GetAttributesOf(1, (const struct _ITEMIDLIST **)&shellItemPtr->absolutePIDL, &uAttribs);
		}
		if ((uAttribs & SFGAO_FILESYSTEM) != 0)
		{
			TCHAR szFolderName[MAX_PATH];
			if (SHGetPathFromIDList(shellItemPtr->absolutePIDL, szFolderName))
			{
				strPath = szFolderName;
				bRes = TRUE;
			}
		}
		if (lpShellFolder != NULL)
		{
			lpShellFolder->Release();
		}
		return bRes;
	}
}