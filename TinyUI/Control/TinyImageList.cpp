#include "../stdafx.h"
#include "TinyImageList.h"

namespace TinyUI
{
	TinyImageList::TinyImageList()
	{

	}
	TinyImageList::~TinyImageList()
	{
		DeleteImageList();
	}
	
	BOOL TinyImageList::Create(INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow)
	{
		return Attach(::ImageList_Create(cx, cy, nFlags, nInitial, nGrow));
	}

	BOOL TinyImageList::Create(TinyImageList& imagelist1, INT nImage1, TinyImageList& imagelist2, INT nImage2, INT dx, INT dy)
	{
		return Attach(::ImageList_Merge(imagelist1.m_hIMAGELIST, nImage1, imagelist2.m_hIMAGELIST, nImage2, dx, dy));
	}
	BOOL TinyImageList::Create(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask)
	{
		return Attach(::ImageList_LoadBitmap(TinyApplication::Instance()->Handle(), MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask));
	}
	BOOL TinyImageList::Create(LPCTSTR lpszBitmapID, INT cx, INT nGrow, COLORREF crMask)
	{
		return Attach(::ImageList_LoadBitmap(TinyApplication::Instance()->Handle(), lpszBitmapID, cx, nGrow, crMask));
	}

	INT TinyImageList::GetImageCount() const
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_GetImageCount(m_hIMAGELIST);
	}
	INT TinyImageList::Add(HBITMAP hBmImage, HBITMAP hBmMask)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_Add(m_hIMAGELIST, hBmImage, hBmMask);
	}
	INT TinyImageList::Add(HBITMAP hBmImage, COLORREF crMask)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_AddMasked(m_hIMAGELIST, hBmImage, crMask);
	}
	BOOL TinyImageList::Remove(INT nImage)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_Remove(m_hIMAGELIST, nImage);
	}
	BOOL TinyImageList::Replace(INT nImage, HBITMAP hBmImage, HBITMAP hBmMask)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_Replace(m_hIMAGELIST, nImage, hBmImage, hBmMask);
	}
	INT TinyImageList::Add(HICON hIcon)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_AddIcon(m_hIMAGELIST, hIcon);
	}
	INT TinyImageList::Replace(INT nImage, HICON hIcon)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_ReplaceIcon(m_hIMAGELIST, nImage, hIcon);
	}
	HICON TinyImageList::ExtractIcon(INT nImage)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_ExtractIcon(NULL, m_hIMAGELIST, nImage);
	}
	BOOL TinyImageList::Draw(HDC hDC, INT nImage, POINT pt, UINT nStyle)
	{
		ASSERT(m_hIMAGELIST != NULL);
		ASSERT(hDC != NULL);
		return ::ImageList_Draw(m_hIMAGELIST, nImage, hDC, pt.x, pt.y, nStyle);
	}
	BOOL TinyImageList::Draw(TinyDC& dc, INT nImage, TinyPoint pt, UINT nStyle)
	{
		ASSERT(m_hIMAGELIST != NULL);
		ASSERT(dc != NULL);
		return ::ImageList_Draw(m_hIMAGELIST, nImage, dc, pt.x, pt.y, nStyle);
	}
	BOOL TinyImageList::DrawEx(HDC hDC, INT nImage, POINT pt, SIZE sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle)
	{
		ASSERT(m_hIMAGELIST != NULL);
		ASSERT(hDC != NULL);
		return ::ImageList_DrawEx(m_hIMAGELIST, nImage, hDC, pt.x, pt.y, sz.cx, sz.cy, clrBk, clrFg, nStyle);
	}
	BOOL TinyImageList::DrawEx(TinyDC& dc, INT nImage, TinyPoint pt, TinySize sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle)
	{
		ASSERT(m_hIMAGELIST != NULL);
		ASSERT(dc != NULL);
		return ::ImageList_DrawEx(m_hIMAGELIST, nImage, dc, pt.x, pt.y, sz.cx, sz.cy, clrBk, clrFg, nStyle);
	}
	COLORREF TinyImageList::SetBkColor(COLORREF cr)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_SetBkColor(m_hIMAGELIST, cr);
	}
	COLORREF TinyImageList::GetBkColor() const
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_GetBkColor(m_hIMAGELIST);
	}
	BOOL TinyImageList::SetOverlayImage(INT nImage, INT nOverlay)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_SetOverlayImage(m_hIMAGELIST, nImage, nOverlay);
	}
	BOOL TinyImageList::GetImageInfo(INT nImage, IMAGEINFO* pImageInfo) const
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_GetImageInfo(m_hIMAGELIST, nImage, pImageInfo);
	}
	BOOL TinyImageList::BeginDrag(INT nImage, TinyPoint ptHotSpot)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_BeginDrag(m_hIMAGELIST, nImage, ptHotSpot.x, ptHotSpot.y);
	}
	void PASCAL TinyImageList::EndDrag()
	{
		::ImageList_EndDrag();
	}
	BOOL PASCAL TinyImageList::DragMove(TinyPoint pt)
	{
		return ::ImageList_DragMove(pt.x, pt.y);
	}
	BOOL TinyImageList::SetDragCursorImage(INT nDrag, TinyPoint ptHotSpot)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_SetDragCursorImage(m_hIMAGELIST, nDrag, ptHotSpot.x, ptHotSpot.y);
	}
	BOOL PASCAL TinyImageList::DragShowNolock(BOOL bShow)
	{
		return ::ImageList_DragShowNolock(bShow);
	}
	TinyImageList* PASCAL TinyImageList::GetDragImage(LPPOINT lpPoint, LPPOINT lpPointHotSpot)
	{
		return (TinyImageList*)TinyImageList::Lookup(::ImageList_GetDragImage(lpPoint, lpPointHotSpot));
	}
	BOOL PASCAL TinyImageList::DragEnter(HWND pWndLock, TinyPoint point)
	{
		return ::ImageList_DragEnter(pWndLock, point.x, point.y);
	}
	BOOL PASCAL TinyImageList::DragLeave(HWND pWndLock)
	{
		return ::ImageList_DragLeave(pWndLock);
	}
	HIMAGELIST TinyImageList::Read(IStream* ps)
	{
		ASSERT(m_hIMAGELIST == NULL);
		return::ImageList_Read(ps);
	}

	BOOL TinyImageList::Write(IStream* ps)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_Write(m_hIMAGELIST, ps);
	}
	BOOL TinyImageList::DrawIndirect(IMAGELISTDRAWPARAMS* pimldp)
	{
		ASSERT(m_hIMAGELIST != NULL);
		DWORD dwMajor = 0, dwMinor = 0;
		pimldp->cbSize = sizeof(IMAGELISTDRAWPARAMS);
		pimldp->himl = m_hIMAGELIST;
		return ::ImageList_DrawIndirect(pimldp);
	}

	BOOL TinyImageList::DrawIndirect(HDC hDC, INT nImage, POINT pt,
		SIZE sz, POINT ptOrigin, UINT fStyle /* = ILD_NORMAL */,
		DWORD dwRop /* = SRCCOPY */, COLORREF rgbBack /* = CLR_DEFAULT */,
		COLORREF rgbFore /* = CLR_DEFAULT */,
		DWORD fState /*= ILS_NORMAL*/, DWORD Frame /*= ILS_PULSE*/, COLORREF crEffect /*= CLR_DEFAULT*/)
	{
		ASSERT(hDC != NULL);

		IMAGELISTDRAWPARAMS drawing;
		drawing.i = nImage;
		drawing.hdcDst = hDC;
		drawing.x = pt.x;
		drawing.y = pt.y;
		drawing.cx = sz.cx;
		drawing.cy = sz.cy;
		drawing.xBitmap = ptOrigin.x;
		drawing.yBitmap = ptOrigin.y;
		drawing.rgbBk = rgbBack;
		drawing.rgbFg = rgbFore;
		drawing.fStyle = fStyle;
		drawing.dwRop = dwRop;
		drawing.fState = fState;
		drawing.Frame = Frame;
		drawing.crEffect = crEffect;
		return DrawIndirect(&drawing);
	}

	BOOL TinyImageList::Create(TinyImageList* pImageList)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return Attach(::ImageList_Duplicate(pImageList->m_hIMAGELIST));
	}

	BOOL TinyImageList::DeleteImageList()
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_Destroy(Detach());
	}

	BOOL TinyImageList::SetImageCount(UINT uNewCount)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_SetImageCount(m_hIMAGELIST, uNewCount);
	}

	BOOL TinyImageList::Copy(INT iDst, INT iSrc, UINT uFlags /* = ILCF_MOVE */)
	{
		ASSERT(m_hIMAGELIST != NULL);
		return ::ImageList_Copy(m_hIMAGELIST, iDst, m_hIMAGELIST, iSrc, uFlags);
	}

	BOOL TinyImageList::Copy(INT iDst, TinyImageList* pSrc, INT iSrc, UINT uFlags /* = ILCF_MOVE */)
	{
		ASSERT(m_hIMAGELIST != NULL);
		ASSERT(pSrc != NULL && (HIMAGELIST)*pSrc != NULL);
		return ::ImageList_Copy(m_hIMAGELIST, iDst, *pSrc, iSrc, uFlags);
	}
}
