// TinySmiley.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TinySmiley.h"
#include <exception>
using namespace std;
#pragma comment(lib, "Msimg32.lib")

extern const char SmileyGUID[] = "{B6AD5231-C3EA-4261-A9B6-C57CC720B4C6}";

extern LONG		g_cLocks;
extern HMODULE	g_hModule;
extern "C"
{
	extern unsigned char	*stbi_load_from_memory_ex(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp, size_t* count);
	extern unsigned char	*stbi_load_from_file_ex(FILE *f, int *x, int *y, int *comp, int req_comp, size_t* count);
	extern void				stbi_image_free(void *retval_from_stbi_load);
};
TinySmiley::TinySmiley()
:m_cx(0),
m_cy(0),
m_count(0),
m_cRef(1)
{

}
TinySmiley::~TinySmiley()
{
	//释放GDI资源
	size_t size = m_images.size();
	for (size_t i = 0; i < size; i++)
	{
		SAFE_DELETE_OBJECT(m_images[i]);
	}
}
HRESULT STDMETHODCALLTYPE TinySmiley::LoadStream(LPSTREAM pStm)
{
	if (!pStm) return S_FALSE;
	STATSTG pstatstg;
	if (FAILED(pStm->Stat(&pstatstg, 0)))
	{
		return S_FALSE;
	}
	INT comp = 0;
	BYTE* pData = NULL;
	//获得字节流大小
	BYTE* pv = new BYTE[(UINT)pstatstg.cbSize.QuadPart];
	if (!pv) return S_FALSE;
	ULONG bytesSaved = 0;
	if (FAILED(pStm->Read(pv, (LONG)pstatstg.cbSize.QuadPart, &bytesSaved)))
	{
		goto error;
	}
	pData = stbi_load_from_memory_ex(pv, (INT)pstatstg.cbSize.QuadPart, &m_cx, &m_cy, &comp, 4, &m_count);
	SAFE_DELETE_ARRAY(pv);
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
			m_images.push_back(hBitmap);
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
				m_images.push_back(hBitmap);
				m_delays.push_back(*(UINT*)seek);
				seek += sizeof(UINT);
			}
		}
	}
	stbi_image_free(pData);
	return m_images.size() == m_count ? S_OK : S_FALSE;
error:
	SAFE_DELETE_ARRAY(pv);
	stbi_image_free(pData);
	return S_FALSE;
}
HRESULT STDMETHODCALLTYPE TinySmiley::LoadFile(LPCSTR pszFilePath)
{
	FILE* pFile = NULL;
	if (fopen_s(&pFile, pszFilePath, "rb") || !pFile)
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
			m_images.push_back(hBitmap);
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
				m_images.push_back(hBitmap);
				m_delays.push_back(*(UINT*)p);
				p += sizeof(UINT);
			}
		}
	}
	stbi_image_free(pData);
	return m_images.size() == m_count ? S_OK : S_FALSE;
