#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
#define PIDLSkip(relativePIDL, cb)	((LPITEMIDLIST)(((BYTE*)(relativePIDL))+cb))
#define PIDLNext(relativePIDL)		PIDLSkip(relativePIDL, (relativePIDL)->mkid.cb)
#define PIDLIsEmpty(allocPIDL)         ((allocPIDL) == NULL || (allocPIDL)->mkid.cb==0)
#define PIDLIsChild(allocPIDL)         (PIDLIsEmpty(allocPIDL) || PIDLIsEmpty(PIDLNext(allocPIDL)))
	UINT GetPIDLSize(LPCITEMIDLIST pidl);
	LPITEMIDLIST CopyPIDL(LPMALLOC pMalloc, LPCITEMIDLIST pidlSource);
	VOID FreePIDL(LPITEMIDLIST pidl);
	typedef struct tagSHELLITEMINFO
	{
		LPSHELLFOLDER  pParentFolder;//父窗口的ShellFoler
		LPITEMIDLIST   absolutePIDL;//绝对PIDL
		LPITEMIDLIST   relativePIDL;//相对PIDL
		BOOL		   bEnumFlag;
		tagSHELLITEMINFO()
		{
			pParentFolder = NULL;
			absolutePIDL = NULL;
			relativePIDL = NULL;
			bEnumFlag = FALSE;
		}
	}
	SHELLITEMINFO, FAR *LPSHELLITEMINFO;

	class TinyShellManager
	{
	public:
		TinyShellManager();
		~TinyShellManager();
		BOOL BrowseFolder(LPCTSTR strOutFolder, HWND hWndParent = NULL, LPCTSTR lplszInitialFolder = NULL,
			LPCTSTR lpszTitle = NULL, UINT ulFlags = BIF_RETURNONLYFSDIRS, LPINT piFolderImage = NULL);
		//返回RelativePIDL
		LPITEMIDLIST GetNext(LPCITEMIDLIST relativePIDL);
		UINT GetSize(LPCITEMIDLIST relativePIDL);
		LPITEMIDLIST FindLastID(LPCITEMIDLIST relativePIDL);
		BOOL RemoveLastID(LPITEMIDLIST relativePIDL);
		LPITEMIDLIST Clone(LPCITEMIDLIST relativePIDL);
		LPITEMIDLIST CloneFirst(LPCITEMIDLIST relativePIDL);
		BOOL IsEqual(LPCITEMIDLIST absolutePIDL1, LPCITEMIDLIST absolutePIDL2);
		BOOL IsParent(LPCITEMIDLIST absolutePIDL1, LPCITEMIDLIST absolutePIDL2, BOOL fImmediate);
		INT GetParent(LPCITEMIDLIST currentPIDL, LPITEMIDLIST& parentPIDL);
		LPITEMIDLIST FindChild(LPCITEMIDLIST pidlParent, LPCITEMIDLIST pidlChild);
		LPITEMIDLIST Combine(LPCITEMIDLIST absolutePIDL, LPCITEMIDLIST relativePIDL);
		LPITEMIDLIST CreateFromPath(LPCTSTR pszPath);
		LPITEMIDLIST Alloc(UINT cbSize);
		void Free(LPITEMIDLIST pidl);
		LPITEMIDLIST Resize(LPITEMIDLIST oldPIDL, UINT cbRequired, UINT cbExtra);
		LPITEMIDLIST AppendID(LPITEMIDLIST appendPIDL, LPCSHITEMID pmkid, BOOL fAppend);
	protected:
		static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	protected:
		LPMALLOC	m_pMalloc;
		LPCTSTR		m_lpszInitialPath;
	};
}


