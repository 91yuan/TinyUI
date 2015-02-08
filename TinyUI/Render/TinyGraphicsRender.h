#pragma once
#include "TinyGraphics.h"
#include "stb_image.c"

namespace TinyUI
{
#define  HSLMAX   255   
#define  RGBMAX   255  
#define HSLUNDEFINED (HSLMAX*2/3)
	/// <summary>
	/// RGBtoHSL
	/// </summary>
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor)
	{
		BYTE R, G, B;
		BYTE H, L, S;
		BYTE cMax, cMin;
		WORD Rdelta, Gdelta, Bdelta;

		R = lRGBColor.rgbRed;
		G = lRGBColor.rgbGreen;
		B = lRGBColor.rgbBlue;

		cMax = max(max(R, G), B);
		cMin = min(min(R, G), B);
		L = (BYTE)((((cMax + cMin)*HSLMAX) + RGBMAX) / (2 * RGBMAX));

		if (cMax == cMin)
		{
			S = 0;
			H = HSLUNDEFINED;
		}
		else
		{
			if (L <= (HSLMAX / 2))
				S = (BYTE)((((cMax - cMin)*HSLMAX) + ((cMax + cMin) / 2)) / (cMax + cMin));
			else
				S = (BYTE)((((cMax - cMin)*HSLMAX) + ((2 * RGBMAX - cMax - cMin) / 2)) / (2 * RGBMAX - cMax - cMin));
			/* hue */
			Rdelta = (WORD)((((cMax - R)*(HSLMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin));
			Gdelta = (WORD)((((cMax - G)*(HSLMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin));
			Bdelta = (WORD)((((cMax - B)*(HSLMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin));

			if (R == cMax)
				H = (BYTE)(Bdelta - Gdelta);
			else if (G == cMax)
				H = (BYTE)((HSLMAX / 3) + Rdelta - Bdelta);
			else
				H = (BYTE)(((2 * HSLMAX) / 3) + Gdelta - Rdelta);

			if (H > HSLMAX) H -= HSLMAX;
		}

		RGBQUAD hsl = { L, S, H, 0 };
		return hsl;
	}
	/// <summary>
	/// HUEtoRGB
	/// </summary>
	FLOAT HUEtoRGB(FLOAT n1, FLOAT n2, FLOAT hue)
	{
		FLOAT rValue;

		if (hue > 360)
			hue = hue - 360;
		else if (hue < 0)
			hue = hue + 360;

		if (hue < 60)
			rValue = n1 + (n2 - n1)*hue / 60.0f;
		else if (hue < 180)
			rValue = n2;
		else if (hue < 240)
			rValue = n1 + (n2 - n1)*(240 - hue) / 60;
		else
			rValue = n1;

		return rValue;
	}
	/// <summary>
	/// HSLtoRGB
	/// </summary>
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor)
	{
		FLOAT h, s, l;
		FLOAT m1, m2;
		BYTE r, g, b;

		h = (FLOAT)lHSLColor.rgbRed * 360.0f / 255.0f;
		s = (FLOAT)lHSLColor.rgbGreen / 255.0f;
		l = (FLOAT)lHSLColor.rgbBlue / 255.0f;

		if (l <= 0.5) m2 = l * (1 + s);
		else m2 = l + s - l*s;

		m1 = 2 * l - m2;

		if (s == 0)
		{
			r = g = b = (BYTE)(l * 255.0f);
		}
		else
		{
			r = (BYTE)(HUEtoRGB(m1, m2, h + 120) * 255.0f);
			g = (BYTE)(HUEtoRGB(m1, m2, h) * 255.0f);
			b = (BYTE)(HUEtoRGB(m1, m2, h - 120) * 255.0f);
		}
		RGBQUAD rgb = { b, g, r, 0 };
		return rgb;
	}
	class TinyGraphicsRender;
	/// <summary>
	/// 裁剪区域
	/// </summary>
	class RenderClip
	{
		friend class TinyGraphicsRender;
	public:
		RenderClip(HDC hDC, TinyRgn& rgn);
		RenderClip(HDC hDC, TinyRectangle& rect);
		~RenderClip();
	private:
		HDC		m_hDC;
		HRGN	m_hRGN;
		HRGN	m_hClipRGN;
	};
	/// <summary>
	/// Render虚基类
	/// </summary>
	class TinyGraphicsRender
	{
	public:
		TinyGraphicsRender(TinyDC& dc);
		~TinyGraphicsRender();
		void DrawShadedRect(TinyRectangle& rect);
		/// <summary>
		/// 绘制直线
		/// </summary>
		void DrawLine(TinyPoint p0, TinyPoint p1);
	public:
		/// <summary>
		/// 裁剪DC
		/// </summary>
		static BOOL GenerateClip(RenderClip& clip);
		static HBITMAP CreateBitmap_24(const TinySize& size, void** pBits);
		static HBITMAP CreateBitmap_24(HBITMAP bitmap);
		static HBITMAP CreateBitmap_32(const TinySize& size, void** pBits);
		static HBITMAP CreateBitmap_32(HBITMAP bitmap, COLORREF clrTransparent = -1);
		static void DrawAlpha(HDC hDstDC, const TinyRectangle& rectDst, HDC hSrcDC, const TinyRectangle& rectSrc, BYTE nOpacity = 255);
	private:
		TinyDC&	m_dc;
	};
}


