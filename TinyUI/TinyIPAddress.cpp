#include "stdafx.h"
#include "TinyIPAddress.h"

namespace TinyUI
{
	TinyIPAddress::TinyIPAddress()
	{

	}
	TinyIPAddress::~TinyIPAddress()
	{

	}
	LPCSTR TinyIPAddress::RetrieveClassName()
	{
		return WC_IPADDRESS;
	}
	LPCSTR TinyIPAddress::RetrieveTitle()
	{
		return TEXT("TinyIPAddress");
	}
	DWORD TinyIPAddress::RetrieveStyle()
	{
		return (WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS);
	}
	DWORD TinyIPAddress::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE);
	}
	BOOL TinyIPAddress::Create(HWND hParent, int x, int y, int cx, int cy)
	{
		INITCOMMONCONTROLSEX initCtrls = { sizeof(INITCOMMONCONTROLSEX), ICC_INTERNET_CLASSES };
		if (InitCommonControlsEx(&initCtrls))
		{
			return TinyControl::Create(hParent, x, y, cx, cy);
		}
		return FALSE;
	}
	void TinyIPAddress::ClearAddress()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, IPM_CLEARADDRESS, 0, 0L);
	}
	BOOL TinyIPAddress::IsBlank() const
	{
		ASSERT(::IsWindow(m_hWND));
		return (BOOL) ::SendMessage(m_hWND, IPM_ISBLANK, 0, 0L);
	}
	int TinyIPAddress::GetAddress(DWORD& dwAddress) const
	{
		ASSERT(::IsWindow(m_hWND));
		return (int) ::SendMessage(m_hWND, IPM_GETADDRESS, 0, (LPARAM)&dwAddress);
	}
	void TinyIPAddress::SetAddress(DWORD dwAddress)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, IPM_SETADDRESS, 0, (LPARAM)dwAddress);
	}
	void TinyIPAddress::SetAddress(BYTE nField0, BYTE nField1, BYTE nField2, BYTE nField3)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, IPM_SETADDRESS, 0, (LPARAM)MAKEIPADDRESS(nField0, nField1, nField2, nField3));
	}
	void TinyIPAddress::SetFieldFocus(WORD nField)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, IPM_SETFOCUS, (WPARAM)nField, 0);
	}
	void TinyIPAddress::SetFieldRange(INT nField, BYTE nLower, BYTE nUpper)
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, IPM_SETRANGE, (WPARAM)nField, MAKEIPRANGE(nLower, nUpper));
	}
}
