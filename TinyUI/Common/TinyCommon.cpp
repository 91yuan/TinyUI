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

#pragma warning(push)//���浱ǰ�ı���������״̬
#pragma warning(disable : 4996)
		nBuf = _vsntprintf(szBuffer, ARRAYSIZE(szBuffer), lpszFormat, args);
#pragma warning(pop)//�ָ�ԭ�ȵľ���״̬

		ASSERT(nBuf >= 0);

		OutputDebugString(szBuffer);

		va_end(args);
	}
	//////////////////////////////////////////////////////////////////////////
};