error:
	stbi_image_free(pData);
	return S_FALSE;
}
HRESULT STDMETHODCALLTYPE TinySmiley::SaveAs(LPSTREAM pStm)//默认保存第一帧到文件流
{
	if (!pStm) return S_FALSE;
	if (m_images.size() == 0) return S_FALSE;

	BITMAP bitmap = { 0 };
	if (!GetObject(m_images[0], sizeof(BITMAP), (LPSTR)&bitmap))
		return S_FALSE;
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = bitmap.bmBitsPixel;
	bi.biCompression = BI_RGB;
	DWORD size = bitmap.bmWidthBytes * bitmap.bmHeight;
	BITMAPFILEHEADER bfh = { 0 };
	bfh.bfType = 0x4d42;
	bfh.bfOffBits = min(14, sizeof(BITMAPFILEHEADER)) + sizeof(BITMAPINFOHEADER)+bi.biClrUsed * sizeof(RGBQUAD);
	bfh.bfSize = bfh.bfOffBits + bitmap.bmWidthBytes*bitmap.bmHeight;
	ULARGE_INTEGER libSize;
	libSize.LowPart = bfh.bfSize;
	pStm->SetSize(libSize);
	ULONG cbWritten = 0;
	pStm->Write(&bfh, min(14, sizeof(BITMAPFILEHEADER)), &cbWritten);
	pStm->Write(&bi, bi.biSize, &cbWritten);
	pStm->Write(bitmap.bmBits, bitmap.bmWidthBytes*bitmap.bmHeight, &cbWritten);
	return S_OK;
}
HRESULT STDMETHODCALLTYPE TinySmiley::GetFrameCount(INT *pFrameCount)
{
	*pFrameCount = m_count;
	return S_OK;
}
HRESULT STDMETHODCALLTYPE TinySmiley::GetFrameDelay(INT iFrame, UINT *pFrameDelay)
{
	if (iFrame >= 0 && iFrame < (INT)m_delays.size())
	{
		*pFrameDelay = m_delays[iFrame];
		return S_OK;
	}
	return S_FALSE;
}
HRESULT STDMETHODCALLTYPE TinySmiley::GetSize(LPSIZE pSize)
{
	pSize->cx = m_cx;
	pSize->cy = m_cy;
	return NOERROR;
}
HRESULT STDMETHODCALLTYPE TinySmiley::Draw(HDC hdc, LPCRECT pRect, INT iFrame)
{
	if (iFrame < 0 || iFrame >= (INT)m_count) return S_FALSE;
	HBITMAP hMenBmp = NULL;
	HDC hMenDC = NULL;
	RECT rect = *pRect;
	BLENDFUNCTION pixelblend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	hMenDC = CreateCompatibleDC(hdc);
	if (!hMenDC) goto error;
	hMenBmp = CreateCompatibleBitmap(hdc, TO_CX(rect), TO_CY(rect));
	if (!hMenBmp) goto error;
	HBITMAP hBmp = m_images[iFrame];
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMenDC, hBmp);
	AlphaBlend(hdc, rect.left, rect.top, TO_CX(rect), TO_CY(rect), hMenDC, 0, 0, m_cx, m_cy, pixelblend);
	SelectObject(hMenDC, hOldBmp);
	SAFE_DELETE_OBJECT(hMenBmp);
	SAFE_DELETE_OBJECT(hMenDC);
	return S_OK;
