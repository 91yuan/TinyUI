#include "../stdafx.h"
#include "TinyAnimate.h"

namespace TinyUI
{
	TinyAnimate::TinyAnimate()
	{

	}
	TinyAnimate::~TinyAnimate()
	{

	}
	LPCSTR TinyAnimate::RetrieveClassName()
	{
		return ANIMATE_CLASS;
	}
	LPCSTR TinyAnimate::RetrieveTitle()
	{
		return TEXT("TinyAnimate");
	}
	DWORD TinyAnimate::RetrieveStyle()
	{
		return  (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS);
	}
	DWORD TinyAnimate::RetrieveExStyle()
	{
		return  (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE);
	}
	BOOL TinyAnimate::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_ANIMATE_CLASS };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	BOOL TinyAnimate::Open(LPCTSTR lpszName)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_OPEN, (WPARAM) ::FindResource(TinyApplication::Instance()->Handle(), lpszName, _T("AVI")), (LPARAM)lpszName);
	}
	BOOL TinyAnimate::Open(UINT nID)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_OPEN, (WPARAM) ::FindResource(TinyApplication::Instance()->Handle(), MAKEINTRESOURCE(nID), _T("AVI")), (LPARAM)nID);
	}
	BOOL TinyAnimate::Play(UINT nFrom, UINT nTo, UINT nRep)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_PLAY, nRep, MAKELPARAM(nFrom, nTo));
	}
	BOOL TinyAnimate::Stop()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_STOP, 0, 0L);
	}
	BOOL TinyAnimate::Close()
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_OPEN, 0, 0L);
	}
	BOOL TinyAnimate::Seek(UINT nTo)
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_PLAY, 0, MAKELPARAM(nTo, nTo));
	}
	BOOL TinyAnimate::IsPlaying() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL)::SendMessage(m_hWND, ACM_ISPLAYING, 0, 0L);
	}

}
