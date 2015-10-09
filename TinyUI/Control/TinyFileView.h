#pragma once
#include "../Common/TinyTime.h"
#include "../Common/TinyShell.h"
#include "TinyListView.h"

namespace TinyUI
{
	using namespace IO;

	class TinyFolderView;
	enum
	{
		ColumnName = 0,
		ColumnSize = 1,
		ColumnType = 2,
		ColumnModified = 3,
	};
	/// <summary>
	/// 文件View
	/// </summary>
	class TinyFileView :public TinyListView
	{
		DECLARE_DYNAMIC(TinyFileView)
	public:
		TinyFileView();
		virtual ~TinyFileView();
	public:
		virtual LRESULT		OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual TinyString	OnGetItemText(INT iItem, INT iColumn, LPSHELLITEMINFO pItem, CHAR* pz, INT size);
		virtual INT			OnGetItemIcon(INT iItem, LPSHELLITEMINFO pItem);
		virtual void		OnSetColumns();
		virtual void		OnFormatFileDate(const TinyTime& tmFile, TinyString& str);
		virtual void		OnFormatFileSize(__int64 lFileSize, TinyString& str);
		virtual void		OnDeleteItem(INT iItem);
		void SetFolderView(TinyFolderView* pNewView);
		INT OnCompareItems(LPARAM lParam1, LPARAM lParam2, INT iColumn);
	private:
		void InitializeFileView();
		void ReleaseItem();
		HRESULT		EnumObjects(LPSHELLFOLDER pParentFolder, LPITEMIDLIST parentPIDL);
		HIMAGELIST	GetShellImageList(BOOL bLarge);
		HRESULT		LockItem(LPSHELLITEMINFO shellItemPtr);
		HRESULT		DisplayItem(LPSHELLITEMINFO shellItemPtr);
	private:
		IShellFolder*		m_psfCurrent;//当前项的PIDL
		LPITEMIDLIST		m_currentAbsPIDL;//当前的绝对PIDL
		TinyShellManager*	m_pShellManager;
		TinyFolderView*     m_pView;
		SHCONTF				m_nTypes;
		BOOL				m_bContextMenu;
		BOOL				m_bIsDesktop;
		BOOL				m_bNoNotify;
	};
}


