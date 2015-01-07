#include "stdafx.h"
#include "TinyFileView.h"
#include "TinyIO.h"

namespace TinyUI
{
	UINT WM_CHANGE_CURRENT_FOLDER = ::RegisterWindowMessage(_T("WM_CHANGE_CURRENT_FOLDER"));
	TinyFileView::TinyFileView()
	{
		m_pShellManager = new TinyShellManager();
		m_psfCurrent = NULL;
		m_currentAbsPIDL = NULL;
		m_bIsDesktop = FALSE;
		m_bNoNotify = FALSE;
		m_pView = NULL;
	}

	TinyFileView::~TinyFileView()
	{
		SAFE_DELETE(m_pShellManager);
		if (m_currentAbsPIDL != NULL)
		{
			CoTaskMemFree(m_currentAbsPIDL);
			m_currentAbsPIDL = NULL;
		}
	}
	void TinyFileView::InitializeFileView()
	{
		SetImageList(GetShellImageList(TRUE), LVSIL_NORMAL);
		SetImageList(GetShellImageList(FALSE), LVSIL_SMALL);
		OnSetColumns();
		if (m_psfCurrent == NULL)
		{
			SHELLITEMINFO shellItem;
			if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &shellItem.absolutePIDL)))
			{
				DisplayItem(&shellItem);
				CoTaskMemFree(shellItem.absolutePIDL);
			}
		}
	}
	void TinyFileView::OnCreate()
	{
		InitializeFileView();
	}
	void TinyFileView::OnDeleteItem(INT iItem)
	{
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_PARAM;
		lvItem.iItem = iItem;
		GetItem(&lvItem);
		LPSHELLITEMINFO shellItemPtr = (LPSHELLITEMINFO)lvItem.lParam;
		if (shellItemPtr != NULL)
		{
			if (shellItemPtr->relativePIDL != NULL)
			{
				CoTaskMemFree(shellItemPtr->relativePIDL);
				shellItemPtr->relativePIDL = NULL;
			}
			if (shellItemPtr->absolutePIDL != NULL)
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
	HIMAGELIST TinyFileView::GetShellImageList(BOOL bLarge)
	{
		TCHAR szWinDir[MAX_PATH + 1];
		if (GetWindowsDirectory(szWinDir, MAX_PATH) == 0)
		{
			return NULL;
		}
		SHFILEINFO sfi;
		HIMAGELIST hImageList = (HIMAGELIST)SHGetFileInfo(szWinDir, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | (bLarge ? 0 : SHGFI_SMALLICON));
		return hImageList;
	}
	void TinyFileView::OnFormatFileDate(const TinyTime& tmFile, TinyString& str)
	{
		TinyOleDateTime dateFile(tmFile.GetTime());
		str = dateFile.Format();
	}
	void TinyFileView::OnFormatFileSize(__int64 lFileSize, TinyString& str)
	{
		str.Empty();

		if (lFileSize == 0)
		{
			str = _T("0");
		}
		else
		{
			lFileSize = lFileSize / 1024 + 1;
			str.Format(_T("%I64d"), lFileSize);
			TCHAR szNumOut[256];
			GetNumberFormat(LOCALE_USER_DEFAULT, LOCALE_NOUSEROVERRIDE, str, NULL, szNumOut, 255);
			str = szNumOut;
			TCHAR szDec[10];
			GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szDec, 10);
			int nDecLen = lstrlen(szDec);
			if (nDecLen > 0)
			{
				for (int i = str.GetLength() - nDecLen - 1; i >= 0; i--)
				{
					if (str.Mid(i, nDecLen) == szDec)
					{
						str = str.Left(i);
						break;
					}
				}
			}
		}
		str += _T(" KB");
	}

	TinyString TinyFileView::OnGetItemText(INT /*iItem*/, INT iColumn, LPSHELLITEMINFO pItem, CHAR* pz, INT size)
	{
		ASSERT(pItem != NULL);
		SHFILEINFO	sfi;
		TCHAR		szPath[MAX_PATH];
		switch (iColumn)
		{
		case ColumnName:
			if (SHGetFileInfo((LPCTSTR)pItem->absolutePIDL, 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
			{
				return sfi.szDisplayName;
			}
			break;

		case ColumnType:
			if (SHGetFileInfo((LPCTSTR)pItem->absolutePIDL, 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_TYPENAME))
			{
				return sfi.szTypeName;
			}
			break;
		case ColumnSize:
		case ColumnModified:
			if (SHGetPathFromIDList(pItem->absolutePIDL, szPath))
			{
				FileStatus fs;
				if (TinyFile::GetStatus(szPath, fs))
				{
					SysString str;

					if (iColumn == 1)
					{
						if ((fs.m_attribute & (SysFile::directory | SysFile::volume)) == 0)
						{
							OnFormatFileSize((long)fs.m_size, str);
						}
					}
					else
					{
						OnFormatFileDate(fs.m_mtime, str);
					}

					return str;
				}
			}
			break;

		default:
			ASSERT(FALSE);
			break;
		}

		return _T("");
	}
	INT TinyFileView::OnGetItemIcon(int /*iItem*/, LPSHELLITEMINFO pItem)
	{
		ASSERT(pItem != NULL);

		SHFILEINFO	sfi;
		int			iIcon = -1;

		if (SHGetFileInfo((LPCTSTR)pItem->absolutePIDL, 0, &sfi, sizeof(sfi),
			SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_LINKOVERLAY))
		{
			iIcon = sfi.iIcon;
		}

		return iIcon;
	}
	INT TinyFileView::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
	{
		LPSHELLITEMINFO pItem1 = (LPSHELLITEMINFO)lParam1;
		LPSHELLITEMINFO	pItem2 = (LPSHELLITEMINFO)lParam2;
		ASSERT(pItem1 != NULL);
		ASSERT(pItem2 != NULL);

		SHFILEINFO	sfi1;
		SHFILEINFO	sfi2;

		TCHAR szPath1[MAX_PATH];
		TCHAR szPath2[MAX_PATH];

		FileStatus fs1;
		FileStatus fs2;

		int nRes = 0;

		switch (iColumn)
		{
		case ColumnName:
		{
			HRESULT hr = pItem1->pParentFolder->CompareIDs(0,
				pItem1->relativePIDL,
				pItem2->relativePIDL);

			if (FAILED(hr))
			{
				return 0;
			}

			nRes = (short)SCODE_CODE(GetScode(hr));
		}
		break;

		case ColumnType:
			if (SHGetFileInfo((LPCTSTR)pItem1->absolutePIDL, 0, &sfi1, sizeof(sfi1), SHGFI_PIDL | SHGFI_TYPENAME) &&
				SHGetFileInfo((LPCTSTR)pItem2->absolutePIDL, 0, &sfi2, sizeof(sfi2), SHGFI_PIDL | SHGFI_TYPENAME))
			{
				nRes = lstrcmpi(sfi1.szTypeName, sfi2.szTypeName);
			}
			break;

		case ColumnSize:
		case ColumnModified:
			if (SHGetPathFromIDList(pItem1->absolutePIDL, szPath1) &&
				SysFile::GetStatus(szPath1, fs1))
			{
				if (SHGetPathFromIDList(pItem2->absolutePIDL, szPath2) &&
					SysFile::GetStatus(szPath2, fs2))
				{
					if (iColumn == ColumnSize)
					{
						nRes = fs1.m_size < fs2.m_size ? -1 :
							fs1.m_size > fs2.m_size ? 1 : 0;
					}
					else
					{
						nRes = fs1.m_mtime < fs2.m_mtime ? -1 :
							fs1.m_mtime > fs2.m_mtime ? 1 : 0;
					}
				}
				else
				{
					nRes = 1;
				}
			}
			else
			{
				nRes = -1;
			}
			break;
		}

		return nRes;
	}
	void TinyFileView::OnSetColumns()
	{
		const TCHAR* szName[] =
		{
			_T("名字"), _T("大小"), _T("类型"), _T("修改时间"),
		};
		for (int iColumn = 0; iColumn < 4; iColumn++)
		{
			int nFormat = (iColumn == 1) ? LVCFMT_RIGHT : LVCFMT_LEFT;
			InsertColumn(iColumn, szName[iColumn], nFormat, 100, iColumn);
		}
	}
	HRESULT TinyFileView::EnumObjects(LPSHELLFOLDER pParentFolder, LPITEMIDLIST parentPIDL)
	{
		LPENUMIDLIST pEnum;
		HRESULT hRes = pParentFolder->EnumObjects(NULL, m_nTypes, &pEnum);
		if (SUCCEEDED(hRes))
		{
			LPITEMIDLIST tempPIDL;
			DWORD dwFetched = 1;
			LPSHELLITEMINFO shellItemPtr;
			while (pEnum->Next(1, &tempPIDL, &dwFetched) == S_OK && dwFetched)
			{
				LVITEM lvItem;
				ZeroMemory(&lvItem, sizeof(lvItem));
				lvItem.mask = LVIF_PARAM | LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
				pParentFolder->AddRef();
				shellItemPtr = (LPSHELLITEMINFO)GlobalAlloc(GPTR, sizeof(SHELLITEMINFO));
				shellItemPtr->relativePIDL = tempPIDL;
				shellItemPtr->absolutePIDL = m_pShellManager->Combine(parentPIDL, tempPIDL);
				shellItemPtr->pParentFolder = pParentFolder;
				lvItem.lParam = (LPARAM)shellItemPtr;
				lvItem.pszText = _T("");
				lvItem.iImage = OnGetItemIcon(GetItemCount(), shellItemPtr);
				DWORD dwAttr = SFGAO_DISPLAYATTRMASK;
				pParentFolder->GetAttributesOf(1, (LPCITEMIDLIST*)&tempPIDL, &dwAttr);

				if (dwAttr & SFGAO_SHARE)
				{
					lvItem.mask |= LVIF_STATE;
					lvItem.stateMask |= LVIS_OVERLAYMASK;
					lvItem.state |= INDEXTOOVERLAYMASK(1);
				}

				if (dwAttr & SFGAO_GHOSTED)
				{
					lvItem.mask |= LVIF_STATE;
					lvItem.stateMask |= LVIS_CUT;
					lvItem.state |= LVIS_CUT;
				}
				int iItem = InsertItem(&lvItem);
				if (iItem >= 0)
				{
					const int nColumns = (int)::SendMessage(GetHeaderCtrl(), HDM_GETITEMCOUNT, 0, 0L);
					for (int iColumn = 0; iColumn < nColumns; iColumn++)
					{
						SetItemText(iItem, iColumn, OnGetItemText(iItem, iColumn, shellItemPtr));
					}
				}
				dwFetched = 0;
			}
			pEnum->Release();
		}

		return hRes;
	}
	void TinyFileView::ReleaseItem()
	{
		if (m_psfCurrent != NULL)
		{
			m_psfCurrent->Release();
			m_psfCurrent = NULL;
			CoTaskMemFree(m_currentAbsPIDL);
			m_currentAbsPIDL = NULL;
		}
	}
	HRESULT TinyFileView::LockItem(LPSHELLITEMINFO shellItemPtr)
	{
		HRESULT hRes = E_FAIL;
		m_currentAbsPIDL = NULL;
		if (shellItemPtr != NULL && shellItemPtr->pParentFolder != NULL)
		{
			ASSERT(shellItemPtr->relativePIDL != NULL);
			hRes = shellItemPtr->pParentFolder->BindToObject(shellItemPtr->relativePIDL, NULL, IID_IShellFolder, (LPVOID*)&m_psfCurrent);
			m_bIsDesktop = FALSE;
		}
		else
		{
			hRes = SHGetDesktopFolder(&m_psfCurrent);
			m_bIsDesktop = TRUE;
		}
		if (SUCCEEDED(hRes) && shellItemPtr != NULL)
		{
			m_currentAbsPIDL = m_pShellManager->Clone(shellItemPtr->absolutePIDL);
		}

		return hRes;
	}
	void TinyFileView::SetFolderView(TinyFolderView* pNewView)
	{
		if (m_pView != pNewView)
		{
			m_pView = pNewView;
		}
	}
	HRESULT TinyFileView::DisplayItem(LPSHELLITEMINFO shellItemPtr)
	{
		HRESULT hRes = E_FAIL;
		if (shellItemPtr != NULL)
		{
			ReleaseItem();
			hRes = LockItem(shellItemPtr);

			if (FAILED(hRes))
			{
				return hRes;
			}
		}
		DeleteAllItems();
		if (m_psfCurrent != NULL)
		{
			SetRedraw(FALSE);
			hRes = EnumObjects(m_psfCurrent, m_currentAbsPIDL);
			SetRedraw(TRUE);
			RedrawWindow();
		}
		if (SUCCEEDED(hRes) && shellItemPtr != NULL)
		{
			if (m_pView != NULL && !m_bNoNotify)
			{
				m_pView->SelectPath(m_currentAbsPIDL);
			}
			if (GetParent() != NULL)
			{
				::SendMessage(GetParent()->Handle(), WM_CHANGE_CURRENT_FOLDER, 0, 0);
			}
		}
		return hRes;
	}
}
