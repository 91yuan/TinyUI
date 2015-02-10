#include "../stdafx.h"
#include "TinyObject.h"

namespace TinyUI
{
	inline void WINAPI TinyObject::operator delete(void* ps)
	{
		::operator delete(ps);
	};
	inline void WINAPI TinyObject::operator delete(void* ps, void*)
	{
		::operator delete(ps);
	};
	inline void* WINAPI TinyObject::operator new(size_t size)
	{
		return ::operator new(size);
	}
	inline void* WINAPI TinyObject::operator new(size_t, void* ps)
	{
		return ps;
	}
#if defined(_DEBUG)
	void* WINAPI TinyObject::operator new(size_t size, LPCSTR pzFile, INT line)
	{
		return _malloc_dbg(size, _NORMAL_BLOCK, pzFile, line);
	}

	void WINAPI TinyObject::operator delete(void *ps, LPCSTR pzFile, INT line)
	{
		_free_dbg(ps, _NORMAL_BLOCK);
	}
#endif

	TinyObject::TinyObject()
	{
	}
};
