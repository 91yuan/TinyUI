#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyButton : public TinyControl
	{
		DECLARE_DYNAMIC(TinyButton)
	public:
		TinyButton();
		virtual ~TinyButton();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		//////////////////////////////////////////////////////////////////////////
		virtual LRESULT OnCommandReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual void OnClick(void*, INT ctrlID);
		virtual void OnDisable(void*, INT ctrlID);
		virtual void OnDoubleClick(void*, INT ctrlID);
		virtual void OnGotFocus(void*, INT ctrlID);
		virtual void OnLostFocus(void*, INT ctrlID);
		Event<void(void*, INT)> Click;
		Event<void(void*, INT)> DoubleClick;
		Event<void(void*, INT)> Disable;
		Event<void(void*, INT)> GotFocus;
		Event<void(void*, INT)> LostFocus;
		//////////////////////////////////////////////////////////////////////////
		BOOL SetText(LPCSTR pzText);
		BOOL GetText(LPSTR pzText, INT iSize);
		UINT GetState() const;
		void SetState(BOOL bHighlight);
		INT GetCheck() const;
		void SetCheck(INT nCheck);
		UINT GetButtonStyle() const;
		void SetButtonStyle(UINT nStyle, BOOL bRedraw = TRUE);
		HICON SetIcon(HICON hIcon);
		HICON GetIcon() const;
		HBITMAP SetBitmap(HBITMAP hBitmap);
		HBITMAP GetBitmap() const;
		HCURSOR SetCursor(HCURSOR hCursor);
		HCURSOR GetCursor();
		BOOL GetIdealSize(LPSIZE psize) const;
		BOOL SetImageList(PBUTTON_IMAGELIST pbuttonImagelist);
		BOOL GetImageList(PBUTTON_IMAGELIST pbuttonImagelist) const;
		BOOL SetTextMargin(LPRECT pmargin);
		BOOL GetTextMargin(LPRECT pmargin) const;
		BOOL GetNote(LPTSTR lpszNote, UINT* pcchNote) const;
		BOOL SetNote(LPCTSTR lpszNote);
		UINT GetNoteLength() const;
		BOOL GetSplitInfo(PBUTTON_SPLITINFO pInfo) const;
		BOOL SetSplitInfo(PBUTTON_SPLITINFO pInfo);
		UINT GetSplitStyle() const;
		BOOL SetSplitStyle(UINT nStyle);
		BOOL GetSplitSize(LPSIZE pSize) const;
		BOOL SetSplitSize(LPSIZE pSize);
		TCHAR GetSplitGlyph() const;
		BOOL SetSplitGlyph(TCHAR chGlyph);
		BOOL SetDropDownState(BOOL fDropDown);
		HICON SetShield(BOOL fElevationRequired);
	};
}



