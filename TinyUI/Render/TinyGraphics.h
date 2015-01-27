#pragma once
#include <Windows.h>
#include "../Common/TinyApplication.h"

/// <summary>
/// 渲染对象(GDI)
/// </summary>
namespace TinyUI
{
	//GDI对象
	class TinySize;
	class TinyPoint;
	class TinyRectangle;
	class TinyRgn;
	class TinyPen;
	class TinyBrush;
	class TinyDC;
	class TinyBitmap;
	class TinyPalette;
	/// <summary>
	/// GDI对象类 T是句柄类型
	/// </summary>
	template<class T = HANDLE>
	class TinyGDIHandle : public TinyObject
	{
	public:
		TinyGDIHandle();
		T Handle() const;
		operator T() const;
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
		ASSERT(pMap != NULL);
		TinyGDIHandle* ps = (TinyGDIHandle*)pMap->FromHandle(_value);
		ASSERT(ps != NULL || ps->m_value != _value);
		return ps;
	}
	template<class T>
	BOOL TinyGDIHandle<T>::Attach(T& _value)
	{
		if (_value == NULL)
		{
			return FALSE;
		}
		m_value = _value;
		TinyHandleMap<T>* pMap = GetMap();
		ASSERT(pMap != NULL);
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
			ASSERT(pMap != NULL);
			pMap->RemoveHandle(m_value);
		}
		m_value = NULL;
#pragma warning(push)
#pragma warning(disable : 4172)
		return _value;
#pragma warning(pop)

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
	class TinyDC : public TinyGDIHandle < HDC >
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
		INT			SaveDC();
		BOOL		RestoreDC(INT nSavedDC);
		INT			GetDeviceCaps(INT nIndex) const;
		UINT		SetBoundsRect(LPCRECT lpRectBounds, UINT flags);
		UINT		GetBoundsRect(LPRECT lpRectBounds, UINT flags);

