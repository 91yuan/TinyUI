#include "stdafx.h"
#include "TinyGraphicsRender.h"

namespace TinyUI
{
	TinyGraphicsRender::TinyGraphicsRender(TinyDC& dc)
		:m_dc(dc)
	{

	}


	TinyGraphicsRender::~TinyGraphicsRender()
	{

	}

	//HBITMAP TinyGraphicsRender::CreateBitmap_32(const TinySize& size, void** pBits)
	//{
	//	if (pBits != NULL)
	//	{
	//		*pBits = NULL;
	//	}

	//	if (size.cx <= 0 || size.cy == 0)
	//	{
	//		return NULL;
	//	}

	//	BITMAPINFO bi = { 0 };
	//	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//	bi.bmiHeader.biWidth = size.cx;
	//	bi.bmiHeader.biHeight = size.cy;
	//	bi.bmiHeader.biSizeImage = size.cx * abs(size.cy);
	//	bi.bmiHeader.biPlanes = 1;
	//	bi.bmiHeader.biBitCount = 32;
	//	bi.bmiHeader.biCompression = BI_RGB;

	//	LPVOID pData = NULL;
	//	HBITMAP hbmp = ::CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, &pData, NULL, 0);

	//	if (pData != NULL && hbmp != NULL && pBits != NULL)
	//	{
	//		*pBits = pData;
	//	}

	//	return hbmp;
	//}
	//HBITMAP TinyGraphicsRender::CreateBitmap_24(const TinySize& size, void** pBits)
	//{
	//	if (pBits != NULL)
	//	{
	//		*pBits = NULL;
	//	}

	//	if (size.cx <= 0 || size.cy == 0)
	//	{
	//		return NULL;
	//	}

	//	BITMAPINFO bi = { 0 };

	//	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//	bi.bmiHeader.biWidth = size.cx;
	//	bi.bmiHeader.biHeight = size.cy;
	//	bi.bmiHeader.biSizeImage = 0;
	//	bi.bmiHeader.biPlanes = 1;
	//	bi.bmiHeader.biBitCount = 24;
	//	bi.bmiHeader.biCompression = BI_RGB;

	//	LPVOID pData = NULL;
	//	HBITMAP hbmp = ::CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, &pData, NULL, 0);

	//	if (pData != NULL && hbmp != NULL && pBits != NULL)
	//	{
	//		*pBits = pData;
	//	}

	//	return hbmp;
	//}
	//HBITMAP TinyGraphicsRender::CreateBitmap_32(HBITMAP bitmap, COLORREF clrTransparent)
	//{
	//	if (bitmap == NULL)
	//	{
	//		return NULL;
	//	}

	//	BITMAP bmp;
	//	if (::GetObject(bitmap, sizeof(BITMAP), &bmp) == 0)
	//	{
	//		return NULL;
	//	}

	//	if (bmp.bmBits == NULL)
	//	{
	//		return NULL;
	//	}

	//	int nHeight = bmp.bmHeight;
	//	LPVOID lpBits = NULL;
	//	HBITMAP hbmp = CreateBitmap_32(TinySize(bmp.bmWidth, nHeight), &lpBits);
	//	nHeight = abs(nHeight);

	//	if (hbmp != NULL)
	//	{
	//		DWORD nSizeImage = bmp.bmWidth * nHeight;

	//		if (bmp.bmBitsPixel == 32)
	//		{
	//			memcpy(lpBits, bmp.bmBits, nSizeImage * 4);
	//		}
	//		else
	//		{
	//			TinyDC dcSrc;
	//			dcSrc.CreateCompatibleDC(NULL);
	//			HBITMAP hbmpSrc = (HBITMAP)dcSrc.SelectObject(bitmap);
	//			if (hbmpSrc != NULL)
	//			{
	//				TinyDC dcDst;
	//				dcDst.CreateCompatibleDC(NULL);
	//				HBITMAP hbmpDst = (HBITMAP)dcDst.SelectObject(hbmp);
	//				dcDst.BitBlt(0, 0, bmp.bmWidth, nHeight, &dcSrc, 0, 0, SRCCOPY);
	//				dcDst.SelectObject(hbmpDst);
	//				dcSrc.SelectObject(hbmpSrc);
	//				COLORREF* pBits = (COLORREF*)lpBits;
	//				if (clrTransparent == -1)
	//				{
	//					for (DWORD i = 0; i < nSizeImage; i++)
	//					{
	//						*pBits |= 0xFF000000;
	//						pBits++;
	//					}
	//				}
	//				else
	//				{
	//					COLORREF clrTrans = RGB(GetBValue(clrTransparent),
	//						GetGValue(clrTransparent),
	//						GetRValue(clrTransparent));
	//					for (DWORD i = 0; i < nSizeImage; i++)
	//					{
	//						if (*pBits != clrTrans)
	//						{
	//							*pBits |= 0xFF000000;
	//						}
	//						else
	//						{
	//							*pBits = (COLORREF)0;
	//						}

