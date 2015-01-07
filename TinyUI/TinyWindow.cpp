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
		return TEXT("TinyWindow");
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
	DWORD TinyWindow::GetStyle() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::GetWindowLong(m_hWND, GWL_STYLE);
	}
	DWORD TinyWindow::SetStyle(LONG dwNewLong) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::SetWindowLong(m_hWND, GWL_STYLE, dwNewLong);
	}
	DWORD TinyWindow::GetExStyle() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (DWORD)::GetWindowLong(m_hWND, GWL_EXSTYLE);
	}

	LONG TinyWindow::GetWindowLong(int nIndex) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowLong(m_hWND, nIndex);
	}

	LONG TinyWindow::SetWindowLong(int nIndex, LONG dwNewLong) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowLong(m_hWND, nIndex, dwNewLong);
	}

	WORD TinyWindow::GetWindowWord(int nIndex) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowWord(m_hWND, nIndex);
	}

	WORD TinyWindow::SetWindowWord(int nIndex, WORD wNewWord) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowWord(m_hWND, nIndex, wNewWord);
	}

	DWORD TinyWindow::GetWindowStyle() throw()
	{
		return ((DWORD)GetWindowLong(GWL_STYLE));
	}

	DWORD TinyWindow::GetWindowExStyle() throw()
	{
		return ((DWORD)GetWindowLong(GWL_EXSTYLE));
	}

	DWORD TinyWindow::SetWindowStyle(DWORD dwNewStyle) throw()
	{
		return ((DWORD)SetWindowLong(GWL_STYLE, dwNewStyle));
	}

	DWORD TinyWindow::SetWindowExStyle(DWORD dwNewStyle) throw()
	{
		return ((DWORD)SetWindowLong(GWL_EXSTYLE, dwNewStyle));
	}

	HMODULE TinyWindow::GetWindowInstance()  throw()
	{
		return ((HMODULE)GetWindowLongPtr(GWLP_HINSTANCE));
	}
	BOOL TinyWindow::SetWindowText(LPCTSTR lpszString) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowText(m_hWND, lpszString);
	}

	INT TinyWindow::GetWindowText(_Out_z_cap_post_count_(nMaxCount, return +1) LPTSTR lpszStringBuf, _In_ int nMaxCount) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowText(m_hWND, lpszStringBuf, nMaxCount);
	}
	INT TinyWindow::GetWindowTextLength() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowTextLength(m_hWND);
	}
	void TinyWindow::SetFont(HFONT hFont, BOOL bRedraw) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
	}
	void TinyWindow::SetText(LPCSTR lpszText) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::SendMessage(m_hWND, WM_SETTEXT, 0, (LPARAM)lpszText);
	}

	INT TinyWindow::GetText(LPCSTR lpszText, INT cchTextMax) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (INT)::SendMessage(m_hWND, WM_GETTEXT, cchTextMax, (LPARAM)lpszText);
	}

	HFONT TinyWindow::GetFont() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (HFONT)::SendMessage(m_hWND, WM_GETFONT, 0, 0);
	}
	HMENU TinyWindow::GetMenu() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (HMENU)::GetMenu(m_hWND);
	}

	BOOL TinyWindow::SetMenu(HMENU hMenu) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetMenu(m_hWND, hMenu);
	}
	HMENU TinyWindow::GetSystemMenu(BOOL bRevert) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return (HMENU)::GetSystemMenu(m_hWND, bRevert);
	}

	BOOL TinyWindow::HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::HiliteMenuItem(m_hWND, hMenu, uItemHilite, uHilite);
	}
	BOOL TinyWindow::IsIconic() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::IsIconic(m_hWND);
	}

	BOOL TinyWindow::IsZoomed() const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::IsZoomed(m_hWND);
	}

	BOOL TinyWindow::MoveWindow(INT x, INT y, INT cx, INT cy, BOOL bRepaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MoveWindow(m_hWND, x, y, cx, cy, bRepaint);
	}
	INT TinyWindow::MapWindowPoints(HWND hWndFrom, POINT& pos)
	{
		ASSERT(::IsWindow(m_hWND));
		return MapWindowPoints(hWndFrom, &pos, 1);
	}
	INT TinyWindow::MapWindowPoints(POINT& pos)
	{
		ASSERT(::IsWindow(m_hWND));
		return MapWindowPoints(NULL, &pos, 1);
	}
	BOOL TinyWindow::MoveWindow(LPCRECT lpRect, BOOL bRepaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
	}
	BOOL TinyWindow::SetForegroundWindow()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetForegroundWindow(m_hWND);
	}
	BOOL TinyWindow::SetWindowPos(HWND hWndInsertAfter, INT x, INT y, INT cx, INT cy, UINT nFlags) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowPos(m_hWND, hWndInsertAfter, x, y, cx, cy, nFlags);
	}

	BOOL TinyWindow::SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowPos(m_hWND, hWndInsertAfter, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, nFlags);
	}

	UINT TinyWindow::ArrangeIconicWindows() throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ArrangeIconicWindows(m_hWND);
	}

	BOOL TinyWindow::BringWindowToTop() throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::BringWindowToTop(m_hWND);
	}

	BOOL TinyWindow::GetWindowRect(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowRect(m_hWND, lpRect);
	}

	BOOL TinyWindow::GetClientRect(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetClientRect(m_hWND, lpRect);
	}

	BOOL TinyWindow::GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::GetWindowPlacement(m_hWND, lpwndpl);
	}

	BOOL TinyWindow::SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::SetWindowPlacement(m_hWND, lpwndpl);
	}
	BOOL TinyWindow::ClientToScreen(LPPOINT lpPoint) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ClientToScreen(m_hWND, lpPoint);
	}

	BOOL TinyWindow::ClientToScreen(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		if (!::ClientToScreen(m_hWND, (LPPOINT)lpRect))
			return FALSE;
		return ::ClientToScreen(m_hWND, ((LPPOINT)lpRect) + 1);
	}

	BOOL TinyWindow::ScreenToClient(LPPOINT lpPoint) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ScreenToClient(m_hWND, lpPoint);
	}

	BOOL TinyWindow::ScreenToClient(LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		if (!::ScreenToClient(m_hWND, (LPPOINT)lpRect))
			return FALSE;
		return ::ScreenToClient(m_hWND, ((LPPOINT)lpRect) + 1);
	}

	INT TinyWindow::MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MapWindowPoints(m_hWND, hWndTo, lpPoint, nCount);
	}

	INT TinyWindow::MapWindowPoints(HWND hWndTo, LPRECT lpRect) const throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::MapWindowPoints(m_hWND, hWndTo, (LPPOINT)lpRect, 2);
	}
	HDC TinyWindow::BeginPaint(LPPAINTSTRUCT lpPaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::BeginPaint(m_hWND, lpPaint);
	}

	void TinyWindow::EndPaint(LPPAINTSTRUCT lpPaint) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		::EndPaint(m_hWND, lpPaint);
	}
}