		TinyPoint	GetBrushOrg() const;
		TinyPoint	SetBrushOrg(INT x, INT y);
		TinyPoint	SetBrushOrg(POINT point);
		INT			EnumObjects(INT nObjectType, INT(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);
		HPEN		SelectObject(TinyPen* pPen);
		HBRUSH		SelectObject(TinyBrush* pBrush);
		HBITMAP		SelectObject(TinyBitmap* pBitmap);
		INT			SelectObject(TinyRgn* pRgn);
		HGDIOBJ		SelectObject(HGDIOBJ hObject);
		COLORREF	GetNearestColor(COLORREF crColor) const;
		HPALETTE	SelectPalette(TinyPalette* pPalette, BOOL bForceBackground);
		UINT		RealizePalette();
		void		UpdateColors();

		COLORREF GetBkColor() const;
		INT GetBkMode() const;
		INT GetPolyFillMode() const;
		INT GetROP2() const;
		INT GetStretchBltMode() const;
		COLORREF GetTextColor() const;

		COLORREF SetBkColor(COLORREF crColor);
		INT SetBkMode(INT nBkMode);
		INT SetPolyFillMode(INT nPolyFillMode);
		INT SetROP2(INT nDrawMode);
		INT SetStretchBltMode(INT nStretchMode);
		COLORREF SetTextColor(COLORREF crColor);

		BOOL GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
		BOOL SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

		COLORREF GetDCBrushColor() const;
		COLORREF SetDCBrushColor(COLORREF crColor);

		COLORREF GetDCPenColor() const;
		COLORREF SetDCPenColor(COLORREF crColor);

		INT SetGraphicsMode(INT iMode);
		INT GetGraphicsMode() const;

		BOOL SetWorldTransform(const XFORM* pXform);
		BOOL ModifyWorldTransform(const XFORM* pXform, DWORD iMode);
		BOOL GetWorldTransform(XFORM* pXform) const;

		INT GetMapMode() const;
		TinyPoint GetViewportOrg() const;
		INT SetMapMode(INT nMapMode);

		TinyPoint SetViewportOrg(INT x, INT y);
		TinyPoint SetViewportOrg(POINT point);
		TinyPoint OffsetViewportOrg(INT nWidth, INT nHeight);

		TinySize GetViewportExt() const;
		TinySize SetViewportExt(INT cx, INT cy);
		TinySize SetViewportExt(SIZE size);
		TinySize ScaleViewportExt(INT xNum, INT xDenom, INT yNum, INT yDenom);

		TinyPoint GetWindowOrg() const;
		TinyPoint SetWindowOrg(INT x, INT y);
		TinyPoint SetWindowOrg(POINT point);
		TinyPoint OffsetWindowOrg(INT nWidth, INT nHeight);

		TinySize GetWindowExt() const;
		TinySize SetWindowExt(INT cx, INT cy);
		TinySize SetWindowExt(SIZE size);
		TinySize ScaleWindowExt(INT xNum, INT xDenom, INT yNum, INT yDenom);

		void DPtoLP(LPPOINT lpPoints, INT nCount = 1) const;
		void DPtoLP(LPRECT lpRect) const;
		void DPtoLP(LPSIZE lpSize) const;
		void LPtoDP(LPPOINT lpPoints, INT nCount = 1) const;
		void LPtoDP(LPRECT lpRect) const;
		void LPtoDP(LPSIZE lpSize) const;

		void DPtoHIMETRIC(LPSIZE lpSize) const;
		void LPtoHIMETRIC(LPSIZE lpSize) const;
		void HIMETRICtoDP(LPSIZE lpSize) const;
		void HIMETRICtoLP(LPSIZE lpSize) const;

		BOOL FillRgn(TinyRgn* pRgn, TinyBrush* pBrush);
		BOOL FrameRgn(TinyRgn* pRgn, TinyBrush* pBrush, INT nWidth, INT nHeight);
		BOOL InvertRgn(TinyRgn* pRgn);
		BOOL PaintRgn(TinyRgn* pRgn);

		INT GetClipBox(LPRECT lpRect) const;
		BOOL PtVisible(INT x, INT y) const;
		BOOL PtVisible(POINT point) const;
		BOOL RectVisible(LPCRECT lpRect) const;
		INT SelectClipRgn(TinyRgn* pRgn);
		INT ExcludeClipRect(INT x1, INT y1, INT x2, INT y2);
		INT ExcludeClipRect(LPCRECT lpRect);
		INT ExcludeUpdateRgn(HWND pWnd);
		INT IntersectClipRect(INT x1, INT y1, INT x2, INT y2);
		INT IntersectClipRect(LPCRECT lpRect);
		INT OffsetClipRgn(INT x, INT y);
		INT OffsetClipRgn(SIZE size);
		INT SelectClipRgn(TinyRgn* pRgn, INT nMode);

		TinyPoint GetCurrentPosition() const;
		TinyPoint MoveTo(INT x, INT y);
		TinyPoint MoveTo(POINT point);
		BOOL LineTo(INT x, INT y);
		BOOL LineTo(POINT point);
		BOOL Arc(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
		BOOL Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
		BOOL Polyline(const POINT* lpPoints, INT nCount);

		BOOL AngleArc(INT x, INT y, INT nRadius, float fStartAngle, float fSweepAngle);
		BOOL ArcTo(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
		BOOL ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
		INT GetArcDirection() const;
		INT SetArcDirection(INT nArcDirection);

		BOOL PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, INT nCount);
		BOOL PolylineTo(const POINT* lpPoints, INT nCount);
		BOOL PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, INT nCount);

		BOOL PolyBezier(const POINT* lpPoints, INT nCount);
		BOOL PolyBezierTo(const POINT* lpPoints, INT nCount);

		void FillRect(LPCRECT lpRect, HBRUSH hBrush);
		void FrameRect(LPCRECT lpRect, HBRUSH hBrush);
		void InvertRect(LPCRECT lpRect);
		BOOL DrawIcon(INT x, INT y, HICON hIcon);
		BOOL DrawIcon(POINT point, HICON hIcon);
		BOOL DrawState(TinyPoint pt, TinySize size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, TinyBitmap* pBitmap, UINT nFlags, TinyBrush* pBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, HICON hIcon, UINT nFlags, HBRUSH hBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, HICON hIcon, UINT nFlags, TinyBrush* pBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText = TRUE, INT nTextLen = 0, HBRUSH hBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText = TRUE, INT nTextLen = 0, TinyBrush* pBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
		BOOL DrawState(TinyPoint pt, TinySize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, TinyBrush* pBrush = NULL);

		BOOL Chord(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
		BOOL Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
		void DrawFocusRect(LPCRECT lpRect);
		BOOL Ellipse(INT x1, INT y1, INT x2, INT y2);
		BOOL Ellipse(LPCRECT lpRect);
		BOOL Pie(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
		BOOL Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
		BOOL Polygon(const POINT* lpPoints, INT nCount);
		BOOL PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, INT nCount);
		BOOL Rectangle(INT x1, INT y1, INT x2, INT y2);
		BOOL Rectangle(LPCRECT lpRect);
		BOOL RoundRect(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3);
		BOOL RoundRect(LPCRECT lpRect, POINT point);

		BOOL PatBlt(INT x, INT y, INT nWidth, INT nHeight, DWORD dwRop);
		BOOL BitBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC, INT xSrc, INT ySrc, DWORD dwRop);
		BOOL StretchBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, DWORD dwRop);
		COLORREF GetPixel(INT x, INT y) const;
		COLORREF GetPixel(POINT point) const;
		COLORREF SetPixel(INT x, INT y, COLORREF crColor);
		COLORREF SetPixel(POINT point, COLORREF crColor);
		BOOL FloodFill(INT x, INT y, COLORREF crColor);
		BOOL ExtFloodFill(INT x, INT y, COLORREF crColor, UINT nFillType);
		BOOL MaskBlt(INT x, INT y, INT nWidth, INT nHeight, TinyDC* pSrcDC, INT xSrc, INT ySrc, TinyBitmap& maskBitmap, INT xMask, INT yMask, DWORD dwRop);
		BOOL PlgBlt(LPPOINT lpPoint, TinyDC* pSrcDC, INT xSrc, INT ySrc, INT nWidth, INT nHeight, TinyBitmap& maskBitmap, INT xMask, INT yMask);
		BOOL SetPixelV(INT x, INT y, COLORREF crColor);
		BOOL SetPixelV(POINT point, COLORREF crColor);
		BOOL GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void* pMesh, ULONG nMeshElements, DWORD dwMode);
		BOOL TransparentBlt(INT xDest, INT yDest, INT nDestWidth, INT nDestHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, UINT clrTransparent);
		BOOL AlphaBlend(INT xDest, INT yDest, INT nDestWidth, INT nDestHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, BLENDFUNCTION blend);