	//						pBits++;
	//					}
	//				}
	//			}
	//		}
	//	}

	//	return hbmp;
	//}
	//HBITMAP TinyGraphicsRender::CreateBitmap_24(HBITMAP bitmap)
	//{
	//	if (bitmap == NULL)
	//	{
	//		return NULL;
	//	}

	//	BITMAP bmp;
	//	if (::GetObject(bitmap, sizeof(BITMAP), &bmp) == 0)
	//	{
	//		return NULL;
	//	}

	//	if (bmp.bmBits == NULL)
	//	{
	//		return NULL;
	//	}

	//	int nHeight = bmp.bmHeight;
	//	LPVOID lpBits = NULL;
	//	HBITMAP hbmp = CreateBitmap_24(TinySize(bmp.bmWidth, nHeight), &lpBits);
	//	nHeight = abs(nHeight);

	//	if (hbmp != NULL)
	//	{
	//		TinyDC dcSrc;
	//		dcSrc.CreateCompatibleDC(NULL);
	//		HBITMAP hbmpSrc = (HBITMAP)dcSrc.SelectObject(bitmap);
	//		if (hbmpSrc != NULL)
	//		{
	//			TinyDC dcDst;
	//			dcDst.CreateCompatibleDC(NULL);
	//			HBITMAP hbmpDst = (HBITMAP)dcDst.SelectObject(hbmp);
	//			dcDst.BitBlt(0, 0, bmp.bmWidth, nHeight, &dcSrc, 0, 0, SRCCOPY);
	//			dcDst.SelectObject(hbmpDst);
	//			dcSrc.SelectObject(hbmpSrc);
	//		}
	//	}
	//	return hbmp;
	//}
	//BOOL TinyGraphicsRender::GrayRect(TinyRectangle rect, int nPercentage, COLORREF clrTransparent, COLORREF clrDisabled)
	//{
	//	if (rect.Height() <= 0 || rect.Width() <= 0)
	//	{
	//		return TRUE;
	//	}
	//	int cx = rect.Width();
	//	int cy = rect.Height();

	//	TinyDC dcMem;
	//	if (!dcMem.CreateCompatibleDC(m_dc))
	//	{
	//		return FALSE;
	//	}

	//	TinyBitmap	bmpMem;
	//	if (!bmpMem.CreateCompatibleBitmap(m_dc, cx, cy))
	//	{
	//		return FALSE;
	//	}

	//	HBITMAP hOldBmp = dcMem.SelectObject(&bmpMem);
	//	if (hOldBmp == NULL)
	//	{
	//		return FALSE;
	//	}

	//	COLORREF* pBits = NULL;
	//	HBITMAP hmbpDib = CreateBitmap_32(TinySize(cx, cy), (LPVOID*)&pBits);

	//	if (hmbpDib == NULL || pBits == NULL)
	//	{
	//		return FALSE;
	//	}

	//	dcMem.SelectObject(hmbpDib);
	//	dcMem.BitBlt(0, 0, cx, cy, &m_dc, rect.left, rect.top, SRCCOPY);

	//	if (clrTransparent != (COLORREF)-1)
	//	{
	//		clrTransparent = RGB(GetBValue(clrTransparent), GetGValue(clrTransparent), GetRValue(clrTransparent));
	//	}

	//	if (clrDisabled == (COLORREF)-1)
	//	{
	//		clrDisabled = globalData.clrBtnHilite;
	//	}

	//	for (int pixel = 0; pixel < cx * cy; pixel++, *pBits++)
	//	{
	//		COLORREF color = (COLORREF)*pBits;
	//		if (color != clrTransparent)
	//		{
	//			double H, S, L;
	//			RGBtoHSL(color, &H, &S, &L);
	//			color = HLStoRGB_ONE(H, L, 0);

