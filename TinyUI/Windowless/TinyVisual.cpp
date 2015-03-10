#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	//inline Visual* GetNextVisual(Visual *val)
	//{
	//	LIST *ps = LIST_NEXT(&val->parent->children, &val->entry);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//inline Visual* GetPrevVisual(Visual *val)
	//{
	//	LIST *ps = LIST_PREV(&val->parent->children, &val->entry);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//inline Visual* GetFirstChild(Visual *val)
	//{
	//	LIST *ps = LIST_HEAD(&val->children);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//inline Visual* GetLastChild(Visual *val)
	//{
	//	LIST *ps = LIST_TAIL(&val->children);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//inline BOOL IsTopMost(const Visual *val)
	//{
	//	return !val->parent;
	//}
	//inline BOOL IsVisible(const Visual *val)
	//{
	//	while (val != NULL)
	//	{
	//		if (!(val->style & VS_VISIBLE))
	//			return FALSE;
	//		val = val->parent;
	//		if (val && (val->style & VS_MINIMIZE))
	//			return FALSE;
	//	}
	//	return TRUE;
	//}
	//void LinkVisual(Visual *win, Visual *previous)
	//{
	//	if (previous == VISUAL_NOTOPMOST)
	//	{
	//		if (!(win->style & VS_TOPMOST) && win->islink)
	//			return;
	//		win->style &= ~VS_TOPMOST;
	//		previous = VISUAL_TOP;
	//	}
	//	//LIST_REMOVE(&win->entry);
	//	if (previous == VISUAL_BOTTOM)
	//	{
	//		LIST_ADD_TAIL(&win->parent->children, &win->entry);
	//		win->style &= ~VS_TOPMOST;
	//	}
	//	else if (previous == VISUAL_TOPMOST)
	//	{
	//		LIST_ADD_HEAD(&win->parent->children, &win->entry);
	//		win->style |= VS_TOPMOST;
	//	}
	//	else if (previous == VISUAL_TOP)
	//	{
	//		LIST *entry = win->parent->children.NEXT;
	//		if (!(win->style & VS_TOPMOST))
	//		{
	//			while (entry != &win->parent->children)
	//			{
	//				Visual *next = LIST_ENTRY(entry, Visual, entry);
	//				if (!(next->style & VS_TOPMOST))
	//					break;
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
	//			Visual *next = GetNextVisual(win);
	//			if (next && (next->style & VS_TOPMOST))
	//				win->style |= VS_TOPMOST;
	//		}
	//	}
	//}
	//BOOL SetParent(Visual* win, Visual* parent)
	//{
	//	Visual *ps = NULL;
	//	for (ps = parent; ps; ps = ps->parent)
	//	{
	//		if (ps == win)
	//		{
	//			return FALSE;
	//		}
	//	}
	//	if (parent != NULL)
	//	{
	//		//添加到第一个非TOPMOST节点之前
	//		win->parent = parent;
	//		LinkVisual(win, VISUAL_TOP);
	//	}
	//	else
	//	{
	//		LIST_REMOVE(&win->entry);
	//		LIST_ADD_HEAD(&win->parent->unlink, &win->entry);
	//		win->islink = FALSE;
	//	}
	//	return TRUE;
	//}
	//BOOL SetVisualPos(Visual* val, Visual* valAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags)
	//{
	//	INT visible = (val->style & WS_VISIBLE) || (uFlags & SWP_SHOWWINDOW);
	//	if (val->parent && !IsVisible(val->parent))
	//		visible = 0;
	//	return TRUE;
	//}
	//Visual* CreateVisual(Visual* parent)
	//{
	//	Visual* win = (Visual*)malloc(sizeof(Visual));
	//	win->parent = parent;
	//	win->region = NULL;
	//	win->islink = FALSE;
	//	win->style = 0;
	//	SetRectEmpty(&win->window_rectangle);
	//	SetRectEmpty(&win->visible_rectangle);
	//	LIST_INIT(&win->children);
	//	LIST_INIT(&win->unlink);
	//	if (parent != NULL)
	//	{
	//		LIST_ADD_HEAD(&parent->unlink, &win->entry);
	//	}
	//	else
	//	{
	//		LIST_INIT(&win->entry);
	//	}
	//	return win;
	//}
	//void DestoryVisual(Visual* win)
	//{
	//	while (!LIST_EMPTY(&win->children))
	//		DestoryVisual(LIST_ENTRY(LIST_HEAD(&win->children), Visual, entry));
	//	while (!LIST_EMPTY(&win->unlink))
	//		DestoryVisual(LIST_ENTRY(LIST_HEAD(&win->unlink), Visual, entry));
	//	LIST_REMOVE(&win->entry);
	//	SAFE_FREE(win);
	//}
	//////////////////////////////////////////////////////////////////////////
	TinyVisual::TinyVisual()
		:m_pParent(NULL),
		m_pNext(NULL),
		m_pPrev(NULL)
	{

	}
	TinyVisual::~TinyVisual()
	{
	}
}
