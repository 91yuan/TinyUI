#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		TinyVisual::TinyVisual(TinyVisual* pOwner)
			:m_pOwner(pOwner)
		{
			m_style = "font-family:arial;color:red;font-size:20px;";
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
		BOOL TinyVisual::IsVisible() const
		{
			return this->m_visible;
		}
		BOOL TinyVisual::IsEnable() const
		{
			return this->m_enable;
		}

		TinyString*  TinyVisual::GetAttribute(const TinyString& key)
		{
			return m_attrMap.GetValue(key);
		}

		void TinyVisual::SetAttribute(const TinyString& key, const TinyString& value)
		{

		}
		BOOL TinyVisual::ParserAttributes()
		{
			if (!m_style.IsEmpty())
			{
				TinyArray<TinyString> _Array;
				m_style.Split(';', _Array);
				for (INT i = 0; i < _Array.GetSize(); i++)
				{
					TinyString str = _Array[i];
					TinyArray < TinyString > _Arrays;
					str.Split(':', _Arrays);
					if (_Arrays.GetSize() > 0)
					{
						m_attrMap.Add(_Arrays[0], _Arrays[1]);
					}
				}
				return TRUE;
			}
			return FALSE;
		}
		void TinyVisual::Layout()
		{

		}
	}
}
