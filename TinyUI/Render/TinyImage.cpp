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
		:m_hBitmap(NULL),
		m_cx(0),
		m_cy(0),
		m_comp(0)
	{

	}
	TinyImage::operator HBITMAP() const
	{
		return m_hBitmap;
	}
	TinyImage::~TinyImage()
	{
		if (m_hBitmap != NULL)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
		}
	}
	BOOL TinyImage::Load(LPCSTR pz)
	{
		ASSERT(pz);
		FILE* pFile = NULL;
		pFile = fopen(pz, "rb");
		if (pFile == NULL)
		{
			return FALSE;
		}
		//解码出来的数据是RGBA
		BYTE* ps = stbi_load_from_file(pFile, &m_cx, &m_cy, &m_comp, 4);
		fclose(pFile);
		if (ps == NULL)
		{
			return FALSE;
		}
		BITMAPINFO bmi;
		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = m_cx;
		bmi.bmiHeader.biHeight = -m_cy;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = m_comp * 8;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = ((((bmi.bmiHeader.biBitCount * m_cx) + 31) / 32) * 4) * m_cy;
		BYTE* pvBits = NULL;
		m_hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
		for (INT i = 0; i < m_cx * m_cy; i++)
		{
			if (m_comp == 3)
			{
				pvBits[i * 3] = (BYTE)(DWORD(ps[i * 4 + 2])*ps[i * 4 + 3] / 255);
				pvBits[i * 3 + 1] = (BYTE)(DWORD(ps[i * 4 + 1])*ps[i * 4 + 3] / 255);
				pvBits[i * 3 + 2] = (BYTE)(DWORD(ps[i * 4])*ps[i * 4 + 3] / 255);
			}
			else if (m_comp == 4)
			{
				pvBits[i * 4 + 3] = ps[i * 4 + 3];//A
				if (pvBits[i * 4 + 3] < 255)
				{
					pvBits[i * 4] = (BYTE)(DWORD(ps[i * 4 + 2])*ps[i * 4 + 3] / 255);//B
					pvBits[i * 4 + 1] = (BYTE)(DWORD(ps[i * 4 + 1])*ps[i * 4 + 3] / 255);//G
					pvBits[i * 4 + 2] = (BYTE)(DWORD(ps[i * 4])*ps[i * 4 + 3] / 255);//R
				}
				else
				{
					pvBits[i * 4] = ps[i * 4 + 2];
					pvBits[i * 4 + 1] = ps[i * 4 + 1];
					pvBits[i * 4 + 2] = ps[i * 4];
				}
			}
		}
		stbi_image_free(ps);
		return m_hBitmap != NULL;
	}
	BOOL TinyImage::Load(BYTE* p, DWORD size)
	{
		ASSERT(p);
		INT x, y, comp;
		BYTE* ps = stbi_load_from_memory(p, size, &m_cx, &m_cy, &m_comp, 4);
		if (ps == NULL)
		{
			return FALSE;
		}
		BITMAPINFO bmi;
		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = m_cx;
		bmi.bmiHeader.biHeight = -m_cy;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = m_comp * 8;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = ((((m_comp * m_cx) + 31) / 32) * 4) * m_cy;
		BYTE* pvBits = NULL;
		m_hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
		for (INT i = 0; i < m_cx * m_cy; i++)
		{
			if (m_comp == 3)
			{
				pvBits[i * 3] = (BYTE)(DWORD(ps[i * 4 + 2])*ps[i * 4 + 3] / 255);
				pvBits[i * 3 + 1] = (BYTE)(DWORD(ps[i * 4 + 1])*ps[i * 4 + 3] / 255);
				pvBits[i * 3 + 2] = (BYTE)(DWORD(ps[i * 4])*ps[i * 4 + 3] / 255);
			}
			else if (m_comp == 4)
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
		}
		stbi_image_free(ps);
		return m_hBitmap != NULL;
	}
	TinySize TinyImage::GetSize()
	{
		return TinySize(m_cx, m_cy);
	}
}
