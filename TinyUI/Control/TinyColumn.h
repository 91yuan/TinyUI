#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// Header¿Ø¼þ
	/// </summary>
	class TinyColumn : public TinyControl
	{
		DECLARE_DYNAMIC(TinyColumn)
	public:
		TinyColumn();
		virtual ~TinyColumn();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveExStyle();
		virtual DWORD RetrieveStyle();
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		INT GetItemCount() const;
		BOOL GetItem(INT nPos,HDITEM* pHeaderItem) const;
		BOOL SetItem(INT nPos,HDITEM* pHeaderItem);
		BOOL GetItemRect(INT nIndex,LPRECT lpRect) const;
		BOOL GetOrderArray(LPINT piArray,INT iCount) const;
		BOOL SetOrderArray(INT iCount,LPINT piArray);
		INT OrderToIndex(INT nOrder) const;
		INT HitTest(LPHDHITTESTINFO pHeaderHitTestInfo);
		INT GetBitmapMargin() const;
		INT SetBitmapMargin(INT nWidth);
		INT InsertItem(INT nPos, HDITEM* phdi);
		BOOL DeleteItem(INT nPos);
		BOOL Layout( HDLAYOUT* pHeaderLayout);
		HIMAGELIST CreateDragImage(INT nIndex);
		INT SetHotDivider(TinyPoint pt);
		INT SetHotDivider(INT nIndex);
		INT SetFilterChangeTimeout(DWORD dwTimeOut);
		INT EditFilter(INT nColumn, BOOL bDiscardChanges);
		BOOL ClearFilter(INT nColumn);
		BOOL ClearAllFilters();
	};
}


