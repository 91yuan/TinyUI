#include "stdafx.h"
#include "TinyHotKey.h"

namespace TinyUI
{
	TinyHotKey::TinyHotKey()
	{
	}
	TinyHotKey::~TinyHotKey()
	{

	}
	LPCSTR TinyHotKey::RetrieveClassName()
	{
		return HOTKEY_CLASS;
	}
	LPCSTR TinyHotKey::RetrieveTitle()
	{
		return TEXT("TinyHotKey");
	}
	DWORD TinyHotKey::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS);
	}
	DWORD TinyHotKey::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE);
	}
	BOOL TinyHotKey::Create(HWND hParent, int x, int y, int cx, int cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_HOTKEY_CLASS };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	void TinyHotKey::SetHotKey(WORD wVirtualKeyCode, WORD wModifiers)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, HKM_SETHOTKEY, MAKEWORD(wVirtualKeyCode, wModifiers), 0L);
	}
	DWORD TinyHotKey::GetHotKey() const
	{
		ASSERT(::IsWindow(m_hWND));
		return DWORD(::SendMessage(m_hWND, HKM_GETHOTKEY, 0, 0L));
	}
	void TinyHotKey::SetRules(WORD wInvalidComb, WORD wModifiers)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, HKM_SETRULES, wInvalidComb, MAKELPARAM(wModifiers, 0));
	}

	void TinyHotKey::GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const
	{
		ASSERT(::IsWindow(m_hWND));
		LRESULT dw = ::SendMessage(m_hWND, HKM_GETHOTKEY, 0, 0L);
		wVirtualKeyCode = LOBYTE(LOWORD(dw));
		wModifiers = HIBYTE(LOWORD(dw));
	}
	static const TCHAR szPlus[] = _T(" + ");
}