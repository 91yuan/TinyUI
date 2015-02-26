#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
	{
		//memset(&m_visual, 0, sizeof(Visual));
		//LIST_INIT(&m_visual.entry);
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
	inline BOOL TinyVisual::IsTop(const Visual *val)
	{
		return !val->parent;
	}
	inline BOOL TinyVisual::IsVisible(const Visual *val)
	{
		while (val != NULL)
		{
			if (!(val->style & VS_VISIBLE))
				return FALSE;
			val = val->parent;
			if (val && (val->style & VS_MINIMIZE))
				return FALSE;
		}
		return TRUE;
	}
	BOOL TinyVisual::SetParent(Visual* val, Visual* parent)
	{
		Visual *ps = NULL;
		for (ps = parent; ps; ps = ps->parent)
		{
			if (ps == val)
			{
				return FALSE;
			}
		}
		if (parent != NULL)
		{
			//添加到第一个非TOPMOST节点之前
			val->parent = parent;
			LIST *entry = val->parent->children.NEXT;
			if (!(val->style & VS_TOPMOST))
			{
				while (entry != &val->parent->children)
				{
					Visual *next = LIST_ENTRY(entry, Visual, entry);
					if (!(next->style & VS_TOPMOST)) break;
					entry = entry->NEXT;
				}
			}
			LIST_ADD_BEFORE(entry, &val->entry);
		}
		return TRUE;
	}
	BOOL TinyVisual::SetVisualPos(Visual* val, Visual* valAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags)
	{
		INT visible = (val->style & WS_VISIBLE) || (uFlags & SWP_SHOWWINDOW);
		if (val->parent && !IsVisible(val->parent)) 
			visible = 0;
		return TRUE;
	}
}
