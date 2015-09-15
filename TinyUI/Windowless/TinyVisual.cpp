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
	TinyVisual*	TinyVisual::GetParent()
	{
		return this->m_pParent;
	}

	BOOL TinyVisual::Add(TinyVisual* ps)
	{
		if (!ps) return FALSE;
		return m_visuals.InsertLast(ps) != NULL;
	}
	BOOL TinyVisual::Remove(TinyVisual* ps)
	{
		if (!ps) return FALSE;
		return m_visuals.RemoveAt((ITERATOR)ps);
	}
	void TinyVisual::RemoveAll()
	{
		m_visuals.RemoveAll();
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
