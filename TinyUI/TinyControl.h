#pragma once
#include "TinyWindow.h"

namespace TinyUI
{
	/// <summary>
	/// ´°¿Ú¿Ø¼þÀà
	/// </summary>
	class TinyControl : public TinyWindow
	{
		DECLARE_DYNAMIC(TinyControl)
	public:
		TinyControl();
		virtual ~TinyControl();
	private:
		static HHOOK m_pHook;
		static LRESULT CALLBACK CbtFilterHook(int code, WPARAM wParam, LPARAM lParam);
	public:
		virtual LPCSTR	RetrieveClassName();
		virtual LPCSTR	RetrieveTitle();
		virtual HICON	RetrieveIcon();
		virtual DWORD	RetrieveStyle();
		virtual DWORD	RetrieveExStyle();
		virtual BOOL	Create(HWND hParent, int x, int y, int cx, int cy, BOOL bHook = TRUE);
	public:
		BEGIN_MSG_MAP(TinyControl, TinyWindow)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_DESTROY, OnDestory)
			MESSAGE_HANDLER(WM_CLOSE, OnClose)
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)
			MESSAGE_HANDLER(WM_COMMANDREFLECT, OnCommandReflect)
			MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
			MESSAGE_HANDLER(WM_NOTIFYREFLECT, OnNotifyReflect)
			MESSAGE_HANDLER(WM_DRAWITEM + WM_REFLECT, OnDrawItemReflect)
			MESSAGE_HANDLER(WM_MEASUREITEM + WM_REFLECT, OnMeasureItemReflect)
			MESSAGE_HANDLER(WM_DELETEITEM + WM_REFLECT, OnDeleteItemReflect)
		END_MSG_MAP()
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCommandReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDeleteItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDrawItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMeasureItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	};
	__declspec(selectany) HHOOK TinyControl::m_pHook = NULL;
}


