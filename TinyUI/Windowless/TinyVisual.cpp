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
		POINT pos = { x, y };
		if (!PtInRect(&val->visible_rectangle, pos))
			return FALSE;
		if (val->region &&!PtInRegion(val->region, x, y))
			return FALSE;
		return TRUE;
	}
	inline BOOL TinyVisual::SetRegion(Visual *val, HRGN region, INT redraw)
	{
		if (redraw && !IsVisible(val))
			redraw = 0;
		return TRUE;
	}
	inline  Visual* TinyVisual::GetTopClippingVisual(Visual *val)
	{
		while (val->parent && !IsTop(val->parent))
			val = val->parent;
		return val;
	}
	BOOL TinyVisual::IntersectRegion(HRGN hRgn, Visual *val)
	{
		OffsetRgn(hRgn, -val->window_rectangle.left, -val->window_rectangle.top);
		if (!CombineRgn(hRgn, hRgn, val->region, RGN_AND)) return FALSE;
		OffsetRgn(hRgn, val->window_rectangle.left, val->window_rectangle.top);
		return TRUE;
	}
	BOOL TinyVisual::ClipChildren(Visual *parent, Visual *last, HRGN hRgn, INT offset_x, INT offset_y)
	{
		Visual *ps = NULL;
		HRGN hTmp = CreateRectRgn(0, 0, 0, 0);
		if (!hTmp) return NULL;
		LIST_FOR_EACH_ENTRY(ps, &parent->children, Visual, entry)
		{
			if (ps == last) break;
			if (!(ps->style & WS_VISIBLE)) continue;
			::SetRectRgn(hTmp, ps->visible_rectangle.left, ps->visible_rectangle.top, ps->visible_rectangle.right, ps->visible_rectangle.bottom);
			if (ps->region && !IntersectRegion(hTmp, ps))
			{
				SAFE_DELETE_OBJECT(hTmp);
				return FALSE;
			}
			OffsetRgn(hTmp, offset_x, offset_y);
			INT iRes = CombineRgn(hRgn, hRgn, hTmp, RGN_DIFF);
			if (iRes == ERROR || iRes == NULLREGION) break;
		}
		SAFE_DELETE_OBJECT(hTmp);
		return TRUE;
	}
	inline void MirrorRectangle(const RECT *client_rect, RECT *rect)
	{
		int width = client_rect->right - client_rect->left;
		int tmp = rect->left;
		rect->left = width - rect->right;
		rect->right = width - tmp;
	}

	inline INT IntersectRectangle(RECT *dst, const RECT *src1, const RECT *src2)
	{
		dst->left = max(src1->left, src2->left);
		dst->top = max(src1->top, src2->top);
		dst->right = min(src1->right, src2->right);
		dst->bottom = min(src1->bottom, src2->bottom);
		return (dst->left < dst->right && dst->top < dst->bottom);
	}

	HRGN TinyVisual::GetVisibleRegion(Visual* val, UINT flags)
	{
		HRGN hTmp = NULL;
		HRGN hRgn = NULL;
		if (!(hRgn = CreateRectRgn(0, 0, 0, 0))) return NULL;
		INT offset_x = 0;
		INT offset_y = 0;
		if (!IsVisible(val)) return NULL;
		if ((flags & DCX_PARENTCLIP) && val->parent && !IsTop(val->parent))
		{
			RECT dst = { 0 };
			IntersectRectangle(&dst, &val->window_rectangle, &val->client_rectangle);
			::SetRectRgn(hRgn, dst.left, dst.top, dst.right, dst.bottom);
			OffsetRgn(hRgn, -val->parent->client_rectangle.left, -val->parent->client_rectangle.top);
		}
		else if (flags & DCX_WINDOW)
		{
			::SetRectRgn(hRgn, val->visible_rectangle.left, val->visible_rectangle.top, val->visible_rectangle.right, val->visible_rectangle.bottom);
			if (val->region && !IntersectRegion(hRgn, val)) goto error;
		}
		else
		{
			RECT dst = { 0 };
			IntersectRectangle(&dst, &val->window_rectangle, &val->client_rectangle);
			::SetRectRgn(hRgn, dst.left, dst.top, dst.right, dst.bottom);
			if (val->region && !IntersectRegion(hRgn, val)) goto error;
		}
		if (flags & DCX_CLIPCHILDREN)
		{
			if (IsTop(val))
			{
				offset_x = offset_y = 0;
			}
			else
			{
				offset_x = val->client_rectangle.left;
				offset_y = val->client_rectangle.top;
			}
			if (!ClipChildren(val, NULL, hRgn, offset_x, offset_y)) goto error;
		}
		if (IsTop(val))
		{
			offset_x = offset_y = 0;
		}
		else
		{
			offset_x = val->window_rectangle.left;
			offset_y = val->window_rectangle.top;
		}
		if ((hTmp = CreateRectRgn(0, 0, 0, 0)) != NULL)
		{
			while (val->parent)
			{
				if ((val->style & VS_CLIPSIBLINGS) && !IsTop(val->parent))
				{
					if (!ClipChildren(val->parent, val, hRgn, 0, 0))
						goto error;
				}
				val = val->parent;
				if (!IsTop(val))
				{
					offset_x += val->client_rectangle.left;
					offset_y += val->client_rectangle.top;
					OffsetRgn(hRgn, val->client_rectangle.left, val->client_rectangle.top);
				}
				RECT dst = { 0 };
				IntersectRectangle(&dst, &val->window_rectangle, &val->client_rectangle);
				::SetRectRgn(hTmp, dst.left, dst.top, dst.right, dst.bottom);
				if (val->region && !IntersectRegion(hTmp, val)) goto error;
				INT iRes = CombineRgn(hRgn, hRgn, hTmp, RGN_AND);
				if (iRes == ERROR) goto error;
				if (iRes == NULLREGION) break;;
			}
			SAFE_DELETE_OBJECT(hTmp);
		}
		OffsetRgn(hRgn, -offset_x, -offset_y);
		return hRgn;
	error:
		SAFE_DELETE_OBJECT(hTmp);
		SAFE_DELETE_OBJECT(hRgn);
		return NULL;
	}
}
