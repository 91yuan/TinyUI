#include "../stdafx.h"
#include "TinyGraphics.h"

namespace TinyUI
{
	TinyHandleMap<HDC>* TinyDC::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHDC());
	}
	TinyHandleMap<HBRUSH>* TinyBrush::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHBRUSH());
	}
	TinyHandleMap<HBITMAP>* TinyBitmap::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHBITMAP());
	}
	TinyHandleMap<HPALETTE>* TinyPalette::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHPALETTE());
	}
	TinyHandleMap<HRGN>* TinyRgn::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHRGN());
	}
	/************************************************************************/
	/* DC                                                                   */
	/************************************************************************/
#pragma region  TinyDC
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

	void TinyDC::Destory()
	{
		if (m_value != NULL)
		{
			::DeleteDC(Detach());
		}
	}
	INT TinyDC::ExcludeUpdateRgn(HWND hWnd)
	{
		ASSERT(m_value != NULL);
		return ::ExcludeUpdateRgn(m_value, hWnd);
	}
	INT TinyDC::GetDeviceCaps(INT nIndex) const
	{
		ASSERT(m_value != NULL);
		return ::GetDeviceCaps(m_value, nIndex);
	}
	TinyPoint TinyDC::GetBrushOrg() const
	{
		ASSERT(m_value != NULL);
		POINT point;
		::GetBrushOrgEx(m_value, &point);
		return point;
	}
	TinyPoint TinyDC::SetBrushOrg(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		POINT point;
		::SetBrushOrgEx(m_value, x, y, &point);
		return point;
	}
	TinyPoint TinyDC::SetBrushOrg(POINT point)
	{
		ASSERT(m_value != NULL);
		::SetBrushOrgEx(m_value, point.x, point.y, &point);
		return point;
	}

	INT TinyDC::EnumObjects(INT nObjectType, INT(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
	{
		ASSERT(m_value != NULL);
		return ::EnumObjects(m_value, nObjectType, (GOBJENUMPROC)lpfn, lpData);
	}

	HGDIOBJ TinyDC::SelectObject(HGDIOBJ hObject)
	{
		ASSERT(m_value != NULL);
		return (hObject != NULL) ? ::SelectObject(m_value, hObject) : NULL;
	}
	COLORREF TinyDC::GetNearestColor(COLORREF crColor) const
	{
		ASSERT(m_value != NULL);
		return ::GetNearestColor(m_value, crColor);
	}
	UINT TinyDC::RealizePalette()
	{
		ASSERT(m_value != NULL);
		return ::RealizePalette(m_value);
	}
	void TinyDC::UpdateColors()
	{
		ASSERT(m_value != NULL);
		::UpdateColors(m_value);
	}
	COLORREF TinyDC::GetBkColor() const
	{
		ASSERT(m_value != NULL);
		return ::GetBkColor(m_value);
	}
	INT TinyDC::GetBkMode() const
	{
		ASSERT(m_value != NULL);
		return ::GetBkMode(m_value);
	}
	INT TinyDC::GetPolyFillMode() const
	{
		ASSERT(m_value != NULL);
		return ::GetPolyFillMode(m_value);
	}
	INT TinyDC::GetROP2() const
	{
		ASSERT(m_value != NULL);
		return ::GetROP2(m_value);
	}
	INT TinyDC::GetStretchBltMode() const
	{
		ASSERT(m_value != NULL);
		return ::GetStretchBltMode(m_value);
	}
	COLORREF TinyDC::GetTextColor() const
	{
		ASSERT(m_value != NULL);
		return ::GetTextColor(m_value);
	}
	INT TinyDC::GetMapMode() const
	{
		ASSERT(m_value != NULL);
		return ::GetMapMode(m_value);
	}
	INT TinyDC::GetGraphicsMode() const
	{
		ASSERT(m_value != NULL);
		return ::GetGraphicsMode(m_value);
	}
	BOOL TinyDC::GetWorldTransform(XFORM* pXform) const
	{
		ASSERT(m_value != NULL);
		return ::GetWorldTransform(m_value, pXform);
	}

	TinyPoint TinyDC::GetViewportOrg() const
	{
		ASSERT(m_value != NULL);
		POINT point;
		::GetViewportOrgEx(m_value, &point);
		return point;
	}
	TinySize TinyDC::GetViewportExt() const
	{
		ASSERT(m_value != NULL);
		SIZE size;
		::GetViewportExtEx(m_value, &size);
		return size;
	}
	TinyPoint TinyDC::GetWindowOrg() const
	{
		ASSERT(m_value != NULL);
		POINT point;
		::GetWindowOrgEx(m_value, &point);
		return point;
	}
	TinySize TinyDC::GetWindowExt() const
	{
		ASSERT(m_value != NULL);
		SIZE size;
		::GetWindowExtEx(m_value, &size);
		return size;
	}

	TinyPoint TinyDC::SetViewportOrg(POINT point)
	{
		ASSERT(m_value != NULL);
		return SetViewportOrg(point.x, point.y);
	}
	TinySize TinyDC::SetViewportExt(SIZE size)
	{
		ASSERT(m_value != NULL);
		return SetViewportExt(size.cx, size.cy);
	}
	TinyPoint TinyDC::SetWindowOrg(POINT point)
	{
		ASSERT(m_value != NULL);
		return SetWindowOrg(point.x, point.y);
	}
	TinySize TinyDC::SetWindowExt(SIZE size)
	{
		ASSERT(m_value != NULL);
		return SetWindowExt(size.cx, size.cy);
	}

	void TinyDC::DPtoLP(LPPOINT lpPoints, INT nCount) const
	{
		ASSERT(m_value != NULL);
		(::DPtoLP(m_value, lpPoints, nCount));
	}
	void TinyDC::DPtoLP(LPRECT lpRect) const
	{
		ASSERT(m_value != NULL);
		(::DPtoLP(m_value, (LPPOINT)lpRect, 2));
	}
	void TinyDC::LPtoDP(LPPOINT lpPoints, INT nCount) const
	{
		ASSERT(m_value != NULL);
		(::LPtoDP(m_value, lpPoints, nCount));
	}
	void TinyDC::LPtoDP(LPRECT lpRect) const
	{
		ASSERT(m_value != NULL);
		(::LPtoDP(m_value, (LPPOINT)lpRect, 2));
	}

	BOOL TinyDC::FillRgn(TinyRgn* pRgn, TinyBrush* pBrush)
	{
		ASSERT(m_value != NULL);
		return ::FillRgn(m_value, (HRGN)pRgn->Handle(), (HBRUSH)pBrush->Handle());
	}
	BOOL TinyDC::FrameRgn(TinyRgn* pRgn, TinyBrush* pBrush, INT nWidth, INT nHeight)
	{
		ASSERT(m_value != NULL);
		return ::FrameRgn(m_value, (HRGN)pRgn->Handle(), (HBRUSH)pBrush->Handle(), nWidth, nHeight);
	}
	BOOL TinyDC::InvertRgn(TinyRgn* pRgn)
	{
		ASSERT(m_value != NULL);
		return ::InvertRgn(m_value, (HRGN)pRgn->Handle());
	}
	BOOL TinyDC::PaintRgn(TinyRgn* pRgn)
	{
		ASSERT(m_value != NULL);
		return ::PaintRgn(m_value, (HRGN)pRgn->Handle());
	}
	BOOL TinyDC::PtVisible(INT x, INT y) const
	{
		ASSERT(m_value != NULL);
		return ::PtVisible(m_value, x, y);
	}
	BOOL TinyDC::PtVisible(POINT point) const
	{
		ASSERT(m_value != NULL);
		return PtVisible(point.x, point.y);
	}
	BOOL TinyDC::RectVisible(LPCRECT lpRect) const
	{
		ASSERT(m_value != NULL);
		return ::RectVisible(m_value, lpRect);
	}
	TinyPoint TinyDC::GetCurrentPosition() const
	{
		ASSERT(m_value != NULL);
		POINT point;
		(::GetCurrentPositionEx(m_value, &point));
		return point;
	}

	TinyPoint TinyDC::MoveTo(POINT point)
	{
		ASSERT(m_value != NULL);
		return MoveTo(point.x, point.y);
	}
	BOOL TinyDC::LineTo(POINT point)
	{
		ASSERT(m_value != NULL);
		return LineTo(point.x, point.y);
	}
	BOOL TinyDC::Arc(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_value != NULL);
		return ::Arc(m_value, x1, y1, x2, y2, x3, y3, x4, y4);
	}
	BOOL TinyDC::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_value != NULL);
		return ::Arc(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	BOOL TinyDC::Polyline(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::Polyline(m_value, lpPoints, nCount);
	}
	void TinyDC::FillRect(LPCRECT lpRect, HBRUSH hBrush)
	{
		ASSERT(m_value != NULL);
		::FillRect(m_value, lpRect, hBrush);
	}
	void TinyDC::FrameRect(LPCRECT lpRect, HBRUSH hBrush)
	{
		ASSERT(m_value != NULL);
		::FrameRect(m_value, lpRect, hBrush);
	}
	void TinyDC::InvertRect(LPCRECT lpRect)
	{
		ASSERT(m_value != NULL);
		::InvertRect(m_value, lpRect);
	}
	BOOL TinyDC::DrawIcon(INT x, INT y, HICON hIcon)
	{
		ASSERT(m_value != NULL);
		return ::DrawIcon(m_value, x, y, hIcon);
	}
	BOOL TinyDC::DrawIcon(POINT point, HICON hIcon)
	{
		ASSERT(m_value != NULL);
		return ::DrawIcon(m_value, point.x, point.y, hIcon);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, TinyBitmap* pBitmap, UINT nFlags, TinyBrush* pBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, (HBRUSH)pBrush->Handle(), NULL, (LPARAM)pBitmap->Handle(), 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, HICON hIcon, UINT nFlags, TinyBrush* pBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, (HBRUSH)pBrush->Handle(), NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText, INT nTextLen, HBRUSH hBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, hBrush, NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT));
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText, INT nTextLen, TinyBrush* pBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, (HBRUSH)pBrush->Handle(), NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT));
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, hBrush, lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_COMPLEX);
	}

	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, TinyBrush* pBrush)
	{
		ASSERT(m_value != NULL);
		return ::DrawState(m_value, (HBRUSH)pBrush->Handle(), lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_COMPLEX);
	}

	BOOL TinyDC::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
	{
		ASSERT(m_value != NULL);
		return ::DrawEdge(m_value, lpRect, nEdge, nFlags);
	}
	BOOL TinyDC::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
	{
		ASSERT(m_value != NULL);
		return ::DrawFrameControl(m_value, lpRect, nType, nState);
	}

	BOOL TinyDC::Chord(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_value != NULL);
		return ::Chord(m_value, x1, y1, x2, y2, x3, y3, x4, y4);
	}

	BOOL TinyDC::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_value != NULL); return ::Chord(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	void TinyDC::DrawFocusRect(LPCRECT lpRect)
	{
		ASSERT(m_value != NULL);
		::DrawFocusRect(m_value, lpRect);
	}
	BOOL TinyDC::Ellipse(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_value != NULL);
		return ::Ellipse(m_value, x1, y1, x2, y2);
	}
	BOOL TinyDC::Ellipse(LPCRECT lpRect)
	{
		ASSERT(m_value != NULL);
		return ::Ellipse(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}
	BOOL TinyDC::Pie(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_value != NULL);
		return ::Pie(m_value, x1, y1, x2, y2, x3, y3, x4, y4);
	}
	BOOL TinyDC::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_value != NULL);
		return ::Pie(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	BOOL TinyDC::Polygon(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::Polygon(m_value, lpPoints, nCount);
	}
	BOOL TinyDC::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::PolyPolygon(m_value, lpPoints, lpPolyCounts, nCount);
	}
	BOOL TinyDC::Rectangle(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_value != NULL);
		return ::Rectangle(m_value, x1, y1, x2, y2);
	}

	BOOL TinyDC::Rectangle(LPCRECT lpRect)
	{
		ASSERT(m_value != NULL);
		return ::Rectangle(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	BOOL TinyDC::RoundRect(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
	{
		ASSERT(m_value != NULL);
		return ::RoundRect(m_value, x1, y1, x2, y2, x3, y3);
	}

	BOOL TinyDC::RoundRect(LPCRECT lpRect, POINT point)
	{
		ASSERT(m_value != NULL);
		return ::RoundRect(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, point.x, point.y);

	}
	BOOL TinyDC::PatBlt(INT x, INT y, INT nWidth, INT nHeight, DWORD dwRop)
	{
		ASSERT(m_value != NULL); return ::PatBlt(m_value, x, y, nWidth, nHeight, dwRop);
	}
	BOOL TinyDC::BitBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC, INT xSrc, INT ySrc, DWORD dwRop)
	{
		ASSERT(m_value != NULL); return ::BitBlt(m_value, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, dwRop);
	}
	BOOL TinyDC::StretchBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, DWORD dwRop)
	{
		ASSERT(m_value != NULL);
		return ::StretchBlt(m_value, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);
	}
	COLORREF TinyDC::GetPixel(INT x, INT y) const
	{
		ASSERT(m_value != NULL);
		return ::GetPixel(m_value, x, y);
	}
	COLORREF TinyDC::GetPixel(POINT point) const
	{
		ASSERT(m_value != NULL);
		return ::GetPixel(m_value, point.x, point.y);
	}
	COLORREF TinyDC::SetPixel(INT x, INT y, COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return ::SetPixel(m_value, x, y, crColor);
	}
	COLORREF TinyDC::SetPixel(POINT point, COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return ::SetPixel(m_value, point.x, point.y, crColor);
	}
	BOOL TinyDC::FloodFill(INT x, INT y, COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return ::FloodFill(m_value, x, y, crColor);
	}
	BOOL TinyDC::ExtFloodFill(INT x, INT y, COLORREF crColor, UINT nFillType)
	{
		ASSERT(m_value != NULL);
		return ::ExtFloodFill(m_value, x, y, crColor, nFillType);
	}
	BOOL TinyDC::TextOut(INT x, INT y, LPCTSTR lpszString, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::TextOut(m_value, x, y, lpszString, nCount);
	}
	BOOL TinyDC::ExtTextOut(INT x, INT y, UINT nOptions, LPCRECT lpRect, LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths)
	{
		ASSERT(m_value != NULL);
		return ::ExtTextOut(m_value, x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths);
	}
	TinySize TinyDC::TabbedTextOut(INT x, INT y, LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions, INT nTabOrigin)
	{
		ASSERT(m_value != NULL);
		return ::TabbedTextOut(m_value, x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
	}

	INT TinyDC::DrawText(LPCTSTR lpszString, INT nCount, LPRECT lpRect, UINT nFormat)
	{
		ASSERT(m_value != NULL);
		return ::DrawText(m_value, lpszString, nCount, lpRect, nFormat);
	}

	INT TinyDC::DrawTextEx(LPTSTR lpszString, INT nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
	{
		ASSERT(m_value != NULL);
		return ::DrawTextEx(m_value, lpszString, nCount, lpRect, nFormat, lpDTParams);
	}

	TinySize TinyDC::GetTextExtent(LPCTSTR lpszString, INT nCount) const
	{
		ASSERT(m_value != NULL);
		SIZE size;
		(::GetTextExtentPoint32(m_value, lpszString, nCount, &size));
		return size;
	}

	TinySize TinyDC::GetOutputTextExtent(LPCTSTR lpszString, INT nCount) const
	{
		ASSERT(m_value != NULL);
		SIZE size;
		(::GetTextExtentPoint32(m_value, lpszString, nCount, &size));
		return size;
	}

	TinySize TinyDC::GetTabbedTextExtent(LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions) const
	{
		ASSERT(m_value != NULL);
		return ::GetTabbedTextExtent(m_value, lpszString, nCount, nTabPositions, lpnTabStopPositions);
	}

	TinySize TinyDC::GetOutputTabbedTextExtent(LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions) const
	{
		ASSERT(m_value != NULL);
		return ::GetTabbedTextExtent(m_value, lpszString, nCount, nTabPositions, lpnTabStopPositions);
	}

	BOOL TinyDC::GrayString(TinyBrush* pBrush, BOOL(CALLBACK* lpfnOutput)(HDC, LPARAM, INT), LPARAM lpData, INT nCount, INT x, INT y, INT nWidth, INT nHeight)
	{
		ASSERT(m_value != NULL);
		return ::GrayString(m_value, (HBRUSH)pBrush->Handle(), (GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight);
	}

	UINT TinyDC::GetTextAlign() const
	{
		ASSERT(m_value != NULL);
		return ::GetTextAlign(m_value);
	}

	INT TinyDC::GetTextFace(INT nCount, _Out_z_cap_post_count_(nCount, return) LPTSTR lpszFacename) const
	{
		ASSERT(m_value != NULL);
		return ::GetTextFace(m_value, nCount, lpszFacename);
	}

	BOOL TinyDC::GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const
	{
		ASSERT(m_value != NULL);
		return ::GetTextMetrics(m_value, lpMetrics);
	}
	INT TinyDC::GetTextCharacterExtra() const
	{
		ASSERT(m_value != NULL);
		return ::GetTextCharacterExtra(m_value);
	}
	BOOL TinyDC::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
	{
		ASSERT(m_value != NULL);
		return ::GetCharWidth(m_value, nFirstChar, nLastChar, lpBuffer);
	}

	BOOL TinyDC::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
	{
		ASSERT(m_value != NULL);
		return ::GetCharWidth(m_value, nFirstChar, nLastChar, lpBuffer);
	}
	DWORD TinyDC::GetFontLanguageInfo() const
	{
		ASSERT(m_value != NULL);
		return ::GetFontLanguageInfo(m_value);
	}

	DWORD TinyDC::GetCharacterPlacement(LPCTSTR lpString, INT nCount, INT nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
	{
		ASSERT(m_value != NULL);
		return ::GetCharacterPlacement(m_value, lpString, nCount, nMaxExtent, lpResults, dwFlags);
	}

	TinySize TinyDC::GetAspectRatioFilter() const
	{
		ASSERT(m_value != NULL);
		SIZE size;
		::GetAspectRatioFilterEx(m_value, &size);
		return size;
	}

	BOOL TinyDC::ScrollDC(INT dx, INT dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, TinyRgn* pRgnUpdate, LPRECT lpRectUpdate)
	{
		ASSERT(m_value != NULL);
		return ::ScrollDC(m_value, dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->Handle(), lpRectUpdate);
	}

	INT TinyDC::Escape(INT nEscape, INT nCount, LPCSTR lpszInData, LPVOID lpOutData)
	{
		ASSERT(m_value != NULL);
		return ::Escape(m_value, nEscape, nCount, lpszInData, lpOutData);
	}

	UINT TinyDC::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
	{
		ASSERT(m_value != NULL);
		return ::SetBoundsRect(m_value, lpRectBounds, flags);
	}
	UINT TinyDC::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
	{
		ASSERT(m_value != NULL);
		return ::GetBoundsRect(m_value, lpRectBounds, flags);
	}
	BOOL TinyDC::ResetDC(const DEVMODE* lpDevMode)
	{
		ASSERT(m_value != NULL);
		return ::ResetDC(m_value, lpDevMode) != NULL;
	}
	UINT TinyDC::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
	{
		ASSERT(m_value != NULL);
		return ::GetOutlineTextMetrics(m_value, cbData, lpotm);
	}
	BOOL TinyDC::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
	{
		ASSERT(m_value != NULL);
		return ::GetCharABCWidths(m_value, nFirstChar, nLastChar, lpabc);
	}
	DWORD TinyDC::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData,
		DWORD cbData) const
	{
		ASSERT(m_value != NULL);
		return ::GetFontData(m_value, dwTable, dwOffset, lpData, cbData);
	}

	INT TinyDC::GetKerningPairs(INT nPairs, LPKERNINGPAIR lpkrnpair) const
	{
		ASSERT(m_value != NULL);
		return ::GetKerningPairs(m_value, nPairs, lpkrnpair);
	}

	DWORD TinyDC::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
	{
		ASSERT(m_value != NULL);
		return ::GetGlyphOutline(m_value, nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
	}
	void TinyDC::Draw3dRect(LPCRECT lpRect,
		COLORREF clrTopLeft, COLORREF clrBottomRight)
	{
		Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
			lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
	}
	void TinyDC::FillSolidRect(LPCRECT lpRect, COLORREF clr)
	{
		ASSERT(m_value != NULL);
		ASSERT(lpRect != NULL);
		::SetBkColor(m_value, clr);
		::ExtTextOut(m_value, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	}

	void TinyDC::FillSolidRect(INT x, INT y, INT cx, INT cy, COLORREF clr)
	{
		ASSERT(m_value != NULL);
		::SetBkColor(m_value, clr);
		TinyRectangle rect(x, y, x + cx, y + cy);
		::ExtTextOut(m_value, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
	}

	void TinyDC::Draw3dRect(INT x, INT y, INT cx, INT cy,
		COLORREF clrTopLeft, COLORREF clrBottomRight)
	{
		FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
		FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
		FillSolidRect(x + cx, y, -1, cy, clrBottomRight);
		FillSolidRect(x, y + cy, cx, -1, clrBottomRight);
	}
	INT TinyDC::StartDoc(LPDOCINFO lpDocInfo)
	{
		ASSERT(m_value != NULL);
		return ::StartDoc(m_value, lpDocInfo);
	}
	INT TinyDC::StartPage()
	{
		ASSERT(m_value != NULL);
		return ::StartPage(m_value);
	}
	INT TinyDC::EndPage()
	{
		ASSERT(m_value != NULL);
		return ::EndPage(m_value);
	}
	INT TinyDC::SetAbortProc(BOOL(CALLBACK* lpfn)(HDC, INT))
	{
		ASSERT(m_value != NULL);
		return ::SetAbortProc(m_value, (ABORTPROC)lpfn);
	}
	INT TinyDC::AbortDoc()
	{
		ASSERT(m_value != NULL);
		return ::AbortDoc(m_value);
	}
	INT TinyDC::EndDoc()
	{
		ASSERT(m_value != NULL);
		return ::EndDoc(m_value);
	}

	BOOL TinyDC::MaskBlt(INT x, INT y, INT nWidth, INT nHeight, TinyDC* pSrcDC, INT xSrc, INT ySrc, TinyBitmap& maskBitmap, INT xMask, INT yMask, DWORD dwRop)
	{
		ASSERT(m_value != NULL);
		return ::MaskBlt(m_value, x, y, nWidth, nHeight, pSrcDC->Handle(), xSrc, ySrc, (HBITMAP)maskBitmap.m_value, xMask, yMask, dwRop);
	}
	BOOL TinyDC::PlgBlt(LPPOINT lpPoint, TinyDC* pSrcDC, INT xSrc, INT ySrc,
		INT nWidth, INT nHeight, TinyBitmap& maskBitmap, INT xMask, INT yMask)
	{
		ASSERT(m_value != NULL);
		return ::PlgBlt(m_value, lpPoint, pSrcDC->Handle(), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.m_value, xMask, yMask);
	}
	BOOL TinyDC::SetPixelV(INT x, INT y, COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return ::SetPixelV(m_value, x, y, crColor);
	}
	BOOL TinyDC::SetPixelV(POINT point, COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return ::SetPixelV(m_value, point.x, point.y, crColor);
	}
	BOOL TinyDC::AngleArc(INT x, INT y, INT nRadius, float fStartAngle, float fSweepAngle)
	{
		ASSERT(m_value != NULL);
		return ::AngleArc(m_value, x, y, nRadius, fStartAngle, fSweepAngle);
	}
	BOOL TinyDC::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_value != NULL); return ArcTo(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	INT TinyDC::GetArcDirection() const
	{
		ASSERT(m_value != NULL);
		return ::GetArcDirection(m_value);
	}
	BOOL TinyDC::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints,
		INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::PolyPolyline(m_value, lpPoints, lpPolyPoints, nCount);
	}
	BOOL TinyDC::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
	{
		ASSERT(m_value != NULL);
		return ::GetColorAdjustment(m_value, lpColorAdjust);
	}

	BOOL TinyDC::PolyBezier(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::PolyBezier(m_value, lpPoints, nCount);
	}

	INT TinyDC::DrawEscape(INT nEscape, INT nInputSize, LPCSTR lpszInputData)
	{
		ASSERT(m_value != NULL);
		return ::DrawEscape(m_value, nEscape, nInputSize, lpszInputData);
	}

	INT TinyDC::Escape(INT nEscape, INT nInputSize, _In_bytecount_(nInputSize) LPCSTR lpszInputData, INT nOutputSize, _Out_bytecap_(nOutputSize) LPSTR lpszOutputData)
	{
		ASSERT(m_value != NULL);
		return ::ExtEscape(m_value, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
	}

	BOOL TinyDC::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
	{
		ASSERT(m_value != NULL);
		return ::GetCharABCWidthsFloat(m_value, nFirstChar, nLastChar, lpABCF);
	}
	BOOL TinyDC::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const
	{
		ASSERT(m_value != NULL);
		return ::GetCharWidthFloat(m_value, nFirstChar, nLastChar, lpFloatBuffer);
	}

	BOOL TinyDC::AbortPath()
	{
		ASSERT(m_value != NULL);
		return ::AbortPath(m_value);
	}
	BOOL TinyDC::BeginPath()
	{
		ASSERT(m_value != NULL);
		return ::BeginPath(m_value);
	}
	BOOL TinyDC::CloseFigure()
	{
		ASSERT(m_value != NULL);
		return ::CloseFigure(m_value);
	}
	BOOL TinyDC::EndPath()
	{
		ASSERT(m_value != NULL);
		return ::EndPath(m_value);
	}
	BOOL TinyDC::FillPath()
	{
		ASSERT(m_value != NULL);
		return ::FillPath(m_value);
	}
	BOOL TinyDC::FlattenPath()
	{
		ASSERT(m_value != NULL);
		return ::FlattenPath(m_value);
	}
	float TinyDC::GetMiterLimit() const
	{
		ASSERT(m_value != NULL); float fMiterLimit;
		(::GetMiterLimit(m_value, &fMiterLimit)); return fMiterLimit;
	}
	INT TinyDC::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, INT nCount) const
	{
		ASSERT(m_value != NULL);
		return ::GetPath(m_value, lpPoints, lpTypes, nCount);
	}
	BOOL TinyDC::SetMiterLimit(float fMiterLimit)
	{
		ASSERT(m_value != NULL);
		return ::SetMiterLimit(m_value, fMiterLimit, NULL);
	}
	BOOL TinyDC::StrokeAndFillPath()
	{
		ASSERT(m_value != NULL);
		return ::StrokeAndFillPath(m_value);
	}
	BOOL TinyDC::StrokePath()
	{
		ASSERT(m_value != NULL);
		return ::StrokePath(m_value);
	}
	BOOL TinyDC::WidenPath()
	{
		ASSERT(m_value != NULL);
		return ::WidenPath(m_value);
	}

	BOOL TinyDC::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
	{
		ASSERT(m_value != NULL);
		return ::GdiComment(m_value, nDataSize, pCommentData);
	}
	BOOL TinyDC::PlayMetaFile(HENHMETAFILE hEnhMF, LPCRECT lpBounds)
	{
		ASSERT(m_value != NULL);
		return ::PlayEnhMetaFile(m_value, hEnhMF, lpBounds);
	}
	TinyDC::TinyDC()
	{

	}
	TinyDC::~TinyDC()
	{
		if (m_value != NULL)
		{
			::DeleteDC(Detach());
		}
	}

	INT TinyDC::StartDoc(LPCTSTR lpszDocName)
	{
		DOCINFO di;
		memset(&di, 0, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = lpszDocName;
		return StartDoc(&di);
	}

	INT TinyDC::SaveDC()
	{
		ASSERT(m_value != NULL);
		return ::SaveDC(m_value);
	}

	BOOL TinyDC::RestoreDC(INT nSavedDC)
	{
		ASSERT(m_value != NULL);
		return ::RestoreDC(m_value, nSavedDC);
	}

	HPEN TinyDC::SelectObject(TinyPen* ps)
	{
		ASSERT(m_value != NULL);
		return (HPEN)::SelectObject(m_value, ps->Handle());
	}

	HBRUSH TinyDC::SelectObject(TinyBrush* ps)
	{
		ASSERT(m_value != NULL);
		return (HBRUSH)::SelectObject(m_value, ps->Handle());
	}

	INT TinyDC::SelectObject(TinyRgn* ps)
	{
		ASSERT(m_value != NULL);
		return (INT)(INT_PTR)::SelectObject(m_value, ps->Handle());
	}

	HPALETTE TinyDC::SelectPalette(TinyPalette* ps, BOOL bForceBackground)
	{
		ASSERT(m_value != NULL);
		return (HPALETTE)::SelectPalette(m_value, (HPALETTE)ps->Handle(), bForceBackground);
	}

	COLORREF TinyDC::SetBkColor(COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return ::SetBkColor(m_value, crColor);
	}

	INT TinyDC::SetBkMode(INT nBkMode)
	{
		ASSERT(m_value != NULL);
		return ::SetBkMode(m_value, nBkMode);
	}

	INT TinyDC::SetPolyFillMode(INT nPolyFillMode)
	{
		ASSERT(m_value != NULL);
		return ::SetPolyFillMode(m_value, nPolyFillMode);
	}

	INT TinyDC::SetROP2(INT nDrawMode)
	{
		ASSERT(m_value != NULL);
		return ::SetROP2(m_value, nDrawMode);
	}

	INT TinyDC::SetStretchBltMode(INT nStretchMode)
	{
		ASSERT(m_value != NULL);
		return  ::SetStretchBltMode(m_value, nStretchMode);
	}

	COLORREF TinyDC::SetTextColor(COLORREF crColor)
	{
		ASSERT(m_value != NULL);
		return  ::SetTextColor(m_value, crColor);
	}

	INT TinyDC::SetGraphicsMode(INT iMode)
	{
		ASSERT(m_value != NULL);
		return ::SetGraphicsMode(m_value, iMode);
	}

	BOOL TinyDC::SetWorldTransform(const XFORM* pXform)
	{
		ASSERT(m_value != NULL);
		return ::SetWorldTransform(m_value, pXform);
	}

	BOOL TinyDC::ModifyWorldTransform(const XFORM* pXform, DWORD iMode)
	{
		ASSERT(m_value != NULL);
		return ::ModifyWorldTransform(m_value, pXform, iMode);
	}

	INT TinyDC::SetMapMode(INT nMapMode)
	{
		ASSERT(m_value != NULL);
		return ::SetMapMode(m_value, nMapMode);
	}

	TinyPoint TinyDC::SetViewportOrg(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		TinyPoint point;
		::SetViewportOrgEx(m_value, x, y, &point);
		return point;
	}

	TinyPoint TinyDC::OffsetViewportOrg(INT nWidth, INT nHeight)
	{
		ASSERT(m_value != NULL);
		TinyPoint point;
		::OffsetViewportOrgEx(m_value, nWidth, nHeight, &point);
		return point;
	}

	TinySize TinyDC::SetViewportExt(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		TinySize size;
		::SetViewportExtEx(m_value, x, y, &size);
		return size;
	}

	TinySize TinyDC::ScaleViewportExt(INT xNum, INT xDenom, INT yNum, INT yDenom)
	{
		ASSERT(m_value != NULL);
		TinySize size;
		::ScaleViewportExtEx(m_value, xNum, xDenom, yNum, yDenom, &size);
		return size;
	}

	TinyPoint TinyDC::SetWindowOrg(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		TinyPoint point;
		::SetWindowOrgEx(m_value, x, y, &point);
		return point;
	}

	TinyPoint TinyDC::OffsetWindowOrg(INT nWidth, INT nHeight)
	{
		ASSERT(m_value != NULL);
		TinyPoint point;
		::OffsetWindowOrgEx(m_value, nWidth, nHeight, &point);
		return point;
	}

	TinySize TinyDC::SetWindowExt(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		TinySize size;
		::SetWindowExtEx(m_value, x, y, &size);
		return size;
	}

	TinySize TinyDC::ScaleWindowExt(INT xNum, INT xDenom, INT yNum, INT yDenom)
	{
		ASSERT(m_value != NULL);
		TinySize size;
		::ScaleWindowExtEx(m_value, xNum, xDenom, yNum, yDenom, &size);
		return size;
	}

	INT TinyDC::GetClipBox(LPRECT lpRect) const
	{
		ASSERT(m_value != NULL);
		return ::GetClipBox(m_value, lpRect);
	}

	INT TinyDC::SelectClipRgn(TinyRgn* pRgn)
	{
		ASSERT(m_value != NULL);
		return  ::SelectClipRgn(m_value, (HRGN)pRgn->Handle());
	}

	INT TinyDC::ExcludeClipRect(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_value != NULL);
		return  ::ExcludeClipRect(m_value, x1, y1, x2, y2);
	}

	INT TinyDC::ExcludeClipRect(LPCRECT lpRect)
	{
		ASSERT(m_value != NULL);
		return ::ExcludeClipRect(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	INT TinyDC::IntersectClipRect(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_value != NULL);
		return::IntersectClipRect(m_value, x1, y1, x2, y2);
	}

	INT TinyDC::IntersectClipRect(LPCRECT lpRect)
	{
		ASSERT(m_value != NULL);
		return ::IntersectClipRect(m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	INT TinyDC::OffsetClipRgn(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		return ::OffsetClipRgn(m_value, x, y);
	}

	INT TinyDC::OffsetClipRgn(SIZE size)
	{
		ASSERT(m_value != NULL);
		return ::OffsetClipRgn(m_value, size.cx, size.cy);
	}

	TinyPoint TinyDC::MoveTo(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		TinyPoint point;
		::MoveToEx(m_value, x, y, &point);
		return point;
	}

	BOOL TinyDC::LineTo(INT x, INT y)
	{
		ASSERT(m_value != NULL);
		return ::LineTo(m_value, x, y);
	}

	UINT TinyDC::SetTextAlign(UINT nFlags)
	{
		ASSERT(m_value != NULL);
		return ::SetTextAlign(m_value, nFlags);
	}

	INT TinyDC::SetTextJustification(INT nBreakExtra, INT nBreakCount)
	{
		ASSERT(m_value != NULL);
		return ::SetTextJustification(m_value, nBreakExtra, nBreakCount);
	}

	INT TinyDC::SetTextCharacterExtra(INT nCharExtra)
	{
		ASSERT(m_value != NULL);
		return ::SetTextCharacterExtra(m_value, nCharExtra);
	}

	DWORD TinyDC::SetMapperFlags(DWORD dwFlag)
	{
		ASSERT(m_value != NULL);
		return ::SetMapperFlags(m_value, dwFlag);
	}

	BOOL TinyDC::ArcTo(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_value != NULL);
		return ::ArcTo(m_value, x1, y1, x2, y2, x3, y3, x4, y4);
	}

	INT TinyDC::SetArcDirection(INT nArcDirection)
	{
		ASSERT(m_value != NULL);
		return  ::SetArcDirection(m_value, nArcDirection);
	}

	BOOL TinyDC::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::PolyDraw(m_value, lpPoints, lpTypes, nCount);
	}

	BOOL TinyDC::PolylineTo(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::PolylineTo(m_value, lpPoints, nCount);
	}

	BOOL TinyDC::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
	{
		ASSERT(m_value != NULL);
		return ::SetColorAdjustment(m_value, lpColorAdjust);
	}

	BOOL TinyDC::PolyBezierTo(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_value != NULL);
		return ::PolyBezierTo(m_value, lpPoints, nCount);
	}

	BOOL TinyDC::SelectClipPath(INT nMode)
	{
		ASSERT(m_value != NULL);
		return ::SelectClipPath(m_value, nMode);
	}

	INT TinyDC::SelectClipRgn(TinyRgn* pRgn, INT nMode)
	{
		ASSERT(m_value != NULL);
		return ::ExtSelectClipRgn(m_value, (HRGN)pRgn->Handle(), nMode);
	}

	void TinyDC::LPtoDP(LPSIZE lpSize) const
	{
		ASSERT(lpSize);

		TinySize sizeWinExt = GetWindowExt();
		TinySize sizeVpExt = GetViewportExt();
		lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
		lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
	}

	void TinyDC::DPtoLP(LPSIZE lpSize) const
	{
		ASSERT(lpSize);

		TinySize sizeWinExt = GetWindowExt();
		TinySize sizeVpExt = GetViewportExt();
		lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
		lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
	}
	BOOL TinyDC::AlphaBlend(INT xDest, INT yDest, INT nDestWidth, INT nDestHeight,
		HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, BLENDFUNCTION blend)
	{
		return ::AlphaBlend(m_value, xDest, yDest, nDestWidth, nDestHeight, hSrcDC,
			xSrc, ySrc, nSrcWidth, nSrcHeight, blend);
	}
	BOOL TinyDC::TransparentBlt(INT xDest, INT yDest, INT nDestWidth,
		INT nDestHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth,
		INT nSrcHeight, UINT crTransparent)
	{
		return ::TransparentBlt(m_value, xDest, yDest, nDestWidth, nDestHeight, hSrcDC,
			xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent);
	}
	BOOL TinyDC::GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
		void* pMesh, ULONG nMeshElements, DWORD dwMode)
	{
		ASSERT(m_value != NULL);
		return ::GradientFill(m_value, pVertices, nVertices, pMesh, nMeshElements, dwMode);
	}
#pragma endregion
	/************************************************************************/
	/* PEN                                                                  */
	/************************************************************************/
	TinyPen::TinyPen()
	{

	}
	TinyPen::~TinyPen()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
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
	TinyHandleMap<HPEN>* TinyPen::GetMap() const
	{
		return &(TinyApplication::Instance()->GetMapHPEN());
	}
	/************************************************************************/
	/* BRUSH                                                                */
	/************************************************************************/
	TinyBrush::TinyBrush()
	{

	}
	TinyBrush::~TinyBrush()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
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
	/************************************************************************/
	/* BITMAP                                                                */
	/************************************************************************/
	TinyBitmap::TinyBitmap()
	{

	}
	TinyBitmap::~TinyBitmap()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
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
	BOOL TinyBitmap::LoadMappedBitmap(HINSTANCE hInstance, UINT nIDBitmap, UINT nFlags, LPCOLORMAP lpColorMap, INT nMapSize)
	{
		HBITMAP hBitmap = ::CreateMappedBitmap(hInstance, nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize);
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::Save(LPCTSTR pzFile)
	{
		ASSERT(pzFile != NULL);
		HDC hDC = NULL;
		INT iBits;
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
	/************************************************************************/
	/* PALETTE                                                              */
	/************************************************************************/
	TinyPalette::TinyPalette()
	{

	}
	TinyPalette::~TinyPalette()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
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
	/************************************************************************/
	/* RGN																	*/
	/************************************************************************/
	TinyRgn::TinyRgn()
	{

	}
	TinyRgn::~TinyRgn()
	{
		if (m_value != NULL)
		{
			::DeleteObject(Detach());
		}
	}
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
	INT TinyRgn::GetRegionData(LPRGNDATA lpRgnData, INT nDataSize) const
	{
		return (INT)::GetRegionData((HRGN)m_value, nDataSize, lpRgnData);
	}
	INT TinyRgn::CombineRgn(const TinyRgn* pRgn1, const TinyRgn* pRgn2, INT nCombineMode)
	{
		return ::CombineRgn((HRGN)m_value, (HRGN)pRgn1->Handle(), (HRGN)pRgn2->Handle(), nCombineMode);
	}
	INT TinyRgn::CopyRgn(const TinyRgn* pRgnSrc)
	{
		return ::CombineRgn((HRGN)m_value, (HRGN)pRgnSrc->Handle(), NULL, RGN_COPY);
	}
	BOOL TinyRgn::EqualRgn(const TinyRgn* pRgn) const
	{
		return ::EqualRgn((HRGN)m_value, (HRGN)pRgn->Handle());
	}
	INT TinyRgn::OffsetRgn(INT x, INT y)
	{
		return ::OffsetRgn((HRGN)m_value, x, y);
	}
	INT TinyRgn::OffsetRgn(POINT point)
	{
		return ::OffsetRgn((HRGN)m_value, point.x, point.y);
	}
	INT TinyRgn::GetRgnBox(LPRECT lpRect) const
	{
		return ::GetRgnBox((HRGN)m_value, lpRect);
	}
	BOOL TinyRgn::PtInRegion(INT x, INT y) const
	{
		return ::PtInRegion((HRGN)m_value, x, y);
	}
	BOOL TinyRgn::PtInRegion(POINT point) const
	{
		return ::PtInRegion((HRGN)m_value, point.x, point.y);
	}
	BOOL TinyRgn::RectInRegion(LPCRECT lpRect) const
	{
		return ::RectInRegion((HRGN)m_value, lpRect);
	}
	void TinyRgn::SetRectRgn(INT x1, INT y1, INT x2, INT y2)
	{
		::SetRectRgn((HRGN)m_value, x1, y1, x2, y2);
	}
	void TinyRgn::SetRectRgn(LPCRECT lpRect)
	{
		::SetRectRgn((HRGN)m_value, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}
	/************************************************************************/
	/* SIZE																	*/
	/************************************************************************/
	TinySize::TinySize() throw()
	{
		cx = cy = 0;
	}
	TinySize::TinySize(INT initCX, INT initCY) throw()
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
	void TinySize::SetSize(INT CX, INT CY) throw()
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
	/************************************************************************/
	/* POINT															    */
	/************************************************************************/
	TinyPoint::TinyPoint() throw()
	{  }
	TinyPoint::TinyPoint(INT initX, INT initY) throw()
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
	void TinyPoint::Offset(INT xOffset, INT yOffset) throw()
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
	void TinyPoint::SetPoint(INT X, INT Y) throw()
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

	/************************************************************************/
	/* RECTANGLE															*/
	/************************************************************************/
	TinyRectangle::TinyRectangle() throw()
	{	}
	TinyRectangle::TinyRectangle(INT l, INT t, INT r, INT b) throw()
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
	INT TinyRectangle::Width() const throw()
	{
		return right - left;
	}
	INT TinyRectangle::Height() const throw()
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
	void TinyRectangle::SetRect(INT x1, INT y1, INT x2, INT y2) throw()
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
	void TinyRectangle::InflateRect(INT x, INT y) throw()
	{
		::InflateRect(this, x, y);
	}
	void TinyRectangle::InflateRect(SIZE size) throw()
	{
		::InflateRect(this, size.cx, size.cy);
	}
	void TinyRectangle::DeflateRect(INT x, INT y) throw()
	{
		::InflateRect(this, -x, -y);
	}
	void TinyRectangle::DeflateRect(SIZE size) throw()
	{
		::InflateRect(this, -size.cx, -size.cy);
	}
	void TinyRectangle::OffsetRect(INT x, INT y) throw()
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
	void TinyRectangle::MoveToY(INT y) throw()
	{
		bottom = Height() + y; top = y;
	}
	void TinyRectangle::MoveToX(INT x) throw()
	{
		right = Width() + x; left = x;
	}
	void TinyRectangle::MoveToXY(INT x, INT y) throw()
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
		INT nTemp;
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

	void TinyRectangle::InflateRect(INT l, INT t, INT r, INT b) throw()
	{
		left -= l;			top -= t;
		right += r;			bottom += b;
	}

	void TinyRectangle::DeflateRect(LPCRECT lpRect) throw()
	{
		left += lpRect->left;	top += lpRect->top;
		right -= lpRect->right;	bottom -= lpRect->bottom;
	}

	void TinyRectangle::DeflateRect(INT l, INT t, INT r, INT b) throw()
	{
		left += l;		top += t;
		right -= r;		bottom -= b;
	}

	TinyRectangle TinyRectangle::MulDiv(INT nMultiplier, INT nDivisor) const throw()
	{
		return TinyRectangle(
			::MulDiv(left, nMultiplier, nDivisor),
			::MulDiv(top, nMultiplier, nDivisor),
			::MulDiv(right, nMultiplier, nDivisor),
			::MulDiv(bottom, nMultiplier, nDivisor));
	}
}