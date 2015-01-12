#include "../stdafx.h"
#include "TinyCommon.h"

namespace TinyUI
{
	void Trace(LPCTSTR lpszFormat, ...)
	{
		va_list args;
		va_start(args, lpszFormat);

		INT nBuf;
		TCHAR szBuffer[512];

#pragma warning(push)//保存当前的编译器警告状态
#pragma warning(disable : 4996)
		nBuf = _vsntprintf(szBuffer, ARRAYSIZE(szBuffer), lpszFormat, args);
#pragma warning(pop)//恢复原先的警告状态

		ASSERT(nBuf >= 0);

		OutputDebugString(szBuffer);

		va_end(args);
	}
	//////////////////////////////////////////////////////////////////////////
};
