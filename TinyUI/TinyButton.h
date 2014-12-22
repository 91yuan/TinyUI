#pragma once
#include "TinyEvent.h"
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
		BOOL Create(HWND hParent, int x, int y, int cx, int cy);
		//////////////////////////////////////////////////////////////////////////
		virtual HRESULT OnCommand(void* sender, UINT code, UINT ctlID, BOOL& bHandled);
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
		UINT GetState() const;
		void SetState(BOOL bHighlight);
		int GetCheck() const;
		void SetCheck(int nCheck);
		UINT GetButtonStyle() const;
		void SetButtonStyle(UINT nStyle, BOOL bRedraw = TRUE);
		HICON SetIcon(HICON hIcon);
		HICON GetIcon() const;
		HBITMAP SetBitmap(HBITMAP hBitmap);
		HBITMAP GetBitmap() const;
		HCURSOR SetCursor(HCURSOR hCursor);
		HCURSOR GetCursor();
		BOOL GetIdealSize(_Out_ LPSIZE psize) const;
		BOOL SetImageList(_In_ PBUTTON_IMAGELIST pbuttonImagelist);
		BOOL GetImageList(_In_ PBUTTON_IMAGELIST pbuttonImagelist) const;
		BOOL SetTextMargin(_In_ LPRECT pmargin);
		BOOL GetTextMargin(_Out_ LPRECT pmargin) const;
		BOOL GetNote(_Out_z_cap_(*pcchNote) LPTSTR lpszNote, _Inout_ UINT* pcchNote) const;
		BOOL SetNote(_In_z_ LPCTSTR lpszNote);
		UINT GetNoteLength() const;
		BOOL GetSplitInfo(_Out_ PBUTTON_SPLITINFO pInfo) const;
		BOOL SetSplitInfo(_In_ PBUTTON_SPLITINFO pInfo);
		UINT GetSplitStyle() const;
		BOOL SetSplitStyle(_In_ UINT nStyle);
		BOOL GetSplitSize(_Out_ LPSIZE pSize) const;
		BOOL SetSplitSize(_In_ LPSIZE pSize);
		TCHAR GetSplitGlyph() const;
		BOOL SetSplitGlyph(_In_ TCHAR chGlyph);
		BOOL SetDropDownState(_In_ BOOL fDropDown);
		HICON SetShield(_In_ BOOL fElevationRequired);
	};
}



