#include "../stdafx.h"
#include "TinyImage.h"
#include "vld.h"

namespace TinyUI
{
	extern "C"
	{
		extern unsigned char	*stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp);
		extern unsigned char	*stbi_load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp);
		extern unsigned char	*stbi_load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp);
		extern unsigned char	*stbi_load_gif_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp, size_t* count);
		extern unsigned char	*stbi_load_gif_from_file(FILE *f, int *x, int *y, int *comp, int req_comp, size_t* count);
		extern void				stbi_image_free(void *retval_from_stbi_load);
	};

	TinyImage::TinyImage()
		:m_hBitmap(NULL),
		m_cx(0),
		m_cy(0)
	{

	}
	TinyImage::operator HBITMAP() const
	{
		return m_hBitmap;
	}
	TinyImage::~TinyImage()
	{
		SAFE_DELETE_OBJECT(m_hBitmap);
	}
	BOOL TinyImage::Load(LPCSTR pz)
	{
		ASSERT(pz);
		FILE* pFile = NULL;
		if (fopen_s(&pFile, pz, "rb") || !pFile)
			return FALSE;
		//解码出来的数据是RGBA
		INT comp = 0;
		BYTE* ps = stbi_load_from_file(pFile, &m_cx, &m_cy, &comp, 4);
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
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = m_cx * m_cy * 4;
		BYTE* pvBits = NULL;
		m_hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
		for (INT i = 0; i < m_cx * m_cy; i++)
		{
			pvBits[i * 4 + 3] = ps[i * 4 + 3];
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
		stbi_image_free(ps);
		return m_hBitmap != NULL;
	}
	BOOL TinyImage::Load(BYTE* p, DWORD size)
	{
		ASSERT(p);
		INT comp = 0;
		BYTE* ps = stbi_load_from_memory(p, size, &m_cx, &m_cy, &comp, 4);
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
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = m_cx * m_cy * 4;
		BYTE* pvBits = NULL;
		m_hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
		for (INT i = 0; i < m_cx * m_cy; i++)
		{
			pvBits[i * 4 + 3] = ps[i * 4 + 3];
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
		stbi_image_free(ps);
		return m_hBitmap != NULL;
	}
	TinySize TinyImage::GetSize()
	{
		return TinySize(m_cx, m_cy);
	}
	TinyRectangle TinyImage::GetRectangle()
	{
		return TinyRectangle(0, 0, m_cx, m_cy);
	}
	BOOL TinyImage::Save(LPCSTR pz)
	{
		return TRUE;
	}
	//////////////////////////////////////////////////////////////////////////
	TinyGIFDecode::TinyGIFDecode()
		:m_count(0)
	{

	}
	TinyGIFDecode::~TinyGIFDecode()
	{
		//释放HBITMAP
		for (INT i = 0; i < m_images.GetSize(); i++)
		{
			SAFE_DELETE_OBJECT(m_images[i]);
		}
	}
	BOOL TinyGIFDecode::Load(LPCSTR pz)
	{
		ASSERT(pz);
		FILE* pFile = NULL;
		if (fopen_s(&pFile, pz, "rb") || !pFile)
			return FALSE;
		//解码出来的数据是RGBA
		INT comp = 0;
		BYTE* pData = stbi_load_gif_from_file(pFile, &m_cx, &m_cy, &comp, 4, &m_count);
		fclose(pFile);
		if (pData == NULL)
		{
			return FALSE;
		}
		BYTE* p = pData + m_count * 4 * m_cx * m_cy;
		for (size_t i = 0; i < m_count; i++)
		{
			BYTE* ps = pData + i * 4 * m_cx * m_cy;
			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFO));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = m_cx;
			bmi.bmiHeader.biHeight = -m_cy;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage = m_cx * m_cy * 4;
			BYTE* pvBits = NULL;
			HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
			if (hBitmap)
			{
				for (INT i = 0; i < m_cx * m_cy; i++)
				{
					pvBits[i * 4 + 3] = ps[i * 4 + 3];
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
				m_images.Add(hBitmap);
				m_delays.Add(*(UINT*)p);
				p += sizeof(UINT);
			}
		}
		stbi_image_free(pData);
		return m_images.GetSize() == m_count;
	}
	BOOL TinyGIFDecode::Load(BYTE* pv, DWORD size)
	{
		ASSERT(pv);
		INT comp = 0;
		BYTE* pData = stbi_load_gif_from_memory(pv, size, &m_cx, &m_cy, &comp, 4, &m_count);
		if (pData == NULL)
		{
			return FALSE;
		}
		BYTE* p = pData + m_count * 4 * m_cx * m_cy;
		for (size_t i = 0; i < m_count; i++)
		{
			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFO));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = m_cx;
			bmi.bmiHeader.biHeight = -m_cy;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage = m_cx * m_cy * 4;
			BYTE* pvBits = NULL;
			HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
			if (hBitmap)
			{
				BYTE* ps = pData + i * m_cx * m_cy;
				for (INT i = 0; i < m_cx * m_cy; i++)
				{
					pvBits[i * 4 + 3] = ps[i * 4 + 3];
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
				m_images.Add(hBitmap);
				m_delays.Add(*(UINT*)p);
				p += sizeof(UINT);
			}
		}
		stbi_image_free(pData);
		return m_images.GetSize() == m_count;
	}
	size_t TinyGIFDecode::GetFrameCount()
	{
		return m_count;
	}
	TinySize TinyGIFDecode::GetSize()
	{
		return TinySize(m_cx, m_cy);
	}
	TinyRectangle	TinyGIFDecode::GetRectangle()
	{
		return TinyRectangle(0, 0, m_cx, m_cy);
	}
	UINT TinyGIFDecode::GetFrameDelay(INT index)
	{
		ASSERT(index >= 0 && index < m_images.GetSize());
		return m_delays[index];
	}
	HBITMAP	TinyGIFDecode::GetFrame(INT index)
	{
		ASSERT(index >= 0 && index < m_images.GetSize());
		return m_images[index];
	}
}
