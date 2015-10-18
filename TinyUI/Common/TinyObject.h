#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
#define DECLARE_DYNAMIC(class_name) \
public: \
	virtual LPCTSTR class_name::GetClassName() const \
	{ \
	return #class_name; \
};
	/// <summary>
	/// 对象基类,不允许拷贝和赋值
	/// </summary>
	class TinyObject 
	{
		DISALLOW_COPY_AND_ASSIGN(TinyObject);
	public:
		TinyObject();
	public:
		virtual ~TinyObject();
		virtual LPCTSTR GetClassName() const = 0;
	};
};

