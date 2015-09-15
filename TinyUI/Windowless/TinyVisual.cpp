#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
		:parent_(NULL)
	{
		memset(&client_bounds_, 0, sizeof(RECT));
	}
	TinyVisual::~TinyVisual()
	{

	}
	void TinyVisual::SetVisible(BOOL vis)
	{
		if (vis != visible_)
		{
			vis = visible_;
			Layout();
		}
	}
	void TinyVisual::SetEnable(BOOL enable)
	{
		if (enable_ != enable)
		{
			enable_ = enable;
			Layout();
		}
	}
	BOOL TinyVisual::Add(TinyVisual* ps)
	{
		if (!ps) return FALSE;
		ps->parent_ = this;
		return this->visuals_.InsertLast(ps) != NULL;
	}
	BOOL TinyVisual::Remove(TinyVisual* ps)
	{
		if (!ps) return FALSE;
		ps->parent_ = NULL;
		return this->visuals_.RemoveAt((ITERATOR)ps);
	}
	void TinyVisual::RemoveAll()
	{
		this->visuals_.RemoveAll();
	}
	DWORD	TinyVisual::GetSize() const
	{
		return this->visuals_.GetSize();
	}
	BOOL TinyVisual::IsVisible() const
	{
		return this->visible_;
	}
	BOOL TinyVisual::IsEnable() const
	{
		return this->enable_;
	}
	void TinyVisual::Layout()
	{

	}
	RECT TinyVisual::GetBounds() const
	{
		return bounds_;
	}
}
