#pragma once
#include "TinyWindowMsg.h"
#include "TinyApplication.h"

namespace TinyUI
{
	/// <summary>
	/// 普通窗口类
	/// </summary>
	class TinyWindow : public TinyWindowMsg, public TinyMessageFilter
	{
		DECLARE_DYNAMIC(TinyWindow)
	public:
		TinyWindow();
		TinyWindow(INT x, INT y, INT cx, INT cy);
		virtual ~TinyWindow();
	public:
		operator HWND() const;
		BOOL operator==(const TinyWindow& wnd) const;
		BOOL operator!=(const TinyWindow& wnd) const;
		BOOL SubclassDlgItem(UINT nID, HWND hDlg);
		BOOL SubclassWindow(HWND hWND);
		HWND UnsubclassWindow(BOOL bForce = FALSE);
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void PreSubclassDlgItem();
		virtual void PreSubclassWindow();
		virtual void OnFinalMessage(HWND hWnd);
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual BOOL DestroyWindow();
	protected:
		HWND			m_hWND;//窗口句柄
		TinyLoopThunk	m_thunk;// Thunk类
		WNDPROC			m_hPrimaryProc;//原始的PROC
	private:
		LRESULT DefWindowProc();
		LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK BeginLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK EndLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LPCSTR RetrieveClass(LPCTSTR lpszClass);
	};
}


