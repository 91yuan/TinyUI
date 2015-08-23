#include "../stdafx.h"
#include "TinyCanvas.h"

namespace TinyUI
{
	TinyCanvas::TinyCanvas(HDC hDC)
		:m_hDC(hDC)
	{
		InitializeDC(hDC);
	}
	TinyCanvas::TinyCanvas()
		: m_hDC(NULL)
	{

	}
	TinyCanvas::~TinyCanvas()
	{
		if (m_hDC != NULL)
		{
			RestoreDC(m_hDC, m_iSave);
		}
	}
	BOOL TinyCanvas::InitializeDC(HDC hDC)
	{
		m_hDC = hDC;
		m_iSave = SaveDC(m_hDC);
		BOOL res = SetGraphicsMode(m_hDC, GM_ADVANCED);
		if (!res) return FALSE;
		res = SetStretchBltMode(m_hDC, HALFTONE);
		if (!res) return FALSE;
		res = SetBrushOrgEx(m_hDC, 0, 0, NULL);
		if (!res) return FALSE;
		res = SetArcDirection(m_hDC, AD_CLOCKWISE);
		if (!res) return FALSE;
		res = SetBkColor(m_hDC, RGB(255, 255, 255));
		if (res == CLR_INVALID) return FALSE;
		res = SetTextColor(m_hDC, RGB(0, 0, 0));
		if (res == CLR_INVALID) return FALSE;
		res = SetDCBrushColor(m_hDC, RGB(255, 255, 255));
		if (res == CLR_INVALID) return FALSE;
		res = SetDCPenColor(m_hDC, RGB(0, 0, 0));
		if (res == CLR_INVALID) return FALSE;
		res = SetBkMode(m_hDC, OPAQUE);
		if (!res) return FALSE;
		res = SetROP2(m_hDC, R2_COPYPEN);
		if (!res) return FALSE;
		GetWorldTransform(m_hDC, &m_matrix);
		return TRUE;
	}
	BOOL TinyCanvas::DrawImage(TinyImage& image, INT x, INT y)
	{
		if (!m_hDC) return FALSE;
		TinyMemDC menDC(m_hDC, image);
		TinyRectangle src = image.GetRectangle();
		TinyRectangle dst = src;
		dst.OffsetRect(x, y);
		return menDC.Render(dst, src, TRUE);
	}
	BOOL TinyCanvas::DrawImage(TinyImage& image, INT x, INT y, INT cx, INT cy)
	{
		if (!m_hDC) return FALSE;
		TinyMemDC menDC(m_hDC, image);
		TinyRectangle src = image.GetRectangle();
		TinyRectangle dst;
		dst.SetRect(x, y, x + cx, y + cy);
		return menDC.Render(dst, src, TRUE);
	}
	BOOL TinyCanvas::DrawImage(TinyImage& image, RECT destRect, INT srcX, INT srcY, INT srcCX, INT srcCY)
	{
		if (!m_hDC) return FALSE;
		TinyMemDC menDC(m_hDC, image);
		TinyRectangle src;
		src.SetRect(srcX, srcY, srcX + srcCX, srcY + srcCY);
		return menDC.Render(destRect, src, TRUE);
	}
	BOOL TinyCanvas::DrawLine(INT sx, INT sy, INT dx, INT dy)
	{
		if (!m_hDC) return FALSE;
		POINT ps;
		if (MoveToEx(m_hDC, sx, sy, &ps))
		{
			return LineTo(m_hDC, dx, dy);
		}
		return FALSE;
	}
	BOOL TinyCanvas::DrawLine(POINT pt1, POINT pt2)
	{
		if (!m_hDC) return FALSE;
		POINT ps;
		if (MoveToEx(m_hDC, pt1.x, pt1.y, &ps))
		{
			return LineTo(m_hDC, pt2.x, pt2.y);
		}
		return FALSE;
	}
	BOOL TinyCanvas::DrawLines(POINT* pts, INT size)
	{
		if (!m_hDC) return FALSE;
		return Polyline(m_hDC, pts, size);
	}
	BOOL TinyCanvas::DrawArc(RECT rect, FLOAT startAngle, FLOAT sweepAngle)
	{
		if (!m_hDC) return FALSE;
		INT cx = abs(rect.right - rect.left);
		INT cy = abs(rect.bottom - rect.top);
		DWORD radius = (DWORD)sqrt(cx*cx + cy*cy);
		POINT pt;
		if (MoveToEx(m_hDC, rect.left, rect.top, &pt))
		{
			return AngleArc(m_hDC, rect.left, rect.top, radius, startAngle, sweepAngle);
		}
		return FALSE;
	}
	BOOL TinyCanvas::DrawArc(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle)
	{
		if (!m_hDC) return FALSE;
		DWORD radius = (DWORD)sqrt(cx*cx + cy*cy);
		POINT pt;
		if (MoveToEx(m_hDC, x, y, &pt))
		{
			return AngleArc(m_hDC, x, y, radius, startAngle, sweepAngle);
		}
		return FALSE;
	}
	BOOL TinyCanvas::DrawRectangle(RECT rect)
	{
		if (!m_hDC) return FALSE;
		return Rectangle(m_hDC, rect.left, rect.top, rect.right, rect.bottom);
	}
	BOOL TinyCanvas::DrawRectangle(INT x, INT y, INT cx, INT cy)
	{
		if (!m_hDC) return FALSE;
		return Rectangle(m_hDC, x, y, x + cx, y + cy);
	}
	BOOL TinyCanvas::DrawBeziers(POINT* pts, INT size)
	{
		if (!m_hDC) return FALSE;
		return PolyBezier(m_hDC, pts, size);
	}
	BOOL TinyCanvas::DrawEllipse(RECT rect)
	{
		if (!m_hDC) return FALSE;
		return Ellipse(m_hDC, rect.left, rect.top, rect.right, rect.bottom);
	}
	BOOL TinyCanvas::DrawEllipse(INT x, INT y, INT cx, INT cy)
	{
		if (!m_hDC) return FALSE;
		return Ellipse(m_hDC, x, y, x + cx, y + cy);
	}
	BOOL TinyCanvas::SetClip(RECT rect)
	{
		if (!m_hDC) return FALSE;
		HRGN hRgn = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
		if (hRgn != NULL)
		{
			SelectClipRgn(m_hDC, hRgn);
			SAFE_DELETE_OBJECT(hRgn);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyCanvas::SetClip(HRGN hRgn)
	{
		if (!m_hDC || !hRgn) return FALSE;
		SelectClipRgn(m_hDC, hRgn);
		return TRUE;
	}
	BOOL TinyCanvas::SetClip(INT x, INT y, INT cx, INT cy)
	{
		if (!m_hDC) return FALSE;
		HRGN hRgn = CreateRectRgn(x, y, x + cx, y + cy);
		if (hRgn != NULL)
		{
			SelectClipRgn(m_hDC, hRgn);
			SAFE_DELETE_OBJECT(hRgn);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyCanvas::SetClip(RECT rect, INT iCombineMode)
	{
		if (!m_hDC) return FALSE;
		HRGN hRgn = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
		if (hRgn != NULL)
		{
			ExtSelectClipRgn(m_hDC, hRgn, iCombineMode);
			SAFE_DELETE_OBJECT(hRgn);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyCanvas::SetClip(HRGN hRgn, INT iCombineMode)
	{
		if (!m_hDC || !hRgn) return FALSE;
		ExtSelectClipRgn(m_hDC, hRgn, iCombineMode);
		return TRUE;
	}
	BOOL TinyCanvas::SetClip(INT x, INT y, INT cx, INT cy, INT iCombineMode)
	{
		if (!m_hDC) return FALSE;
		HRGN hRgn = CreateRectRgn(x, y, x + cx, y + cy);
		if (hRgn != NULL)
		{
			ExtSelectClipRgn(m_hDC, hRgn, iCombineMode);
			SAFE_DELETE_OBJECT(hRgn);
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyCanvas::ResetClip()
	{
		if (!m_hDC) return FALSE;
		return ExtSelectClipRgn(m_hDC, NULL, RGN_COPY) != ERROR;
	}
	BOOL TinyCanvas::IntersectClip(RECT rect)
	{
		if (!m_hDC) return FALSE;
		return IntersectClipRect(m_hDC, rect.left, rect.top, rect.right, rect.bottom) != ERROR;
	}
	BOOL TinyCanvas::IntersectClip(INT x, INT y, INT cx, INT cy)
	{
		if (!m_hDC) return FALSE;
		return IntersectClipRect(m_hDC, x, y, x + cx, y + cy) != ERROR;
	}
	BOOL TinyCanvas::IntersectClip(HRGN hRgn)
	{
		if (!m_hDC) return FALSE;
		HRGN hNewRgn = CreateRectRgn(0, 0, 0, 0);
		if (!hNewRgn) goto LABEL;
		if (GetClipRgn(m_hDC, hNewRgn) != 1)
			goto LABEL;
		if (CombineRgn(hNewRgn, hNewRgn, hRgn, RGN_AND) == ERROR)
			goto LABEL;
		SAFE_DELETE_OBJECT(hNewRgn);
		return TRUE;
	LABEL:
		SAFE_DELETE_OBJECT(hNewRgn);
		return FALSE;
	}
	BOOL TinyCanvas::ExcludeClip(RECT rect)
	{
		if (!m_hDC) return FALSE;
		return ExcludeClipRect(m_hDC, rect.left, rect.top, rect.right, rect.bottom);
	}
	BOOL TinyCanvas::ExcludeClip(INT x, INT y, INT cx, INT cy)
	{
		if (!m_hDC) return FALSE;
		return ExcludeClipRect(m_hDC, x, y, x + cx, y + cy);
	}
	BOOL TinyCanvas::ExcludeClip(HRGN hRgn)
	{
		if (!m_hDC) return FALSE;
		HRGN hNewRgn = CreateRectRgn(0, 0, 0, 0);
		if (!hNewRgn) goto LABEL;
		if (GetClipRgn(m_hDC, hNewRgn) != 1)
			goto LABEL;
		if (CombineRgn(hNewRgn, hNewRgn, hRgn, RGN_DIFF) == ERROR)
			goto LABEL;
		SAFE_DELETE_OBJECT(hNewRgn);
		return TRUE;
	LABEL:
		SAFE_DELETE_OBJECT(hNewRgn);
		return FALSE;
	}
	BOOL TinyCanvas::IsClipEmpty() const
	{
		if (!m_hDC) return FALSE;
		HRGN hNewRgn = CreateRectRgn(0, 0, 0, 0);
		BOOL bRes = GetClipRgn(m_hDC, hNewRgn) == 0;
		SAFE_DELETE_OBJECT(hNewRgn);
		return bRes;
	}
	BOOL TinyCanvas::IsVisibleClipEmpty() const
	{
		if (!m_hDC) return FALSE;
		RECT rect = { 0 };
		return GetClipBox(m_hDC, &rect) == NULLREGION;
	}
	BOOL TinyCanvas::TranslateTransform(FLOAT x, FLOAT y)
	{
		if (!m_hDC) return FALSE;
		m_matrix.SetTranslate(x, y);
		return SetWorldTransform(m_hDC, &m_matrix);
	}
	BOOL TinyCanvas::RotateTransform(FLOAT angle)
	{
		if (!m_hDC) return FALSE;
		m_matrix.SetRotate(angle);
		return SetWorldTransform(m_hDC, &m_matrix);
	}
	BOOL TinyCanvas::ScaleTransform(FLOAT sx, FLOAT sy)
	{
		if (!m_hDC) return FALSE;
		m_matrix.SetScale(sx, sy);
		return SetWorldTransform(m_hDC, &m_matrix);
	}
	BOOL TinyCanvas::ShearTransform(FLOAT sh, FLOAT sv)
	{
		if (!m_hDC) return FALSE;
		m_matrix.SetShear(sh, sv);
		return SetWorldTransform(m_hDC, &m_matrix);
	}
	BOOL TinyCanvas::ResetTransform()
	{
		if (!m_hDC) return FALSE;
		m_matrix.Reset();
		return SetWorldTransform(m_hDC, &m_matrix);
	}
};
