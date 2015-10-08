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
		/// ���ӻ�Ԫ��
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
			RECT						m_bounds;//����ڸ�Ԫ�ص�λ��
			RECT						m_client_bounds;//����0,0,cx,cy��λ��
			TinyString					m_name;
			TinyString					m_text;
			TinyVisual*					m_parent;
			TinyArray<TinyVisual*>		m_visuals;
		};
	}
}



