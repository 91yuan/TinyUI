#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
		:m_pParent(NULL),
		m_pChildren(NULL),
		m_pNext(NULL),
		m_pPrev(NULL),
		m_dwStyle(WS_VISIBLE)
	{
		memset(&m_bounds, 0, sizeof(RECT));
	}
	TinyVisual::~TinyVisual()
	{

	}
	BOOL TinyVisual::Create(TinyVisual* pParent, INT x, INT y, INT cx, INT cy, DWORD dwStyle)
	{
		this->m_pParent = pParent;
		return FALSE;
	}
	void TinyVisual::SetStyle(DWORD dwStyle)
	{
		m_dwStyle = dwStyle;
	}
	DWORD TinyVisual::GetStyle() const
	{
		return m_dwStyle;
	}
	TinyVisual*	TinyVisual::GetVisual(TinyVisual* _this,DWORD dwCMD)
	{
		switch (dwCMD)
		{
		case GW_HWNDNEXT:
			break;
		case GW_HWNDPREV:
			break;
		case GW_HWNDFIRST:
			break;
		case GW_HWNDLAST:
			break;
		default:
			break;
		}
	}
	BOOL TinyVisual::SetVisualPos(TinyVisual* _this,TinyVisual* pInsertAfter, INT x, INT y, INT cx, INT cy, UINT nFlags)
	{

		/*ITERATOR pos = m_list.Lookup(pInsertAfter);
		if (nFlags & SWP_HIDEWINDOW)
		{
		m_dwStyle &= ~WS_VISIBLE;
		}
		if (nFlags & SWP_SHOWWINDOW)
		{
		m_dwStyle |= WS_VISIBLE;
		}
		TinyRectangle bounds = m_bounds;
		if (nFlags & SWP_NOMOVE)
		{
		bounds.right = bounds.left + cx;
		bounds.bottom = bounds.top + cy;
		}
		if (nFlags & SWP_NOSIZE)
		{
		TinySize size = bounds.Size();
		bounds.left = x;
		bounds.top = y;
		bounds.right = x + size.cx;
		bounds.bottom = y + size.cy;
		}
		if (nFlags & SWP_NOZORDER)
		{
		m_list.InsertFirst();
		}
		this->m_bounds = bounds;*/
		return FALSE;
	}
	BOOL TinyVisual::IsVisible() const
	{
		return m_dwStyle & WS_VISIBLE;
	}
	BOOL TinyVisual::IsEnable() const
	{
		return !(m_dwStyle & WS_DISABLED);
	}
	void TinyVisual::Layout()
	{

	}
}