	//			if (nPercentage == -1)
	//			{
	//				*pBits = RGB_TO_RGBA(
	//					min(255, GetRValue(color) + ((GetBValue(clrDisabled) -
	//					GetRValue(color)) / 2)),
	//					min(255, GetGValue(color) + ((GetGValue(clrDisabled) -
	//					GetGValue(color)) / 2)),
	//					min(255, GetBValue(color) + ((GetRValue(clrDisabled) -
	//					GetBValue(color)) / 2)));
	//			}
	//			else
	//			{
	//				*pBits = CLR_TO_RGBA(PixelAlpha(color, .01 * nPercentage, .01 * nPercentage, .01 * nPercentage));
	//			}
	//		}
	//	}

	//	//-------------------------------------------
	//	// Copy highligted bitmap back to the screen:
	//	//-------------------------------------------
	//	m_dc.BitBlt(rect.left, rect.top, cx, cy, &dcMem, 0, 0, SRCCOPY);

	//	dcMem.SelectObject(hOldBmp);
	//	DeleteObject(hmbpDib);

	//	return TRUE;
	//}
	//COLORREF TinyGraphicsRender::PixelAlpha(COLORREF srcPixel, int percent)
	//{
	//	COLORREF clrFinal = RGB(min(255, (GetRValue(srcPixel) * percent) / 100),
	//		min(255, (GetGValue(srcPixel) * percent) / 100),
	//		min(255, (GetBValue(srcPixel) * percent) / 100));
	//	return (clrFinal);
	//}
	//static inline int AdjustChannel(int nValue, double nPercent)
	//{
	//	int nNewValue = (int)(.5 + nPercent * nValue);
	//	if (nValue == 0 && nPercent > 1.)
	//	{
	//		nNewValue = (int)(.5 + (nPercent - 1.) * 255);
	//	}

	//	return min(nNewValue, 255);
	//}
	//COLORREF TinyGraphicsRender::PixelAlpha(COLORREF srcPixel, double percentR, double percentG, double percentB)
	//{
	//	COLORREF clrFinal = RGB(AdjustChannel(GetRValue(srcPixel), percentR),
	//		AdjustChannel(GetGValue(srcPixel), percentG),
	//		AdjustChannel(GetBValue(srcPixel), percentB));

	//	return (clrFinal);

	//}
	//COLORREF TinyGraphicsRender::PixelAlpha(COLORREF srcPixel, COLORREF dstPixel, int percent)
	//{
	//	int ipercent = 100 - percent;
	//	COLORREF clrFinal = RGB((GetRValue(srcPixel) * percent + GetRValue(dstPixel) * ipercent) / 100,
	//		(GetGValue(srcPixel) * percent + GetGValue(dstPixel) * ipercent) / 100,
	//		(GetBValue(srcPixel) * percent + GetBValue(dstPixel) * ipercent) / 100);
	//	return (clrFinal);
	//}
	//void TinyGraphicsRender::SetPixel(COLORREF* pBits, int cx, int cy, int x, int y, COLORREF color)
	//{
	//	y = cy - y;
	//	int nOffset = cx * y + x;
	//	if (nOffset < cx * cy)
	//	{
	//		COLORREF* pColor = (COLORREF*)(pBits + nOffset);
	//		*pColor = RGB(GetBValue(color), GetGValue(color), GetRValue(color));
	//	}
	//}
	//double TinyGraphicsRender::HuetoRGB(double m1, double m2, double h)
	//{
	//	if (h < 0) h += 1.0;
	//	if (h > 1) h -= 1.0;
	//	if (6.0*h < 1)
	//		return (m1 + (m2 - m1)*h*6.0);
	//	if (2.0*h < 1)
	//		return m2;
	//	if (3.0*h < 2.0)
	//		return (m1 + (m2 - m1)*((2.0 / 3.0) - h)*6.0);
	//	return m1;
	//}
	//BYTE TinyGraphicsRender::HueToRGB(float rm1, float rm2, float rh)
	//{
	//	if (rh > 360.0f)
	//		rh -= 360.0f;
	//	else if (rh < 0.0f)
	//		rh += 360.0f;

