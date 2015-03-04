#include "../stdafx.h"
#include "TinyGraphics.h"

namespace TinyUI
{
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
	INT TinyDC::ExcludeUpdateRgn(HWND hWnd)
	{
		ASSERT(m_hDC != NULL);
		return ::ExcludeUpdateRgn(m_hDC, hWnd);
	}
	INT TinyDC::GetDeviceCaps(INT nIndex) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetDeviceCaps(m_hDC, nIndex);
	}
	TinyPoint TinyDC::GetBrushOrg() const
	{
		ASSERT(m_hDC != NULL);
		POINT point;
		::GetBrushOrgEx(m_hDC, &point);
		return point;
	}
	TinyPoint TinyDC::SetBrushOrg(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		POINT point;
		::SetBrushOrgEx(m_hDC, x, y, &point);
		return point;
	}
	TinyPoint TinyDC::SetBrushOrg(POINT point)
	{
		ASSERT(m_hDC != NULL);
		::SetBrushOrgEx(m_hDC, point.x, point.y, &point);
		return point;
	}
	INT TinyDC::EnumObjects(INT nObjectType, INT(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
	{
		ASSERT(m_hDC != NULL);
		return ::EnumObjects(m_hDC, nObjectType, (GOBJENUMPROC)lpfn, lpData);
	}
	HGDIOBJ TinyDC::SelectObject(HGDIOBJ hObject)
	{
		ASSERT(m_hDC != NULL);
		return (hObject != NULL) ? ::SelectObject(m_hDC, hObject) : NULL;
	}
	COLORREF TinyDC::GetNearestColor(COLORREF crColor) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetNearestColor(m_hDC, crColor);
	}
	UINT TinyDC::RealizePalette()
	{
		ASSERT(m_hDC != NULL);
		return ::RealizePalette(m_hDC);
	}
	void TinyDC::UpdateColors()
	{
		ASSERT(m_hDC != NULL);
		::UpdateColors(m_hDC);
	}
	COLORREF TinyDC::GetBkColor() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetBkColor(m_hDC);
	}
	INT TinyDC::GetBkMode() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetBkMode(m_hDC);
	}
	INT TinyDC::GetPolyFillMode() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetPolyFillMode(m_hDC);
	}
	INT TinyDC::GetROP2() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetROP2(m_hDC);
	}
	INT TinyDC::GetStretchBltMode() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetStretchBltMode(m_hDC);
	}
	COLORREF TinyDC::GetTextColor() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTextColor(m_hDC);
	}
	INT TinyDC::GetMapMode() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetMapMode(m_hDC);
	}
	INT TinyDC::GetGraphicsMode() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetGraphicsMode(m_hDC);
	}
	BOOL TinyDC::GetWorldTransform(XFORM* pXform) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetWorldTransform(m_hDC, pXform);
	}
	TinyPoint TinyDC::GetViewportOrg() const
	{
		ASSERT(m_hDC != NULL);
		POINT point;
		::GetViewportOrgEx(m_hDC, &point);
		return point;
	}
	TinySize TinyDC::GetViewportExt() const
	{
		ASSERT(m_hDC != NULL);
		SIZE size;
		::GetViewportExtEx(m_hDC, &size);
		return size;
	}
	TinyPoint TinyDC::GetWindowOrg() const
	{
		ASSERT(m_hDC != NULL);
		POINT point;
		::GetWindowOrgEx(m_hDC, &point);
		return point;
	}
	TinySize TinyDC::GetWindowExt() const
	{
		ASSERT(m_hDC != NULL);
		SIZE size;
		::GetWindowExtEx(m_hDC, &size);
		return size;
	}

	TinyPoint TinyDC::SetViewportOrg(POINT point)
	{
		ASSERT(m_hDC != NULL);
		return SetViewportOrg(point.x, point.y);
	}
	TinySize TinyDC::SetViewportExt(SIZE size)
	{
		ASSERT(m_hDC != NULL);
		return SetViewportExt(size.cx, size.cy);
	}
	TinyPoint TinyDC::SetWindowOrg(POINT point)
	{
		ASSERT(m_hDC != NULL);
		return SetWindowOrg(point.x, point.y);
	}
	TinySize TinyDC::SetWindowExt(SIZE size)
	{
		ASSERT(m_hDC != NULL);
		return SetWindowExt(size.cx, size.cy);
	}

	void TinyDC::DPtoLP(LPPOINT lpPoints, INT nCount) const
	{
		ASSERT(m_hDC != NULL);
		(::DPtoLP(m_hDC, lpPoints, nCount));
	}
	void TinyDC::DPtoLP(LPRECT lpRect) const
	{
		ASSERT(m_hDC != NULL);
		(::DPtoLP(m_hDC, (LPPOINT)lpRect, 2));
	}
	void TinyDC::LPtoDP(LPPOINT lpPoints, INT nCount) const
	{
		ASSERT(m_hDC != NULL);
		(::LPtoDP(m_hDC, lpPoints, nCount));
	}
	void TinyDC::LPtoDP(LPRECT lpRect) const
	{
		ASSERT(m_hDC != NULL);
		(::LPtoDP(m_hDC, (LPPOINT)lpRect, 2));
	}

	BOOL TinyDC::FillRgn(TinyRgn* pRgn, TinyBrush* pBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::FillRgn(m_hDC, (HRGN)pRgn->Handle(), (HBRUSH)pBrush->Handle());
	}
	BOOL TinyDC::FrameRgn(TinyRgn* pRgn, TinyBrush* pBrush, INT nWidth, INT nHeight)
	{
		ASSERT(m_hDC != NULL);
		return ::FrameRgn(m_hDC, (HRGN)pRgn->Handle(), (HBRUSH)pBrush->Handle(), nWidth, nHeight);
	}
	BOOL TinyDC::InvertRgn(TinyRgn* pRgn)
	{
		ASSERT(m_hDC != NULL);
		return ::InvertRgn(m_hDC, (HRGN)pRgn->Handle());
	}
	BOOL TinyDC::PaintRgn(TinyRgn* pRgn)
	{
		ASSERT(m_hDC != NULL);
		return ::PaintRgn(m_hDC, (HRGN)pRgn->Handle());
	}
	BOOL TinyDC::PtVisible(INT x, INT y) const
	{
		ASSERT(m_hDC != NULL);
		return ::PtVisible(m_hDC, x, y);
	}
	BOOL TinyDC::PtVisible(POINT point) const
	{
		ASSERT(m_hDC != NULL);
		return PtVisible(point.x, point.y);
	}
	BOOL TinyDC::RectVisible(LPCRECT lpRect) const
	{
		ASSERT(m_hDC != NULL);
		return ::RectVisible(m_hDC, lpRect);
	}
	TinyPoint TinyDC::GetCurrentPosition() const
	{
		ASSERT(m_hDC != NULL);
		POINT point;
		(::GetCurrentPositionEx(m_hDC, &point));
		return point;
	}

	TinyPoint TinyDC::MoveTo(POINT point)
	{
		ASSERT(m_hDC != NULL);
		return MoveTo(point.x, point.y);
	}
	BOOL TinyDC::LineTo(POINT point)
	{
		ASSERT(m_hDC != NULL);
		return LineTo(point.x, point.y);
	}
	BOOL TinyDC::Arc(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_hDC != NULL);
		return ::Arc(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
	}
	BOOL TinyDC::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_hDC != NULL);
		return ::Arc(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	BOOL TinyDC::Polyline(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::Polyline(m_hDC, lpPoints, nCount);
	}
	void TinyDC::FillRect(LPCRECT lpRect, HBRUSH hBrush)
	{
		ASSERT(m_hDC != NULL);
		::FillRect(m_hDC, lpRect, hBrush);
	}
	void TinyDC::FrameRect(LPCRECT lpRect, HBRUSH hBrush)
	{
		ASSERT(m_hDC != NULL);
		::FrameRect(m_hDC, lpRect, hBrush);
	}
	void TinyDC::InvertRect(LPCRECT lpRect)
	{
		ASSERT(m_hDC != NULL);
		::InvertRect(m_hDC, lpRect);
	}
	BOOL TinyDC::DrawIcon(INT x, INT y, HICON hIcon)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawIcon(m_hDC, x, y, hIcon);
	}
	BOOL TinyDC::DrawIcon(POINT point, HICON hIcon)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawIcon(m_hDC, point.x, point.y, hIcon);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, TinyBitmap* pBitmap, UINT nFlags, TinyBrush* pBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, (HBRUSH)pBrush->Handle(), NULL, (LPARAM)pBitmap->Handle(), 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, HICON hIcon, UINT nFlags, TinyBrush* pBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, (HBRUSH)pBrush->Handle(), NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON);
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText, INT nTextLen, HBRUSH hBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT));
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText, INT nTextLen, TinyBrush* pBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, (HBRUSH)pBrush->Handle(), NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT));
	}
	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, hBrush, lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_COMPLEX);
	}

	BOOL TinyDC::DrawState(TinyPoint pt, TinySize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, TinyBrush* pBrush)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawState(m_hDC, (HBRUSH)pBrush->Handle(), lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_COMPLEX);
	}

	BOOL TinyDC::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawEdge(m_hDC, lpRect, nEdge, nFlags);
	}
	BOOL TinyDC::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawFrameControl(m_hDC, lpRect, nType, nState);
	}

	BOOL TinyDC::Chord(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_hDC != NULL);
		return ::Chord(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
	}

	BOOL TinyDC::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_hDC != NULL); return ::Chord(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	void TinyDC::DrawFocusRect(LPCRECT lpRect)
	{
		ASSERT(m_hDC != NULL);
		::DrawFocusRect(m_hDC, lpRect);
	}
	BOOL TinyDC::Ellipse(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_hDC != NULL);
		return ::Ellipse(m_hDC, x1, y1, x2, y2);
	}
	BOOL TinyDC::Ellipse(LPCRECT lpRect)
	{
		ASSERT(m_hDC != NULL);
		return ::Ellipse(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}
	BOOL TinyDC::Pie(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_hDC != NULL);
		return ::Pie(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
	}
	BOOL TinyDC::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_hDC != NULL);
		return ::Pie(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	BOOL TinyDC::Polygon(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::Polygon(m_hDC, lpPoints, nCount);
	}
	BOOL TinyDC::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::PolyPolygon(m_hDC, lpPoints, lpPolyCounts, nCount);
	}
	BOOL TinyDC::Rectangle(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_hDC != NULL);
		return ::Rectangle(m_hDC, x1, y1, x2, y2);
	}

	BOOL TinyDC::Rectangle(LPCRECT lpRect)
	{
		ASSERT(m_hDC != NULL);
		return ::Rectangle(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	BOOL TinyDC::RoundRect(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
	{
		ASSERT(m_hDC != NULL);
		return ::RoundRect(m_hDC, x1, y1, x2, y2, x3, y3);
	}

	BOOL TinyDC::RoundRect(LPCRECT lpRect, POINT point)
	{
		ASSERT(m_hDC != NULL);
		return ::RoundRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, point.x, point.y);

	}
	BOOL TinyDC::PatBlt(INT x, INT y, INT nWidth, INT nHeight, DWORD dwRop)
	{
		ASSERT(m_hDC != NULL); return ::PatBlt(m_hDC, x, y, nWidth, nHeight, dwRop);
	}
	BOOL TinyDC::BitBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC, INT xSrc, INT ySrc, DWORD dwRop)
	{
		ASSERT(m_hDC != NULL); return ::BitBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, dwRop);
	}
	BOOL TinyDC::StretchBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, DWORD dwRop)
	{
		ASSERT(m_hDC != NULL);
		return ::StretchBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);
	}
	COLORREF TinyDC::GetPixel(INT x, INT y) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetPixel(m_hDC, x, y);
	}
	COLORREF TinyDC::GetPixel(POINT point) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetPixel(m_hDC, point.x, point.y);
	}
	COLORREF TinyDC::SetPixel(INT x, INT y, COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return ::SetPixel(m_hDC, x, y, crColor);
	}
	COLORREF TinyDC::SetPixel(POINT point, COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return ::SetPixel(m_hDC, point.x, point.y, crColor);
	}
	BOOL TinyDC::FloodFill(INT x, INT y, COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return ::FloodFill(m_hDC, x, y, crColor);
	}
	BOOL TinyDC::ExtFloodFill(INT x, INT y, COLORREF crColor, UINT nFillType)
	{
		ASSERT(m_hDC != NULL);
		return ::ExtFloodFill(m_hDC, x, y, crColor, nFillType);
	}
	BOOL TinyDC::TextOut(INT x, INT y, LPCTSTR lpszString, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::TextOut(m_hDC, x, y, lpszString, nCount);
	}
	BOOL TinyDC::ExtTextOut(INT x, INT y, UINT nOptions, LPCRECT lpRect, LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths)
	{
		ASSERT(m_hDC != NULL);
		return ::ExtTextOut(m_hDC, x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths);
	}
	TinySize TinyDC::TabbedTextOut(INT x, INT y, LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions, INT nTabOrigin)
	{
		ASSERT(m_hDC != NULL);
		return ::TabbedTextOut(m_hDC, x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
	}

	INT TinyDC::DrawText(LPCTSTR lpszString, INT nCount, LPRECT lpRect, UINT nFormat)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawText(m_hDC, lpszString, nCount, lpRect, nFormat);
	}

	INT TinyDC::DrawTextEx(LPTSTR lpszString, INT nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawTextEx(m_hDC, lpszString, nCount, lpRect, nFormat, lpDTParams);
	}

	TinySize TinyDC::GetTextExtent(LPCTSTR lpszString, INT nCount) const
	{
		ASSERT(m_hDC != NULL);
		SIZE size;
		(::GetTextExtentPoint32(m_hDC, lpszString, nCount, &size));
		return size;
	}

	TinySize TinyDC::GetOutputTextExtent(LPCTSTR lpszString, INT nCount) const
	{
		ASSERT(m_hDC != NULL);
		SIZE size;
		(::GetTextExtentPoint32(m_hDC, lpszString, nCount, &size));
		return size;
	}

	TinySize TinyDC::GetTabbedTextExtent(LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTabbedTextExtent(m_hDC, lpszString, nCount, nTabPositions, lpnTabStopPositions);
	}

	TinySize TinyDC::GetOutputTabbedTextExtent(LPCTSTR lpszString, INT nCount, INT nTabPositions, LPINT lpnTabStopPositions) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTabbedTextExtent(m_hDC, lpszString, nCount, nTabPositions, lpnTabStopPositions);
	}

	BOOL TinyDC::GrayString(TinyBrush* pBrush, BOOL(CALLBACK* lpfnOutput)(HDC, LPARAM, INT), LPARAM lpData, INT nCount, INT x, INT y, INT nWidth, INT nHeight)
	{
		ASSERT(m_hDC != NULL);
		return ::GrayString(m_hDC, (HBRUSH)pBrush->Handle(), (GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight);
	}

	UINT TinyDC::GetTextAlign() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTextAlign(m_hDC);
	}

	INT TinyDC::GetTextFace(INT nCount, _Out_z_cap_post_count_(nCount, return) LPTSTR lpszFacename) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTextFace(m_hDC, nCount, lpszFacename);
	}

	BOOL TinyDC::GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTextMetrics(m_hDC, lpMetrics);
	}
	INT TinyDC::GetTextCharacterExtra() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetTextCharacterExtra(m_hDC);
	}
	BOOL TinyDC::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetCharWidth(m_hDC, nFirstChar, nLastChar, lpBuffer);
	}

	BOOL TinyDC::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetCharWidth(m_hDC, nFirstChar, nLastChar, lpBuffer);
	}
	DWORD TinyDC::GetFontLanguageInfo() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetFontLanguageInfo(m_hDC);
	}

	DWORD TinyDC::GetCharacterPlacement(LPCTSTR lpString, INT nCount, INT nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetCharacterPlacement(m_hDC, lpString, nCount, nMaxExtent, lpResults, dwFlags);
	}

	TinySize TinyDC::GetAspectRatioFilter() const
	{
		ASSERT(m_hDC != NULL);
		SIZE size;
		::GetAspectRatioFilterEx(m_hDC, &size);
		return size;
	}

	BOOL TinyDC::ScrollDC(INT dx, INT dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, TinyRgn* pRgnUpdate, LPRECT lpRectUpdate)
	{
		ASSERT(m_hDC != NULL);
		return ::ScrollDC(m_hDC, dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->Handle(), lpRectUpdate);
	}

	INT TinyDC::Escape(INT nEscape, INT nCount, LPCSTR lpszInData, LPVOID lpOutData)
	{
		ASSERT(m_hDC != NULL);
		return ::Escape(m_hDC, nEscape, nCount, lpszInData, lpOutData);
	}

	UINT TinyDC::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
	{
		ASSERT(m_hDC != NULL);
		return ::SetBoundsRect(m_hDC, lpRectBounds, flags);
	}
	UINT TinyDC::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
	{
		ASSERT(m_hDC != NULL);
		return ::GetBoundsRect(m_hDC, lpRectBounds, flags);
	}
	BOOL TinyDC::ResetDC(const DEVMODE* lpDevMode)
	{
		ASSERT(m_hDC != NULL);
		return ::ResetDC(m_hDC, lpDevMode) != NULL;
	}
	UINT TinyDC::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetOutlineTextMetrics(m_hDC, cbData, lpotm);
	}
	BOOL TinyDC::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetCharABCWidths(m_hDC, nFirstChar, nLastChar, lpabc);
	}
	DWORD TinyDC::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData,
		DWORD cbData) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetFontData(m_hDC, dwTable, dwOffset, lpData, cbData);
	}

	INT TinyDC::GetKerningPairs(INT nPairs, LPKERNINGPAIR lpkrnpair) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetKerningPairs(m_hDC, nPairs, lpkrnpair);
	}

	DWORD TinyDC::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetGlyphOutline(m_hDC, nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
	}
	void TinyDC::Draw3dRect(LPCRECT lpRect,
		COLORREF clrTopLeft, COLORREF clrBottomRight)
	{
		Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
			lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
	}
	void TinyDC::FillSolidRect(LPCRECT lpRect, COLORREF clr)
	{
		ASSERT(m_hDC != NULL);
		ASSERT(lpRect != NULL);
		::SetBkColor(m_hDC, clr);
		::ExtTextOut(m_hDC, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	}

	void TinyDC::FillSolidRect(INT x, INT y, INT cx, INT cy, COLORREF clr)
	{
		ASSERT(m_hDC != NULL);
		::SetBkColor(m_hDC, clr);
		TinyRectangle rect(x, y, x + cx, y + cy);
		::ExtTextOut(m_hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
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
		ASSERT(m_hDC != NULL);
		return ::StartDoc(m_hDC, lpDocInfo);
	}
	INT TinyDC::StartPage()
	{
		ASSERT(m_hDC != NULL);
		return ::StartPage(m_hDC);
	}
	INT TinyDC::EndPage()
	{
		ASSERT(m_hDC != NULL);
		return ::EndPage(m_hDC);
	}
	INT TinyDC::SetAbortProc(BOOL(CALLBACK* lpfn)(HDC, INT))
	{
		ASSERT(m_hDC != NULL);
		return ::SetAbortProc(m_hDC, (ABORTPROC)lpfn);
	}
	INT TinyDC::AbortDoc()
	{
		ASSERT(m_hDC != NULL);
		return ::AbortDoc(m_hDC);
	}
	INT TinyDC::EndDoc()
	{
		ASSERT(m_hDC != NULL);
		return ::EndDoc(m_hDC);
	}

	BOOL TinyDC::MaskBlt(INT x, INT y, INT nWidth, INT nHeight, TinyDC* pSrcDC, INT xSrc, INT ySrc, TinyBitmap& maskBitmap, INT xMask, INT yMask, DWORD dwRop)
	{
		ASSERT(m_hDC != NULL);
		return ::MaskBlt(m_hDC, x, y, nWidth, nHeight, pSrcDC->Handle(), xSrc, ySrc, (HBITMAP)maskBitmap.m_hBITMAP, xMask, yMask, dwRop);
	}
	BOOL TinyDC::PlgBlt(LPPOINT lpPoint, TinyDC* pSrcDC, INT xSrc, INT ySrc,
		INT nWidth, INT nHeight, TinyBitmap& maskBitmap, INT xMask, INT yMask)
	{
		ASSERT(m_hDC != NULL);
		return ::PlgBlt(m_hDC, lpPoint, pSrcDC->Handle(), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.m_hBITMAP, xMask, yMask);
	}
	BOOL TinyDC::SetPixelV(INT x, INT y, COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return ::SetPixelV(m_hDC, x, y, crColor);
	}
	BOOL TinyDC::SetPixelV(POINT point, COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return ::SetPixelV(m_hDC, point.x, point.y, crColor);
	}
	BOOL TinyDC::AngleArc(INT x, INT y, INT nRadius, float fStartAngle, float fSweepAngle)
	{
		ASSERT(m_hDC != NULL);
		return ::AngleArc(m_hDC, x, y, nRadius, fStartAngle, fSweepAngle);
	}
	BOOL TinyDC::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		ASSERT(m_hDC != NULL); return ArcTo(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	INT TinyDC::GetArcDirection() const
	{
		ASSERT(m_hDC != NULL);
		return ::GetArcDirection(m_hDC);
	}
	BOOL TinyDC::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints,
		INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::PolyPolyline(m_hDC, lpPoints, lpPolyPoints, nCount);
	}
	BOOL TinyDC::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetColorAdjustment(m_hDC, lpColorAdjust);
	}

	BOOL TinyDC::PolyBezier(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::PolyBezier(m_hDC, lpPoints, nCount);
	}

	INT TinyDC::DrawEscape(INT nEscape, INT nInputSize, LPCSTR lpszInputData)
	{
		ASSERT(m_hDC != NULL);
		return ::DrawEscape(m_hDC, nEscape, nInputSize, lpszInputData);
	}

	INT TinyDC::Escape(INT nEscape, INT nInputSize, _In_bytecount_(nInputSize) LPCSTR lpszInputData, INT nOutputSize, _Out_bytecap_(nOutputSize) LPSTR lpszOutputData)
	{
		ASSERT(m_hDC != NULL);
		return ::ExtEscape(m_hDC, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
	}

	BOOL TinyDC::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetCharABCWidthsFloat(m_hDC, nFirstChar, nLastChar, lpABCF);
	}
	BOOL TinyDC::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetCharWidthFloat(m_hDC, nFirstChar, nLastChar, lpFloatBuffer);
	}

	BOOL TinyDC::AbortPath()
	{
		ASSERT(m_hDC != NULL);
		return ::AbortPath(m_hDC);
	}
	BOOL TinyDC::BeginPath()
	{
		ASSERT(m_hDC != NULL);
		return ::BeginPath(m_hDC);
	}
	BOOL TinyDC::CloseFigure()
	{
		ASSERT(m_hDC != NULL);
		return ::CloseFigure(m_hDC);
	}
	BOOL TinyDC::EndPath()
	{
		ASSERT(m_hDC != NULL);
		return ::EndPath(m_hDC);
	}
	BOOL TinyDC::FillPath()
	{
		ASSERT(m_hDC != NULL);
		return ::FillPath(m_hDC);
	}
	BOOL TinyDC::FlattenPath()
	{
		ASSERT(m_hDC != NULL);
		return ::FlattenPath(m_hDC);
	}
	float TinyDC::GetMiterLimit() const
	{
		ASSERT(m_hDC != NULL); float fMiterLimit;
		(::GetMiterLimit(m_hDC, &fMiterLimit)); return fMiterLimit;
	}
	INT TinyDC::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, INT nCount) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetPath(m_hDC, lpPoints, lpTypes, nCount);
	}
	BOOL TinyDC::SetMiterLimit(float fMiterLimit)
	{
		ASSERT(m_hDC != NULL);
		return ::SetMiterLimit(m_hDC, fMiterLimit, NULL);
	}
	BOOL TinyDC::StrokeAndFillPath()
	{
		ASSERT(m_hDC != NULL);
		return ::StrokeAndFillPath(m_hDC);
	}
	BOOL TinyDC::StrokePath()
	{
		ASSERT(m_hDC != NULL);
		return ::StrokePath(m_hDC);
	}
	BOOL TinyDC::WidenPath()
	{
		ASSERT(m_hDC != NULL);
		return ::WidenPath(m_hDC);
	}

	BOOL TinyDC::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
	{
		ASSERT(m_hDC != NULL);
		return ::GdiComment(m_hDC, nDataSize, pCommentData);
	}
	BOOL TinyDC::PlayMetaFile(HENHMETAFILE hEnhMF, LPCRECT lpBounds)
	{
		ASSERT(m_hDC != NULL);
		return ::PlayEnhMetaFile(m_hDC, hEnhMF, lpBounds);
	}
	TinyDC::TinyDC(HDC hDC)
	{
		if (hDC != NULL)
		{
			Attach(hDC);
		}
	}
	TinyDC::~TinyDC()
	{
		if (m_hDC != NULL)
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
		ASSERT(m_hDC != NULL);
		return ::SaveDC(m_hDC);
	}

	BOOL TinyDC::RestoreDC(INT nSavedDC)
	{
		ASSERT(m_hDC != NULL);
		return ::RestoreDC(m_hDC, nSavedDC);
	}

	HPEN TinyDC::SelectObject(TinyPen* ps)
	{
		ASSERT(m_hDC != NULL);
		return (HPEN)::SelectObject(m_hDC, ps->Handle());
	}

	HBRUSH TinyDC::SelectObject(TinyBrush* ps)
	{
		ASSERT(m_hDC != NULL);
		return (HBRUSH)::SelectObject(m_hDC, ps->Handle());
	}

	INT TinyDC::SelectObject(TinyRgn* ps)
	{
		ASSERT(m_hDC != NULL);
		return (INT)(INT_PTR)::SelectObject(m_hDC, ps->Handle());
	}

	HPALETTE TinyDC::SelectPalette(TinyPalette* ps, BOOL bForceBackground)
	{
		ASSERT(m_hDC != NULL);
		return (HPALETTE)::SelectPalette(m_hDC, (HPALETTE)ps->Handle(), bForceBackground);
	}

	COLORREF TinyDC::SetBkColor(COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return ::SetBkColor(m_hDC, crColor);
	}

	INT TinyDC::SetBkMode(INT nBkMode)
	{
		ASSERT(m_hDC != NULL);
		return ::SetBkMode(m_hDC, nBkMode);
	}

	INT TinyDC::SetPolyFillMode(INT nPolyFillMode)
	{
		ASSERT(m_hDC != NULL);
		return ::SetPolyFillMode(m_hDC, nPolyFillMode);
	}

	INT TinyDC::SetROP2(INT nDrawMode)
	{
		ASSERT(m_hDC != NULL);
		return ::SetROP2(m_hDC, nDrawMode);
	}

	INT TinyDC::SetStretchBltMode(INT nStretchMode)
	{
		ASSERT(m_hDC != NULL);
		return  ::SetStretchBltMode(m_hDC, nStretchMode);
	}

	COLORREF TinyDC::SetTextColor(COLORREF crColor)
	{
		ASSERT(m_hDC != NULL);
		return  ::SetTextColor(m_hDC, crColor);
	}

	INT TinyDC::SetGraphicsMode(INT iMode)
	{
		ASSERT(m_hDC != NULL);
		return ::SetGraphicsMode(m_hDC, iMode);
	}

	BOOL TinyDC::SetWorldTransform(const XFORM* pXform)
	{
		ASSERT(m_hDC != NULL);
		return ::SetWorldTransform(m_hDC, pXform);
	}

	BOOL TinyDC::ModifyWorldTransform(const XFORM* pXform, DWORD iMode)
	{
		ASSERT(m_hDC != NULL);
		return ::ModifyWorldTransform(m_hDC, pXform, iMode);
	}

	INT TinyDC::SetMapMode(INT nMapMode)
	{
		ASSERT(m_hDC != NULL);
		return ::SetMapMode(m_hDC, nMapMode);
	}

	TinyPoint TinyDC::SetViewportOrg(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		TinyPoint point;
		::SetViewportOrgEx(m_hDC, x, y, &point);
		return point;
	}

	TinyPoint TinyDC::OffsetViewportOrg(INT nWidth, INT nHeight)
	{
		ASSERT(m_hDC != NULL);
		TinyPoint point;
		::OffsetViewportOrgEx(m_hDC, nWidth, nHeight, &point);
		return point;
	}

	TinySize TinyDC::SetViewportExt(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		TinySize size;
		::SetViewportExtEx(m_hDC, x, y, &size);
		return size;
	}

	TinySize TinyDC::ScaleViewportExt(INT xNum, INT xDenom, INT yNum, INT yDenom)
	{
		ASSERT(m_hDC != NULL);
		TinySize size;
		::ScaleViewportExtEx(m_hDC, xNum, xDenom, yNum, yDenom, &size);
		return size;
	}

	TinyPoint TinyDC::SetWindowOrg(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		TinyPoint point;
		::SetWindowOrgEx(m_hDC, x, y, &point);
		return point;
	}

	TinyPoint TinyDC::OffsetWindowOrg(INT nWidth, INT nHeight)
	{
		ASSERT(m_hDC != NULL);
		TinyPoint point;
		::OffsetWindowOrgEx(m_hDC, nWidth, nHeight, &point);
		return point;
	}

	TinySize TinyDC::SetWindowExt(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		TinySize size;
		::SetWindowExtEx(m_hDC, x, y, &size);
		return size;
	}

	TinySize TinyDC::ScaleWindowExt(INT xNum, INT xDenom, INT yNum, INT yDenom)
	{
		ASSERT(m_hDC != NULL);
		TinySize size;
		::ScaleWindowExtEx(m_hDC, xNum, xDenom, yNum, yDenom, &size);
		return size;
	}

	INT TinyDC::GetClipBox(LPRECT lpRect) const
	{
		ASSERT(m_hDC != NULL);
		return ::GetClipBox(m_hDC, lpRect);
	}

	INT TinyDC::SelectClipRgn(TinyRgn* pRgn)
	{
		ASSERT(m_hDC != NULL);
		return  ::SelectClipRgn(m_hDC, (HRGN)pRgn->Handle());
	}

	INT TinyDC::ExcludeClipRect(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_hDC != NULL);
		return  ::ExcludeClipRect(m_hDC, x1, y1, x2, y2);
	}

	INT TinyDC::ExcludeClipRect(LPCRECT lpRect)
	{
		ASSERT(m_hDC != NULL);
		return ::ExcludeClipRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	INT TinyDC::IntersectClipRect(INT x1, INT y1, INT x2, INT y2)
	{
		ASSERT(m_hDC != NULL);
		return::IntersectClipRect(m_hDC, x1, y1, x2, y2);
	}

	INT TinyDC::IntersectClipRect(LPCRECT lpRect)
	{
		ASSERT(m_hDC != NULL);
		return ::IntersectClipRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	INT TinyDC::OffsetClipRgn(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		return ::OffsetClipRgn(m_hDC, x, y);
	}

	INT TinyDC::OffsetClipRgn(SIZE size)
	{
		ASSERT(m_hDC != NULL);
		return ::OffsetClipRgn(m_hDC, size.cx, size.cy);
	}

	TinyPoint TinyDC::MoveTo(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		TinyPoint point;
		::MoveToEx(m_hDC, x, y, &point);
		return point;
	}

	BOOL TinyDC::LineTo(INT x, INT y)
	{
		ASSERT(m_hDC != NULL);
		return ::LineTo(m_hDC, x, y);
	}

	UINT TinyDC::SetTextAlign(UINT nFlags)
	{
		ASSERT(m_hDC != NULL);
		return ::SetTextAlign(m_hDC, nFlags);
	}

	INT TinyDC::SetTextJustification(INT nBreakExtra, INT nBreakCount)
	{
		ASSERT(m_hDC != NULL);
		return ::SetTextJustification(m_hDC, nBreakExtra, nBreakCount);
	}

	INT TinyDC::SetTextCharacterExtra(INT nCharExtra)
	{
		ASSERT(m_hDC != NULL);
		return ::SetTextCharacterExtra(m_hDC, nCharExtra);
	}

	DWORD TinyDC::SetMapperFlags(DWORD dwFlag)
	{
		ASSERT(m_hDC != NULL);
		return ::SetMapperFlags(m_hDC, dwFlag);
	}

	BOOL TinyDC::ArcTo(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
	{
		ASSERT(m_hDC != NULL);
		return ::ArcTo(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
	}

	INT TinyDC::SetArcDirection(INT nArcDirection)
	{
		ASSERT(m_hDC != NULL);
		return  ::SetArcDirection(m_hDC, nArcDirection);
	}

	BOOL TinyDC::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::PolyDraw(m_hDC, lpPoints, lpTypes, nCount);
	}

	BOOL TinyDC::PolylineTo(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::PolylineTo(m_hDC, lpPoints, nCount);
	}

	BOOL TinyDC::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
	{
		ASSERT(m_hDC != NULL);
		return ::SetColorAdjustment(m_hDC, lpColorAdjust);
	}

	BOOL TinyDC::PolyBezierTo(const POINT* lpPoints, INT nCount)
	{
		ASSERT(m_hDC != NULL);
		return ::PolyBezierTo(m_hDC, lpPoints, nCount);
	}

	BOOL TinyDC::SelectClipPath(INT nMode)
	{
		ASSERT(m_hDC != NULL);
		return ::SelectClipPath(m_hDC, nMode);
	}

	INT TinyDC::SelectClipRgn(TinyRgn* pRgn, INT nMode)
	{
		ASSERT(m_hDC != NULL);
		return ::ExtSelectClipRgn(m_hDC, (HRGN)pRgn->Handle(), nMode);
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
		return ::AlphaBlend(m_hDC, xDest, yDest, nDestWidth, nDestHeight, hSrcDC,
			xSrc, ySrc, nSrcWidth, nSrcHeight, blend);
	}
	BOOL TinyDC::TransparentBlt(INT xDest, INT yDest, INT nDestWidth,
		INT nDestHeight, HDC hSrcDC, INT xSrc, INT ySrc, INT nSrcWidth,
		INT nSrcHeight, UINT crTransparent)
	{
		return ::TransparentBlt(m_hDC, xDest, yDest, nDestWidth, nDestHeight, hSrcDC,
			xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent);
	}
	BOOL TinyDC::GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
		void* pMesh, ULONG nMeshElements, DWORD dwMode)
	{
		ASSERT(m_hDC != NULL);
		return ::GradientFill(m_hDC, pVertices, nVertices, pMesh, nMeshElements, dwMode);
	}
#pragma endregion
	TinyMemDC::TinyMemDC(HDC hDC, INT cx, INT cy)
		:m_hDestDC(hDC)
		, m_hOldBitmap(NULL)
	{
		m_size.cx = cx;
		m_size.cy = cy;
		if (Attach(::CreateCompatibleDC(hDC)))
		{
			m_bitmap.Attach(::CreateCompatibleBitmap(hDC, cx, cy));
			m_hOldBitmap = (HBITMAP)::SelectObject(m_hDC, m_bitmap);
		}
	}
	TinyMemDC::TinyMemDC(HDC hDC, HBITMAP hBitmap)
		:m_hDestDC(hDC),
		m_hOldBitmap(NULL)
	{
		if (Attach(::CreateCompatibleDC(hDC)))
		{
			BITMAP bitmap = { 0 };
			::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
			m_size.cx = bitmap.bmWidth;
			m_size.cy = bitmap.bmHeight;
			m_hOldBitmap = (HBITMAP)::SelectObject(m_hDC, hBitmap);
		}
	}
	SIZE TinyMemDC::GetSize() const
	{
		return m_size;
	}
	BOOL TinyMemDC::Render(RECT dstPaint, RECT dstCenter, RECT srcPaint, RECT srcCenter, BOOL bAlpha)
	{
		if (dstPaint.left == dstPaint.right || dstPaint.top == dstPaint.bottom)
			return FALSE;

		RECT srcRectangles[9];
		SetRect(&srcRectangles[0], srcPaint.left, srcPaint.top, srcCenter.left, srcCenter.top);
		SetRect(&srcRectangles[1], srcCenter.left, srcPaint.top, srcCenter.right, srcCenter.top);
		SetRect(&srcRectangles[2], srcCenter.right, srcPaint.top, srcPaint.right, srcCenter.top);
		SetRect(&srcRectangles[3], srcPaint.left, srcCenter.top, srcCenter.left, srcCenter.bottom);
		SetRect(&srcRectangles[4], srcCenter.left, srcCenter.top, srcCenter.right, srcCenter.bottom);
		SetRect(&srcRectangles[5], srcCenter.right, srcCenter.top, srcPaint.right, srcCenter.bottom);
		SetRect(&srcRectangles[6], srcPaint.left, srcCenter.bottom, srcCenter.left, srcPaint.bottom);
		SetRect(&srcRectangles[7], srcCenter.left, srcCenter.bottom, srcCenter.right, srcPaint.bottom);
		SetRect(&srcRectangles[8], srcCenter.right, srcCenter.bottom, srcPaint.right, srcPaint.bottom);

		RECT dstRectangles[9];
		SetRect(&dstRectangles[0], dstPaint.left, dstPaint.top, dstCenter.left, dstCenter.top);
		SetRect(&dstRectangles[1], dstCenter.left, dstPaint.top, dstCenter.right, dstCenter.top);
		SetRect(&dstRectangles[2], dstCenter.right, dstPaint.top, dstPaint.right, dstCenter.top);
		SetRect(&dstRectangles[3], dstPaint.left, dstCenter.top, dstCenter.left, dstCenter.bottom);
		SetRect(&dstRectangles[4], dstCenter.left, dstCenter.top, dstCenter.right, dstCenter.bottom);
		SetRect(&dstRectangles[5], dstCenter.right, dstCenter.top, dstPaint.right, dstCenter.bottom);
		SetRect(&dstRectangles[6], dstPaint.left, dstCenter.bottom, dstCenter.left, dstPaint.bottom);
		SetRect(&dstRectangles[7], dstCenter.left, dstCenter.bottom, dstCenter.right, dstPaint.bottom);
		SetRect(&dstRectangles[8], dstCenter.right, dstCenter.bottom, dstPaint.right, dstPaint.bottom);

		if (bAlpha)
		{
			BLENDFUNCTION bs = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
			BOOL bRes = TRUE;
			for (INT i = 0; i < 9; i++)
			{
				INT dstCX = TO_CX(dstRectangles[i]);
				INT dstCY = TO_CY(dstRectangles[i]);
				INT srcCX = TO_CX(srcRectangles[i]);
				INT srcCY = TO_CY(srcRectangles[i]);

				if (dstCX == 0 || dstCY == 0 || srcCX == 0 || srcCY == 0)
					continue;

				bRes = ::AlphaBlend(m_hDestDC,
					dstRectangles[i].left,
					dstRectangles[i].top,
					dstCX,
					dstCY,
					m_hDC,
					srcRectangles[i].left,
					srcRectangles[i].top,
					srcCX,
					srcCY,
					bs);
				if (!bRes) return FALSE;
			}
		}
		else
		{
			BOOL bRes = TRUE;
			for (INT i = 0; i < 9; i++)
			{
				INT dstCX = TO_CX(dstRectangles[i]);
				INT dstCY = TO_CY(dstRectangles[i]);

				if (dstCX == 0 || dstCY == 0)
					continue;

				bRes = ::BitBlt(m_hDestDC,
					dstRectangles[i].left,
					dstRectangles[i].top,
					dstCX,
					dstCY,
					m_hDC,
					srcRectangles[i].left,
					srcRectangles[1].top,
					SRCCOPY);
				if (!bRes) return FALSE;
			}
		}
		return TRUE;
	}
	BOOL TinyMemDC::Render(RECT dstPaint, RECT srcPaint, BOOL bAlpha)
	{
		if (dstPaint.left == dstPaint.right || dstPaint.top == dstPaint.bottom)
			return FALSE;

		if (bAlpha)
		{
			BLENDFUNCTION bs = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
			return ::AlphaBlend(m_hDestDC,
				dstPaint.left,
				dstPaint.top,
				abs(dstPaint.right - dstPaint.left),
				abs(dstPaint.bottom - dstPaint.top),
				m_hDC,
				srcPaint.left,
				srcPaint.top,
				abs(srcPaint.right - srcPaint.left),
				abs(srcPaint.bottom - srcPaint.top),
				bs);
		}
		else
		{
			return ::BitBlt(m_hDestDC,
				dstPaint.left,
				dstPaint.top,
				abs(dstPaint.right - dstPaint.left),
				abs(dstPaint.bottom - dstPaint.top),
				m_hDC,
				srcPaint.left,
				srcPaint.top,
				SRCCOPY);
		}
	}
	TinyMemDC::~TinyMemDC()
	{
		if (m_hDC && m_hOldBitmap)
		{
			::SelectObject(m_hDC, m_hOldBitmap);
			m_hOldBitmap = NULL;
		}
	}
#pragma region  TinyGDIObject
	/************************************************************************/
	/* PEN                                                                  */
	/************************************************************************/
	TinyPen::TinyPen()
	{

	}
	TinyPen::~TinyPen()
	{
		::DeleteObject(Detach());
	}
	BOOL TinyPen::CreatePen(INT nPenStyle, INT nWidth, COLORREF crColor)
	{
		return Attach(::CreatePen(nPenStyle, nWidth, crColor));
	}
	BOOL TinyPen::CreatePen(INT nPenStyle, INT nWidth, const LOGBRUSH* pLogBrush, INT nStyleCount, const DWORD* lpStyle)
	{
		return Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle));
	}
	BOOL TinyPen::CreatePen(LPLOGPEN lpLogPen)
	{
		return Attach(::CreatePenIndirect(lpLogPen));
	}
	INT TinyPen::GetExtLogPen(EXTLOGPEN* pLogPen)
	{
		ASSERT(m_hPEN != NULL);
		return ::GetObject(m_hPEN, sizeof(EXTLOGPEN), pLogPen);
	}
	INT TinyPen::GetLogPen(LOGPEN* pLogPen)
	{
		ASSERT(m_hPEN != NULL);
		return ::GetObject(m_hPEN, sizeof(LOGPEN), pLogPen);
	}
	/************************************************************************/
	/* BRUSH                                                                */
	/************************************************************************/
	TinyBrush::TinyBrush()
	{

	}
	TinyBrush::~TinyBrush()
	{
		::DeleteObject(Detach());
	}
	BOOL TinyBrush::CreateBrush(COLORREF crColor)
	{
		return Attach(::CreateSolidBrush(crColor));
	}
	BOOL TinyBrush::CreateBrush(INT nIndex, COLORREF crColor)
	{
		return Attach(::CreateHatchBrush(nIndex, crColor));
	}
	BOOL TinyBrush::CreateBrush(HBITMAP hBitmap)
	{
		ASSERT(hBitmap != NULL);
		return Attach(::CreatePatternBrush(hBitmap));
	}
	BOOL TinyBrush::CreateBrush(const LOGBRUSH* lpLogBrush)
	{
		ASSERT(lpLogBrush != NULL);
		return Attach(::CreateBrushIndirect(lpLogBrush));
	}
	BOOL TinyBrush::CreateBrush(const void* lpPackedDIB, UINT nUsage)
	{
		ASSERT(lpPackedDIB != NULL);
		return Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
	}
	INT	 TinyBrush::GetLogBrush(LOGBRUSH* pLogBrush)
	{
		ASSERT(m_hBRUSH != NULL);
		return ::GetObject(m_hBRUSH, sizeof(LOGBRUSH), pLogBrush);
	}
	/************************************************************************/
	/* BITMAP                                                                */
	/************************************************************************/
	TinyBitmap::TinyBitmap()
	{

	}
	TinyBitmap::~TinyBitmap()
	{
		::DeleteObject(Detach());
	}
	BOOL TinyBitmap::CreateBitmap(INT nWidth, INT nHeight, UINT nPlanes, UINT nBitcount, const void* lpBits)
	{
		return Attach(::CreateBitmap(nWidth, nHeight, nPlanes, nBitcount, lpBits));
	}
	BOOL TinyBitmap::CreateBitmap(LPBITMAP lpBitmap)
	{
		return Attach(::CreateBitmapIndirect(lpBitmap));
	}
	BOOL TinyBitmap::CreateCompatibleBitmap(HDC hDC, INT nWidth, INT nHeight)
	{
		ASSERT(hDC != NULL);
		return Attach(::CreateCompatibleBitmap(hDC, nWidth, nHeight));
	}
	BOOL TinyBitmap::CreateDiscardableBitmap(HDC hDC, INT nWidth, INT nHeight)
	{
		ASSERT(hDC != NULL);
		return Attach(::CreateCompatibleBitmap(hDC, nWidth, nHeight));
	}
	INT	TinyBitmap::GetBitmap(BITMAP* pBitMap)
	{
		ASSERT(m_hBITMAP != NULL);
		ASSERT(pBitMap != NULL);
		return ::GetObject(m_hBITMAP, sizeof(BITMAP), pBitMap);
	}
	DWORD TinyBitmap::SetBitmapBits(DWORD dwCount, const void* lpBits)
	{
		return ::SetBitmapBits(m_hBITMAP, dwCount, lpBits);
	}
	DWORD TinyBitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
	{
		return ::GetBitmapBits(m_hBITMAP, dwCount, lpBits);
	}
	BOOL TinyBitmap::SetBitmapDimension(INT nWidth, INT nHeight, SIZE& size)
	{
		return ::SetBitmapDimensionEx(m_hBITMAP, nWidth, nHeight, &size);
	}
	BOOL TinyBitmap::GetBitmapDimension(SIZE& size) const
	{
		return ::GetBitmapDimensionEx(m_hBITMAP, &size);
	}
	BOOL TinyBitmap::LoadBitmap(HINSTANCE hInstance, UINT nIDResource)
	{
		return Attach(::LoadBitmap(hInstance, MAKEINTRESOURCE(nIDResource)));
	}
	BOOL TinyBitmap::LoadBitmap(HINSTANCE hInstance, LPCTSTR lpszResourceName)
	{
		return Attach(::LoadBitmap(hInstance, lpszResourceName));
	}
	BOOL TinyBitmap::LoadOEMBitmap(UINT nIDBitmap)
	{
		HBITMAP hBitmap = ::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap));
		return Attach(hBitmap);
	}
	BOOL TinyBitmap::LoadMappedBitmap(HINSTANCE hInstance, UINT nIDBitmap, UINT nFlags, LPCOLORMAP lpColorMap, INT nMapSize)
	{
		return Attach(::CreateMappedBitmap(hInstance, nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize));
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
		GetObject(m_hBITMAP, sizeof(bitmap), (LPSTR)&bitmap);
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
		GetDIBits(hDC, m_hBITMAP, 0, (UINT)bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
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
		::DeleteObject(Detach());
	}
	BOOL TinyPalette::CreatePalette(LPLOGPALETTE lpLogPalette)
	{
		return Attach(::CreatePalette(lpLogPalette));
	}
	BOOL TinyPalette::CreatePalette(HDC hDC)
	{
		HPALETTE hP = ::CreateHalftonePalette(hDC);
		return Attach(hP);
	}
	INT	 TinyPalette::GetEntryCount()
	{
		ASSERT(m_hPALETTE != NULL);
		WORD nEntries = 0;
		::GetObject(m_hPALETTE, sizeof(WORD), &nEntries);
		return (INT)nEntries;
	}
	UINT TinyPalette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
	{
		ASSERT(m_hPALETTE != NULL);
		return ::GetPaletteEntries(m_hPALETTE, nStartIndex, nNumEntries, lpPaletteColors);
	}
	UINT TinyPalette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
	{
		ASSERT(m_hPALETTE != NULL);
		return ::SetPaletteEntries(m_hPALETTE, nStartIndex, nNumEntries, lpPaletteColors);
	}
	void TinyPalette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
	{
		ASSERT(m_hPALETTE != NULL);
		::AnimatePalette(m_hPALETTE, nStartIndex, nNumEntries, lpPaletteColors);
	}
	UINT TinyPalette::GetNearestPaletteIndex(COLORREF crColor) const
	{
		ASSERT(m_hPALETTE != NULL);
		return ::GetNearestPaletteIndex(m_hPALETTE, crColor);
	}
	BOOL TinyPalette::ResizePalette(UINT nNumEntries)
	{
		ASSERT(m_hPALETTE != NULL);
		return ::ResizePalette(m_hPALETTE, nNumEntries);
	}
	/************************************************************************/
	/* RGN																	*/
	/************************************************************************/
	TinyRgn::TinyRgn()
	{

	}
	TinyRgn::~TinyRgn()
	{
		::DeleteObject(Detach());
	}
	BOOL TinyRgn::CreateRgn(INT x1, INT y1, INT x2, INT y2)
	{
		return Attach(::CreateRectRgn(x1, y1, x2, y2));
	}
	BOOL TinyRgn::CreateRgn(LPCRECT lpRect)
	{
		return Attach(::CreateRectRgnIndirect(lpRect));
	}
	BOOL TinyRgn::CreateEllipticRgn(INT x1, INT y1, INT x2, INT y2)
	{
		return Attach(::CreateEllipticRgn(x1, y1, x2, y2));
	}
	BOOL TinyRgn::CreateEllipticRgn(LPCRECT lpRect)
	{
		return Attach(::CreateEllipticRgnIndirect(lpRect));
	}
	BOOL TinyRgn::CreatePolygonRgn(LPPOINT lpPoints, INT nCount, INT nMode)
	{
		return Attach(::CreatePolygonRgn(lpPoints, nCount, nMode));
	}
	BOOL TinyRgn::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, INT nCount, INT nPolyFillMode)
	{
		return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode));
	}
	BOOL TinyRgn::CreateRoundRectRgn(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
	{
		return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3));
	}
	BOOL TinyRgn::CreateRgn(HDC hDC)
	{
		ASSERT(hDC != NULL);
		return Attach(::PathToRegion(hDC));
	}
	BOOL TinyRgn::CreateRgn(const XFORM* lpXForm, INT nCount, const RGNDATA* pRgnData)
	{
		return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData));
	}
	INT TinyRgn::GetRegionData(LPRGNDATA lpRgnData, INT nDataSize) const
	{
		return (INT)::GetRegionData(m_hHRGN, nDataSize, lpRgnData);
	}
	INT TinyRgn::CombineRgn(const TinyRgn* pRgn1, const TinyRgn* pRgn2, INT nCombineMode)
	{
		return ::CombineRgn(m_hHRGN, (HRGN)pRgn1->Handle(), (HRGN)pRgn2->Handle(), nCombineMode);
	}
	INT TinyRgn::CopyRgn(const TinyRgn* pRgnSrc)
	{
		return ::CombineRgn(m_hHRGN, (HRGN)pRgnSrc->Handle(), NULL, RGN_COPY);
	}
	BOOL TinyRgn::EqualRgn(const TinyRgn* pRgn) const
	{
		return ::EqualRgn(m_hHRGN, (HRGN)pRgn->Handle());
	}
	INT TinyRgn::OffsetRgn(INT x, INT y)
	{
		return ::OffsetRgn(m_hHRGN, x, y);
	}
	INT TinyRgn::OffsetRgn(POINT point)
	{
		return ::OffsetRgn(m_hHRGN, point.x, point.y);
	}
	INT TinyRgn::GetRgnBox(LPRECT lpRect) const
	{
		return ::GetRgnBox(m_hHRGN, lpRect);
	}
	BOOL TinyRgn::PtInRegion(INT x, INT y) const
	{
		return ::PtInRegion(m_hHRGN, x, y);
	}
	BOOL TinyRgn::PtInRegion(POINT point) const
	{
		return ::PtInRegion(m_hHRGN, point.x, point.y);
	}
	BOOL TinyRgn::RectInRegion(LPCRECT lpRect) const
	{
		return ::RectInRegion(m_hHRGN, lpRect);
	}
	void TinyRgn::SetRectRgn(INT x1, INT y1, INT x2, INT y2)
	{
		::SetRectRgn(m_hHRGN, x1, y1, x2, y2);
	}
	void TinyRgn::SetRectRgn(LPCRECT lpRect)
	{
		::SetRectRgn(m_hHRGN, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
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
#pragma endregion
}
