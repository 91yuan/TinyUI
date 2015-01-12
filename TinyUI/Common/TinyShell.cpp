#include "../stdafx.h"
#include "TinyShell.h"

namespace TinyUI
{
	TinyShellManager::TinyShellManager()
	{
		m_lpszInitialPath = NULL;
		SHGetMalloc(&m_pMalloc);
	}
	TinyShellManager::~TinyShellManager()
	{
		if (m_pMalloc != NULL)
		{
			m_pMalloc->Release();
			m_pMalloc = NULL;
		}
	}
	INT CALLBACK TinyShellManager::BrowseCallbackProc(
		HWND hwnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
	{
		if (uMsg == BFFM_INITIALIZED)
		{
			TinyShellManager* pThis = (TinyShellManager*)lpData;
			if (pThis->m_lpszInitialPath != NULL)
			{
				SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM)pThis->m_lpszInitialPath);
			}
		}
		return 0;
	}
	BOOL TinyShellManager::BrowseFolder(LPCTSTR strFolder,
		HWND hWndParent/* = NULL*/,
		LPCTSTR lplszInitialFolder/* = NULL*/,
		LPCTSTR lpszTitle/* = NULL*/,
		UINT ulFlags/* = BIF_RETURNONLYFSDIRS */,
		LPINT piFolderImage/* = NULL*/)
	{
		TCHAR szDisplayName[MAX_PATH];

		BROWSEINFO bi;
		ZeroMemory(&bi, sizeof (bi));

		bi.lpszTitle = lpszTitle != NULL ? lpszTitle : _T("");
		bi.pszDisplayName = szDisplayName;
		bi.hwndOwner = hWndParent;
		bi.lpfn = BrowseCallbackProc;
		bi.lParam = (LPARAM) this;
		bi.pidlRoot = NULL;
		bi.ulFlags = ulFlags;
		bi.iImage = -1;
		m_lpszInitialPath = lplszInitialFolder;
		BOOL bRes = FALSE;
		LPITEMIDLIST pidlRes = SHBrowseForFolder(&bi);
		if (pidlRes != NULL)
		{
			TCHAR szPath[MAX_PATH];
			if (SHGetPathFromIDList(pidlRes, szPath))
			{
				strFolder = szPath;

				if (piFolderImage != NULL)
				{
					*piFolderImage = bi.iImage;
				}
				bRes = TRUE;
			}
			Free(pidlRes);
		}
		m_lpszInitialPath = NULL;
		return bRes;
	}
	//·µ»ØRelativePIDL
	LPITEMIDLIST TinyShellManager::GetNext(LPCITEMIDLIST relativePIDL)
	{
		if (relativePIDL && relativePIDL->mkid.cb)
		{
			return PIDLNext(relativePIDL);
		}
		return NULL;
	}

	UINT TinyShellManager::GetSize(LPCITEMIDLIST relativePIDL)
	{
		UINT cbTotal = 0;
		if (relativePIDL)
		{
			cbTotal += sizeof(relativePIDL->mkid.cb);
			while (relativePIDL->mkid.cb)
			{
				cbTotal += relativePIDL->mkid.cb;
				relativePIDL = PIDLNext(relativePIDL);
			}
		}
		return cbTotal;
	}
	LPITEMIDLIST TinyShellManager::FindLastID(LPCITEMIDLIST relativePIDL)
	{
		LPCITEMIDLIST pidlLast = relativePIDL;
		LPCITEMIDLIST pidlNext = relativePIDL;
		if (relativePIDL == NULL)
			return NULL;
		while (pidlNext->mkid.cb)
		{
			pidlLast = pidlNext;
			pidlNext = PIDLNext(pidlLast);
		}
		return (LPITEMIDLIST)pidlLast;
	}
	BOOL TinyShellManager::RemoveLastID(LPITEMIDLIST relativePIDL)
	{
		BOOL fRemoved = FALSE;
		if (relativePIDL == NULL)
			return(FALSE);
		if (relativePIDL->mkid.cb)
		{
			LPITEMIDLIST pidlLast = (LPITEMIDLIST)FindLastID(relativePIDL);
			pidlLast->mkid.cb = 0;
			fRemoved = TRUE;
		}
		return fRemoved;
	}

	LPITEMIDLIST TinyShellManager::Clone(LPCITEMIDLIST relativePIDL)
	{
		UINT cb = GetSize(relativePIDL);
		LPITEMIDLIST newPIDL = (LPITEMIDLIST)CoTaskMemAlloc(cb);
		if (newPIDL)
			CopyMemory(newPIDL, relativePIDL, cb);
		return newPIDL;
	}
	INT TinyShellManager::GetParent(LPCITEMIDLIST currentPIDL, LPITEMIDLIST& parentPIDL)
	{
		UINT nCount = GetSize(currentPIDL);
		if (nCount == 0)
		{
			return -1;
		}
		if (nCount == 1)
		{
			SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &parentPIDL);
			return 0;
		}
		USHORT uiParentSize = 0;
		LPCITEMIDLIST lpidlCurr = currentPIDL;

		for (UINT i = 0; i < nCount - 1; i++)
		{
			uiParentSize = (USHORT)(uiParentSize + lpidlCurr->mkid.cb);
			lpidlCurr = PIDLNext(lpidlCurr);
		}

		parentPIDL = (LPITEMIDLIST)CoTaskMemAlloc(uiParentSize + 2);
		CopyMemory((LPBYTE)parentPIDL, (LPBYTE)currentPIDL, uiParentSize);
		return nCount - 1;
	}
	LPITEMIDLIST TinyShellManager::CloneFirst(LPCITEMIDLIST relativePIDL)
	{
		UINT cb = relativePIDL->mkid.cb + sizeof(relativePIDL->mkid.cb);
		LPITEMIDLIST pidlRet = (LPITEMIDLIST)CoTaskMemAlloc(cb);
		if (pidlRet)
		{
			CopyMemory(pidlRet, relativePIDL, relativePIDL->mkid.cb);
			PIDLNext(pidlRet)->mkid.cb = 0;
		}
		return pidlRet;
	}
	BOOL TinyShellManager::IsEqual(LPCITEMIDLIST absolutePIDL1, LPCITEMIDLIST absolutePIDL2)
	{
		BOOL bRet = FALSE;
		IShellFolder *psfDesktop;
		if (SUCCEEDED(SHGetDesktopFolder(&psfDesktop)))
		{
			bRet = psfDesktop->CompareIDs(0, absolutePIDL1, absolutePIDL2) == 0;
			psfDesktop->Release();
		}
		return bRet;
	}
	BOOL TinyShellManager::IsParent(LPCITEMIDLIST absolutePIDL1, LPCITEMIDLIST absolutePIDL2, BOOL fImmediate)
	{
		LPITEMIDLIST pidl2Prefix;
		UINT cb;
		LPCITEMIDLIST pidl1T;
		LPCITEMIDLIST pidl2T;
		if (!absolutePIDL1 || !absolutePIDL2)
			return FALSE;
		for (pidl1T = absolutePIDL1, pidl2T = absolutePIDL2; !PIDLIsEmpty(pidl1T);
			pidl1T = PIDLNext(pidl1T), pidl2T = PIDLNext(pidl2T))
		{
			if (PIDLIsEmpty(pidl2T))
				return FALSE;
		}
		if (fImmediate)
		{
			if (PIDLIsEmpty(pidl2T) || !PIDLIsEmpty(PIDLNext(pidl2T)))
				return FALSE;
		}
		cb = (UINT)pidl2T - (UINT)absolutePIDL2;
		pidl2Prefix = (LPITEMIDLIST)CoTaskMemAlloc(cb + sizeof(absolutePIDL2->mkid.cb));
		if (pidl2Prefix)
		{
			CopyMemory(pidl2Prefix, absolutePIDL2, cb);
			*(USHORT *)((BYTE *)pidl2Prefix + cb) = 0;
			BOOL fRet = IsEqual(absolutePIDL1, pidl2Prefix);
			CoTaskMemFree(pidl2Prefix);
			return fRet;
		}
		return FALSE;
	}
	LPITEMIDLIST TinyShellManager::FindChild(LPCITEMIDLIST pidlParent, LPCITEMIDLIST pidlChild)
	{
		if (IsParent(pidlParent, pidlChild, FALSE))
		{
			while (!PIDLIsEmpty(pidlParent))
			{
				pidlChild = PIDLNext(pidlChild);
				pidlParent = PIDLNext(pidlParent);
			}
			return (LPITEMIDLIST)pidlChild;
		}
		return NULL;
	}

	LPITEMIDLIST  TinyShellManager::Combine(LPCITEMIDLIST absolutePIDL, LPCITEMIDLIST relativePIDL)
	{
		LPITEMIDLIST pidlNew;
		UINT cb1 = GetSize(absolutePIDL) - sizeof(absolutePIDL->mkid.cb);
		UINT cb2 = GetSize(relativePIDL);
		pidlNew = (LPITEMIDLIST)CoTaskMemAlloc(cb1 + cb2);
		if (pidlNew)
		{
			CopyMemory(pidlNew, absolutePIDL, cb1);
			CopyMemory(((LPSTR)pidlNew) + cb1, relativePIDL, cb2);
		}
		return pidlNew;
	}
	LPITEMIDLIST TinyShellManager::Alloc(UINT cbSize)
	{
		if (m_pMalloc == NULL) return NULL;
		LPITEMIDLIST allocPIDL = (LPITEMIDLIST)m_pMalloc->Alloc(cbSize);
		if (allocPIDL) memset(allocPIDL, 0, cbSize);
		return allocPIDL;
	}
	void TinyShellManager::Free(LPITEMIDLIST pidl)
	{
		if (m_pMalloc == NULL) return;
		if (pidl != NULL)
		{
			m_pMalloc->Free(pidl);
		}
	}
	LPITEMIDLIST TinyShellManager::Resize(LPITEMIDLIST oldPIDL, UINT cbRequired, UINT cbExtra)
	{
		if (m_pMalloc == NULL) return NULL;
		LPITEMIDLIST savePIDL = oldPIDL;
		if (oldPIDL == NULL)
		{
			oldPIDL = Alloc(cbRequired + cbExtra);
		}
		else if (!cbExtra || m_pMalloc->GetSize(oldPIDL) < cbRequired)
		{
			oldPIDL = (LPITEMIDLIST)m_pMalloc->Realloc(oldPIDL, cbRequired + cbExtra);
		}
		return oldPIDL;
	}

	LPITEMIDLIST TinyShellManager::CreateFromPath(LPCTSTR pszPath)
	{
		LPITEMIDLIST pidl = NULL;
		IShellFolder *psfDesktop;
		if (SUCCEEDED(SHGetDesktopFolder(&psfDesktop)))
		{
			ULONG cchEaten;
			WCHAR wszPath[MAX_PATH];
			SHTCharToUnicode(pszPath, wszPath, ARRAYSIZE(wszPath));
			psfDesktop->ParseDisplayName(NULL, NULL, wszPath, &cchEaten, &pidl, NULL);
			psfDesktop->Release();
		}
		return pidl;
	}
}
