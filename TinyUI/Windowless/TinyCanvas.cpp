#include "../stdafx.h"
#include "TinyCanvas.h"

namespace TinyUI
{
	TinyCanvas::TinyCanvas()
		:m_hDC(NULL)
	{
		
	}
	TinyCanvas::~TinyCanvas()
	{

	}
	BOOL TinyCanvas::InitializeDC(HDC hDC)
	{
		m_hDC = hDC;
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
		return TRUE;
	}
};