	//	if (rh < 60.0f)
	//		rm1 = rm1 + (rm2 - rm1) * rh / 60.0f;
	//	else if (rh < 180.0f)
	//		rm1 = rm2;
	//	else if (rh < 240.0f)
	//		rm1 = rm1 + (rm2 - rm1) * (240.0f - rh) / 60.0f;

	//	return static_cast<BYTE>(rm1 * 255);
	//}
	//COLORREF TinyGraphicsRender::HLStoRGB_ONE(double H, double L, double S)
	//{
	//	double r, g, b;
	//	double m1, m2;

	//	if (S == 0) {
	//		r = g = b = L;
	//	}
	//	else {
	//		if (L <= 0.5)
	//			m2 = L*(1.0 + S);
	//		else
	//			m2 = L + S - L*S;
	//		m1 = 2.0*L - m2;
	//		r = HuetoRGB(m1, m2, H + 1.0 / 3.0);
	//		g = HuetoRGB(m1, m2, H);
	//		b = HuetoRGB(m1, m2, H - 1.0 / 3.0);
	//	}
	//	return RGB((BYTE)(r * 255), (BYTE)(g * 255), (BYTE)(b * 255));
	//}

	//COLORREF TinyGraphicsRender::HLStoRGB_TWO(double H, double L, double S)
	//{
	//	WORD R, G, B;

	//	if (S == 0.0)
	//		R = G = B = unsigned char(L * 255.0);
	//	else
	//	{
	//		float rm1, rm2;

	//		if (L <= 0.5f)
	//			rm2 = (float)(L + L * S);
	//		else
	//			rm2 = (float)(L + S - L * S);

	//		rm1 = (float)(2.0f * L - rm2);

	//		R = HueToRGB(rm1, rm2, (float)(H + 120.0f));
	//		G = HueToRGB(rm1, rm2, (float)(H));
	//		B = HueToRGB(rm1, rm2, (float)(H - 120.0f));
	//	}

	//	return RGB(R, G, B);
	//}

	//double TinyGraphicsRender::MakeHue_ONE(double H)
	//{
	//	H -= (int)(H);
	//	if (H < 0.0)
	//	{
	//		H += 1.0;
	//	}

	//	return H;
	//}

	//double TinyGraphicsRender::MakeHue_TWO(double H)
	//{
	//	return MakeHue_ONE(H / 360.0) * 360.0;
	//}

	//void TinyGraphicsRender::RGBtoHSL(COLORREF rgb, double *H, double *S, double *L)
	//{
	//	double delta;
	//	double r = (double)GetRValue(rgb) / 255;
	//	double g = (double)GetGValue(rgb) / 255;
	//	double b = (double)GetBValue(rgb) / 255;
	//	double cmax = max(r, max(g, b));
	//	double cmin = min(r, min(g, b));
	//	*L = (cmax + cmin) / 2.0;

	//	if (cmax == cmin)
	//	{
	//		*S = 0;
	//		*H = 0;
	//	}
	//	else
	//	{
	//		if (*L < 0.5)
	//			*S = (cmax - cmin) / (cmax + cmin);
	//		else
	//			*S = (cmax - cmin) / (2.0 - cmax - cmin);

	//		delta = cmax - cmin;
	//		if (r == cmax)
	//			*H = (g - b) / delta;
	//		else if (g == cmax)
	//			*H = 2.0 + (b - r) / delta;
	//		else
	//			*H = 4.0 + (r - g) / delta;
	//		*H /= 6.0;
	//		if (*H < 0.0)
	//			*H += 1;
	//	}
	//}

	//void TinyGraphicsRender::RGBtoHSV(COLORREF rgb, double *H, double *S, double *V)
	//{
	//	double r = (double)GetRValue(rgb) / 255;
	//	double g = (double)GetGValue(rgb) / 255;
	//	double b = (double)GetBValue(rgb) / 255;

	//	double dblMin = min(r, min(g, b));
	//	double dblMax = max(r, max(g, b));

	//	*V = dblMax;
	//	double delta = dblMax - dblMin;

	//	if (dblMax != 0)
	//		*S = delta / dblMax;
	//	else
	//	{
	//		*S = 0;
	//		*H = -1;
	//		return;
	//	}

	//	if (delta == 0.)
	//	{
	//		*H = 1;
	//	}
	//	else
	//	{
	//		if (r == dblMax)
	//			*H = (g - b) / delta;
	//		else if (g == dblMax)
	//			*H = 2 + (b - r) / delta;
	//		else
	//			*H = 4 + (r - g) / delta;
	//	}

