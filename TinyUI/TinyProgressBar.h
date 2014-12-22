#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyProgressBar :public TinyControl
	{
	public:
		TinyProgressBar();
		virtual ~TinyProgressBar();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		void SetRange(_In_ SHORT nLower, _In_ SHORT nUpper);
		void SetRange32(_In_ INT nLower, _In_ INT nUpper);
		void GetRange(_Out_ INT& nLower, _Out_ INT& nUpper) const;
		INT GetPos() const;
		INT SetPos(_In_ INT nPos);
		INT OffsetPos(_In_ INT nPos);
		INT SetStep(_In_ INT nStep);
		COLORREF SetBkColor(_In_ COLORREF clrNew);
		COLORREF SetBarColor(_In_ COLORREF clrBar);
		BOOL SetMarquee(_In_ BOOL fMarqueeMode, _In_ INT nInterval);
		INT GetStep() const;
		COLORREF GetBkColor() const;
		COLORREF GetBarColor() const;
		INT SetState(_In_ INT iState);
		INT GetState() const;
		INT StepIt();
	};
}