		BOOL TextOut(INT x, INT y, LPCTSTR lpszString, INT nCount);
		BOOL ExtTextOut(INT x, INT y, UINT nOptions, LPCRECT lpRect, LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths);
		TinySize TabbedTextOut(INT x, INT y, LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions, INT nTabOrigin);

		INT DrawText(LPCTSTR lpszString, INT nCount, LPRECT lpRect, UINT nFormat);
		INT DrawTextEx(LPTSTR lpszString, INT nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);

		TinySize GetTextExtent(LPCTSTR lpszString, INT nCount) const;
		TinySize GetOutputTextExtent(LPCTSTR lpszString, INT nCount) const;
		TinySize GetTabbedTextExtent(LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions) const;
		TinySize GetOutputTabbedTextExtent(LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions) const;
		BOOL GrayString(TinyBrush* pBrush, BOOL(CALLBACK* lpfnOutput)(HDC, LPARAM, INT), LPARAM lpData, INT nCount, INT x, INT y, INT nWidth, INT nHeight);
		UINT GetTextAlign() const;
		UINT SetTextAlign(UINT nFlags);
		INT GetTextFace(INT nCount, LPTSTR lpszFacename) const;

		BOOL GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const;
		INT SetTextJustification(INT nBreakExtra, INT nBreakCount);
		INT GetTextCharacterExtra() const;
		INT SetTextCharacterExtra(INT nCharExtra);

