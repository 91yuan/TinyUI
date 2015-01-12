#include "../stdafx.h"
#include "TinyDialog.h"

namespace TinyUI
{
	TinyDialog::TinyDialog() :
		m_bModal(FALSE),
		m_iDlgResult(0),
		m_hPrimaryProc(NULL),
		m_hWND(NULL),
		m_pTemplateName(NULL)

	{

	}
	TinyDialog::~TinyDialog()
	{
		if (m_hWND != NULL)
		{
			if (IsModal())
			{
				EndDialog(m_iDlgResult);
			}
			else
			{
				DestroyWindow();
			}
			m_iDlgResult = 0;
			m_bModal = FALSE;
			m_hWND = NULL;
		}
	}
	void TinyDialog::PreSubclassDialog()
	{

	}
	BOOL TinyDialog::PreTranslateMessage(MSG* pMsg)
	{
		return IsDialogMessage(pMsg);
	}
	LRESULT TinyDialog::DefWindowProc()
	{
		return FALSE;
	}
	INT_PTR CALLBACK TinyDialog::BeginLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		TinyDialog *_this = NULL;
		if (uMsg == WM_INITDIALOG)
		{
			ASSERT(lParam != NULL);
			_this = (TinyDialog*)lParam;
			if (_this != NULL)
			{
				_this->m_hWND = hWnd;
				_this->m_thunk.Initialize((WNDPROC)TinyDialog::EndLoop, _this);
				DLGPROC hProc = (DLGPROC)_this->m_thunk.GetWNDPROC();
				DLGPROC hOldProc = (DLGPROC)::SetWindowLongPtr(hWnd, DWLP_DLGPROC, (LONG_PTR)hProc);
				if (hOldProc != BeginLoop)
					TRACE(_T("Subclassing through a hook discarded.\n"));
				return hProc(hWnd, uMsg, wParam, lParam);
			}
		}
		return FALSE;
	};
	INT_PTR CALLBACK TinyDialog::EndLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		TinyDialog* _this = (TinyDialog*)hWnd;
		TinyMsg msg(_this->m_hWND, uMsg, wParam, lParam);
		const TinyMsg* pOldMsg = _this->m_pCurrentMsg;
		_this->m_pCurrentMsg = &msg;
		LRESULT lRes;
		BOOL bRet = _this->ProcessWindowMessage(_this->m_hWND, uMsg, wParam, lParam, lRes);
		ASSERT(_this->m_pCurrentMsg == &msg);
		_this->m_pCurrentMsg = pOldMsg;
		//ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.chs/winui/winui/windowsuserinterface/windowing/dialogboxes/dialogboxreference/dialogboxfunctions/dialogproc.htm
		//IF bRet==1 process the message
		if (bRet)
		{
			switch (uMsg)
			{
			case WM_COMPAREITEM:
			case WM_VKEYTOITEM:
			case WM_CHARTOITEM:
			case WM_INITDIALOG:
			case WM_QUERYDRAGICON:
			case WM_CTLCOLORMSGBOX:
			case WM_CTLCOLOREDIT:
			case WM_CTLCOLORLISTBOX:
			case WM_CTLCOLORBTN:
			case WM_CTLCOLORDLG:
			case WM_CTLCOLORSCROLLBAR:
			case WM_CTLCOLORSTATIC:
				bRet = (BOOL)lRes;
				break;
			default:
				if ((_this->m_dwState & 0x00000001) == 0)
				{
					::SetWindowLongPtr(_this->m_hWND, DWLP_MSGRESULT, lRes);
				}
				break;
			}
		}
		else if (uMsg == WM_NCDESTROY)
		{
			_this->m_dwState |= 0x00000001;
		}
		if ((_this->m_dwState & 0x00000001) && _this->m_pCurrentMsg == NULL)
		{
			HWND hWndThis = _this->m_hWND;
			_this->m_hWND = NULL;
			_this->m_dwState &= ~0x00000001;
			_this->OnFinalMessage(hWndThis);
		}
		return (INT_PTR)bRet;
	}
	TinyDialog::operator HWND() const
	{
		return this == NULL ? NULL : m_hWND;
	}
	BOOL TinyDialog::operator == (const TinyDialog& wnd) const
	{
		return ((HWND)wnd) == m_hWND;
	}
	BOOL TinyDialog::operator != (const TinyDialog& wnd) const
	{
		return ((HWND)wnd) != m_hWND;
	}
	BOOL TinyDialog::Create(HWND hParent, LPCTSTR lpTemplateName)
	{
		this->m_pTemplateName = lpTemplateName;
		BOOL result;
		ASSUME(m_hWND == NULL);
		result = m_thunk.Initialize(NULL, NULL);
		if (result == FALSE)
		{
			SetLastError(ERROR_OUTOFMEMORY);
			return NULL;
		}
		m_bModal = FALSE;
		HWND hWnd = ::CreateDialogParam(TinyApplication::Instance()->Handle(), lpTemplateName, hParent, TinyDialog::BeginLoop, (LPARAM)this);
		if (hWnd == NULL)
			return FALSE;
		m_hWND = hWnd;
		TinyApplication::Instance()->GetMapHWND().AddHandle(m_hWND, this);
		return TRUE;
	}
	BOOL TinyDialog::Create(HWND hParent, WORD wInteger)
	{
		this->m_wInteger = wInteger;
		this->m_pTemplateName = MAKEINTRESOURCE(wInteger);
		return Create(hParent, this->m_pTemplateName);
	}
	BOOL TinyDialog::SubclassDialog(HWND hWND)
	{
		PreSubclassDialog();
		ASSERT(::IsWindow(hWND));
		BOOL result = m_thunk.Initialize((WNDPROC)TinyDialog::EndLoop, this);
		if (result == FALSE) return FALSE;
		DLGPROC hProc = (DLGPROC)m_thunk.GetWNDPROC();
		DLGPROC hDlgProc = (DLGPROC)::SetWindowLongPtr(hWND, DWLP_DLGPROC, (LONG_PTR)hProc);
		if (hDlgProc == NULL)
			return FALSE;
		m_hPrimaryProc = hDlgProc;
		m_hWND = hWND;
		return TRUE;
	}
	INT_PTR TinyDialog::DoModal(HWND hParent, WORD wInteger)
	{
		this->m_wInteger = wInteger;
		this->m_pTemplateName = MAKEINTRESOURCE(wInteger);
		return DoModal(hParent, this->m_pTemplateName);
	}
	INT_PTR TinyDialog::DoModal(HWND hParent, LPCTSTR lpTemplateName)
	{
		this->m_pTemplateName = MAKEINTRESOURCE(m_wInteger);
		BOOL result;
		ASSUME(m_hWND == NULL);
		result = m_thunk.Initialize(NULL, NULL);
		if (result == FALSE)
		{
			SetLastError(ERROR_OUTOFMEMORY);
			return -1;
		}
		m_bModal = TRUE;
		m_iDlgResult = ::DialogBoxParam(TinyApplication::Instance()->Handle(), lpTemplateName, hParent, BeginLoop, (LPARAM)this);
		return m_iDlgResult;
	}
	BOOL TinyDialog::MapDialogRect(LPRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MapDialogRect(m_hWND, lpRect);
	}

	BOOL TinyDialog::EndDialog()
	{
		ASSERT(::IsWindow(m_hWND));
		TinyApplication::Instance()->GetMapHWND().RemoveHandle(m_hWND);
		return ::EndDialog(m_hWND, m_iDlgResult);
	}
	BOOL TinyDialog::EndDialog(INT_PTR m_DlgResult)
	{
		ASSERT(::IsWindow(m_hWND));
		TinyApplication::Instance()->GetMapHWND().RemoveHandle(m_hWND);
		return ::EndDialog(m_hWND, m_DlgResult);
	}
	BOOL TinyDialog::EndDialog(HWND hWnd, INT_PTR m_DlgResult)
	{
		ASSERT(::IsWindow(hWnd));
		TinyApplication::Instance()->GetMapHWND().RemoveHandle(hWnd);
		return ::EndDialog(hWnd, m_DlgResult);
	}
	BOOL TinyDialog::IsModal() const throw()
	{
		return m_bModal;
	}
	void TinyDialog::OnFinalMessage(HWND hWnd)
	{

	}
	BOOL TinyDialog::DestroyWindow()
	{
		if (m_hWND != NULL)
		{
			TinyApplication::Instance()->GetMapHWND().RemoveHandle(m_hWND);
			return ::DestroyWindow(m_hWND);
		}
		return FALSE;
	}
}

