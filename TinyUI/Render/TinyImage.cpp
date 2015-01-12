#include "../stdafx.h"
#include "TinyImage.h"

namespace TinyUI
{
	extern "C"
	{
		extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp);
		extern unsigned char *stbi_load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp);
		extern void  stbi_image_free(void *retval_from_stbi_load);
	};

	TinyImage::TinyImage()
		:m_hBitmap(NULL)
	{

	}
	TinyImage::~TinyImage()
	{
		if (m_hBitmap != NULL)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
		}
	}
	BOOL TinyImage::Load(LPCSTR pz, INT req_comp)
	{
		ASSERT(pz);
		FILE* f = NULL;
		f = fopen(pz, "rb");
		if (f == NULL)
		{
			return FALSE;
		}
		INT x, y, cmp;
		BYTE* ps = stbi_load_from_file(f, &x, &y, &cmp, req_comp);
		fclose(f);
		if (ps == NULL)
		{
			return FALSE;
		}
		BITMAPINFO bmi;
		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = x;
		bmi.bmiHeader.biHeight = -y;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = cmp * 8;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = x * y * cmp;
		BYTE* pvBits = NULL;
		m_hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
		for (INT i = 0; i < x * y; i++)
		{
			pvBits[i * 4 + 3] = ps[i * 4 + 3];
			if (pvBits[i * 4 + 3] < 255)
			{
				pvBits[i * 4] = (BYTE)(DWORD(ps[i * 4 + 2])*ps[i * 4 + 3] / 255);
				pvBits[i * 4 + 1] = (BYTE)(DWORD(ps[i * 4 + 1])*ps[i * 4 + 3] / 255);
				pvBits[i * 4 + 2] = (BYTE)(DWORD(ps[i * 4])*ps[i * 4 + 3] / 255);
			}
			else
			{
				pvBits[i * 4] = ps[i * 4 + 2];
				pvBits[i * 4 + 1] = ps[i * 4 + 1];
				pvBits[i * 4 + 2] = ps[i * 4];
			}
		}
		memcpy(pvBits, ps, bmi.bmiHeader.biSizeImage);
		stbi_image_free(ps);
		return m_hBitmap != NULL;
	}
	BOOL TinyImage::Load(BYTE* data, DWORD size, INT req_comp)
	{
		ASSERT(data);
		INT x, y, comp;
		BYTE* ps = stbi_load_from_memory(data, size, &x, &y, &comp, req_comp);
		if (ps == NULL)
		{
			return FALSE;
		}
		BITMAPINFO bmi;
		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = x;
		bmi.bmiHeader.biHeight = -y;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = comp * 8;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = x * y * comp;
		BYTE* pvBits = NULL;
		m_hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
		memcpy(pvBits, ps, bmi.bmiHeader.biSizeImage);
		stbi_image_free(ps);
		return m_hBitmap != NULL;
	}
	void TinyImage::Render(TinyDC& dc, INT x, INT y, INT cx, INT cy)
	{
		TinyMenDC memDC(dc.Handle(), cx, cy);
		memDC.Render(x, y, cx, cy);
	}
	void TinyImage::Render(HDC hDC, INT x, INT y, INT cx, INT cy)
	{
		ASSERT(hDC);
		TinyMenDC memDC(hDC, cx, cy);
		memDC.Render(x, y, cx, cy);
	}
}