		DWORD GetCharacterPlacement(LPCTSTR lpString, INT nCount, INT nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;

		BOOL GetTextExtentExPointI(LPWORD pgiIn, INT cgi, INT nMaxExtent, LPINT lpnFit, LPINT alpDx, _Out_opt_ LPSIZE lpSize) const;
		BOOL GetTextExtentPointI(LPWORD pgiIn, INT cgi, _Out_opt_ LPSIZE lpSize) const;

		BOOL DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags);
		BOOL DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState);

		BOOL ScrollDC(INT dx, INT dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, TinyRgn* pRgnUpdate, LPRECT lpRectUpdate);

		BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
		BOOL GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
		DWORD SetMapperFlags(DWORD dwFlag);
		TinySize GetAspectRatioFilter() const;

		BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
		DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const;
		INT GetKerningPairs(INT nPairs, LPKERNINGPAIR lpkrnpair) const;
		UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
		DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

		BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const;
		BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const;

		DWORD GetFontLanguageInfo() const;
		BOOL GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;

		BOOL GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;
		virtual INT Escape(INT nEscape, INT nCount, LPCSTR lpszInData, LPVOID lpOutData);
		INT Escape(INT nEscape, INT nInputSize, LPCSTR lpszInputData, INT nOutputSize, _Out_bytecap_(nOutputSize) LPSTR lpszOutputData);
		INT DrawEscape(INT nEscape, INT nInputSize, LPCSTR lpszInputData);

		INT StartDoc(LPCTSTR lpszDocName);
		INT StartDoc(LPDOCINFO lpDocInfo);
		INT StartPage();
		INT EndPage();
		INT SetAbortProc(BOOL(CALLBACK* lpfn)(HDC, INT));
		INT AbortDoc();
		INT EndDoc();

		BOOL PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds);
		BOOL AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
		BOOL AbortPath();
		BOOL BeginPath();
		BOOL CloseFigure();
		BOOL EndPath();
		BOOL FillPath();
		BOOL FlattenPath();
		BOOL StrokeAndFillPath();
		BOOL StrokePath();
		BOOL WidenPath();
		float GetMiterLimit() const;
		BOOL SetMiterLimit(float fMiterLimit);
		INT GetPath(LPPOINT lpPoints, LPBYTE lpTypes, INT nCount) const;
		BOOL SelectClipPath(INT nMode);
		static TinyBrush* PASCAL GetHalftoneBrush();
		void DrawDragRect(LPCRECT lpRect, SIZE size, LPCRECT lpRectLast, SIZE sizeLast, TinyBrush* pBrush = NULL, TinyBrush* pBrushLast = NULL);
		void FillSolidRect(LPCRECT lpRect, COLORREF clr);
		void FillSolidRect(INT x, INT y, INT cx, INT cy, COLORREF clr);
		void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
		void Draw3dRect(INT x, INT y, INT cx, INT cy, COLORREF clrTopLeft, COLORREF clrBottomRight);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HDC>* GetMap() const;
	};
	/// <summary>
	/// 内存DC
	/// </summary>
	/*class TinyMenDC : public TinyDC
	{
	DECLARE_DYNAMIC(TinyMenDC)
	public:
	TinyMenDC(HDC hDC, INT cx, INT cy);
	TinyMenDC(HDC hDC, HBITMAP hBitmap);
	void Render(INT destX, INT destY, INT destCX, INT destCY, INT srcX, INT srcY, INT srcCX, INT srcCY, BOOL bAlpha = TRUE, BYTE Alpha = 0);
	virtual ~TinyMenDC();
	private:
	HBITMAP m_hOldBitmap;
	HDC		m_hDC;
	};*/
	/// <summary>
	/// Pen类
	/// </summary>
	class TinyPen : public TinyGDIHandle < HPEN >
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

	/// <summary>
	/// Brush类
	/// </summary>
	class TinyBrush : public TinyGDIHandle < HBRUSH >
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

	/// <summary>
	/// Bitmap类
	/// </summary>
	class TinyBitmap : public TinyGDIHandle < HBITMAP >
	{
		DECLARE_DYNAMIC(TinyBitmap)
	public:
		TinyBitmap();
		virtual ~TinyBitmap();
		BOOL	CreateBitmap(INT nWidth, INT nHeight, UINT nPlanes, UINT nBitcount, const void* lpBits);
		BOOL	CreateBitmap(LPBITMAP lpBitmap);
		BOOL	CreateCompatibleBitmap(HDC hDC, INT nWidth, INT nHeight);
		BOOL	CreateDiscardableBitmap(HDC hDC, INT nWidth, INT nHeight);
		DWORD	SetBitmapBits(DWORD dwCount, const void* lpBits);
		DWORD	GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
		BOOL	SetBitmapDimension(INT nWidth, INT nHeight, SIZE& size);
		BOOL	GetBitmapDimension(SIZE& size) const;
		BOOL	LoadBitmap(HINSTANCE hInstance, UINT nIDResource);
		BOOL	LoadBitmap(HINSTANCE hInstance, LPCTSTR lpszResourceName);
		BOOL	LoadOEMBitmap(UINT nIDBitmap);
		BOOL	LoadMappedBitmap(HINSTANCE hInstance, UINT nIDBitmap, UINT nFlags, LPCOLORMAP lpColorMap, INT nMapSize);
		INT		GetBitmap(BITMAP* pBitMap);
		BOOL	Save(LPCTSTR pzSaveFile);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HBITMAP>* GetMap() const;
	};
	/// <summary>
	/// TinyPalette
	/// </summary>
	class TinyPalette : public TinyGDIHandle < HPALETTE >
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
	/// <summary>
	/// TinyRgn
	/// </summary>
	class TinyRgn : public TinyGDIHandle < HRGN >
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
		INT CombineRgn(const TinyRgn* pRgn1, const TinyRgn* pRgn2, INT nCombineMode);
		INT CopyRgn(const TinyRgn* pRgnSrc);
		BOOL EqualRgn(const TinyRgn* pRgn) const;
		INT OffsetRgn(INT x, INT y);
		INT OffsetRgn(POINT point);
		INT GetRgnBox(LPRECT lpRect) const;
		BOOL PtInRegion(INT x, INT y) const;
		BOOL PtInRegion(POINT point) const;
		BOOL RectInRegion(LPCRECT lpRect) const;
		INT GetRegionData(LPRGNDATA lpRgnData, INT nCount) const;
		void SetRectRgn(INT x1, INT y1, INT x2, INT y2);
		void SetRectRgn(LPCRECT lpRect);
	public:
		virtual void Destory();
		virtual TinyHandleMap<HRGN>* GetMap() const;
	};
	/// <summary>
	/// Size类
	/// </summary>
	class TinySize : public tagSIZE
	{
	public:
		TinySize() throw();
		TinySize(INT initCX, INT initCY) throw();
		TinySize(SIZE initSize) throw();
		TinySize(POINT initPt) throw();
		TinySize(DWORD dwSize) throw();
		BOOL operator==(SIZE size) const throw();
		BOOL operator!=(SIZE size) const throw();
		void operator+=(SIZE size) throw();
		void operator-=(SIZE size) throw();
		void SetSize(INT CX, INT CY) throw();
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
		TinyPoint(INT initX, INT initY) throw();
		TinyPoint(POINT initPt) throw();
		TinyPoint(SIZE initSize) throw();
		TinyPoint(LPARAM dwPoint) throw();

		void Offset(INT xOffset, INT yOffset) throw();
		void Offset(POINT point) throw();
		void Offset(SIZE size) throw();
		void SetPoint(INT X, INT Y) throw();

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
		TinyRectangle(INT l, INT t, INT r, INT b) throw();
		TinyRectangle(const RECT& srcRect) throw();
		TinyRectangle(LPCRECT lpSrcRect) throw();
		TinyRectangle(POINT point, SIZE size) throw();
		TinyRectangle(POINT topLeft, POINT bottomRight) throw();
		INT Width() const throw();
		INT Height() const throw();
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
		void SetRect(INT x1, INT y1, INT x2, INT y2) throw();
		void SetRect(POINT topLeft, POINT bottomRight) throw();
		void SetRectEmpty() throw();
		void CopyRect(LPCRECT lpSrcRect) throw();
		BOOL EqualRect(LPCRECT lpRect) const throw();
		void InflateRect(INT x, INT y) throw();
		void InflateRect(SIZE size) throw();
		void InflateRect(LPCRECT lpRect) throw();
		void InflateRect(INT l, INT t, INT r, INT b) throw();
		void DeflateRect(INT x, INT y) throw();
		void DeflateRect(SIZE size) throw();
		void DeflateRect(LPCRECT lpRect) throw();
		void DeflateRect(INT l, INT t, INT r, INT b) throw();
		void OffsetRect(INT x, INT y) throw();
		void OffsetRect(SIZE size) throw();
		void OffsetRect(POINT point) throw();
		void NormalizeRect() throw();
		void MoveToY(INT y) throw();
		void MoveToX(INT x) throw();
		void MoveToXY(INT x, INT y) throw();
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
		TinyRectangle MulDiv(INT nMultiplier, INT nDivisor) const throw();
	};

}


