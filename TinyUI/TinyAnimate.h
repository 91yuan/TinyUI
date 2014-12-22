#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyAnimate :public TinyControl
	{
		DECLARE_DYNAMIC(TinyAnimate)
	public:
		TinyAnimate();
		virtual ~TinyAnimate();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, int x, int y, int cx, int cy);
		BOOL Open(_In_z_ LPCTSTR lpszFileName);
		BOOL Open(_In_ UINT nID);
		BOOL Play(_In_ UINT nFrom, _In_ UINT nTo, _In_ UINT nRep);
		BOOL Stop();
		BOOL Close();
		BOOL Seek(_In_ UINT nTo);
		BOOL IsPlaying() const;
	};
}


