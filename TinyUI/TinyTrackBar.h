#pragma once
#include "TinyEvent.h"
#include "TinyControl.h"

namespace TinyUI
{
	class TinyTrackBar :public TinyControl
	{
	private:
		INT currentPos;
	public:
		TinyTrackBar();
		virtual ~TinyTrackBar();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual BOOL Create(HWND hParent, int x, int y, int cx, int cy);
		BEGIN_MSG_MAP(TinyTrackBar, TinyControl)
			MESSAGE_HANDLER(WM_NOTIFY + WM_REFLECT, WmNotifyReflect)
			MESSAGE_HANDLER(WM_HSCROLL + WM_REFLECT, WmHScrollReflect)
		END_MSG_MAP()
		virtual LRESULT WmNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT WmHScrollReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		Event<void(void*, INT)> EVENT_PosChanging;
		INT GetLineSize() const;
		INT SetLineSize(INT nSize);
		INT GetPageSize() const;
		INT SetPageSize(INT nSize);
		INT GetRangeMax() const;
		INT GetRangeMin() const;
		void GetRange(INT& nMin, INT& nMax) const;
		void SetRangeMin(INT nMin, BOOL bRedraw = FALSE);
		void SetRangeMax(INT nMax, BOOL bRedraw = FALSE);
		void SetRange(INT nMin, INT nMax, BOOL bRedraw = FALSE);
		void GetSelection(INT& nMin, INT& nMax) const;
		void SetSelection(INT nMin, INT nMax);
		void GetChannelRect(LPRECT lprc) const;
		void GetThumbRect(LPRECT lprc) const;
		INT GetPos() const;
		void SetPos(int nPos);
		UINT GetNumTics() const;
		DWORD* GetTicArray() const;
		INT GetTic(INT nTic) const;
		INT GetTicPos(INT nTic) const;
		BOOL SetTic(INT nTic);
		void SetTicFreq(INT nFreq);
		HWND GetBuddy(BOOL fLocation = TRUE) const;
		HWND SetBuddy(HWND pWndBuddy, _In_ BOOL fLocation = TRUE);
		HWND GetToolTips() const;
		void SetToolTips(HWND pWndTip);
		INT SetTipSide(INT nLocation);
		void SetThumbLength(INT nLength);
		INT GetThumbLength() const;
		void ClearSel(BOOL bRedraw = FALSE);
		void ClearTics(BOOL bRedraw = FALSE);
	};
}



