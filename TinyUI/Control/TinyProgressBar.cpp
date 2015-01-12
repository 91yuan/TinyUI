#include "stdafx.h"
#include "TinyProgressBar.h"

namespace TinyUI
{
	TinyProgressBar::TinyProgressBar()
	{
	}
	TinyProgressBar::~TinyProgressBar()
	{

	}
	LPCSTR TinyProgressBar::RetrieveClassName()
	{
		return PROGRESS_CLASS;
	}
	LPCSTR TinyProgressBar::RetrieveTitle()
	{
		return TEXT("TinyProgressBar");
	}
	DWORD TinyProgressBar::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS);
	}
	DWORD TinyProgressBar::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE);
	}
	BOOL TinyProgressBar::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_INTERNET_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	COLORREF TinyProgressBar::SetBkColor(COLORREF clrNew)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, PBM_SETBKCOLOR, 0, (LPARAM)clrNew);
	}
	void TinyProgressBar::SetRange(short nLower, short nUpper)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, PBM_SETRANGE, 0, MAKELPARAM(nLower, nUpper));
	}
	void TinyProgressBar::SetRange32(INT nLower, INT nUpper)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, PBM_SETRANGE32, (WPARAM)nLower, (LPARAM)nUpper);
	}
	INT TinyProgressBar::GetPos() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_GETPOS, 0, 0);
	}
	INT TinyProgressBar::OffsetPos(INT nPos)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_DELTAPOS, nPos, 0L);
	}
	INT TinyProgressBar::SetStep(INT nStep)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_SETSTEP, nStep, 0L);
	}
	INT TinyProgressBar::StepIt()
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_STEPIT, 0, 0L);
	}
	INT TinyProgressBar::SetPos(INT nPos)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_SETPOS, nPos, 0L);
	}

	COLORREF TinyProgressBar::SetBarColor(COLORREF clrBar)
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, PBM_SETBARCOLOR, 0, clrBar);
	}

	BOOL TinyProgressBar::SetMarquee(BOOL fMarqueeMode, INT nInterval)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, PBM_SETMARQUEE, (WPARAM)fMarqueeMode, (LPARAM)nInterval);
	}

	INT TinyProgressBar::GetStep() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_GETSTEP, 0, 0L);
	}
	COLORREF TinyProgressBar::GetBkColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, PBM_GETBKCOLOR, 0, 0L);
	}
	COLORREF TinyProgressBar::GetBarColor() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (COLORREF) ::SendMessage(m_hWND, PBM_GETBARCOLOR, 0, 0L);
	}
	INT TinyProgressBar::SetState(INT iState)
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_SETSTATE, (WPARAM)iState, 0L);
	}
	INT TinyProgressBar::GetState() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT) ::SendMessage(m_hWND, PBM_GETSTATE, 0, 0L);
	}
}