#include "../stdafx.h"
#include "TinyImage.h"
//#include "vld.h"

namespace TinyUI
{
	extern "C"
	{
		extern unsigned char	*stbi_load_from_memory_ex(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp, size_t* count);
		extern unsigned char	*stbi_load_from_file_ex(FILE *f, int *x, int *y, int *comp, int req_comp, size_t* count);
		extern void				stbi_image_free(void *retval_from_stbi_load);
	};

	TinyImage::TinyImage()
		:m_cx(0),
		m_cy(0),
		m_count(0),
		m_hBitmap(NULL)
	{

	}
	TinyImage::~TinyImage()
	{
		for (INT i = 0; i < m_images.GetSize(); i++)
		{
			SAFE_DELETE_OBJECT(m_images[i]);
		}
	}
	BOOL TinyImage::Load(LPCSTR pz)
	{
		FILE* pFile = NULL;
		if (fopen_s(&pFile, pz, "rb") || !pFile)
			return S_FALSE;
		//解码出来的数据是RGBA
		INT comp = 0;
		BYTE* pData = NULL;
		pData = stbi_load_from_file_ex(pFile, &m_cx, &m_cy, &comp, 4, &m_count);
		fclose(pFile);
		if (pData == NULL)
		{
			goto error;
		}
		if (m_count == 1)
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
				for (INT i = 0; i < m_cx * m_cy; i++)
				{
					pvBits[i * 4 + 3] = pData[i * 4 + 3];
					if (pvBits[i * 4 + 3] < 255)
					{
						pvBits[i * 4] = (BYTE)(DWORD(pData[i * 4 + 2])*pData[i * 4 + 3] / 255);//B
						pvBits[i * 4 + 1] = (BYTE)(DWORD(pData[i * 4 + 1])*pData[i * 4 + 3] / 255);//G
						pvBits[i * 4 + 2] = (BYTE)(DWORD(pData[i * 4])*pData[i * 4 + 3] / 255);//R
					}
					else
					{
						pvBits[i * 4] = pData[i * 4 + 2];
						pvBits[i * 4 + 1] = pData[i * 4 + 1];
						pvBits[i * 4 + 2] = pData[i * 4];
					}
				}
				m_images.Add(hBitmap);
			}
		}
		else
		{
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
		}
		stbi_image_free(pData);
		m_hBitmap = m_images.GetSize() == 0 ? NULL : m_images[0];
		return m_images.GetSize() == m_count ? S_OK : S_FALSE;
	error:
		stbi_image_free(pData);
		return S_FALSE;
	}
	BOOL TinyImage::Load(BYTE* p, DWORD size)
	{
		if (!p) return S_FALSE;
		INT comp = 0;
		BYTE* pData = stbi_load_from_memory_ex(p, size, &m_cx, &m_cy, &comp, 4, &m_count);
		if (!pData)
		{
			goto error;
		}
		if (m_count == 1)
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
				for (INT i = 0; i < m_cx * m_cy; i++)
				{
					pvBits[i * 4 + 3] = pData[i * 4 + 3];
					if (pvBits[i * 4 + 3] < 255)
					{
						pvBits[i * 4] = (BYTE)(DWORD(pData[i * 4 + 2])*pData[i * 4 + 3] / 255);//B
						pvBits[i * 4 + 1] = (BYTE)(DWORD(pData[i * 4 + 1])*pData[i * 4 + 3] / 255);//G
						pvBits[i * 4 + 2] = (BYTE)(DWORD(pData[i * 4])*pData[i * 4 + 3] / 255);//R
					}
					else
					{
						pvBits[i * 4] = pData[i * 4 + 2];
						pvBits[i * 4 + 1] = pData[i * 4 + 1];
						pvBits[i * 4 + 2] = pData[i * 4];
					}
				}
				m_images.Add(hBitmap);
			}
		}
		else
		{
			BYTE* seek = pData + m_count * 4 * m_cx * m_cy;
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
					m_delays.Add(*(UINT*)seek);
					seek += sizeof(UINT);
				}
			}
		}
		stbi_image_free(pData);
		m_hBitmap = m_images.GetSize() == 0 ? NULL : m_images[0];
		return m_images.GetSize() == m_count ? S_OK : S_FALSE;
	error:
		stbi_image_free(pData);
		return S_FALSE;
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
	size_t TinyImage::GetFrameCount()
	{
		return m_count;
	}
	HBITMAP	TinyImage::GetFrame(INT index)
	{
		if (index < 0 || index >= (INT)m_count)
		{
			return NULL;
		}
		return m_images[index];
	}
	INT	TinyImage::GetFrameDelay(INT index)
	{
		if (index < 0 || index >= (INT)m_count)
		{
			return -1;
		}
		return m_delays[index];
	}
	TinyImage::operator HBITMAP() const
	{
		return m_hBitmap;
	}
}
