#include "../stdafx.h"
#include "TinyGraphicsRender.h"

namespace TinyUI
{
	TinyGraphicsRender::TinyGraphicsRender(TinyDC& dc)
		:m_dc(dc)
	{

	}


	TinyGraphicsRender::~TinyGraphicsRender()
	{

	}

	void TinyGraphicsRender::DrawShadedRect(TinyRectangle& rect)
	{
		WORD bits[] =
		{
			0x0055, 0x00AA, 0x0055, 0x00AA,
			0x0055, 0x00AA, 0x0055, 0x00AA
		};
		HBITMAP hBitmap = CreateBitmap(8, 8, 1, 1, &bits);
		HBRUSH hBrush = CreatePatternBrush(hBitmap);
		HBRUSH hOldBrush = (HBRUSH)m_dc.SelectObject(hBrush);
		COLORREF backColor = m_dc.SetBkColor(COLOR_3DFACE);
		COLORREF textColor = m_dc.SetTextColor(COLOR_3DHIGHLIGHT);
		m_dc.PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
		m_dc.SelectObject(hOldBrush);
		m_dc.SetBkColor(backColor);
		m_dc.SetTextColor(textColor);
		DeleteObject(hBrush);
		DeleteObject(hBitmap);
	}
	void TinyGraphicsRender::DrawLine(TinyPoint p0, TinyPoint p1)
	{
		m_dc.MoveTo(p0);
		m_dc.LineTo(p1);
	}
}

