#pragma once
#include "TinyWindowMsg.h"
#include "TinyApplication.h"

namespace TinyUI
{
	/// <summary>
	/// 对话框类
	/// </summary>
	class TinyDialog : public TinyWindowMsg, public TinyMessageFilter
	{
		DECLARE_DYNAMIC(TinyDialog)
	private:
		HWND			m_hWND;//窗口句柄
		TinyLoopThunk	m_thunk;// Thunk类
		INT_PTR			m_iDlgResult;
		BOOL			m_bModal;
		DLGPROC			m_hPrimaryProc;//原始对话框过程
		WORD			m_wInteger;
		LPCTSTR			m_pTemplateName;
		static INT_PTR CALLBACK BeginLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static INT_PTR CALLBACK EndLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		virtual void PreSubclassDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void OnFinalMessage(HWND hWnd);
		virtual BOOL DestroyWindow();
	private:
		BOOL IsDialogMessage(LPMSG lpMsg) throw();
	public:
		TinyDialog();
		virtual ~TinyDialog();
		BOOL SubclassDialog(HWND hWnd);
		LRESULT DefWindowProc();
		virtual BOOL Create(HWND hParent, WORD wInteger);
		virtual BOOL Create(HWND hParent, LPCTSTR lpTemplateName);
		virtual INT_PTR DoModal(HWND hParent = ::GetActiveWindow(), WORD wInteger = 0);
		virtual INT_PTR DoModal(HWND hParent = ::GetActiveWindow(), LPCTSTR lpTemplateName = NULL);
		BOOL MapDialogRect(LPRECT lpRect);
		BOOL EndDialog();
		BOOL EndDialog(INT_PTR m_DlgResult);
		BOOL EndDialog(HWND hWnd, INT_PTR m_DlgResult);
		BOOL IsModal() const throw();
	};
}


