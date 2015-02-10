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
	protected:
		TinyObject();
	public:
		virtual ~TinyObject();
		virtual LPCTSTR GetClassName() const = 0;
	public:
		void* WINAPI operator new(size_t size);
		void* WINAPI operator new(size_t, void* ps);
		void WINAPI operator delete(void* ps);
		void WINAPI operator delete(void* ps, void* place);
#if defined(_DEBUG)
		void* WINAPI operator new(size_t size, LPCSTR pzFile, INT line);
		void WINAPI operator delete(void *ps, LPCSTR pzFile, INT line);
#endif
		DISALLOW_COPY_AND_ASSIGN(TinyObject);
	};
};

