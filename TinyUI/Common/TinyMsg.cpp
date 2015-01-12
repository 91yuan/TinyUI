#include "../stdafx.h"
#include "TinyMsg.h"

namespace TinyUI
{
	TinyMsg::TinyMsg() : cbSize(sizeof(TinyMsg)), bHandled(TRUE)
	{
		hwnd = NULL;
		message = 0;
		wParam = 0;
		lParam = 0;
		time = 0;
		pt.x = pt.y = 0;
	}
	TinyMsg::TinyMsg(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, DWORD dwTime, POINT ptIn, BOOL bHandledIn) : cbSize(sizeof(TinyMsg)), bHandled(bHandledIn)
	{
		hwnd = hWnd;
		message = uMsg;
		wParam = wParamIn;
		lParam = lParamIn;
		time = dwTime;
		pt = ptIn;
	}
	TinyMsg::TinyMsg(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, BOOL bHandledIn) : cbSize(sizeof(TinyMsg)), bHandled(bHandledIn)
	{
		hwnd = hWnd;
		message = uMsg;
		wParam = wParamIn;
		lParam = lParamIn;
		time = 0;
		pt.x = pt.y = 0;
	}
	TinyMsg::TinyMsg(MSG& msg, BOOL bHandledIn) : cbSize(sizeof(TinyMsg)), bHandled(bHandledIn)
	{
		hwnd = msg.hwnd;
		message = msg.message;
		wParam = msg.wParam;
		lParam = msg.lParam;
		time = msg.time;
		pt = msg.pt;
	}
	/////////////////////////////////////////////////////////////////////////
	TinyMessageFilters::TinyMessageFilters()
	{

	}
	TinyMessageFilters::~TinyMessageFilters()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyMessageFilters::Add(TinyMessageFilter*  element)
	{
		return m_array.Add(element);
	}
	BOOL TinyMessageFilters::Remove(TinyMessageFilter* element)
	{
		return m_array.Remove(element);
	}
	BOOL TinyMessageFilters::RemoveAt(INT index)
	{
		return m_array.RemoveAt(index);
	}
	void TinyMessageFilters::RemoveAll()
	{
		m_array.RemoveAll();
	}
	TinyMessageFilter* TinyMessageFilters::operator[](INT index)
	{
		return m_array[index];
	}
	const TinyMessageFilter* TinyMessageFilters::operator[](INT index) const
	{
		return m_array[index];
	}
	INT TinyMessageFilters::Lookup(TinyMessageFilter* element) const
	{
		return m_array.Lookup(element);
	}
	INT  TinyMessageFilters::GetSize() const
	{
		return m_array.GetSize();
	}
	//////////////////////////////////////////////////////////////////////////
	BOOL TinyMessageLoop::AddMessageFilter(TinyMessageFilter* pMessageFilter)
	{
		return mFilters.Add(pMessageFilter);
	}
	BOOL TinyMessageLoop::RemoveMessageFilter(TinyMessageFilter* pMessageFilter)
	{
		return mFilters.Remove(pMessageFilter);
	}
	INT TinyMessageLoop::MessageLoop()
	{
		MSG msg;
		BOOL bRet;
		while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
		{
			if (bRet == -1)
			{
				TRACE(_T("::GetMessage returned -1 (error)\n"));
			}
			else if (!bRet)
			{
				TRACE(_T("MessageLoop::Run - exiting\n"));
				break;
			}
			if (!PreTranslateMessage(&msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
		return (INT)msg.wParam;
	}
	BOOL TinyMessageLoop::PreTranslateMessage(MSG* pMsg)
	{
		for (INT i = mFilters.GetSize() - 1; i >= 0; i--)
		{
			TinyMessageFilter* pMessageFilter = mFilters[i];
			if (pMessageFilter != NULL && 
				pMessageFilter->PreTranslateMessage(pMsg))
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
}
