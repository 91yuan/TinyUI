#include "../stdafx.h"
#include "TinyHandleMap.h"
#include "TinyApplication.h"

namespace TinyUI
{
	TinyHandleHWND::TinyHandleHWND()
		:m_hWND(NULL)
	{

	}
	TinyHandleHWND::~TinyHandleHWND()
	{

	}
	TinyHandleHWND::operator HWND() const
	{
		return this == NULL ? NULL : m_hWND;
	}
	HWND TinyHandleHWND::Handle() const
	{
		return this == NULL ? NULL : m_hWND;
	}
	BOOL TinyHandleHWND::operator == (const TinyHandleHWND& obj) const
	{
		return obj.m_hWND == m_hWND;
	}
	BOOL TinyHandleHWND::operator != (const TinyHandleHWND& obj) const
	{
		return obj.m_hWND != m_hWND;
	}
	BOOL TinyHandleHWND::Attach(HWND hWND)
	{
		if (hWND == NULL)
		{
			return FALSE;
		}
		m_hWND = hWND;
		TinyHandleMap<HWND, TinyHandleHWND*> map = TinyApplication::Instance()->GetMapHWND();
		TinyHandleHWND* ps = this;
		map.Add(m_hWND, ps);
		return TRUE;
	}
	HWND TinyHandleHWND::Detach()
	{
		HWND hWND = m_hWND;
		if (hWND != NULL)
		{
			TinyHandleMap<HWND, TinyHandleHWND*> map = TinyApplication::Instance()->GetMapHWND();
			map.Remove(m_hWND);
		}
		m_hWND = NULL;
		return hWND;
	}
	TinyHandleHWND* TinyHandleHWND::Lookup(HWND hWND)
	{
		TinyHandleMap<HWND, TinyHandleHWND*> map = TinyApplication::Instance()->GetMapHWND();
		return map.Lookup(hWND);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHMENU::TinyHandleHMENU()
		:m_hMENU(NULL)
	{

	}
	TinyHandleHMENU::~TinyHandleHMENU()
	{

	}
	TinyHandleHMENU::operator HMENU() const
	{
		return this == NULL ? NULL : m_hMENU;
	}
	HMENU TinyHandleHMENU::Handle() const
	{
		return this == NULL ? NULL : m_hMENU;
	}
	BOOL TinyHandleHMENU::operator == (const TinyHandleHMENU& obj) const
	{
		return obj.m_hMENU == m_hMENU;
	}
	BOOL TinyHandleHMENU::operator != (const TinyHandleHMENU& obj) const
	{
		return obj.m_hMENU != m_hMENU;
	}
	BOOL TinyHandleHMENU::Attach(HMENU hMENU)
	{
		if (hMENU == NULL)
		{
			return FALSE;
		}
		m_hMENU = hMENU;
		TinyHandleMap<HMENU, TinyHandleHMENU*> map = TinyApplication::Instance()->GetMapHMENU();
		TinyHandleHMENU* ps = this;
		map.Add(m_hMENU, ps);
		return TRUE;
	}
	HMENU TinyHandleHMENU::Detach()
	{
		HMENU hMENU = m_hMENU;
		if (hMENU != NULL)
		{
			TinyHandleMap<HMENU, TinyHandleHMENU*> map = TinyApplication::Instance()->GetMapHMENU();
			map.Remove(m_hMENU);
		}
		m_hMENU = NULL;
		return hMENU;
	}
	TinyHandleHMENU* TinyHandleHMENU::Lookup(HMENU hMENU)
	{
		TinyHandleMap<HMENU, TinyHandleHMENU*> map = TinyApplication::Instance()->GetMapHMENU();
		return map.Lookup(hMENU);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHDC::TinyHandleHDC()
		:m_hDC(NULL)
	{

	}
	TinyHandleHDC::~TinyHandleHDC()
	{

	}
	TinyHandleHDC::operator HDC() const
	{
		return this == NULL ? NULL : m_hDC;
	}
	HDC TinyHandleHDC::Handle() const
	{
		return this == NULL ? NULL : m_hDC;
	}
	BOOL TinyHandleHDC::operator == (const TinyHandleHDC& obj) const
	{
		return obj.m_hDC == m_hDC;
	}
	BOOL TinyHandleHDC::operator != (const TinyHandleHDC& obj) const
	{
		return obj.m_hDC != m_hDC;
	}
	BOOL TinyHandleHDC::Attach(HDC hDC)
	{
		if (hDC == NULL)
		{
			return FALSE;
		}
		m_hDC = hDC;
		TinyHandleMap<HDC, TinyHandleHDC*> map = TinyApplication::Instance()->GetMapHDC();
		TinyHandleHDC* ps = this;
		map.Add(m_hDC, ps);
		return TRUE;
	}
	HDC TinyHandleHDC::Detach()
	{
		HDC hDC = m_hDC;
		if (hDC != NULL)
		{
			TinyHandleMap<HDC, TinyHandleHDC*> map = TinyApplication::Instance()->GetMapHDC();
			map.Remove(m_hDC);
		}
		m_hDC = NULL;
		return hDC;
	}
	TinyHandleHDC* TinyHandleHDC::Lookup(HDC hDC)
	{
		TinyHandleMap<HDC, TinyHandleHDC*> map = TinyApplication::Instance()->GetMapHDC();
		return map.Lookup(hDC);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHBITMAP::TinyHandleHBITMAP()
		:m_hBITMAP(NULL)
	{

	}
	TinyHandleHBITMAP::~TinyHandleHBITMAP()
	{

	}
	TinyHandleHBITMAP::operator HBITMAP() const
	{
		return this == NULL ? NULL : m_hBITMAP;
	}
	HBITMAP TinyHandleHBITMAP::Handle() const
	{
		return this == NULL ? NULL : m_hBITMAP;
	}
	BOOL TinyHandleHBITMAP::operator == (const TinyHandleHBITMAP& obj) const
	{
		return obj.m_hBITMAP == m_hBITMAP;
	}
	BOOL TinyHandleHBITMAP::operator != (const TinyHandleHBITMAP& obj) const
	{
		return obj.m_hBITMAP != m_hBITMAP;
	}
	BOOL TinyHandleHBITMAP::Attach(HBITMAP hBITMAP)
	{
		if (hBITMAP == NULL)
		{
			return FALSE;
		}
		m_hBITMAP = hBITMAP;
		TinyHandleMap<HBITMAP, TinyHandleHBITMAP*> map = TinyApplication::Instance()->GetMapHBITMAP();
		TinyHandleHBITMAP* ps = this;
		map.Add(m_hBITMAP, ps);
		return TRUE;
	}
	HBITMAP TinyHandleHBITMAP::Detach()
	{
		HBITMAP hBITMAP = m_hBITMAP;
		if (hBITMAP != NULL)
		{
			TinyHandleMap<HBITMAP, TinyHandleHBITMAP*> map = TinyApplication::Instance()->GetMapHBITMAP();
			map.Remove(m_hBITMAP);
		}
		m_hBITMAP = NULL;
		return hBITMAP;
	}
	TinyHandleHBITMAP* TinyHandleHBITMAP::Lookup(HBITMAP hBITMAP)
	{
		TinyHandleMap<HBITMAP, TinyHandleHBITMAP*> map = TinyApplication::Instance()->GetMapHBITMAP();
		return map.Lookup(hBITMAP);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHFONT::TinyHandleHFONT()
		:m_hFONT(NULL)
	{

	}
	TinyHandleHFONT::~TinyHandleHFONT()
	{

	}
	TinyHandleHFONT::operator HFONT() const
	{
		return this == NULL ? NULL : m_hFONT;
	}
	HFONT TinyHandleHFONT::Handle() const
	{
		return this == NULL ? NULL : m_hFONT;
	}
	BOOL TinyHandleHFONT::operator == (const TinyHandleHFONT& obj) const
	{
		return obj.m_hFONT == m_hFONT;
	}
	BOOL TinyHandleHFONT::operator != (const TinyHandleHFONT& obj) const
	{
		return obj.m_hFONT != m_hFONT;
	}
	BOOL TinyHandleHFONT::Attach(HFONT hFONT)
	{
		if (hFONT == NULL)
		{
			return FALSE;
		}
		m_hFONT = hFONT;
		TinyHandleMap<HFONT, TinyHandleHFONT*> map = TinyApplication::Instance()->GetMapHFONT();
		TinyHandleHFONT* ps = this;
		map.Add(m_hFONT, ps);
		return TRUE;
	}
	HFONT TinyHandleHFONT::Detach()
	{
		HFONT hFONT = m_hFONT;
		if (hFONT != NULL)
		{
			TinyHandleMap<HFONT, TinyHandleHFONT*> map = TinyApplication::Instance()->GetMapHFONT();
			map.Remove(m_hFONT);
		}
		m_hFONT = NULL;
		return hFONT;
	}
	TinyHandleHFONT* TinyHandleHFONT::Lookup(HFONT hFONT)
	{
		TinyHandleMap<HFONT, TinyHandleHFONT*> map = TinyApplication::Instance()->GetMapHFONT();
		return  map.Lookup(hFONT);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHPEN::TinyHandleHPEN()
		:m_hPEN(NULL)
	{

	}
	TinyHandleHPEN::~TinyHandleHPEN()
	{

	}
	TinyHandleHPEN::operator HPEN() const
	{
		return this == NULL ? NULL : m_hPEN;
	}
	HPEN TinyHandleHPEN::Handle() const
	{
		return this == NULL ? NULL : m_hPEN;
	}
	BOOL TinyHandleHPEN::operator == (const TinyHandleHPEN& obj) const
	{
		return obj.m_hPEN == m_hPEN;
	}
	BOOL TinyHandleHPEN::operator != (const TinyHandleHPEN& obj) const
	{
		return obj.m_hPEN != m_hPEN;
	}
	BOOL TinyHandleHPEN::Attach(HPEN hPEN)
	{
		if (hPEN == NULL)
		{
			return FALSE;
		}
		m_hPEN = hPEN;
		TinyHandleMap<HPEN, TinyHandleHPEN*> map = TinyApplication::Instance()->GetMapHPEN();
		TinyHandleHPEN* ps = this;
		map.Add(hPEN, ps);
		return TRUE;
	}
	HPEN TinyHandleHPEN::Detach()
	{
		HPEN hPEN = m_hPEN;
		if (hPEN != NULL)
		{
			TinyHandleMap<HPEN, TinyHandleHPEN*> map = TinyApplication::Instance()->GetMapHPEN();
			map.Remove(m_hPEN);
		}
		m_hPEN = NULL;
		return hPEN;
	}
	TinyHandleHPEN* TinyHandleHPEN::Lookup(HPEN hPEN)
	{
		TinyHandleMap<HPEN, TinyHandleHPEN*> map = TinyApplication::Instance()->GetMapHPEN();
		return map.Lookup(hPEN);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHBRUSH::TinyHandleHBRUSH()
		:m_hBRUSH(NULL)
	{

	}
	TinyHandleHBRUSH::~TinyHandleHBRUSH()
	{

	}
	TinyHandleHBRUSH::operator HBRUSH() const
	{
		return this == NULL ? NULL : m_hBRUSH;
	}
	HBRUSH TinyHandleHBRUSH::Handle() const
	{
		return this == NULL ? NULL : m_hBRUSH;
	}
	BOOL TinyHandleHBRUSH::operator == (const TinyHandleHBRUSH& obj) const
	{
		return obj.m_hBRUSH == m_hBRUSH;
	}
	BOOL TinyHandleHBRUSH::operator != (const TinyHandleHBRUSH& obj) const
	{
		return obj.m_hBRUSH != m_hBRUSH;
	}
	BOOL TinyHandleHBRUSH::Attach(HBRUSH hBRUSH)
	{
		if (hBRUSH == NULL)
		{
			return FALSE;
		}
		m_hBRUSH = hBRUSH;
		TinyHandleMap<HBRUSH, TinyHandleHBRUSH*> map = TinyApplication::Instance()->GetMapHBRUSH();
		TinyHandleHBRUSH* ps = this;
		map.Add(hBRUSH, ps);
		return TRUE;
	}
	HBRUSH TinyHandleHBRUSH::Detach()
	{
		HBRUSH hBRUSH = m_hBRUSH;
		if (hBRUSH != NULL)
		{
			TinyHandleMap<HBRUSH, TinyHandleHBRUSH*> map = TinyApplication::Instance()->GetMapHBRUSH();
			map.Remove(hBRUSH);
		}
		m_hBRUSH = NULL;
		return hBRUSH;
	}
	TinyHandleHBRUSH* TinyHandleHBRUSH::Lookup(HBRUSH hBRUSH)
	{
		TinyHandleMap<HBRUSH, TinyHandleHBRUSH*> map = TinyApplication::Instance()->GetMapHBRUSH();
		return map.Lookup(hBRUSH);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHPALETTE::TinyHandleHPALETTE()
		:m_hPALETTE(NULL)
	{

	}
	TinyHandleHPALETTE::~TinyHandleHPALETTE()
	{

	}
	TinyHandleHPALETTE::operator HPALETTE() const
	{
		return this == NULL ? NULL : m_hPALETTE;
	}
	HPALETTE TinyHandleHPALETTE::Handle() const
	{
		return this == NULL ? NULL : m_hPALETTE;
	}
	BOOL TinyHandleHPALETTE::operator == (const TinyHandleHPALETTE& obj) const
	{
		return obj.m_hPALETTE == m_hPALETTE;
	}
	BOOL TinyHandleHPALETTE::operator != (const TinyHandleHPALETTE& obj) const
	{
		return obj.m_hPALETTE != m_hPALETTE;
	}
	BOOL TinyHandleHPALETTE::Attach(HPALETTE hPALETTE)
	{
		if (hPALETTE == NULL)
		{
			return FALSE;
		}
		m_hPALETTE = hPALETTE;
		TinyHandleMap<HPALETTE, TinyHandleHPALETTE*> map = TinyApplication::Instance()->GetMapHPALETTE();
		TinyHandleHPALETTE* ps = this;
		map.Add(hPALETTE, ps);
		return TRUE;
	}
	HPALETTE TinyHandleHPALETTE::Detach()
	{
		HPALETTE hPALETTE = m_hPALETTE;
		if (hPALETTE != NULL)
		{
			TinyHandleMap<HPALETTE, TinyHandleHPALETTE*> map = TinyApplication::Instance()->GetMapHPALETTE();
			map.Remove(hPALETTE);
		}
		m_hPALETTE = NULL;
		return hPALETTE;
	}
	TinyHandleHPALETTE* TinyHandleHPALETTE::Lookup(HPALETTE hPALETTE)
	{
		TinyHandleMap<HPALETTE, TinyHandleHPALETTE*> map = TinyApplication::Instance()->GetMapHPALETTE();
		return map.Lookup(hPALETTE);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHRGN::TinyHandleHRGN()
		:m_hHRGN(NULL)
	{

	}
	TinyHandleHRGN::~TinyHandleHRGN()
	{

	}
	TinyHandleHRGN::operator HRGN() const
	{
		return this == NULL ? NULL : m_hHRGN;
	}
	HRGN TinyHandleHRGN::Handle() const
	{
		return this == NULL ? NULL : m_hHRGN;
	}
	BOOL TinyHandleHRGN::operator == (const TinyHandleHRGN& obj) const
	{
		return obj.m_hHRGN == m_hHRGN;
	}
	BOOL TinyHandleHRGN::operator != (const TinyHandleHRGN& obj) const
	{
		return obj.m_hHRGN != m_hHRGN;
	}
	BOOL TinyHandleHRGN::Attach(HRGN hHRGN)
	{
		if (hHRGN == NULL)
		{
			return FALSE;
		}
		m_hHRGN = hHRGN;
		TinyHandleMap<HRGN, TinyHandleHRGN*> map = TinyApplication::Instance()->GetMapHRGN();
		TinyHandleHRGN* ps = this;
		map.Add(m_hHRGN, ps);
		return TRUE;
	}
	HRGN TinyHandleHRGN::Detach()
	{
		HRGN hHRGN = m_hHRGN;
		if (hHRGN != NULL)
		{
			TinyHandleMap<HRGN, TinyHandleHRGN*> map = TinyApplication::Instance()->GetMapHRGN();
			map.Remove(hHRGN);
		}
		m_hHRGN = NULL;
		return hHRGN;
	}
	TinyHandleHRGN* TinyHandleHRGN::Lookup(HRGN hRGN)
	{
		TinyHandleMap<HRGN, TinyHandleHRGN*> map = TinyApplication::Instance()->GetMapHRGN();
		return map.Lookup(hRGN);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyHandleHIMAGELIST::TinyHandleHIMAGELIST()
		:m_hIMAGELIST(NULL)
	{

	}
	TinyHandleHIMAGELIST::~TinyHandleHIMAGELIST()
	{

	}
	TinyHandleHIMAGELIST::operator HIMAGELIST() const
	{
		return this == NULL ? NULL : m_hIMAGELIST;
	}
	HIMAGELIST TinyHandleHIMAGELIST::Handle() const
	{
		return this == NULL ? NULL : m_hIMAGELIST;
	}
	BOOL TinyHandleHIMAGELIST::operator == (const TinyHandleHIMAGELIST& obj) const
	{
		return obj.m_hIMAGELIST == m_hIMAGELIST;
	}
	BOOL TinyHandleHIMAGELIST::operator != (const TinyHandleHIMAGELIST& obj) const
	{
		return obj.m_hIMAGELIST != m_hIMAGELIST;
	}
	BOOL TinyHandleHIMAGELIST::Attach(HIMAGELIST hIMAGELIST)
	{
		if (hIMAGELIST == NULL)
		{
			return FALSE;
		}
		m_hIMAGELIST = hIMAGELIST;
		TinyHandleMap<HIMAGELIST, TinyHandleHIMAGELIST*> map = TinyApplication::Instance()->GetMapHIMAGELIST();
		TinyHandleHIMAGELIST* ps = this;
		map.Add(m_hIMAGELIST, ps);
		return TRUE;
	}
	HIMAGELIST TinyHandleHIMAGELIST::Detach()
	{
		HIMAGELIST hIMAGELIST = m_hIMAGELIST;
		if (hIMAGELIST != NULL)
		{
			TinyHandleMap<HIMAGELIST, TinyHandleHIMAGELIST*> map = TinyApplication::Instance()->GetMapHIMAGELIST();
			map.Remove(hIMAGELIST);
		}
		m_hIMAGELIST = NULL;
		return hIMAGELIST;
	}
	TinyHandleHIMAGELIST* TinyHandleHIMAGELIST::Lookup(HIMAGELIST hIMAGELIST)
	{
		TinyHandleMap<HIMAGELIST, TinyHandleHIMAGELIST*> map = TinyApplication::Instance()->GetMapHIMAGELIST();
		return map.Lookup(hIMAGELIST);
	}
}