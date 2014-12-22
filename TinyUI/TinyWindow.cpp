#include "stdafx.h"
#include "TinyWindow.h"
#include "TinyApplication.h"

namespace TinyUI
{
	TinyWindow::TinyWindow()
		:m_hPrimaryProc(::DefWindowProc)
	{
	};
	TinyWindow::TinyWindow(INT x, INT y, INT cx, INT cy) :
		m_hPrimaryProc(::DefWindowProc)
	{
		Create(NULL, x, y, cx, cy);
	};
	TinyWindow::~TinyWindow()
	{
	};
	TinyWindow::operator HWND() const
	{
		return this == NULL ? NULL : m_hWND;
	}
	BOOL TinyWindow::operator == (const TinyWindow& wnd) const
	{
		return ((HWND)wnd) == m_hWND;
	}
	BOOL TinyWindow::operator != (const TinyWindow& wnd) const
	{
		return ((HWND)wnd) != m_hWND;
	}
	LRESULT TinyWindow::DefWindowProc()
	{
		const TinyMsg* pMsg = m_pCurrentMsg;
		LRESULT lRes = 0;
		if (pMsg != NULL)
			lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
		return lRes;
	}
	LRESULT TinyWindow::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
#ifdef STRICT
		return ::CallWindowProc(m_hPrimaryProc, m_hWND, uMsg, wParam, lParam);
#else
		return ::CallWindowProc((FARPROC)m_hPrimaryProc, m_hWND, uMsg, wParam, lParam);
#endif
	}
	LPCSTR TinyWindow::RetrieveClassName()
	{
		return TEXT("TinyWindowClass");
	}
	HICON TinyWindow::RetrieveIcon()
	{
		return NULL;
	}
	LPCTSTR TinyWindow::RetrieveTitle()
	{
		return TEXT("TinyWindowTitle");
	}
	DWORD TinyWindow::RetrieveStyle()
	{
		return 0;
	}
	DWORD TinyWindow::RetrieveExStyle()
	{
		return 0;
	}
	LPCSTR TinyWindow::RetrieveClass(LPCTSTR lpszClass)
	{
		HINSTANCE hInstance = TinyApplication::Instance()->Handle();
		ASSERT(hInstance != NULL);
		ATOM atom = 0;
		WNDCLASSEX class_ex;
		memset(&class_ex, 0, sizeof(WNDCLASSEX));
		atom = (ATOM)::GetClassInfoEx(hInstance, lpszClass, &class_ex);
		if (atom == 0)
		{
			class_ex.cbSize = sizeof(WNDCLASSEX);
			class_ex.lpfnWndProc = TinyWindow::BeginLoop;
			class_ex.cbClsExtra = 0;
			class_ex.cbWndExtra = 0;
			class_ex.hInstance = hInstance;
			class_ex.hIcon = RetrieveIcon();
			class_ex.style &= ~CS_GLOBALCLASS;
			class_ex.style |= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			class_ex.hCursor = LoadCursor(NULL, IDC_ARROW);
			class_ex.hbrBackground = GetSysColorBrush(0x0F);
			class_ex.lpszMenuName = NULL;
			class_ex.lpszClassName = lpszClass;
			class_ex.hIconSm = class_ex.hIcon;
			atom = ::RegisterClassEx(&class_ex);
			return MAKEINTATOM(atom);
		}
		return lpszClass;
	};
	BOOL TinyWindow::PreCreateWindow(CREATESTRUCT& cs)
	{
		return TRUE;
	}
	BOOL TinyWindow::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		BOOL result;
		ASSERT(m_hWND == NULL);
		result = m_thunk.Initialize(NULL, NULL);
		if (result == FALSE)
		{
			SetLastError(ERROR_OUTOFMEMORY);
			return FALSE;
		}
		HINSTANCE hInstance = TinyApplication::Instance()->Handle();
		if (hInstance == NULL)
		{
			SetLastError(ERROR_INVALID_DATA);
			return FALSE;
		}
		CREATESTRUCT cs;
		cs.lpszClass = RetrieveClassName();
		cs.lpszName = RetrieveTitle();
		cs.dwExStyle = RetrieveExStyle();
		cs.style = RetrieveStyle();
		cs.x = x;
		cs.y = y;
		cs.cx = cx;
		cs.cy = cy;
		cs.hwndParent = hParent;
		cs.hMenu = NULL;
		cs.hInstance = hInstance;
		cs.lpCreateParams = this;
		if (!PreCreateWindow(cs))
			return FALSE;
		LPCTSTR lpszClass = RetrieveClass(cs.lpszClass);
		HWND hWND = ::CreateWindowEx(cs.dwExStyle, lpszClass, cs.lpszName,
			cs.style, cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent,
			cs.hMenu, cs.hInstance, cs.lpCreateParams);
		if (hWND == NULL)
			return FALSE;
		m_hWND = hWND;
		TinyApplication::Instance()->GetMapHWND().AddHandle(m_hWND, this);
		return TRUE;
	};
	BOOL TinyWindow::DestroyWindow()
	{
		if (m_hWND != NULL)
		{
			TinyApplication::Instance()->GetMapHWND().RemoveHandle(m_hWND);
			return ::DestroyWindow(m_hWND);
		}
		return FALSE;
	}
	void TinyWindow::PreSubclassWindow()
	{

	}
	BOOL TinyWindow::SubclassWindow(HWND hWnd)
	{
		PreSubclassWindow();
		ASSERT(::IsWindow(hWnd));
		BOOL result = m_thunk.Initialize(TinyWindow::EndLoop, this);
		if (result == FALSE) return FALSE;
		WNDPROC hProc = m_thunk.GetWNDPROC();
		WNDPROC hOldProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)hProc);
		if (hOldProc == NULL) return FALSE;
		m_hPrimaryProc = hOldProc;
		m_hWND = hWnd;
		return TRUE;
	};
	void TinyWindow::PreSubclassDlgItem()
	{

	}
	BOOL TinyWindow::SubclassDlgItem(UINT nID, HWND hDlg)
	{
		PreSubclassDlgItem();
		ASSERT(::IsWindow(hDlg));
		HWND hItem = ::GetDlgItem(hDlg, nID);
		if (hItem == NULL) return FALSE;
		return SubclassWindow(hItem);
	}
	HWND TinyWindow::UnsubclassWindow(BOOL bForce /* = FALSE */)
	{
		ASSERT(m_hWND != NULL);
		WNDPROC pOurProc = m_thunk.GetWNDPROC();
		WNDPROC pActiveProc = (WNDPROC)::GetWindowLongPtr(m_hWND, GWLP_WNDPROC);
		HWND hWnd = NULL;
		if (bForce || pOurProc == pActiveProc)
		{
			if (!::SetWindowLongPtr(m_hWND, GWLP_WNDPROC, (LONG_PTR)m_hPrimaryProc))
				return NULL;
			m_hPrimaryProc = ::DefWindowProc;
			hWnd = m_hWND;
			m_hWND = NULL;
		}
		return hWnd;
	}
	LRESULT TinyWindow::BeginLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		TinyWindow *_this = NULL;
		if (uMsg == WM_NCCREATE)
		{
			ASSERT(lParam != NULL);
			_this = (TinyWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			if (_this != NULL)
			{
				_this->m_hWND = hWnd;
				_this->m_thunk.Initialize(TinyWindow::EndLoop, _this);
				WNDPROC hProc = _this->m_thunk.GetWNDPROC();
				WNDPROC hOldProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)hProc);
				if (hOldProc != BeginLoop)
				{
					ASSERT(_T("HOOK子类化失败.\n"));
				}
				return hProc(hWnd, uMsg, wParam, lParam);
			}
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	LRESULT TinyWindow::EndLoop(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		TinyWindow* _this = NULL;
		ASSERT(hWnd);
		_this = (TinyWindow*)hWnd;
		if (_this != NULL)
		{
			TinyMsg msg(_this->m_hWND, uMsg, wParam, lParam);
			const TinyMsg* pOldMsg = _this->m_pCurrentMsg;
			_this->m_pCurrentMsg = &msg;

			//添加和移除筛选器
			switch (msg.message)
			{
			case WM_CREATE:
			{
							  TinyMessageLoop* pLoop = TinyApplication::Instance()->GetMessageLoop();
							  ASSERT(pLoop != NULL);
							  pLoop->AddMessageFilter(_this);
			}
				break;
			case WM_DESTROY:
			{
							   TinyMessageLoop* pLoop = TinyApplication::Instance()->GetMessageLoop();
							   ASSERT(pLoop != NULL);
							   pLoop->RemoveMessageFilter(_this);
			}
				break;
			default:
				break;
			}

			LRESULT lRes = 0;
			BOOL bRet = _this->ProcessWindowMessage(_this->m_hWND, uMsg, wParam, lParam, lRes);
			ASSERT(_this->m_pCurrentMsg == &msg);
			if (!bRet)//如果没有设置Handle,调用CallWindowProc处理
			{
				if (uMsg != WM_NCDESTROY)
				{
					lRes = _this->DefWindowProc(uMsg, wParam, lParam);
				}
				else
				{
					//UnSubclass
					LONG_PTR hProc = ::GetWindowLongPtr(_this->m_hWND, GWLP_WNDPROC);
					lRes = _this->DefWindowProc(uMsg, wParam, lParam);
					if (_this->m_hPrimaryProc != ::DefWindowProc && ::GetWindowLongPtr(_this->m_hWND, GWLP_WNDPROC) == hProc)
					{
						::SetWindowLongPtr(_this->m_hWND, GWLP_WNDPROC, (LONG_PTR)_this->m_hPrimaryProc);
					}
					_this->m_dwState |= 0x00000001;//设置状态Destryed
				}
			}
			if ((_this->m_dwState & 0x00000001)
				&& pOldMsg == NULL)
			{
				HWND hWndThis = _this->m_hWND;

				_this->m_hWND = NULL;
				_this->m_dwState &= ~0x00000001;
				_this->m_pCurrentMsg = pOldMsg;
				_this->OnFinalMessage(hWndThis);
			}
			else
			{
				_this->m_pCurrentMsg = pOldMsg;
			}
			return lRes;
		}
		return ::DefWindowProc(_this->m_hWND, uMsg, wParam, lParam);
	};
	void TinyWindow::OnFinalMessage(HWND hWnd)
	{

	}

	BOOL TinyWindow::PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}
	BOOL TinyWindow::ShowWindow(INT nCmdShow) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ShowWindow(m_hWND, nCmdShow);
	}
	BOOL TinyWindow::UpdateWindow() throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::UpdateWindow(m_hWND);
	}
}
