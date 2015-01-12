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
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		BOOL Open( LPCTSTR lpszFileName);
		BOOL Open( UINT nID);
		BOOL Play( UINT nFrom,  UINT nTo,  UINT nRep);
		BOOL Stop();
		BOOL Close();
		BOOL Seek( UINT nTo);
		BOOL IsPlaying() const;
	};
}


