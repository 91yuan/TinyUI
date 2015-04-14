#include "../stdafx.h"
#include "TinyTabBox.h"

namespace TinyUI
{
	void TinyTabItem::Render(TinyMemDC& dc)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	TinyTabBox::TinyTabBox()
	{

	}
	TinyTabBox::~TinyTabBox()
	{

	}
	BOOL TinyTabBox::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}

	LRESULT TinyTabBox::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return TRUE;
	}

	LRESULT TinyTabBox::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyTabBox::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	BOOL TinyTabBox::Add(TinyTabItem* ps)
	{
		ASSERT(ps);
		return m_tabs.Add(ps);
	}
	BOOL TinyTabBox::Remove(TinyTabItem* ps)
	{
		ASSERT(ps);
		return m_tabs.Remove(ps);
	}
	BOOL TinyTabBox::RemoveAt(INT index)
	{
		return m_tabs.RemoveAt(index);
	}
}