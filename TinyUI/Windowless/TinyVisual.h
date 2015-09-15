#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
#define BEGIN_attribute

	class TinyVisual;
	class TinyVisualRoot;
	/// <summary>
	/// 可视化元素
	/// </summary>
	class TinyVisual
	{
		DISALLOW_COPY_AND_ASSIGN(TinyVisual);
	public:
		TinyVisual();
		~TinyVisual();
		BOOL	Create(TinyVisual* pParent, INT x, INT y, INT cx, INT cy, DWORD dwStyle);
		BOOL	IsVisible() const;
		BOOL	IsEnable() const;
		void	SetStyle(DWORD dwStyle);
		DWORD	GetStyle() const;
		TinyVisual*	GetParent();
	public:
		BOOL	Add(TinyVisual* ps);
		BOOL	Remove(TinyVisual* ps);
		void	RemoveAll();
	public:
		virtual void Layout();
	protected:
		DWORD						m_dwStyle;
		RECT						m_bounds;
		TinyString					m_name;
		TinyString					m_text;
		TinyVisual*					m_pParent;
		TinyVisual*					m_pChildren;
		TinyVisual*					m_pNext;
		TinyVisual*					m_pPrev;
		TinyLinkList<TinyVisual*>	m_visuals;
	};
}



