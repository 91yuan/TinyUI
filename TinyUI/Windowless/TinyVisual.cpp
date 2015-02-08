#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	//TinyVisual::TinyVisual()
	//{

	//}

	//TinyVisual::~TinyVisual()
	//{
	//}
	//inline Visual* TinyVisual::GetNextVisual(Visual *val)
	//{
	//	LIST *ps = LIST_NEXT(&val->parent->children, &val->entry);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//inline Visual* TinyVisual::GetPrevVisual(Visual *val)
	//{
	//	LIST *ps = LIST_PREV(&val->parent->children, &val->entry);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//inline Visual* TinyVisual::GetFirstChild(Visual *val)
	//{
	//	LIST *ps = LIST_HEAD(&val->children);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}

	//inline Visual* TinyVisual::GetLastChild(Visual *val)
	//{
	//	LIST *ps = LIST_TAIL(&val->children);
	//	return ps ? LIST_ENTRY(ps, Visual, entry) : NULL;
	//}
	//void TinyVisual::LinkVisual(Visual* val, Visual* previous)
	//{
	//	//if (previous == WINPTR_NOTOPMOST)
	//	//{
	//	//	if (!(val->ex_style & WS_EX_TOPMOST) && val->is_linked)
	//	//	{
	//	//		return;
	//	//	}
	//	//	val->ex_style &= ~WS_EX_TOPMOST;
	//	//	previous = WINPTR_TOP;
	//	//}
	//	//LIST_REMOVE(&val->entry);
	//	//if (previous == WINPTR_BOTTOM)
	//	//{
	//	//	LIST_ADD_TAIL(&val->parent->children, &val->entry);
	//	//	val->ex_style &= ~WS_EX_TOPMOST;
	//	//}
	//	//else if (previous == WINPTR_TOPMOST)
	//	//{
	//	//	LIST_ADD_HEAD(&val->parent->children, &val->entry);
	//	//	val->ex_style |= WS_EX_TOPMOST;
	//	//}
	//	//else if (previous == WINPTR_TOP)
	//	//{
	//	//	LIST *entry = val->parent->children.NEXT;
	//	//	if (!(val->ex_style & WS_EX_TOPMOST))//在第一个非顶层窗口之前插入
	//	//	{
	//	//		while (entry != &val->parent->children)
	//	//		{
	//	//			Visual *next = LIST_ENTRY(entry, Visual, entry);
	//	//			if (!(next->ex_style & WS_EX_TOPMOST)) break;
	//	//			entry = entry->NEXT;
	//	//		}
	//	//	}
	//	//	LIST_ADD_BEFORE(entry, &val->entry);
	//	//}
	//	//else
	//	//{
	//	//	LIST_ADD_AFTER(&previous->entry, &val->entry);
	//	//	if (!(previous->ex_style & WS_EX_TOPMOST)) 
	//	//		val->ex_style &= ~WS_EX_TOPMOST;
	//	//	else
	//	//	{
	//	//		Visual *next = GetNextVisual(val);
	//	//		if (next && (next->ex_style & WS_EX_TOPMOST))
	//	//			val->ex_style |= WS_EX_TOPMOST;
	//	//	}
	//	//}
	//}
	//BOOL TinyVisual::SetParentVisual(Visual *val, Visual *parent)
	//{
	//	//Visual *ps = NULL;
	//	////避免重复设置父元素
	//	//for (ps = parent; ps; ps = ps->parent)
	//	//{
	//	//	if (ps == val)
	//	//		return FALSE;
	//	//}
	//	////没有设置父元素
	//	//if (parent != NULL)
	//	//{
	//	//	val->parent = parent;
	//	//	LinkVisual(val, WINPTR_TOP);
	//	//}
	//	//else//设置成顶层元素
	//	//{
	//	//	LIST_REMOVE(&val->entry);
	//	//	LIST_ADD_HEAD(&val->parent->unlinked, &val->entry);
	//	//}
	//	return TRUE;
	//}
	//BOOL TinyVisual::IsVisible(const Visual *val)
	//{
	//	while (val != NULL)
	//	{
	//		if (!(val->style & WS_VISIBLE)) return FALSE;
	//		val = val->parent;
	//		if (val && (val->style & WS_MINIMIZE)) return FALSE;
	//	}
	//	return TRUE;
	//}
}
