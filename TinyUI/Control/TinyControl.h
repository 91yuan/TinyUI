#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyWindow.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// 窗口控件类
	/// </summary>
	class TinyControl : public TinyWindow
	{
		DECLARE_DYNAMIC(TinyControl)
	public:
		TinyControl();
		virtual ~TinyControl();
	private:
		static HHOOK m_pHook;
		static LRESULT CALLBACK CbtFilterHook(INT code, WPARAM wParam, LPARAM lParam);
		//5个创建窗口函数
	public:
		virtual LPCSTR	RetrieveClassName();
		virtual LPCSTR	RetrieveTitle();
		virtual HICON	RetrieveIcon();
		virtual DWORD	RetrieveStyle();
		virtual DWORD	RetrieveExStyle();
		virtual BOOL	Create(HWND hParent, INT x, INT y, INT cx, INT cy, BOOL bHook = TRUE);
	public:
		BEGIN_MSG_MAP(TinyControl, TinyWindow)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_DESTROY, OnDestory)
			MESSAGE_HANDLER(WM_CLOSE, OnClose)
			MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)
			MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_ERASEBKGND, OnErasebkgnd)
			MESSAGE_HANDLER(WM_COMMANDREFLECT, OnCommandReflect)
			MESSAGE_HANDLER(WM_NOTIFYREFLECT, OnNotifyReflect)
			MESSAGE_HANDLER(WM_DRAWITEMREFLECT, OnDrawItemReflect)
			MESSAGE_HANDLER(WM_MEASUREITEMREFLECT, OnMeasureItemReflect)
			MESSAGE_HANDLER(WM_DELETEITEMREFLECT, OnDeleteItemReflect)
		END_MSG_MAP()
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
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


