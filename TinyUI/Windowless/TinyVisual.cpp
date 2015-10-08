#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		TinyVisual::TinyVisual()
			:m_parent(NULL)
		{
			memset(&m_bounds, 0, sizeof(RECT));
			memset(&m_client_bounds, 0, sizeof(RECT));
		}
		TinyVisual::~TinyVisual()
		{

		}
		void TinyVisual::SetVisible(BOOL vis)
		{
			if (vis != m_visible)
			{
				vis = m_visible;
				Layout();
			}
		}
		void TinyVisual::SetEnable(BOOL enable)
		{
			if (m_enable != enable)
			{
				m_enable = enable;
				Layout();
			}
		}
		BOOL TinyVisual::IsFocusable() const
		{
			return m_focusable && m_enable;
		}
		void TinyVisual::SetFocusable(BOOL focusable)
		{
			if (m_focusable != focusable)
			{
				m_focusable = focusable;
			}
		}
		
		BOOL TinyVisual::IsVisible() const
		{
			return this->m_visible;
		}
		BOOL TinyVisual::IsEnable() const
		{
			return this->m_enable;
		}
		void TinyVisual::Layout()
		{

		}
		RECT TinyVisual::GetBounds() const
		{
			return m_bounds;
		}
	}
}
