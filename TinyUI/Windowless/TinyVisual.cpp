#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual(TinyVisualHWND* hostHWND)
		: m_hostHWND(hostHWND),
		m_parent(NULL)
	{
		m_visuals.OWNER = this;
		m_visuals.NEXT = m_visuals.PREV = &m_visuals;
	}
	TinyVisual::TinyVisual(TinyVisual* parent, INT x, INT y, INT cx, INT cy)
		: m_hostHWND(NULL),
		m_parent(NULL)
	{
		m_parent = parent;
		m_hostHWND = parent->m_hostHWND;
		m_visuals.OWNER = this;
		m_visuals.NEXT = m_visuals.PREV = &m_visuals;
	}
	TinyVisual::~TinyVisual()
	{

	}
	LPCSTR	TinyVisual::GetName()
	{
		return m_name.STR();
	}
	void TinyVisual::SetName(LPCSTR pzName)
	{
		m_name = pzName;
	}
	TinyVisual* TinyVisual::New(TinyVisual* parent, INT x, INT y, INT cx, INT cy)
	{
		TinyVisual* ps = new TinyVisual(parent, x, y, cx, cy);
	}
	void TinyVisual::Delete(TinyVisual* val)
	{
		while (!IsEmpty(&val->m_visuals))
			Delete(GetFirst(&val->m_visuals)->OWNER);
		Remove(&val->m_visuals);
		SAFE_DELETE(val);
	}
	Visual* TinyVisual::GetNext(const Visual *list, const Visual *elem)
	{
		struct Visual *ps = elem->NEXT;
		if (elem->NEXT == list) ps = NULL;
		return ps;
	}
	Visual* TinyVisual::GetPrev(const Visual *list, const Visual *elem)
	{
		struct Visual *ps = elem->PREV;
		if (elem->PREV == list) ps = NULL;
		return ps;
	}
	inline Visual *TinyVisual::GetFirst(const Visual *list)
	{
		return  GetNext(list, list);
	}
	inline Visual *TinyVisual::GetLast(const Visual *list)
	{
		return GetPrev(list, list);
	}
	BOOL TinyVisual::IsEmpty(Visual* list)
	{
		return list->NEXT == list;
	}
	void TinyVisual::Remove(struct Visual *elem)
	{
		elem->NEXT->PREV = elem->PREV;
		elem->PREV->NEXT = elem->NEXT;
	}
}
