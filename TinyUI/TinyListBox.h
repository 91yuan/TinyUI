#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ап╠М©ь╪Ч
	/// </summary>
	class TinyListBox :public TinyControl
	{
	public:
		TinyListBox();
		virtual ~TinyListBox();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveTitle();
		virtual LPCSTR RetrieveClassName();
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		INT GetCount() const;
		INT GetCurSel() const;
		INT SetCurSel(int nSelect);
		INT GetHorizontalExtent() const;
		void SetHorizontalExtent(int cxExtent);
		INT GetSelCount() const;
		INT GetSelItems(INT nMaxItems, LPINT rgIndex) const;
		INT GetTopIndex() const;
		INT SetTopIndex(INT nIndex);
		DWORD_PTR GetItemData(INT nIndex) const;
		INT SetItemData(INT nIndex, LPARAM dwItemData);
		void* GetItemDataPtr(INT nIndex) const;
		INT SetItemDataPtr(INT nIndex, void* pData);
		INT GetItemRect(INT nIndex, LPRECT lpRect) const;
		INT GetSel(INT nIndex) const;
		INT SetSel(INT nIndex, BOOL bSelect);
		INT GetText(INT nIndex, LPTSTR lpszBuffer) const;
		INT GetTextLen(INT nIndex) const;
		void SetColumnWidth(INT cxWidth);
		INT GetItemAt(POINT pos);
		BOOL SetTabStops(int nTabStops, LPINT rgTabStops);
		void SetTabStops();
		BOOL SetTabStops(const int& cxEachStop);
		INT SetItemHeight(INT nIndex, UINT cyItemHeight);
		INT GetItemHeight(INT nIndex) const;
		INT FindStringExact(INT nIndexStart, LPCTSTR lpszFind) const;
		INT GetCaretIndex() const;
		INT SetCaretIndex(INT nIndex, BOOL bScroll = TRUE);
		INT AddString(LPCTSTR lpszItem);
		INT DeleteString(UINT nIndex);
		INT InsertString(INT nIndex, LPCTSTR lpszItem);
		void ResetContent();
		INT Dir(UINT attr, LPCTSTR lpszWildCard);
		INT FindString(int nStartAfter, LPCTSTR lpszItem) const;
		INT SelectString(int nStartAfter, LPCTSTR lpszItem);
		INT SelItemRange(BOOL bSelect, int nFirstItem, int nLastItem);
		LCID GetLocale() const;
		LCID SetLocale(LCID nNewLocale);
		INT InitStorage(INT nItems, UINT nBytes);
		void SetAnchorIndex(INT nIndex);
		INT GetAnchorIndex() const;
	};
}
