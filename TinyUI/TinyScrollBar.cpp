#include "stdafx.h"
#include "TinyScrollBar.h"

namespace TinyUI
{
	TinyScrollBar::TinyScrollBar()
	{
	}
	TinyScrollBar::~TinyScrollBar()
	{

	}
	LPCSTR TinyScrollBar::RetrieveClassName()
	{
		return WC_SCROLLBAR;
	}
	LPCSTR TinyScrollBar::RetrieveTitle()
	{
		return TEXT("TinyScrollBar");
	}
	DWORD TinyScrollBar::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CHILD | SBS_VERT);
	}
	DWORD TinyScrollBar::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE);
	}
	BOOL TinyScrollBar::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	INT TinyScrollBar::GetScrollPos() const
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetScrollPos(m_hWND, SB_CTL);
	}
	INT TinyScrollBar::SetScrollPos(INT nPos, BOOL bRedraw)
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetScrollPos(m_hWND, SB_CTL, nPos, bRedraw);
	}
	void TinyScrollBar::GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const
	{
		ASSERT(::IsWindow(m_hWND));
		::GetScrollRange(m_hWND, SB_CTL, lpMinPos, lpMaxPos);
	}
	void TinyScrollBar::SetScrollRange(INT nMinPos, INT nMaxPos, BOOL bRedraw)
	{
		ASSERT(::IsWindow(m_hWND));
		::SetScrollRange(m_hWND, SB_CTL, nMinPos, nMaxPos, bRedraw);
	}
	void TinyScrollBar::ShowScrollBar(BOOL bShow)
	{
		ASSERT(::IsWindow(m_hWND));
		::ShowScrollBar(m_hWND, SB_CTL, bShow);
	}
	BOOL TinyScrollBar::EnableScrollBar(UINT nArrowFlags)
	{
		ASSERT(::IsWindow(m_hWND));
		return ::EnableScrollBar(m_hWND, SB_CTL, nArrowFlags);
	}

	BOOL TinyScrollBar::SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw)
	{
		return ::SetScrollInfo(m_hWND, SB_CTL, lpScrollInfo, bRedraw);
	}
	BOOL TinyScrollBar::GetScrollInfo(INT fnBar, LPSCROLLINFO lpScrollInfo)
	{
		return ::GetScrollInfo(m_hWND, fnBar, lpScrollInfo);
	}
	INT TinyScrollBar::GetScrollLimit(INT fnBar)
	{
		int nMin, nMax;
		GetScrollRange(&nMin, &nMax);
		SCROLLINFO info;
		info.fMask = SIF_PAGE;
		info.cbSize = sizeof(SCROLLINFO);
		if (GetScrollInfo(fnBar, &info))
		{
			nMax -= __max(info.nPage - 1, 0);
		}
		return nMax;
	}
}
