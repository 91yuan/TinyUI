#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	class TinyVisual;
	/// <summary>
	/// 可视化元素
	/// </summary>
	class TinyVisual : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisual);
		DISALLOW_COPY_AND_ASSIGN(TinyVisual);
	public:
		TinyVisual();
		~TinyVisual();
		BOOL		IsVisible() const;
		BOOL		IsEnable() const;
		void		SetVisible(BOOL	vis);
		void		SetEnable(BOOL enable);
		RECT		GetBounds() const;
	public:
		BOOL		Add(TinyVisual* ps);
		BOOL		Remove(TinyVisual* ps);
		void		RemoveAll();
		DWORD		GetSize() const;
	public:
		virtual void Layout();
	protected:
		BOOL						visible_;
		BOOL						enable_;
		RECT						bounds_;//客户端区域
		TinyString					name_;
		TinyString					text_;
		TinyVisual*					parent_;
		TinyLinkList<TinyVisual*>	visuals_;
	};
}



