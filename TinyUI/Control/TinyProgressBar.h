#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyProgressBar :public TinyControl
	{
		DECLARE_DYNAMIC(TinyProgressBar)
	public:
		TinyProgressBar();
		virtual ~TinyProgressBar();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		void SetRange( SHORT nLower,  SHORT nUpper);
		void SetRange32( INT nLower,  INT nUpper);
		void GetRange( INT& nLower,  INT& nUpper) const;
		INT GetPos() const;
		INT SetPos( INT nPos);
		INT OffsetPos( INT nPos);
		INT SetStep( INT nStep);
		COLORREF SetBkColor( COLORREF clrNew);
		COLORREF SetBarColor( COLORREF clrBar);
		BOOL SetMarquee( BOOL fMarqueeMode,  INT nInterval);
		INT GetStep() const;
		COLORREF GetBkColor() const;
		COLORREF GetBarColor() const;
		INT SetState( INT iState);
		INT GetState() const;
		INT StepIt();
	};
}



