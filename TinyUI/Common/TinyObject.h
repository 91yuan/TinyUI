#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	/// <summary>
	/// 对象基类
	/// </summary>
	class TINY_NO_VTABLE TinyObject
	{
	public:
		virtual LPCTSTR GetClassName() const = 0;//类型转化的名字
	};
#define DECLARE_DYNAMIC(class_name) \
public: \
	virtual LPCTSTR class_name::GetClassName() const \
	{ \
	return #class_name; \
	};
	
};

