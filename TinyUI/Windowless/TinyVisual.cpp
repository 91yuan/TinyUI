#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	//visual *TinyVisual::create_visual(visual *parent, INT x, INT y, INT cx, INT cy)
	//{
	//	visual* win = NULL;
	//	if (!(win = (visual*)malloc(sizeof(visual)))) goto error;
	//	win->parent = parent;
	//	win->last_active = parent;
	//	win->window_region = NULL;
	//	memset(win->name, 0, 150);
	//	SetRect(&win->visible_rectangle, x, y, x + cx, y + cy);
	//	SetRect(&win->window_rectangle, x, y, x + cx, y + cy);
	//	win->alpha = 0;
	//	win->style = 0;
	//	INIT_LIST(&win->children);
	//	if (parent)
	//	{
	//		LIST_ADD_AFTER(&parent->children, &win->entry);
	//	}
	//	else
	//	{
	//		INIT_LIST(&win->entry);
	//	}
	//	return win;
	//error:
	//	SAFE_FREE(win);
	//	return NULL;
	//};
	//void TinyVisual::destroy_visual(visual *win)
	//{
	//	while (!IS_LIST_EMPTY(&win->children))
	//	{
	//		destroy_visual(LIST_ENTRY(&win->children, visual, entry));
	//	}
	//	LIST_DEL(&win->entry);
	//	if (win->window_region != NULL)
	//	{
	//		SAFE_DELETE_OBJECT(win->window_region);
	//	}
	//	SAFE_FREE(win);
	//};
	//inline  visual *TinyVisual::get_next_window(visual *win)
	//{
	//	list *ptr = LIST_NEXT(&win->parent->children, &win->entry);
	//	return ptr ? LIST_ENTRY(ptr, visual, entry) : NULL;
	//}

	//inline  visual *TinyVisual::get_prev_window(visual *win)
	//{
	//	list *ptr = LIST_PREV(&win->parent->children, &win->entry);
	//	return ptr ? LIST_ENTRY(ptr, visual, entry) : NULL;
	//}

	//inline  visual *TinyVisual::get_first_child(visual *win)
	//{
	//	list *ptr = LIST_NEXT(&win->children, &win->children);
	//	return ptr ? LIST_ENTRY(ptr, visual, entry) : NULL;
	//}

	//inline  visual *TinyVisual::get_last_child(visual *win)
	//{
	//	list *ptr = LIST_PREV(&win->children, &win->children);
	//	return ptr ? LIST_ENTRY(ptr, visual, entry) : NULL;
	//}

	//BOOL TinyVisual::set_parent(visual *win, visual *parent)
	//{
	//	visual *ps = NULL;
	//	for (ps = parent; ps; ps = ps->parent)
	//	{
	//		if (ps == win)
	//		{
	//			return FALSE;
	//		}
	//	}
	//	//设置父节点
	//	if (parent != NULL)
	//	{
	//		win->parent = parent;
	//		//后加的元素放在TOP
	//		LIST_ADD_BEFORE(parent->children.NEXT, &win->entry);
	//	}
	//	return TRUE;
	//}
	//void TinyVisual::link_window(visual *win, visual *previous)
	//{
	//	LIST_DEL(&win->entry);
	//	if (previous == WINPTR_BOTTOM)
	//	{
	//		LIST_ADD_BEFORE(&win->parent->children, &win->entry);
	//		win->style &= ~VS_TOPMOST;
	//	}
	//	else if (previous == WINPTR_TOPMOST)
	//	{
	//		LIST_ADD_AFTER(&win->parent->children, &win->entry);
	//		win->style |= VS_TOPMOST;
	//	}
	//	else if (previous == WINPTR_TOP)
	//	{
	//		list *entry = win->parent->children.NEXT;
	//		if (!(win->style & VS_TOPMOST))
	//		{
	//			while (entry != &win->parent->children)
	//			{
	//				visual *next = LIST_ENTRY(entry, struct visual, entry);
	//				if (!(next->style & VS_TOPMOST)) break;
	//				if (next->owner == win->owner)
	//				{
	//					win->style |= VS_TOPMOST;
	//					break;
	//				}
	//				entry = entry->NEXT;
	//			}
	//		}
	//		LIST_ADD_BEFORE(entry, &win->entry);
	//	}
	//	else
	//	{
	//		LIST_ADD_AFTER(&previous->entry, &win->entry);
	//		if (!(previous->style & VS_TOPMOST))
	//			win->style &= ~VS_TOPMOST;
	//		else
	//		{
	//			visual *next = get_next_window(win);
	//			if (next && (next->style & VS_TOPMOST))
	//				win->style |= VS_TOPMOST;
	//		}
	//	}
	//}
	//BOOL TinyVisual::is_visible(const  visual *win)
	//{
	//	while (win)
	//	{
	//		if (!(win->style & VS_VISIBLE)) return FALSE;
	//		win = win->parent;
	//		if (win && (win->style & VS_MINIMIZE)) return FALSE;
	//	}
	//	return TRUE;
	//}
	//BOOL TinyVisual::is_child_window(visual *parent, visual *child)
	//{
	//	if (!parent || !child) return FALSE;
	//	while (child->parent)
	//	{
	//		if (child->parent == parent)
	//			return TRUE;
	//		child = child->parent;
	//	}
	//	return FALSE;
	//}
	//inline BOOL TinyVisual::is_point_in_window(visual *win, INT x, INT y)
	//{
	//	if (!(win->style & VS_VISIBLE))
	//		return FALSE;
	//	POINT pos = { x, y };
	//	if (!PtInRect(&win->visible_rectangle, pos))
	//		return FALSE;
	//	if (win->window_region != NULL && !PtInRegion(win->window_region, x, y))
	//		return FALSE;
	//	return TRUE;
	//}
	//visual *TinyVisual::child_window_by_point(visual *parent, INT x, INT y)
	//{
	//	struct visual *ps = NULL;
	//	POINT pt = { x, y };
	//	LIST_FOR_EACH_ENTRY(ps, &parent->children, visual, entry)
	//	{
	//		if (is_point_in_window(ps, x, y)) return ps;
	//		return child_window_by_point(ps, x, y);
	//	}
	//	return parent;
	//}
	//inline BOOL TinyVisual::is_desktop_window(const  visual *win)
	//{
	//	return !win->parent;
	//}
	//////////////////////////////////////////////////////////////////////////
	TinyVisual::TinyVisual()
		:m_window_region(NULL)
	{
		SetRectEmpty(&m_window_rectangle);
		SetRectEmpty(&m_visible_rectangle);
	}
	TinyVisual* TinyVisual::New(TinyVisual* parent, INT x, INT y, INT cx, INT cy)
	{
		TinyVisual* ps = new TinyVisual();
		SetRect(&ps->m_visible_rectangle, x, y, x + cx, y + cy);
		SetRect(&ps->m_window_rectangle, x, y, x + cx, y + cy);
		ps->m_style = VS_VISIBLE;
		ps->m_alpha = 255;
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
	void TinyVisual::SetVisualPos(INT x, INT y, INT cx, INT cy, UINT fFlag)
	{

	}
	BOOL TinyVisual::SetParent(TinyVisual* parent)
	{
		return TRUE;
	}
	void TinyVisual::GetRectangle(RECT& rect)
	{
		CopyRect(&m_window_rectangle, &rect);
	}
	void TinyVisual::SetName(LPCSTR pzName)
	{
		strcpy_s(m_name, 150, pzName);
	}
	LPCSTR	TinyVisual::GetName()
	{
		return m_name;
	}
	TinyVisual* TinyVisual::FindVisual(TinyVisual* val, POINT pos)
	{
		return NULL;
	}
}
