#pragma once
#include "../Render/TinyGraphics.h"
#include "../Common/TinyApplication.h"

namespace TinyUI
{
	class TinyImageList : public TinyObject
	{
		DECLARE_DYNAMIC(TinyImageList)
	public:
		TinyImageList();
		virtual ~TinyImageList();
		static TinyImageList* PASCAL FromHandle(HIMAGELIST hImageList);
		BOOL Create(INT cx, INT cy, UINT nFlags, INT nInitial, INT nGrow);
		BOOL Create(UINT nBitmapID, INT cx, INT nGrow, COLORREF crMask);
		BOOL Create(LPCTSTR lpszBitmapID, INT cx, INT nGrow, COLORREF crMask);
		BOOL Create(TinyImageList& imagelist1, INT nImage1, TinyImageList& imagelist2, INT nImage2, INT dx, INT dy);
		BOOL Create(TinyImageList* pImageList);
		BOOL Attach(HIMAGELIST hImageList);
		HIMAGELIST Detach();

		operator HIMAGELIST() const;
		HIMAGELIST Handle() const;

		INT GetImageCount() const;
		COLORREF SetBkColor(COLORREF cr);
		COLORREF GetBkColor() const;
		BOOL GetImageInfo(INT nImage, IMAGEINFO* pImageInfo) const;

		BOOL DeleteImageList();
		BOOL SetImageCount(UINT uNewCount);
		HIMAGELIST Read(IStream* ps);
		BOOL Write(IStream* ps);
		INT Add(HBITMAP hBmImage, HBITMAP hBmMask);
		INT Add(HBITMAP hBmImage, COLORREF crMask);
		BOOL Remove(INT nImage);
		BOOL Replace(INT nImage, HBITMAP hBmImage, HBITMAP hBmMask);
		INT Add(HICON hIcon);
		INT Replace(INT nImage, HICON hIcon);
		HICON ExtractIcon(INT nImage);
		BOOL Draw(HDC hDC, INT nImage, POINT pt, UINT nStyle);
		BOOL Draw(TinyDC& dc, INT nImage, TinyPoint pt, UINT nStyle);
		BOOL DrawEx(HDC hDC, INT nImage, POINT pt, SIZE sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle);
		BOOL DrawEx(TinyDC& dc, INT nImage, TinyPoint pt, TinySize sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle);
		BOOL SetOverlayImage(INT nImage, INT nOverlay);
		BOOL Copy(INT iDst, INT iSrc, UINT uFlags = ILCF_MOVE);
		BOOL Copy(INT iDst, TinyImageList* pSrc, INT iSrc, UINT uFlags = ILCF_MOVE);
		BOOL DrawIndirect(IMAGELISTDRAWPARAMS* pimldp);
		BOOL DrawIndirect(HDC hDC, INT nImage, POINT pt, SIZE sz, POINT ptOrigin,
			UINT fStyle = ILD_NORMAL, DWORD dwRop = SRCCOPY,
			COLORREF rgbBack = CLR_DEFAULT, COLORREF rgbFore = CLR_DEFAULT,
			DWORD fState = ILS_NORMAL, DWORD Frame = 0, COLORREF crEffect = CLR_DEFAULT);

		BOOL BeginDrag(INT nImage, TinyPoint ptHotSpot);
		BOOL SetDragCursorImage(INT nDrag, TinyPoint ptHotSpot);
		static void PASCAL EndDrag();
		static BOOL PASCAL DragMove(TinyPoint pt);
		static BOOL PASCAL DragShowNolock(BOOL bShow);
		static TinyImageList* PASCAL GetDragImage(LPPOINT lpPoint, LPPOINT lpPointHotSpot);
		static BOOL PASCAL DragEnter(HWND pWndLock, TinyPoint point);
		static BOOL PASCAL DragLeave(HWND pWndLock);
	private:
		HIMAGELIST m_hImageList;
	};
}

