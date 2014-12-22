#include "stdafx.h"
#include "TinyImageList.h"

namespace TinyUI
{
	TinyImageList::TinyImageList()
		:m_hImageList(NULL)
	{

	}
	TinyImageList::~TinyImageList()
	{
		DeleteImageList();
	}
	TinyImageList* PASCAL TinyImageList::FromHandle(HIMAGELIST hImageList)
	{
		TinyImageList* pImageList = static_cast<TinyImageList*>(TinyApplication::Instance()->GetMapHIMAGELIST().FromHandle(hImageList));
		ASSERT(pImageList == NULL || pImageList->m_hImageList == hImageList);
		return pImageList;
	}
	BOOL TinyImageList::Attach(HIMAGELIST hImageList)
	{
		ASSERT(m_hImageList == NULL);
		if (hImageList == NULL)
		{
			return FALSE;
		}
		m_hImageList = hImageList;
		TinyApplication::Instance()->GetMapHIMAGELIST().AddHandle(m_hImageList, this);
		return TRUE;
	}
	HIMAGELIST TinyImageList::Detach()
	{
		HIMAGELIST hImageList = m_hImageList;
		if (hImageList != NULL)
		{
			TinyApplication::Instance()->GetMapHIMAGELIST().RemoveHandle(m_hImageList);
		}
		m_hImageList = NULL;
		return hImageList;
	}
	BOOL TinyImageList::Create(INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow)
	{
		return Attach(::ImageList_Create(cx, cy, nFlags, nInitial, nGrow));
	}

