#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"
#include "TinyUtility.h"

namespace TinyUI
{
	namespace Windowless
	{

		/// <summary>
		/// ���ӻ�Ԫ�ػ���
		/// </summary>
		class TinyVisual : public TinyObject
		{
			DECLARE_DYNAMIC(TinyVisual);
			DISALLOW_COPY_AND_ASSIGN(TinyVisual);
		public:
			TinyVisual(TinyVisual* pOwner = NULL);
			virtual	~TinyVisual();
			BOOL		IsVisible() const;
			BOOL		IsEnable() const;
			void		SetVisible(BOOL	vis);
			void		SetEnable(BOOL enable);
		public:
			TinyString* GetAttribute(const TinyString& key);
			void		SetAttribute(const TinyString& key, const TinyString& value);
			BOOL		ParserAttributes();
			TinyString	ToStyle();
		public:
			virtual void Layout();
		protected:
			BOOL							m_visible;
			BOOL							m_enable;
			RECT							m_padding;//��ƫ����
			RECT							m_margin;//��ƫ����
			SIZE							m_size;//Ԫ�ش�С
			TinyMap<TinyString, TinyString> m_attrMap;//����ӳ��
			TinyString						m_style;
			TinyString						m_name;
			TinyVisual*						m_pOwner;
		};
	}
}



