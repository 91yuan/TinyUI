#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ¹ö¶¯Ìõ¿Ø¼þ
	/// </summary>
	class TinyScrollBar :public TinyControl
	{
		DECLARE_DYNAMIC(TinyScrollBar)
	public:
		TinyScrollBar();
		virtual ~TinyScrollBar();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		INT GetScrollPos() const;
		INT SetScrollPos(INT nPos, BOOL bRedraw = TRUE);
		void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const;
		void SetScrollRange(INT nMinPos, INT nMaxPos, BOOL bRedraw = TRUE);
		void ShowScrollBar(BOOL bShow = TRUE);
		BOOL EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH);
		BOOL SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
		BOOL GetScrollInfo(INT fnBar, LPSCROLLINFO lpScrollInfo);
		INT GetScrollLimit(INT fnBar);
	};
}



