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
	private:
		TinyDC&	m_dc;
	};
}


