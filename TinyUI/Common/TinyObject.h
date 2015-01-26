#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	/// <summary>
	/// �������
	/// </summary>
	class TinyObject
	{
	public:
		TinyObject();
		virtual ~TinyObject();
		TinyObject(const TinyObject& other);
		TinyObject& operator = (const TinyObject& other);
		void AddRef(const TinyObject& clone);
		void Release();
		/// <summary>
		/// ����ת��������
		/// </summary>
		virtual LPCTSTR GetClassName() const = 0;
	protected:
		/// <summary>
		/// ʹ�����ü���ǰ�����ȴ���
		/// </summary>
		virtual TinyReference* CreateReference() const;
		virtual TinyReference* CloneReference(const TinyReference* data) const;
	protected:
		TinyReference* m_reference;
	};
#define DECLARE_DYNAMIC(class_name) \
public: \
	virtual LPCTSTR class_name::GetClassName() const \
				{ \
	return #class_name; \
				};

};

