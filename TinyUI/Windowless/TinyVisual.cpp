#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
		:m_window_region(NULL),
		m_parent(NULL)
	{
		SetRectEmpty(&m_window_rectangle);
		SetRectEmpty(&m_visible_rectangle);
		m_visuals.OWNER = this;
	}
	TinyVisual* TinyVisual::New(TinyVisual* parent, INT x, INT y, INT cx, INT cy)
	{
		TinyVisual* ps = new TinyVisual();
		ps->m_style = VS_VISIBLE;
		ps->m_alpha = 255;
		ps->m_parent = parent;
		SetVisualPos(ps, NULL, x, y, cx, cy, 0);
		return ps;
	}
	void TinyVisual::Delete(TinyVisual* val)
	{
		SAFE_DELETE(val);
	}
	TinyVisual::~TinyVisual()
	{
		TinyVisual::Delete(this);
	}
	BOOL TinyVisual::HandleEvent(TinyVisualEvent* pEvent, BOOL& bHandle)
	{
		ASSERT(pEvent);
		return FALSE;
	}
	BOOL TinyVisual::SetVisualPos(TinyVisual* val, TinyVisual* insertAfter, INT x, INT y, INT cx, INT cy, UINT fFlag)
	{
		TinyVisual* oldParent = val->m_parent;
		if (!(fFlag & SWP_NOZORDER))
		{
			//insertAfter父节点和val父节点必须一致
			if (val->m_parent != insertAfter->m_parent)
			{
				return FALSE;
			}
			_MOVE_AFTER(&val->m_visuals, &insertAfter->m_visuals);
		}
		if (!(fFlag & SWP_NOMOVE))
		{
			if (x < -32768) x = -32768;
			else if (x > 32767) x = 32767;
			if (y < -32768) y = -32768;
			else if (y > 32767) y = 32767;
		}
		else
		{
			x = val->m_window_rectangle.left;
			y = val->m_window_rectangle.top;
		}
		if (!(fFlag & SWP_NOSIZE))
		{
			if (cx < 0) cx = 0;
			else if (cx > 32767) cx = 32767;
			if (cy < 0) cy = 0;
			else if (cy > 32767) cy = 32767;
		}
		else
		{
			cx = TO_CX(val->m_window_rectangle);
			cy = TO_CY(val->m_window_rectangle);
		}
		RECT new_rectangle = { x, y, x + cx, y + cy };
		INT offsetL = val->m_window_rectangle.left - new_rectangle.left;
		INT offsetT = val->m_window_rectangle.top - new_rectangle.top;
		INT offsetR = val->m_window_rectangle.right - new_rectangle.right;
		INT offsetB = val->m_window_rectangle.bottom - new_rectangle.bottom;
		val->m_window_rectangle.left = x;
		val->m_window_rectangle.top = y;
		val->m_window_rectangle.right = x + cx;
		val->m_window_rectangle.bottom = y + cy;
		//更新子元素
		POINT pos = { x, y };
		Visual *ps = val->m_visuals.NEXT;
		while (ps)
		{
			ps->OWNER->m_window_rectangle.left = ps->OWNER->m_window_rectangle.left + offsetL;
			ps->OWNER->m_window_rectangle.top = ps->OWNER->m_window_rectangle.top + offsetT;
			ps->OWNER->m_window_rectangle.right = ps->OWNER->m_window_rectangle.right + offsetR;
			ps->OWNER->m_window_rectangle.bottom = ps->OWNER->m_window_rectangle.left + offsetB;
			ps = ps->NEXT;
		}
		return TRUE;
	}
	BOOL TinyVisual::SetParent(TinyVisual* parent)
	{
		TinyVisual *val = NULL;
		for (val = parent; val; val = val->m_parent)
		{
			if (val == this)
				return FALSE;
		}
		if (parent != NULL)
		{
			m_parent = parent;
			_ADD_BEFORE(parent->m_visuals.NEXT, &m_visuals);
		}
		return TRUE;
	}
	void TinyVisual::GetRectangle(RECT& rect)
	{
		CopyRect(&m_window_rectangle, &rect);
	}
	void TinyVisual::SetName(LPCSTR pzName)
	{
		strcpy_s(m_name, MAX_STRING, pzName);
	}
	LPCSTR	TinyVisual::GetName()
	{
		return m_name;
	}
	BOOL TinyVisual::IsVisible(const TinyVisual *win)
	{
		while (win)
		{
			if (!(win->m_style & VS_VISIBLE)) return FALSE;
			win = win->m_parent;
			if (win && (win->m_style & VS_MINIMIZE)) return FALSE;
		}
		return TRUE;
	}
	BOOL TinyVisual::IsTop(const TinyVisual *win)
	{
		return !win->m_parent;
	}
	BOOL TinyVisual::PtInVisual(const TinyVisual *win, INT x, INT y)
	{
		if (!(win->m_style & VS_VISIBLE))
			return FALSE;
		POINT pos = { x, y };
		if (!PtInRect(&win->m_visible_rectangle, pos))
			return FALSE;
		if (win->m_window_region != NULL &&
			!PtInRegion(win->m_window_region, x, y))
			return FALSE;
		return TRUE;
	}
	inline void TinyVisual::_ADD(Visual *newVal, Visual *prevVal, Visual *nextVal)
	{
		nextVal->PREV = newVal;
		newVal->NEXT = nextVal;
		newVal->PREV = prevVal;
		prevVal->NEXT = newVal;
	}
	inline void TinyVisual::_ADD_AFTER(Visual *newVal, Visual *nodeVal)
	{
		_ADD(newVal, nodeVal, nodeVal->NEXT);
	}
	inline void TinyVisual::_ADD_BEFORE(Visual *newVal, Visual *nodeVal)
	{
		_ADD(newVal, nodeVal->PREV, nodeVal);
	}
	inline void TinyVisual::_MOVE_AFTER(Visual *val, Visual *nodeVal)
	{
		_DEL_ENTRY(val);
		_ADD_AFTER(val, nodeVal);
	}
	inline void TinyVisual::_MOVE_BEFORE(Visual *val, Visual *nodeVal)
	{
		_DEL_ENTRY(val);
		_ADD_BEFORE(val, nodeVal);
	}
	void TinyVisual::_DEL(Visual * prevVal, Visual * nextVal)
	{
		nextVal->PREV = prevVal;
		prevVal->NEXT = nextVal;
	}
	void TinyVisual::_DEL_ENTRY(Visual *entry)
	{
		_DEL(entry->PREV, entry->NEXT);
	}

}
