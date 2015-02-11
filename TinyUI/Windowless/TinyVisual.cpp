#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
	{
		LIST_INIT(&m_visual.entry);
	}

	TinyVisual::~TinyVisual()
	{
	}
	inline Visual* TinyVisual::GetNextVisual(Visual *val)
	{
		LIST *ps = LIST_NEXT(&val->parent->children, &val->entry);
		return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	}
	inline Visual* TinyVisual::GetPrevVisual(Visual *val)
	{
		LIST *ps = LIST_PREV(&val->parent->children, &val->entry);
		return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	}
	inline Visual* TinyVisual::GetFirstChild(Visual *val)
	{
		LIST *ps = LIST_HEAD(&val->children);
		return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	}
	inline Visual* TinyVisual::GetLastChild(Visual *val)
	{
		LIST *ps = LIST_TAIL(&val->children);
		return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	}
	void TinyVisual::LinkVisual(Visual* val, Visual* previous)
	{
		if (previous == VISUAL_NOTOPMOST)
		{
			if (!(val->style & VS_TOPMOST)) return;
			val->style &= ~VS_TOPMOST;
			previous = VISUAL_TOP;
		}
		LIST_REMOVE(&val->entry);
		if (previous == VISUAL_BOTTOM)
		{
			LIST_ADD_TAIL(&val->parent->children, &val->entry);
			val->style &= ~VS_TOPMOST;
		}
		else if (previous == VISUAL_TOPMOST)
		{
			LIST_ADD_HEAD(&val->parent->children, &val->entry);
			val->style |= VS_TOPMOST;
		}
		else if (previous == VISUAL_TOP)
		{
			LIST *entry = val->parent->children.NEXT;
			if (!(val->style & VS_TOPMOST))//没有TOP MOST风格
			{
				while (entry != &val->parent->children)
				{
					Visual *next = LIST_ENTRY(entry, Visual, entry);
					if (!(next->style & VS_TOPMOST))
						break;
					entry = entry->NEXT;
				}
			}
			LIST_ADD_BEFORE(entry, &val->entry);
		}
		else
		{
			LIST_ADD_AFTER(&previous->entry, &val->entry);
			if (!(previous->style & VS_TOPMOST)) val->style &= ~WS_EX_TOPMOST;
			else
			{
				Visual *next = GetNextVisual(val);
				if (next && (next->style & VS_TOPMOST))
					val->style |= WS_EX_TOPMOST;
			}
		}
	}
	BOOL TinyVisual::SetParent(Visual *val, Visual *parent)
	{
		Visual* ps = NULL;
		for (ps = parent; ps; ps = ps->parent)
		{
			if (ps == val)
			{
				return FALSE;
			}
		}
		if (parent)
		{
			val->parent = parent;
			LinkVisual(val, VISUAL_TOP);
		}
		return TRUE;
	}
	inline BOOL TinyVisual::IsVisible(const Visual *val)
	{
		while (val != NULL)
		{
			if (!(val->style & VS_VISIBLE)) return FALSE;
			val = val->parent;
			if (val && (val->style & VS_MINIMIZE)) return FALSE;
		}
		return TRUE;
	}
	inline BOOL TinyVisual::IsTop(const Visual *val)
	{
		return !val->parent;
	}
	inline BOOL TinyVisual::GetVisibleRectangle(const Visual* val, TinyRectangle& rect)
	{
		INT offset_x = 0, offset_y = 0;
		if (!(val->style & VS_VISIBLE)) return FALSE;
	}
	inline HRGN TinyVisual::GetVisibleRegion(const Visual* val, UINT flags)
	{
		INT offset_x, offset_y;
		HRGN hRgn = NULL;
		if (!(hRgn = CreateRectRgn(0, 0, 0, 0))) return NULL;
		if (!IsVisible(val)) return hRgn;
	}
	inline BOOL TinyVisual::PtInVisual(const Visual* val, INT x, INT y)
	{
		if (!(val->style & VS_VISIBLE))
			return FALSE;
		if (val->style & (VS_CHILD | VS_DISABLED))
			return FALSE;
		POINT pos{ x, y };
		/*if (val->visible_region &&!PtInRegion(val->visible_region, x, y))
			return FALSE;*/
		return TRUE;
	}
	inline BOOL TinyVisual::SetRegion(Visual *val, HRGN region, INT redraw)
	{
		if (redraw && !IsVisible(val))
			redraw = 0;
		return TRUE;
	}
}
