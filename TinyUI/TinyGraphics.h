#pragma once
#include <Windows.h>
#include "TinyApplication.h"

/// <summary>
/// 渲染对象(GDI)
/// </summary>
namespace TinyUI
{
	/// <summary>
	/// GDI对象类 T是句柄类型
	/// </summary>
	template<class T = HANDLE>
	class TinyGDIHandle : public TinyObject
	{
	public:
		TinyGDIHandle();
		operator T() const;
		T Handle() const;
		virtual BOOL Attach(T& val);
		virtual T& Detach();
		BOOL operator==(const TinyGDIHandle& obj) const;
		BOOL operator!=(const TinyGDIHandle& obj) const;
	public:
		T m_value;
		static TinyGDIHandle* Lookup(T& _value);
	public:
		virtual TinyHandleMap<T>* GetMap() const;
		virtual void Destory();//子类重载实现,子类自己实现逻辑去释放资源
		virtual ~TinyGDIHandle();
	};
	template<class T>
	TinyGDIHandle<T>::TinyGDIHandle()
		:m_value(NULL)
	{

	}
	template<class T>
	TinyGDIHandle<T>::~TinyGDIHandle()
	{
		Destory();
	}
	template<class T>
	T TinyGDIHandle<T>::Handle() const
	{
		return this == NULL ? NULL : m_value;
	}
	template<class T>
	TinyGDIHandle<T>::operator T() const
	{
		return this == NULL ? NULL : m_value;
	}
	template<class T>
	BOOL TinyGDIHandle<T>::operator==(const TinyGDIHandle& _value) const
	{
		return ((T)_value) == m_value;
	}
	template<class T>
	BOOL TinyGDIHandle<T>::operator!=(const TinyGDIHandle& _value) const
	{
		return ((T)_value) != m_value;
	}
	template<class T>
	TinyGDIHandle<T>* TinyGDIHandle<T>::Lookup(T& _value)
	{
		TinyHandleMap<T>* pMap = GetMap();
		ASSERT(pMap == NULL);
		TinyGDIHandle* ps = (TinyGDIHandle*)pMap->FromHandle(_value);
		ASSERT(ps == NULL || ps->m_value == _value);
		return ps;
	}
	template<class T>
	BOOL TinyGDIHandle<T>::Attach(T& _value)
	{
		ASSERT(m_value == NULL);
		if (_value == NULL) return FALSE;
		m_value = _value;
		TinyHandleMap<T>* pMap = GetMap();
		ASSERT(pMap == NULL);
		pMap->AddHandle(m_value, this);
		return TRUE;
	}
	template<class T>
	T& TinyGDIHandle<T>::Detach()
	{
		T _value = m_value;
		if (_value != NULL)
		{
			TinyHandleMap<T>* pMap = GetMap();
			ASSERT(pMap == NULL);
			pMap->RemoveHandle(m_value);
		}
		m_value = NULL;
		return _value;
	}
	template<class T>
	void TinyGDIHandle<T>::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
	template<class T>
	TinyHandleMap<T>* TinyGDIHandle<T>::GetMap() const
	{
		return NULL;
	}
	/// <summary>
	/// DC类
	/// </summary>
	class TinyDC : public TinyGDIHandle<HDC>
	{
		DECLARE_DYNAMIC(TinyDC)
	public:
		TinyDC();
		virtual ~TinyDC();
	public:
		BOOL		CreateDC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const void* lpInitData);
		BOOL		CreateIC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const void* lpInitData);
		BOOL		CreateCompatibleDC(HDC hDC);
		BOOL		ResetDC(const DEVMODE* lpDevMode);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HDC>* GetMap() const;
	};
	/// <summary>
	/// Pen类
	/// </summary>
	class TinyPen : public TinyGDIHandle<HPEN>
	{
		DECLARE_DYNAMIC(TinyPen)
	public:
		TinyPen();
		virtual ~TinyPen();
	public:
		BOOL	CreatePen(INT nPenStyle, INT nWidth, COLORREF crColor);
		BOOL	CreatePen(INT nPenStyle, INT nWidth, const LOGBRUSH* pLogBrush, INT nStyleCount, const DWORD* lpStyle);
		BOOL	CreatePen(LPLOGPEN lpLogPen);
		INT		GetExtLogPen(EXTLOGPEN* pLogPen);
		INT		GetLogPen(LOGPEN* pLogPen);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HPEN>* GetMap() const;
	};
	TinyHandleMap<HDC>* TinyDC::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHDC());
	}
	/// <summary>
	/// Brush类
	/// </summary>
	class TinyBrush : public TinyGDIHandle<HBRUSH>
	{
		DECLARE_DYNAMIC(TinyBrush)
	public:
		TinyBrush();
		virtual ~TinyBrush();
		BOOL	CreateBrush(COLORREF crColor);
		BOOL	CreateBrush(INT nIndex, COLORREF crColor);
		BOOL	CreateBrush(HBITMAP hBitmap);
		BOOL	CreateBrush(const LOGBRUSH* lpLogBrush);
		BOOL	CreateBrush(const void* lpPackedDIB, UINT nUsage);
		INT		GetLogBrush(LOGBRUSH* pLogBrush);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HBRUSH>* GetMap() const;
	};
	TinyHandleMap<HBRUSH>* TinyBrush::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHBRUSH());
	}
	/// <summary>
	/// Bitmap类
	/// </summary>
	class TinyBitmap : public TinyGDIHandle<HBITMAP>
	{
		DECLARE_DYNAMIC(TinyBitmap)
	public:
		TinyBitmap();
		virtual ~TinyBitmap();
		BOOL	CreateBitmap(INT nWidth, INT nHeight, UINT nPlanes, UINT nBitcount, const void* lpBits);
		BOOL	CreateBitmap(LPBITMAP lpBitmap);
		BOOL	CreateCompatibleBitmap(HDC hDC, INT nWidth, INT nHeight);
		BOOL	CreateDiscardableBitmap(HDC hDC, INT nWidth, INT nHeight);
		INT		GetBitmap(BITMAP* pBitMap);
		DWORD	SetBitmapBits(DWORD dwCount, const void* lpBits);
		DWORD	GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
		BOOL	SetBitmapDimension(INT nWidth, INT nHeight, SIZE& size);
		BOOL	GetBitmapDimension(SIZE& size) const;
		BOOL	LoadBitmap(HINSTANCE hInstance, UINT nIDResource);
		BOOL	LoadBitmap(HINSTANCE hInstance, LPCTSTR lpszResourceName);
		BOOL	LoadOEMBitmap(UINT nIDBitmap);
		BOOL	LoadMappedBitmap(HINSTANCE hInstance, UINT nIDBitmap, UINT nFlags, LPCOLORMAP lpColorMap, int nMapSize);
		BOOL	Save(LPCTSTR pzSaveFile);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HBITMAP>* GetMap() const;
	};
	TinyHandleMap<HBITMAP>* TinyBitmap::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHBITMAP());
	}
	/// <summary>
	/// TinyPalette
	/// </summary>
	class TinyPalette : public TinyGDIHandle<HPALETTE>
	{
		DECLARE_DYNAMIC(TinyPalette)
	public:
		TinyPalette();
		virtual ~TinyPalette();
		BOOL CreatePalette(LPLOGPALETTE lpLogPalette);
		BOOL CreatePalette(HDC hDC);
		INT	 GetEntryCount();
		UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
		UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
		void AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
		UINT GetNearestPaletteIndex(COLORREF crColor) const;
		BOOL ResizePalette(UINT nNumEntries);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HPALETTE>* GetMap() const;
	};
	TinyHandleMap<HPALETTE>* TinyPalette::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHPALETTE());
	}
	/// <summary>
	/// TinyRgn
	/// </summary>
	class TinyRgn : public TinyGDIHandle<HRGN>
	{
		DECLARE_DYNAMIC(TinyRgn)
	public:
		TinyRgn();
		virtual ~TinyRgn();
		BOOL CreateRgn(INT x1, INT y1, INT x2, INT y2);
		BOOL CreateRgn(LPCRECT lpRect);
		BOOL CreateRgn(HDC hDC);
		BOOL CreateRgn(const XFORM* lpXForm, INT nCount, const RGNDATA* pRgnData);
		BOOL CreateEllipticRgn(INT x1, INT y1, INT x2, INT y2);
		BOOL CreateEllipticRgn(LPCRECT lpRect);
		BOOL CreatePolygonRgn(LPPOINT lpPoints, INT nCount, INT nMode);
		BOOL CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, INT nCount, INT nPolyFillMode);
		BOOL CreateRoundRectRgn(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HRGN>* GetMap() const;
	};
	TinyHandleMap<HRGN>* TinyRgn::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHRGN());
	}

	class TinySize;
	class TinyPoint;
	class TinyRectangle;
	/// <summary>
	/// Size类
	/// </summary>
	class TinySize : public tagSIZE
	{
	public:
		TinySize() throw();
		TinySize(int initCX, int initCY) throw();
		TinySize(SIZE initSize) throw();
		TinySize(POINT initPt) throw();
		TinySize(DWORD dwSize) throw();
		BOOL operator==(SIZE size) const throw();
		BOOL operator!=(SIZE size) const throw();
		void operator+=(SIZE size) throw();
		void operator-=(SIZE size) throw();
		void SetSize(int CX, int CY) throw();
		TinySize operator+(SIZE size) const throw();
		TinySize operator-(SIZE size) const throw();
		TinySize operator-() const throw();
		TinyPoint operator+(POINT point) const throw();
		TinyPoint operator-(POINT point) const throw();
		TinyRectangle operator+(const RECT* lpRect) const throw();
		TinyRectangle operator-(const RECT* lpRect) const throw();
	};
	/// <summary>
	/// Point类
	/// </summary>
	class TinyPoint : public tagPOINT
	{
	public:
		TinyPoint() throw();
		TinyPoint(int initX, int initY) throw();
		TinyPoint(POINT initPt) throw();
		TinyPoint(SIZE initSize) throw();
		TinyPoint(LPARAM dwPoint) throw();

		void Offset(int xOffset, int yOffset) throw();
		void Offset(POINT point) throw();
		void Offset(SIZE size) throw();
		void SetPoint(int X, int Y) throw();

		BOOL operator==(POINT point) const throw();
		BOOL operator!=(POINT point) const throw();
		void operator+=(SIZE size) throw();
		void operator-=(SIZE size) throw();
		void operator+=(POINT point) throw();
		void operator-=(POINT point) throw();

		TinyPoint operator+(SIZE size) const throw();
		TinyPoint operator-(SIZE size) const throw();
		TinyPoint operator-() const throw();
		TinyPoint operator+(POINT point) const throw();
		TinySize operator-(POINT point) const throw();

		TinyRectangle operator+(const RECT* lpRect) const throw();
		TinyRectangle operator-(const RECT* lpRect) const throw();
	};

	/// <summary>
	/// Rectangle类
	/// </summary>
	class TinyRectangle : public tagRECT
	{
	public:
		TinyRectangle() throw();
		TinyRectangle(int l, int t, int r, int b) throw();
		TinyRectangle(const RECT& srcRect) throw();
		TinyRectangle(LPCRECT lpSrcRect) throw();
		TinyRectangle(POINT point, SIZE size) throw();
		TinyRectangle(POINT topLeft, POINT bottomRight) throw();
		int Width() const throw();
		int Height() const throw();
		TinySize Size() const throw();
		TinyPoint& TopLeft() throw();
		TinyPoint& BottomRight() throw();
		const TinyPoint& TopLeft() const throw();
		const TinyPoint& BottomRight() const throw();
		TinyPoint CenterPoint() const throw();
		void SwapLeftRight() throw();
		static void WINAPI SwapLeftRight(LPRECT lpRect) throw();
		operator LPRECT() throw();
		operator LPCRECT() const throw();
		BOOL IsRectEmpty() const throw();
		BOOL IsRectNull() const throw();
		BOOL PtInRect(POINT point) const throw();
		void SetRect(int x1, int y1, int x2, int y2) throw();
		void SetRect(POINT topLeft, POINT bottomRight) throw();
		void SetRectEmpty() throw();
		void CopyRect(LPCRECT lpSrcRect) throw();
		BOOL EqualRect(LPCRECT lpRect) const throw();
		void InflateRect(int x, int y) throw();
		void InflateRect(SIZE size) throw();
		void InflateRect(LPCRECT lpRect) throw();
		void InflateRect(int l, int t, int r, int b) throw();
		void DeflateRect(int x, int y) throw();
		void DeflateRect(SIZE size) throw();
		void DeflateRect(LPCRECT lpRect) throw();
		void DeflateRect(int l, int t, int r, int b) throw();
		void OffsetRect(int x, int y) throw();
		void OffsetRect(SIZE size) throw();
		void OffsetRect(POINT point) throw();
		void NormalizeRect() throw();
		void MoveToY(int y) throw();
		void MoveToX(int x) throw();
		void MoveToXY(int x, int y) throw();
		void MoveToXY(POINT point) throw();
		BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();
		BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();
		BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw();
		void operator=(const RECT& srcRect) throw();
		BOOL operator==(const RECT& rect) const throw();
		BOOL operator!=(const RECT& rect) const throw();
		void operator+=(POINT point) throw();
		void operator+=(SIZE size) throw();
		void operator+=(LPCRECT lpRect) throw();
		void operator-=(POINT point) throw();
		void operator-=(SIZE size) throw();
		void operator-=(LPCRECT lpRect) throw();
		void operator&=(const RECT& rect) throw();
		void operator|=(const RECT& rect) throw();
		TinyRectangle operator+(POINT point) const throw();
		TinyRectangle operator-(POINT point) const throw();
		TinyRectangle operator+(LPCRECT lpRect) const throw();
		TinyRectangle operator+(SIZE size) const throw();
		TinyRectangle operator-(SIZE size) const throw();
		TinyRectangle operator-(LPCRECT lpRect) const throw();
		TinyRectangle operator&(const RECT& rect2) const throw();
		TinyRectangle operator|(const RECT& rect2) const throw();
		TinyRectangle MulDiv(int nMultiplier, int nDivisor) const throw();
	};

}


