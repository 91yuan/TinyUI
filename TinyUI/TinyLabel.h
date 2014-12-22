#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyLabel :public TinyControl
	{
		DECLARE_DYNAMIC(TinyLabel)
	public:
		TinyLabel();
		virtual ~TinyLabel();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual BOOL Create(HWND hParent, int x, int y, int cx, int cy);
		HICON SetIcon(HICON hIcon);
		HICON GetIcon() const;
		HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
		HENHMETAFILE GetEnhMetaFile() const;
		HBITMAP SetBitmap(HBITMAP hBitmap);
		HBITMAP GetBitmap() const;
		HCURSOR SetCursor(HCURSOR hCursor);
		HCURSOR GetCursor();
	};
}

