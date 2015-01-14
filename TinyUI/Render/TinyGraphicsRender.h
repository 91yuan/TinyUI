#pragma once
#include "TinyGraphics.h"
#include "stb_image.c"

namespace TinyUI
{
#define CLR_TO_RGBA(c) c | 0xFF000000
#define RGB_TO_RGBA(r, g, b) CLR_TO_RGBA(RGB(r, g, b))
#define _RGBA(r, g, b, a) RGB(r, g, b) | (a << 24)

	/// <summary>
	/// Render–Èª˘¿‡
	/// </summary>
	class TinyGraphicsRender
	{
	public:
		TinyGraphicsRender(TinyDC& dc);
		~TinyGraphicsRender();
		static void DrawAlpha(HDC hDstDC, const TinyRectangle& rectDst, HDC hSrcDC, const TinyRectangle& rectSrc, BYTE nOpacity = 255);
	private:
		static HBITMAP CreateBitmap_24(const TinySize& size, void** pBits);
		static HBITMAP CreateBitmap_24(HBITMAP bitmap);
		static HBITMAP CreateBitmap_32(const TinySize& size, void** pBits);
		static HBITMAP CreateBitmap_32(HBITMAP bitmap, COLORREF clrTransparent = -1);
	private:
		TinyDC&	m_dc;
	};
}