error:
	SAFE_DELETE_OBJECT(hMenBmp);
	SAFE_DELETE_OBJECT(hMenDC);
	return S_FALSE;
}
HRESULT STDMETHODCALLTYPE TinySmiley::QueryInterface(REFIID riid, void **ppvObject)
{
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ISmiley))
	{
		*ppvObject = this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return NOERROR;
}
ULONG STDMETHODCALLTYPE TinySmiley::AddRef(void)
{
	return InterlockedIncrement(&this->m_cRef);
}
ULONG STDMETHODCALLTYPE TinySmiley::Release(void)
{
	if (InterlockedDecrement(&this->m_cRef))
	{
		return this->m_cRef;
	}
	delete this;
	return NOERROR;
}
//////////////////////////////////////////////////////////////////////////
template<class T>
ClassFactory<T>::ClassFactory()
:m_cRef(1)
{

}
template<class T>
ClassFactory<T>::~ClassFactory()
{

}
template<class T>
HRESULT STDMETHODCALLTYPE ClassFactory<T>::CreateInstance(_In_opt_ IUnknown *pUnk, _In_ REFIID riid, _COM_Outptr_ void **ppvObject)
{
	HRESULT hRes = E_UNEXPECTED;
	if (pUnk != NULL) hRes = CLASS_E_NOAGGREGATION;
	else
	{
		T* p = NULL;
		if ((p = new T()) == NULL)
		{
			hRes = E_OUTOFMEMORY;
		}
		else
		{
			hRes = p->QueryInterface(riid, ppvObject);
			p->Release();
		}
	}
	return hRes;
}
template<class T>
HRESULT STDMETHODCALLTYPE ClassFactory<T>::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement((LONG*)&(g_cLocks));
	else
		InterlockedDecrement((LONG*)&(g_cLocks));
	return S_OK;
}
template<class T>
HRESULT STDMETHODCALLTYPE ClassFactory<T>::QueryInterface(REFIID riid, void **ppvObject)
{
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
	{
		*ppvObject = this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return NOERROR;
}
template<class T>
ULONG STDMETHODCALLTYPE ClassFactory<T>::AddRef(void)
{
	return InterlockedIncrement(&this->m_cRef);
}
template<class T>
ULONG STDMETHODCALLTYPE ClassFactory<T>::Release(void)
{
	if (InterlockedDecrement(&this->m_cRef))
	{
		return this->m_cRef;
	}
	delete this;
	return NOERROR;
}
//////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterServer(void)
{
	HKEY hkeyCLSID = NULL;
	LONG err;
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(g_hModule, szPath, MAX_PATH);
	err = ::RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hkeyCLSID);
	if (err == ERROR_SUCCESS) {
		HKEY hkeyOurs = NULL;
		err = ::RegCreateKey(hkeyCLSID, SmileyGUID, &hkeyOurs);
		if (err == ERROR_SUCCESS) {
			HKEY hkeyInproc = NULL;
			err = ::RegCreateKey(hkeyOurs, "InProcServer32", &hkeyInproc);
			if (err == ERROR_SUCCESS) {
				err = ::RegSetValueEx(hkeyInproc, NULL, 0, REG_SZ, (LPBYTE)szPath, lstrlen(szPath) + 1);
				::RegCloseKey(hkeyInproc);
			}
			::RegCloseKey(hkeyOurs);
		}
		::RegCloseKey(hkeyCLSID);
		if (err == ERROR_SUCCESS) {
			err = ::RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Smiley", &hkeyCLSID);
			if (err == ERROR_SUCCESS) {
				err = ::RegSetValueEx(hkeyCLSID, SmileyGUID, 0, REG_SZ, (LPBYTE)"", 2);
				::RegCloseKey(hkeyCLSID);
			}
		}
	}
	if (err == ERROR_SUCCESS)
		return S_OK;
	else
		return HRESULT_FROM_WIN32(err);
}
STDAPI DllUnregisterServer(void)
{
	HKEY hkeyCLSID = NULL;
	LONG err;
	err = ::RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hkeyCLSID);
	if (err == ERROR_SUCCESS) {
		HKEY hkeyOurs = NULL;
		err = ::RegOpenKey(hkeyCLSID, SmileyGUID, &hkeyOurs);
		if (err == ERROR_SUCCESS) {
			err = ::RegDeleteKey(hkeyOurs, "InProcServer32");
			::RegCloseKey(hkeyOurs);
		}
		::RegCloseKey(hkeyCLSID);
		if (err == ERROR_SUCCESS) {
			err = ::RegOpenKey(HKEY_LOCAL_MACHINE, "Software\\Smiley", &hkeyCLSID);
			if (err == ERROR_SUCCESS) {
				err = ::RegDeleteValue(hkeyCLSID, SmileyGUID);
				::RegCloseKey(hkeyCLSID);
			}
		}
	}
	if (err == ERROR_SUCCESS)
		return S_OK;
	else
		return HRESULT_FROM_WIN32(err);
}
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	if (IsEqualCLSID(rclsid, CLSID_Smiley))
	{
		ClassFactory<TinySmiley> *cf = new ClassFactory<TinySmiley>();
		return cf->QueryInterface(riid, ppv);
	}
	*ppv = NULL;
	return CLASS_E_CLASSNOTAVAILABLE;;
}
STDAPI DllCanUnloadNow(void)
{
	return g_cLocks == 0 ? S_OK : S_FALSE;
}
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	return S_OK;
}

