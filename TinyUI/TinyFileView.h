#pragma once
#include "TinyTime.h"
#include "TinyShell.h"
#include "TinyString.h"
#include "TinyListView.h"

namespace TinyUI
{
	class TinyFolderView;
	enum
	{
		ColumnName = 0,
		ColumnSize = 1,
		ColumnType = 2,
		ColumnModified = 3,
	};
	//////////////////////////////////////////////////////////////////////////
	//文件View
	class TinyFileView :public TinyListView
	{
		DECLARE_DYNAMIC(TinyFileView)
	public:
		TinyFileView();
		virtual ~TinyFileView();
	public:
		virtual void OnSetColumns();
		virtual INT OnGetItemText(INT iItem, INT iColumn, LPSHELLITEMINFO pItem, CHAR* pz, INT size);
		INT OnCompareItems(LPARAM lParam1, LPARAM lParam2, INT iColumn);
		virtual INT OnGetItemIcon(INT iItem, LPSHELLITEMINFO pItem);
		virtual void OnFormatFileDate(const TinyTime& tmFile, TinyString& str);
		virtual void OnFormatFileSize(__int64 lFileSize, TinyString& str);
		void SetFolderView(TinyFolderView* pNewView);
		virtual void OnCreate();
		virtual void OnDeleteItem(INT iItem);
	private:
		void InitializeFileView();
		HRESULT EnumObjects(LPSHELLFOLDER pParentFolder, LPITEMIDLIST parentPIDL);
		HIMAGELIST GetShellImageList(BOOL bLarge);
		HRESULT LockItem(LPSHELLITEMINFO shellItemPtr);
		HRESULT DisplayItem(LPSHELLITEMINFO shellItemPtr);
		void ReleaseItem();
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


