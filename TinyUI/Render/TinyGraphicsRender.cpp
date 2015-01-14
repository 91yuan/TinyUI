#include "../stdafx.h"
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
	void TinyGraphicsRender::DrawAlpha(HDC hDstDC, const TinyRectangle& rectDst, HDC hSrcDC, const TinyRectangle& rectSrc, BYTE nOpacity)
	{
		BLENDFUNCTION pixelblend = { AC_SRC_OVER, 0, nOpacity, AC_SRC_ALPHA };
		AlphaBlend(hDstDC, rectSrc.left, rectDst.top, rectDst.Width(), rectDst.Height(), hSrcDC, rectSrc.left, rectSrc.top, rectSrc.Width(), rectSrc.Height(), pixelblend);
	}
	HBITMAP TinyGraphicsRender::CreateBitmap_24(const TinySize& size, void** pBits)
	{
		if (pBits != NULL)
		{
			*pBits = NULL;
		}

		if (size.cx <= 0 || size.cy == 0)
		{
			return NULL;
		}

		BITMAPINFO bi = { 0 };
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = size.cx;
		bi.bmiHeader.biHeight = size.cy;
		bi.bmiHeader.biSizeImage = 0;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 24;
		bi.bmiHeader.biCompression = BI_RGB;
		LPVOID pData = NULL;
		HBITMAP hbmp = ::CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, &pData, NULL, 0);
		if (pData != NULL && hbmp != NULL && pBits != NULL)
		{
			*pBits = pData;
		}
		return hbmp;
	}
	HBITMAP TinyGraphicsRender::CreateBitmap_24(HBITMAP bitmap)
	{
		if (bitmap == NULL)
		{
			return NULL;
		}

		BITMAP bmp;
		if (::GetObject(bitmap, sizeof (BITMAP), &bmp) == 0)
		{
			return NULL;
		}

		if (bmp.bmBits == NULL)
		{
			return NULL;
		}
		LPVOID lpBits = NULL;
		HBITMAP hBitmap = CreateBitmap_24(TinySize(bmp.bmWidth, bmp.bmHeight), &lpBits);
		if (hBitmap != NULL)
		{
			HDC hSrcDC = NULL;
			hSrcDC = CreateCompatibleDC(NULL);
			HBITMAP hOldSrc = (HBITMAP)SelectObject(hSrcDC, bitmap);
			if (hOldSrc != NULL)
			{
				HDC hDstDC = NULL;
				hDstDC = CreateCompatibleDC(NULL);
				HBITMAP hOldDst = (HBITMAP)SelectObject(hDstDC, hBitmap);
				if (hOldDst != NULL)
				{
					BitBlt(hDstDC, 0, 0, bmp.bmWidth, bmp.bmHeight, hSrcDC, 0, 0, SRCCOPY);
					SelectObject(hDstDC, hOldDst);
					SelectObject(hSrcDC, hOldSrc);
				}
				DeleteDC(hDstDC);
			}
			DeleteDC(hSrcDC);
		}
		return hBitmap;
	}
	HBITMAP TinyGraphicsRender::CreateBitmap_32(const TinySize& size, void** pBits)
	{
		if (pBits != NULL)
		{
			*pBits = NULL;
		}
		if (size.cx <= 0 || size.cy == 0)
		{
			return NULL;
		}
		BITMAPINFO bi = { 0 };
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = size.cx;
		bi.bmiHeader.biHeight = size.cy;
		bi.bmiHeader.biSizeImage = size.cx * abs(size.cy);
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 32;
		bi.bmiHeader.biCompression = BI_RGB;
		LPVOID pData = NULL;
		HBITMAP hBitmap = ::CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, &pData, NULL, 0);
		if (pData != NULL && hBitmap != NULL && pBits != NULL)
		{
			*pBits = pData;
		}
		return hBitmap;
	}
	HBITMAP TinyGraphicsRender::CreateBitmap_32(HBITMAP bitmap, COLORREF clrTransparent)
	{
		if (bitmap == NULL)
		{
			return NULL;
		}
		BITMAP bmp;
		if (::GetObject(bitmap, sizeof (BITMAP), &bmp) == 0)
		{
			return NULL;
		}
		if (bmp.bmBits == NULL)
		{
			return NULL;
		}
		LPVOID lpBits = NULL;
		HBITMAP hBitmap = CreateBitmap_32(TinySize(bmp.bmWidth, bmp.bmHeight), &lpBits);
		if (hBitmap != NULL)
		{
			DWORD nSizeImage = bmp.bmWidth * bmp.bmHeight;

			if (bmp.bmBitsPixel == 32)
			{
				memcpy(lpBits, bmp.bmBits, nSizeImage * 4);
			}
			else
			{
				HDC hSrcDC = NULL;
				hSrcDC = CreateCompatibleDC(NULL);
				HBITMAP hbmpSrc = (HBITMAP)SelectObject(hSrcDC, bitmap);
				if (hbmpSrc != NULL)
				{
					HDC hDstDC = NULL;
					hDstDC = CreateCompatibleDC(NULL);
					HBITMAP hbmpDst = (HBITMAP)SelectObject(hDstDC, hBitmap);

					BitBlt(hDstDC, 0, 0, bmp.bmWidth, bmp.bmHeight, hSrcDC, 0, 0, SRCCOPY);

					SelectObject(hDstDC, hbmpDst);
					SelectObject(hSrcDC, hbmpSrc);

					DeleteDC(hDstDC);

					COLORREF* pBits = (COLORREF*)lpBits;
					if (clrTransparent == -1)
					{
						for (DWORD i = 0; i < nSizeImage; i++)
						{
							*pBits |= 0xFF000000;
							pBits++;
						}
					}
					else
					{
						COLORREF clrTrans = RGB(GetBValue(clrTransparent), GetGValue(clrTransparent), GetRValue(clrTransparent));
						for (DWORD i = 0; i < nSizeImage; i++)
						{
							if (*pBits != clrTrans)
							{
								*pBits |= 0xFF000000;
							}
							else
							{
								*pBits = (COLORREF)0;
							}

							pBits++;
						}
					}
				}
				DeleteDC(hSrcDC);
			}
		}
		return hBitmap;
	}
}

