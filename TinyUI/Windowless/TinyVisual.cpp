#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		TinyVisual::TinyVisual(TinyVisual* pOwner)
			:m_pOwner(pOwner)
		{

		}
		TinyVisual::~TinyVisual()
		{

		}
		const TinyString& TinyVisual::name() const
		{
			return m_name;
		}
		void TinyVisual::SetName(const TinyString& name)
		{
			m_name = name;
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

		void TinyVisual::SetAttribute(const TinyString& key, TinyString& value)
		{
			m_attrMap.SetAt(key, value);
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
		TinyString	TinyVisual::ToStyle()
		{
			TinyString str;
			ITERATOR is = m_attrMap.First();
			while (is)
			{
				const TinyString* key = m_attrMap.GetKeyAt(is);
				const TinyString* value = m_attrMap.GetValueAt(is);
				str.Append(*key);
				str.Append(":");
				str.Append(*value);
				str.Append(";");
				is = m_attrMap.Next(is);
			}
			return str;
		}
		BOOL TinyVisual::BuildUI()
		{
			/*const TinyString* value = m_attrMap.GetValue(TinyUI::Windowless::Width);
			if (value) m_size.cx = atoi(value->STR());
			value = m_attrMap.GetValue(TinyUI::Windowless::Height);
			if (value) m_size.cy = atoi(value->STR());*/
			return FALSE;
		}
		void TinyVisual::Layout()
		{

		}
	}
}
