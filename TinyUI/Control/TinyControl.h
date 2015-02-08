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
			MESSAGE_HANDLER(WM_SIZE, OnSize)
			MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
			MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNCMouseMove)
			MESSAGE_HANDLER(WM_NCMOUSEHOVER, OnNCMouseHover)
			MESSAGE_HANDLER(WM_NCHITTEST, OnNCHitTest)
			MESSAGE_HANDLER(WM_NCPAINT, OnNCPaint)
			MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNCLButtonDown)
			MESSAGE_HANDLER(WM_NCLBUTTONUP, OnNCLButtonUp)
			MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, OnNCLButtonDBClick)
			MESSAGE_HANDLER(WM_NCRBUTTONDOWN, OnNCRButtonDown)
			MESSAGE_HANDLER(WM_NCRBUTTONUP, OnNCRButtonUp)
			MESSAGE_HANDLER(WM_NCRBUTTONDBLCLK, OnNCRButtonDBClick)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_ERASEBKGND, OnErasebkgnd)
			MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
			MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
			MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
			MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnRButtonDBClick)
			MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
			MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
			MESSAGE_HANDLER(WM_RBUTTONDBLCLK, OnRButtonDBClick)
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)
			MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
			MESSAGE_HANDLER(WM_COMMANDREFLECT, OnCommandReflect)
			MESSAGE_HANDLER(WM_NOTIFYREFLECT, OnNotifyReflect)
			MESSAGE_HANDLER(WM_DRAWITEMREFLECT, OnDrawItemReflect)
			MESSAGE_HANDLER(WM_MEASUREITEMREFLECT, OnMeasureItemReflect)
			MESSAGE_HANDLER(WM_DELETEITEMREFLECT, OnDeleteItemReflect)
		END_MSG_MAP()
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCRButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnRButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
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


