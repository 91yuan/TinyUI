#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	/// <summary>
	/// �������
	/// </summary>
	class TINY_NO_VTABLE TinyObject
	{
	public:
		virtual LPCTSTR GetClassName() const = 0;//����ת��������
	};
#define DECLARE_DYNAMIC(class_name) \
public: \
	virtual LPCTSTR class_name::GetClassName() const \
	{ \
	return #class_name; \
	};
	
};

