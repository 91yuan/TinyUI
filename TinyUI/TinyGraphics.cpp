#include "stdafx.h"
#include "TinyGraphics.h"
#include "TinyApplication.h"

namespace TinyUI
{
	BOOL TinyDC::CreateDC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const void* lpInitData)
	{
		HDC hDC = ::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData);
		return Attach(hDC);
	}
	BOOL TinyDC::CreateIC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const void* lpInitData)
	{
		HDC hDC = ::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData);
		return Attach(hDC);
	}
	BOOL TinyDC::CreateCompatibleDC(HDC hDC)
	{
		HDC hAttribDC = ::CreateCompatibleDC(hDC);
		return Attach(hAttribDC);
	}
	BOOL TinyDC::ResetDC(const DEVMODE* lpDevMode)
	{
		if (m_value == NULL)
			return FALSE;
		return ::ResetDC(m_value, lpDevMode) != NULL;
	}
	void TinyDC::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteDC(Detach());
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyPen::CreatePen(INT nPenStyle, INT nWidth, COLORREF crColor)
	{
		HPEN hPen = ::CreatePen(nPenStyle, nWidth, crColor);
		return Attach(hPen);
	}
	BOOL TinyPen::CreatePen(INT nPenStyle, INT nWidth, const LOGBRUSH* pLogBrush, INT nStyleCount, const DWORD* lpStyle)
	{
		HPEN hPen = ::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle);
		return Attach(hPen);
	}
	BOOL TinyPen::CreatePen(LPLOGPEN lpLogPen)
	{
		HPEN hPen = ::CreatePenIndirect(lpLogPen);
		return Attach(hPen);
	}
	INT TinyPen::GetExtLogPen(EXTLOGPEN* pLogPen)
	{
		ASSERT(m_value != NULL);
		return ::GetObject(m_value, sizeof(EXTLOGPEN), pLogPen);
	}
	INT TinyPen::GetLogPen(LOGPEN* pLogPen)
	{
		ASSERT(m_value != NULL);
		return ::GetObject(m_value, sizeof(LOGPEN), pLogPen);
	}
	void TinyPen::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
	TinyHandleMap<HPEN>* TinyPen::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHPEN());
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyBrush::CreateBrush(COLORREF crColor)
	{
		HBRUSH hBrush = ::CreateSolidBrush(crColor);
		return Attach(hBrush);
	}
	BOOL TinyBrush::CreateBrush(INT nIndex, COLORREF crColor)
	{
		HBRUSH hBrush = ::CreateHatchBrush(nIndex, crColor);
		return Attach(hBrush);
	}
	BOOL TinyBrush::CreateBrush(HBITMAP hBitmap)
	{
		ASSERT(hBitmap != NULL);
		HBRUSH hBrush = ::CreatePatternBrush(hBitmap);
		return Attach(hBrush);
	}
	BOOL TinyBrush::CreateBrush(const LOGBRUSH* lpLogBrush)
	{
		ASSERT(lpLogBrush != NULL);
		HBRUSH hBrush = ::CreateBrushIndirect(lpLogBrush);
		return Attach(hBrush);
	}
	BOOL TinyBrush::CreateBrush(const void* lpPackedDIB, UINT nUsage)
	{
		ASSERT(lpPackedDIB != NULL);
		HBRUSH hBrush = ::CreateDIBPatternBrushPt(lpPackedDIB, nUsage);
		return Attach(hBrush);
	}
	INT	 TinyBrush::GetLogBrush(LOGBRUSH* pLogBrush)
	{
		ASSERT(m_value != NULL);
		return ::GetObject(m_value, sizeof(LOGBRUSH), pLogBrush);
	}
	void TinyBrush::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyBitmap::CreateBitmap(INT nWidth, INT nHeight, UINT nPlanes, UINT nBitcount, const void* lpBits)
	{
		HBITMAP hBitmap = ::CreateBitmap(nWidth, nHeight, nPlanes, nBitcount, lpBits);
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::CreateBitmap(LPBITMAP lpBitmap)
	{
		HBITMAP hAttribBitmap = ::CreateBitmapIndirect(lpBitmap);
		return Attach(hAttribBitmap);
	}
	BOOL TinyBitmap::CreateCompatibleBitmap(HDC hDC, INT nWidth, INT nHeight)
	{
		ASSERT(hDC != NULL);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::CreateDiscardableBitmap(HDC hDC, INT nWidth, INT nHeight)
	{
		ASSERT(hDC != NULL);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
		return Attach(hBitmap);
	}
	INT	TinyBitmap::GetBitmap(BITMAP* pBitMap)
	{
		ASSERT(m_value != NULL);
		ASSERT(pBitMap != NULL);
		return ::GetObject(m_value, sizeof(BITMAP), pBitMap);
	}
	DWORD TinyBitmap::SetBitmapBits(DWORD dwCount, const void* lpBits)
	{
		return ::SetBitmapBits((HBITMAP)m_value, dwCount, lpBits);
	}
	DWORD TinyBitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
	{
		return ::GetBitmapBits((HBITMAP)m_value, dwCount, lpBits);
	}
	BOOL TinyBitmap::SetBitmapDimension(INT nWidth, INT nHeight, SIZE& size)
	{
		return ::SetBitmapDimensionEx((HBITMAP)m_value, nWidth, nHeight, &size);
	}
	BOOL TinyBitmap::GetBitmapDimension(SIZE& size) const
	{
		return ::GetBitmapDimensionEx((HBITMAP)m_value, &size);
	}
	BOOL TinyBitmap::LoadBitmap(HINSTANCE hInstance, UINT nIDResource)
	{
		HBITMAP hBitmap = ::LoadBitmap(hInstance, MAKEINTRESOURCE(nIDResource));
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::LoadBitmap(HINSTANCE hInstance, LPCTSTR lpszResourceName)
	{
		HBITMAP hBitmap = ::LoadBitmap(hInstance, lpszResourceName);
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::LoadOEMBitmap(UINT nIDBitmap)
	{
		HBITMAP hBitmap = ::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap));
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::LoadMappedBitmap(HINSTANCE hInstance, UINT nIDBitmap, UINT nFlags, LPCOLORMAP lpColorMap, int nMapSize)
	{
		HBITMAP hBitmap = ::CreateMappedBitmap(hInstance, nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize);
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::Save(LPCTSTR pzFile)
	{
		ASSERT(pzFile != NULL);
		HDC hDC = NULL;
		int iBits;
		WORD wBitCount;
		DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
		BITMAP bitmap;
		BITMAPFILEHEADER bmfHdr;
		BITMAPINFOHEADER bi;
		LPBITMAPINFOHEADER lpbi;
		HANDLE hFile, hDib, hPalette, hOldPalette = NULL;
		hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
		iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
		DeleteDC(hDC);
		if (iBits <= 1) wBitCount = 1;
		else if (iBits <= 4) wBitCount = 4;
		else if (iBits <= 8) wBitCount = 8;
		else wBitCount = 24;
		GetObject(m_value, sizeof(bitmap), (LPSTR)&bitmap);
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bitmap.bmWidth;
		bi.biHeight = bitmap.bmHeight;
		bi.biPlanes = 1;
		bi.biBitCount = 32;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrImportant = 0;
		bi.biClrUsed = 0;
		dwBmBitsSize = ((bitmap.bmWidth * wBitCount + 31) / 32) * 4 * bitmap.bmHeight;
		hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
		*lpbi = bi;
		hPalette = GetStockObject(DEFAULT_PALETTE);
		if (hPalette)
		{
			hDC = ::GetDC(NULL);
			hOldPalette = ::SelectPalette(hDC, (HPALETTE)hPalette, FALSE);
			RealizePalette(hDC);
		}
		GetDIBits(hDC, (HBITMAP)m_value, 0, (UINT)bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
		if (hOldPalette)
		{
			::SelectPalette(hDC, (HPALETTE)hOldPalette, TRUE);
			RealizePalette(hDC);
			::ReleaseDC(NULL, hDC);
		}
		hFile = CreateFile(pzFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (hFile == INVALID_HANDLE_VALUE) return FALSE;
		bmfHdr.bfType = 0x4D42; // "BM" 
		dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;
		bmfHdr.bfSize = dwDIBSize;
		bmfHdr.bfReserved1 = 0;
		bmfHdr.bfReserved2 = 0;
		bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
		WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		GlobalUnlock(hDib);
		GlobalFree(hDib);
		CloseHandle(hFile);
		return TRUE;
	}
	void TinyBitmap::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyPalette::CreatePalette(LPLOGPALETTE lpLogPalette)
	{
		HPALETTE hP = ::CreatePalette(lpLogPalette);
		return Attach(hP);
	}
	BOOL TinyPalette::CreatePalette(HDC hDC)
	{
		HPALETTE hP = ::CreateHalftonePalette(hDC);
		return Attach(hP);
	}
	INT	 TinyPalette::GetEntryCount()
	{
		ASSERT(m_value != NULL); 
		WORD nEntries = 0;
		::GetObject(m_value, sizeof(WORD), &nEntries); 
		return (INT)nEntries;
	}
	UINT TinyPalette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
	{
		ASSERT(m_value != NULL);
		return ::GetPaletteEntries((HPALETTE)m_value, nStartIndex, nNumEntries, lpPaletteColors);
	}
	UINT TinyPalette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
	{
		ASSERT(m_value != NULL);
		return ::SetPaletteEntries((HPALETTE)m_value, nStartIndex, nNumEntries, lpPaletteColors);
	}
	void TinyPalette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
	{
		ASSERT(m_value != NULL);
		::AnimatePalette((HPALETTE)m_value, nStartIndex, nNumEntries, lpPaletteColors);
	}
	UINT TinyPalette::GetNearestPaletteIndex(COLORREF crColor) const
	{
		ASSERT(m_value != NULL);
		return ::GetNearestPaletteIndex((HPALETTE)m_value, crColor);
	}
	BOOL TinyPalette::ResizePalette(UINT nNumEntries)
	{
		ASSERT(m_value != NULL);
		return ::ResizePalette((HPALETTE)m_value, nNumEntries);
	}
	void TinyPalette::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyRgn::CreateRgn(INT x1, INT y1, INT x2, INT y2)
	{
		HRGN hRgn = ::CreateRectRgn(x1, y1, x2, y2);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreateRgn(LPCRECT lpRect)
	{
		HRGN hRgn = ::CreateRectRgnIndirect(lpRect);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreateEllipticRgn(INT x1, INT y1, INT x2, INT y2)
	{
		HRGN hRgn = ::CreateEllipticRgn(x1, y1, x2, y2);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreateEllipticRgn(LPCRECT lpRect)
	{
		HRGN hRgn = ::CreateEllipticRgnIndirect(lpRect);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreatePolygonRgn(LPPOINT lpPoints, INT nCount, INT nMode)
	{
		HRGN hRgn = ::CreatePolygonRgn(lpPoints, nCount, nMode);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, INT nCount, INT nPolyFillMode)
	{
		HRGN hRgn = ::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreateRoundRectRgn(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
	{
		HRGN hRgn = ::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreateRgn(HDC hDC)
	{
		ASSERT(hDC != NULL);
		HRGN hRgn = ::PathToRegion(hDC);
		return Attach(hRgn);
	}
	BOOL TinyRgn::CreateRgn(const XFORM* lpXForm, INT nCount, const RGNDATA* pRgnData)
	{
		HRGN hRgn = ::ExtCreateRegion(lpXForm, nCount, pRgnData);
		return Attach(hRgn);
	}
	void TinyRgn::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
	//////////////////////////////////////////////////////////////////////////
	TinySize::TinySize() throw()
	{
		cx = cy = 0;
	}
	TinySize::TinySize(int initCX, int initCY) throw()
	{
		cx = initCX; cy = initCY;
	}
	TinySize::TinySize(SIZE initSize) throw()
	{
		*(SIZE*)this = initSize;
	}
	TinySize::TinySize(POINT initPt) throw()
	{
		*(POINT*)this = initPt;
	}
	TinySize::TinySize(DWORD dwSize) throw()
	{
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize);
	}
	BOOL TinySize::operator==(SIZE size) const throw()
	{
		return (cx == size.cx && cy == size.cy);
	}
	BOOL TinySize::operator!=(SIZE size) const throw()
	{
		return (cx != size.cx || cy != size.cy);
	}
	void TinySize::operator+=(SIZE size) throw()
	{
		cx += size.cx; cy += size.cy;
	}
	void TinySize::operator-=(SIZE size) throw()
	{
		cx -= size.cx; cy -= size.cy;
	}
	void TinySize::SetSize(int CX, int CY) throw()
	{
		cx = CX; cy = CY;
	}
	TinySize TinySize::operator+(SIZE size) const throw()
	{
		return TinySize(cx + size.cx, cy + size.cy);
	}
	TinySize TinySize::operator-(SIZE size) const throw()
	{
		return TinySize(cx - size.cx, cy - size.cy);
	}
	TinySize TinySize::operator-() const throw()
	{
		return TinySize(-cx, -cy);
	}
	TinyPoint TinySize::operator+(POINT point) const throw()
	{
		return TinyPoint(cx + point.x, cy + point.y);
	}
	TinyPoint TinySize::operator-(POINT point) const throw()
	{
		return TinyPoint(cx - point.x, cy - point.y);
	}
	TinyRectangle TinySize::operator+(const RECT* lpRect) const throw()
	{
		return TinyRectangle(lpRect) + *this;
	}
	TinyRectangle TinySize::operator-(const RECT* lpRect) const throw()
	{
		return TinyRectangle(lpRect) - *this;
	}
	//////////////////////////////////////////////////////////////////////////
	TinyPoint::TinyPoint() throw()
	{  }
	TinyPoint::TinyPoint(int initX, int initY) throw()
	{
		x = initX; y = initY;
	}
	TinyPoint::TinyPoint(POINT initPt) throw()
	{
		*(POINT*)this = initPt;
	}
	TinyPoint::TinyPoint(SIZE initSize) throw()
	{
		*(SIZE*)this = initSize;
	}
	TinyPoint::TinyPoint(LPARAM dwPoint) throw()
	{
		x = (short)GET_X_LPARAM(dwPoint);
		y = (short)GET_Y_LPARAM(dwPoint);
	}
	void TinyPoint::Offset(int xOffset, int yOffset) throw()
	{
		x += xOffset; y += yOffset;
	}
	void TinyPoint::Offset(POINT point) throw()
	{
		x += point.x; y += point.y;
	}
	void TinyPoint::Offset(SIZE size) throw()
	{
		x += size.cx; y += size.cy;
	}
	void TinyPoint::SetPoint(int X, int Y) throw()
	{
		x = X; y = Y;
	}
	BOOL TinyPoint::operator==(POINT point) const throw()
	{
		return (x == point.x && y == point.y);
	}
	BOOL TinyPoint::operator!=(POINT point) const throw()
	{
		return (x != point.x || y != point.y);
	}
	void TinyPoint::operator+=(SIZE size) throw()
	{
		x += size.cx; y += size.cy;
	}
	void TinyPoint::operator-=(SIZE size) throw()
	{
		x -= size.cx; y -= size.cy;
	}
	void TinyPoint::operator+=(POINT point) throw()
	{
		x += point.x; y += point.y;
	}
	void TinyPoint::operator-=(POINT point) throw()
	{
		x -= point.x; y -= point.y;
	}
	TinyPoint TinyPoint::operator+(SIZE size) const throw()
	{
		return TinyPoint(x + size.cx, y + size.cy);
	}
	TinyPoint TinyPoint::operator-(SIZE size) const throw()
	{
		return TinyPoint(x - size.cx, y - size.cy);
	}
	TinyPoint TinyPoint::operator-() const throw()
	{
		return TinyPoint(-x, -y);
	}
	TinyPoint TinyPoint::operator+(POINT point) const throw()
	{
		return TinyPoint(x + point.x, y + point.y);
	}
	TinySize TinyPoint::operator-(POINT point) const throw()
	{
		return TinySize(x - point.x, y - point.y);
	}
	TinyRectangle TinyPoint::operator+(const RECT* lpRect) const throw()
	{
		return TinyRectangle(lpRect) + *this;
	}
	TinyRectangle TinyPoint::operator-(const RECT* lpRect) const throw()
	{
		return TinyRectangle(lpRect) - *this;
	}

	// SysRect
	TinyRectangle::TinyRectangle() throw()
	{	}
	TinyRectangle::TinyRectangle(int l, int t, int r, int b) throw()
	{
		left = l; top = t; right = r; bottom = b;
	}
	TinyRectangle::TinyRectangle(const RECT& srcRect) throw()
	{
		::CopyRect(this, &srcRect);
	}
	TinyRectangle::TinyRectangle(LPCRECT lpSrcRect) throw()
	{
		::CopyRect(this, lpSrcRect);
	}
	TinyRectangle::TinyRectangle(POINT point, SIZE size) throw()
	{
		right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy;
	}
	TinyRectangle::TinyRectangle(POINT topLeft, POINT bottomRight) throw()
	{
		left = topLeft.x; top = topLeft.y;
		right = bottomRight.x; bottom = bottomRight.y;
	}
	int TinyRectangle::Width() const throw()
	{
		return right - left;
	}
	int TinyRectangle::Height() const throw()
	{
		return bottom - top;
	}
	TinySize TinyRectangle::Size() const throw()
	{
		return TinySize(right - left, bottom - top);
	}
	TinyPoint& TinyRectangle::TopLeft() throw()
	{
		return *((TinyPoint*)this);
	}
	TinyPoint& TinyRectangle::BottomRight() throw()
	{
		return *((TinyPoint*)this + 1);
	}
	const TinyPoint& TinyRectangle::TopLeft() const throw()
	{
		return *((TinyPoint*)this);
	}
	const TinyPoint& TinyRectangle::BottomRight() const throw()
	{
		return *((TinyPoint*)this + 1);
	}
	TinyPoint TinyRectangle::CenterPoint() const throw()
	{
		return TinyPoint((left + right) / 2, (top + bottom) / 2);
	}
	void TinyRectangle::SwapLeftRight() throw()
	{
		SwapLeftRight(LPRECT(this));
	}
	void WINAPI TinyRectangle::SwapLeftRight(LPRECT lpRect) throw()
	{
		LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp;
	}
	TinyRectangle::operator LPRECT() throw()
	{
		return this;
	}
	TinyRectangle::operator LPCRECT() const throw()
	{
		return this;
	}
	BOOL TinyRectangle::IsRectEmpty() const throw()
	{
		return ::IsRectEmpty(this);
	}
	BOOL TinyRectangle::IsRectNull() const throw()
	{
		return (left == 0 && right == 0 && top == 0 && bottom == 0);
	}
	BOOL TinyRectangle::PtInRect(POINT point) const throw()
	{
		return ::PtInRect(this, point);
	}
	void TinyRectangle::SetRect(int x1, int y1, int x2, int y2) throw()
	{
		::SetRect(this, x1, y1, x2, y2);
	}
	void TinyRectangle::SetRect(POINT topLeft, POINT bottomRight) throw()
	{
		::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	}
	void TinyRectangle::SetRectEmpty() throw()
	{
		::SetRectEmpty(this);
	}
	void TinyRectangle::CopyRect(LPCRECT lpSrcRect) throw()
	{
		::CopyRect(this, lpSrcRect);
	}
	BOOL TinyRectangle::EqualRect(LPCRECT lpRect) const throw()
	{
		return ::EqualRect(this, lpRect);
	}
	void TinyRectangle::InflateRect(int x, int y) throw()
	{
		::InflateRect(this, x, y);
	}
	void TinyRectangle::InflateRect(SIZE size) throw()
	{
		::InflateRect(this, size.cx, size.cy);
	}
	void TinyRectangle::DeflateRect(int x, int y) throw()
	{
		::InflateRect(this, -x, -y);
	}
	void TinyRectangle::DeflateRect(SIZE size) throw()
	{
		::InflateRect(this, -size.cx, -size.cy);
	}
	void TinyRectangle::OffsetRect(int x, int y) throw()
	{
		::OffsetRect(this, x, y);
	}
	void TinyRectangle::OffsetRect(POINT point) throw()
	{
		::OffsetRect(this, point.x, point.y);
	}
	void TinyRectangle::OffsetRect(SIZE size) throw()
	{
		::OffsetRect(this, size.cx, size.cy);
	}
	void TinyRectangle::MoveToY(int y) throw()
	{
		bottom = Height() + y; top = y;
	}
	void TinyRectangle::MoveToX(int x) throw()
	{
		right = Width() + x; left = x;
	}
	void TinyRectangle::MoveToXY(int x, int y) throw()
	{
		MoveToX(x); MoveToY(y);
	}
	void TinyRectangle::MoveToXY(POINT pt) throw()
	{
		MoveToX(pt.x); MoveToY(pt.y);
	}
	BOOL TinyRectangle::IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw()
	{
		return ::IntersectRect(this, lpRect1, lpRect2);
	}
	BOOL TinyRectangle::UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw()
	{
		return ::UnionRect(this, lpRect1, lpRect2);
	}
	void TinyRectangle::operator=(const RECT& srcRect) throw()
	{
		::CopyRect(this, &srcRect);
	}
	BOOL TinyRectangle::operator==(const RECT& rect) const throw()
	{
		return ::EqualRect(this, &rect);
	}
	BOOL TinyRectangle::operator!=(const RECT& rect) const throw()
	{
		return !::EqualRect(this, &rect);
	}
	void TinyRectangle::operator+=(POINT point) throw()
	{
		::OffsetRect(this, point.x, point.y);
	}
	void TinyRectangle::operator+=(SIZE size) throw()
	{
		::OffsetRect(this, size.cx, size.cy);
	}
	void TinyRectangle::operator+=(LPCRECT lpRect) throw()
	{
		InflateRect(lpRect);
	}
	void TinyRectangle::operator-=(POINT point) throw()
	{
		::OffsetRect(this, -point.x, -point.y);
	}
	void TinyRectangle::operator-=(SIZE size) throw()
	{
		::OffsetRect(this, -size.cx, -size.cy);
	}
	void TinyRectangle::operator-=(LPCRECT lpRect) throw()
	{
		DeflateRect(lpRect);
	}
	void TinyRectangle::operator&=(const RECT& rect) throw()
	{
		::IntersectRect(this, this, &rect);
	}
	void TinyRectangle::operator|=(const RECT& rect) throw()
	{
		::UnionRect(this, this, &rect);
	}
	TinyRectangle TinyRectangle::operator+(POINT pt) const throw()
	{
		TinyRectangle rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect;
	}
	TinyRectangle TinyRectangle::operator-(POINT pt) const throw()
	{
		TinyRectangle rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect;
	}
	TinyRectangle TinyRectangle::operator+(SIZE size) const throw()
	{
		TinyRectangle rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect;
	}
	TinyRectangle TinyRectangle::operator-(SIZE size) const throw()
	{
		TinyRectangle rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect;
	}
	TinyRectangle TinyRectangle::operator+(LPCRECT lpRect) const throw()
	{
		TinyRectangle rect(this); rect.InflateRect(lpRect); return rect;
	}
	TinyRectangle TinyRectangle::operator-(LPCRECT lpRect) const throw()
	{
		TinyRectangle rect(this); rect.DeflateRect(lpRect); return rect;
	}
	TinyRectangle TinyRectangle::operator&(const RECT& rect2) const throw()
	{
		TinyRectangle rect; ::IntersectRect(&rect, this, &rect2);
		return rect;
	}
	TinyRectangle TinyRectangle::operator|(const RECT& rect2) const throw()
	{
		TinyRectangle rect; ::UnionRect(&rect, this, &rect2);
		return rect;
	}
	BOOL TinyRectangle::SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw()
	{
		return ::SubtractRect(this, lpRectSrc1, lpRectSrc2);
	}

	void TinyRectangle::NormalizeRect() throw()
	{
		int nTemp;
		if (left > right)
		{
			nTemp = left;
			left = right;
			right = nTemp;
		}
		if (top > bottom)
		{
			nTemp = top;
			top = bottom;
			bottom = nTemp;
		}
	}

	void TinyRectangle::InflateRect(LPCRECT lpRect) throw()
	{
		left -= lpRect->left;		top -= lpRect->top;
		right += lpRect->right;		bottom += lpRect->bottom;
	}

	void TinyRectangle::InflateRect(int l, int t, int r, int b) throw()
	{
		left -= l;			top -= t;
		right += r;			bottom += b;
	}

	void TinyRectangle::DeflateRect(LPCRECT lpRect) throw()
	{
		left += lpRect->left;	top += lpRect->top;
		right -= lpRect->right;	bottom -= lpRect->bottom;
	}

	void TinyRectangle::DeflateRect(int l, int t, int r, int b) throw()
	{
		left += l;		top += t;
		right -= r;		bottom -= b;
	}

	TinyRectangle TinyRectangle::MulDiv(int nMultiplier, int nDivisor) const throw()
	{
		return TinyRectangle(
			::MulDiv(left, nMultiplier, nDivisor),
			::MulDiv(top, nMultiplier, nDivisor),
			::MulDiv(right, nMultiplier, nDivisor),
			::MulDiv(bottom, nMultiplier, nDivisor));
	}
}