	BOOL TinyImageList::Create(TinyImageList& imagelist1, INT nImage1, TinyImageList& imagelist2, INT nImage2, INT dx, INT dy)
	{
		return Attach(::ImageList_Merge(imagelist1.m_hImageList, nImage1, imagelist2.m_hImageList, nImage2, dx, dy));
	}
	BOOL TinyImageList::Create(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask)
	{
		return Attach(::ImageList_LoadBitmap(TinyApplication::Instance()->Handle(), MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask));
	}
	BOOL TinyImageList::Create(LPCTSTR lpszBitmapID, INT cx, INT nGrow, COLORREF crMask)
	{
		return Attach(::ImageList_LoadBitmap(TinyApplication::Instance()->Handle(), lpszBitmapID, cx, nGrow, crMask));
	}
	TinyImageList::operator HIMAGELIST() const
	{
		return m_hImageList;
	}
	HIMAGELIST TinyImageList::Handle() const
	{
		return (this == NULL) ? NULL : m_hImageList;
	}
	INT TinyImageList::GetImageCount() const
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_GetImageCount(m_hImageList);
	}
	INT TinyImageList::Add(HBITMAP hBmImage, HBITMAP hBmMask)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_Add(m_hImageList, hBmImage, hBmMask);
	}
	INT TinyImageList::Add(HBITMAP hBmImage, COLORREF crMask)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_AddMasked(m_hImageList, hBmImage, crMask);
	}
	BOOL TinyImageList::Remove(INT nImage)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_Remove(m_hImageList, nImage);
	}
	BOOL TinyImageList::Replace(INT nImage, HBITMAP hBmImage, HBITMAP hBmMask)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_Replace(m_hImageList, nImage, hBmImage, hBmMask);
	}
	INT TinyImageList::Add(HICON hIcon)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_AddIcon(m_hImageList, hIcon);
	}
	INT TinyImageList::Replace(INT nImage, HICON hIcon)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_ReplaceIcon(m_hImageList, nImage, hIcon);
	}
	HICON TinyImageList::ExtractIcon(INT nImage)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_ExtractIcon(NULL, m_hImageList, nImage);
	}
	BOOL TinyImageList::Draw(HDC hDC, INT nImage, POINT pt, UINT nStyle)
	{
		ASSERT(m_hImageList != NULL);
		ASSERT(hDC != NULL);
		return ::ImageList_Draw(m_hImageList, nImage, hDC, pt.x, pt.y, nStyle);
	}
	BOOL TinyImageList::Draw(TinyDC& dc, INT nImage, TinyPoint pt, UINT nStyle)
	{
		ASSERT(m_hImageList != NULL);
		ASSERT(dc != NULL);
		return ::ImageList_Draw(m_hImageList, nImage, dc, pt.x, pt.y, nStyle);
	}
	BOOL TinyImageList::DrawEx(HDC hDC, INT nImage, POINT pt, SIZE sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle)
	{
		ASSERT(m_hImageList != NULL);
		ASSERT(hDC != NULL);
		return ::ImageList_DrawEx(m_hImageList, nImage, hDC, pt.x, pt.y, sz.cx, sz.cy, clrBk, clrFg, nStyle);
	}
	BOOL TinyImageList::DrawEx(TinyDC& dc, int nImage, TinyPoint pt, TinySize sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle)
	{
		ASSERT(m_hImageList != NULL);
		ASSERT(dc != NULL);
		return ::ImageList_DrawEx(m_hImageList, nImage, dc, pt.x, pt.y, sz.cx, sz.cy, clrBk, clrFg, nStyle);
	}
	COLORREF TinyImageList::SetBkColor(COLORREF cr)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_SetBkColor(m_hImageList, cr);
	}
	COLORREF TinyImageList::GetBkColor() const
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_GetBkColor(m_hImageList);
	}
	BOOL TinyImageList::SetOverlayImage(int nImage, int nOverlay)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_SetOverlayImage(m_hImageList, nImage, nOverlay);
	}
	BOOL TinyImageList::GetImageInfo(int nImage, IMAGEINFO* pImageInfo) const
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_GetImageInfo(m_hImageList, nImage, pImageInfo);
	}
	BOOL TinyImageList::BeginDrag(int nImage, TinyPoint ptHotSpot)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_BeginDrag(m_hImageList, nImage, ptHotSpot.x, ptHotSpot.y);
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
		ASSERT(m_hImageList != NULL);
		return ::ImageList_SetDragCursorImage(m_hImageList, nDrag, ptHotSpot.x, ptHotSpot.y);
	}
	BOOL PASCAL TinyImageList::DragShowNolock(BOOL bShow)
	{
		return ::ImageList_DragShowNolock(bShow);
	}
	TinyImageList* PASCAL TinyImageList::GetDragImage(LPPOINT lpPoint, LPPOINT lpPointHotSpot)
	{
		return TinyImageList::FromHandle(::ImageList_GetDragImage(lpPoint, lpPointHotSpot));
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
		ASSERT(m_hImageList == NULL);
		return::ImageList_Read(ps);
	}

	BOOL TinyImageList::Write(IStream* ps)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_Write(m_hImageList, ps);
	}
	BOOL TinyImageList::DrawIndirect(IMAGELISTDRAWPARAMS* pimldp)
	{
		ASSERT(m_hImageList != NULL);
		DWORD dwMajor = 0, dwMinor = 0;
		pimldp->cbSize = sizeof(IMAGELISTDRAWPARAMS);
		pimldp->himl = m_hImageList;
		return ::ImageList_DrawIndirect(pimldp);
	}

	BOOL TinyImageList::DrawIndirect(HDC hDC, int nImage, POINT pt,
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
		ASSERT(m_hImageList != NULL);
		return Attach(::ImageList_Duplicate(pImageList->m_hImageList));
	}

	BOOL TinyImageList::DeleteImageList()
	{
		if (m_hImageList == NULL)
		{
			return FALSE;
		}
		return ::ImageList_Destroy(Detach());
	}

	BOOL TinyImageList::SetImageCount(UINT uNewCount)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_SetImageCount(m_hImageList, uNewCount);
	}

	BOOL TinyImageList::Copy(int iDst, int iSrc, UINT uFlags /* = ILCF_MOVE */)
	{
		ASSERT(m_hImageList != NULL);
		return ::ImageList_Copy(m_hImageList, iDst, m_hImageList, iSrc, uFlags);
	}

	BOOL TinyImageList::Copy(int iDst, TinyImageList* pSrc, int iSrc, UINT uFlags /* = ILCF_MOVE */)
	{
		ASSERT(m_hImageList != NULL);
		ASSERT(pSrc != NULL && (HIMAGELIST)*pSrc != NULL);
		return ::ImageList_Copy(m_hImageList, iDst, *pSrc, iSrc, uFlags);
	}
}