	//	*H *= 60;

	//	if (*H < 0)
	//		*H += 360;
	//}

	//COLORREF TinyGraphicsRender::HSVtoRGB(double h, double s, double v)
	//{
	//	int i;
	//	double f, p, q, t;
	//	double r, g, b;

	//	if (s == 0)
	//	{
	//		r = g = b = v;
	//	}
	//	else
	//	{
	//		h /= 60;
	//		i = (int)floor(h);
	//		f = h - i;
	//		p = v * (1 - s);
	//		q = v * (1 - s * f);
	//		t = v * (1 - s * (1 - f));

	//		switch (i)
	//		{
	//		case 0:
	//			r = v;
	//			g = t;
	//			b = p;
	//			break;
	//		case 1:
	//			r = q;
	//			g = v;
	//			b = p;
	//			break;
	//		case 2:
	//			r = p;
	//			g = v;
	//			b = t;
	//			break;
	//		case 3:
	//			r = p;
	//			g = q;
	//			b = v;
	//			break;
	//		case 4:
	//			r = t;
	//			g = p;
	//			b = v;
	//			break;
	//		default:
	//			r = v;
	//			g = p;
	//			b = q;
	//			break;
	//		}
	//	}
	//	return RGB(
	//		(int)(.5 + r * 255),
	//		(int)(.5 + g * 255),
	//		(int)(.5 + b * 255));
	//}
	//COLORREF TinyGraphicsRender::SmartMixColors(COLORREF color1, COLORREF color2, double dblLumRatio, int k1, int k2)
	//{
	//	ASSERT(k1 >= 0);
	//	ASSERT(k2 >= 0);

	//	if (k1 + k2 == 0)
	//	{
	//		ASSERT(FALSE);
	//		return RGB(0, 0, 0);
	//	}

	//	COLORREF color = RGB(
	//		min(255, (GetRValue(color1) * k1 + GetRValue(color2) * k2) / (k1 + k2)),
	//		min(255, (GetGValue(color1) * k1 + GetGValue(color2) * k2) / (k1 + k2)),
	//		min(255, (GetBValue(color1) * k1 + GetBValue(color2) * k2) / (k1 + k2)));

	//	double h1, s1, v1;
	//	RGBtoHSV(color, &h1, &s1, &v1);

	//	double h2, s2, v2;
	//	RGBtoHSV(color2, &h2, &s2, &v2);

	//	v1 = v2;
	//	s1 = (s1 *  k1 + s2 *  k2) / (k1 + k2);

	//	color = HSVtoRGB(h1, s1, v1);

	//	if (dblLumRatio != 1.)
	//	{
	//		double H, S, L;
	//		RGBtoHSL(color, &H, &S, &L);

	//		color = HLStoRGB_ONE(H, min(1., L * dblLumRatio), S);
	//	}

	//	return color;
	//}
	//COLORREF TinyGraphicsRender::MixColors(COLORREF clr1, COLORREF clr2, double dblRatio)
	//{
	//	ASSERT(dblRatio >= 0.0f && dblRatio <= 1.0f);

	//	return RGB(
	//		min(255, GetRValue(clr1) + dblRatio * (GetRValue(clr2) - GetRValue(clr1))),
	//		min(255, GetGValue(clr1) + dblRatio * (GetGValue(clr2) - GetGValue(clr1))),
	//		min(255, GetBValue(clr1) + dblRatio * (GetBValue(clr2) - GetBValue(clr1)))
	//		);
	//}
	//void TinyGraphicsRender::DrawAlpha(TinyDC* pDstDC, const TinyRectangle& rectDst, TinyDC* pSrcDC, const TinyRectangle& rectSrc, BYTE nOpacity)
	//{
	//	BLENDFUNCTION pixelblend = { AC_SRC_OVER, 0, nOpacity, 1 };
	//	pDstDC->AlphaBlend(rectDst.left,
	//		rectDst.top,
	//		rectDst.Width(),
	//		rectDst.Height(),
	//		pSrcDC,
	//		rectSrc.left,
	//		rectSrc.top,
	//		rectSrc.Width(),
	//		rectSrc.Height(),
	//		pixelblend);
	//}
}

