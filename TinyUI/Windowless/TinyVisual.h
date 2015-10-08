#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	namespace Windowless
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
			BOOL		IsFocusable() const;
			void		SetFocusable(BOOL focusable);
			RECT		GetBounds() const;
		public:
			virtual void Layout();
		protected:
			BOOL						m_visible;
			BOOL					    m_focusable;
			BOOL						m_enable;
			RECT						m_bounds;//相对于父元素的位置
			RECT						m_client_bounds;//坐标0,0,cx,cy的位置
			TinyString					m_name;
			TinyString					m_text;
			TinyVisual*					m_parent;
			TinyArray<TinyVisual*>		m_visuals;
		};
	}
}



