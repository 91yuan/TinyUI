#include "../stdafx.h"
#include "TinyFrameUI.h"

namespace TinyUI
{
	TinyFrameUI::TinyFrameUI()
	{
	}


	TinyFrameUI::~TinyFrameUI()
	{
	}

	LRESULT TinyFrameUI::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);//退出应用程序
		return FALSE;
	}

	BOOL TinyFrameUI::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	BOOL TinyFrameUI::ShowWindow(int nCmdShow) throw()
	{
		ASSERT(::IsWindow(m_hWND));
		return ::ShowWindow(m_hWND, nCmdShow);
	}

	BOOL TinyFrameUI::UpdateWindow() throw()
	{
		ASSERT(m_hWND != NULL);
		return ::UpdateWindow(m_hWND);
	}
	DWORD TinyFrameUI::RetrieveStyle()
	{
		return (WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW);
	}

	DWORD TinyFrameUI::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR);
	}

	LPCSTR TinyFrameUI::RetrieveClassName()
	{
		return TEXT("FramwUI");
	}

	LPCSTR TinyFrameUI::RetrieveTitle()
	{
		return TEXT("FramwUI");
	}

	HICON TinyFrameUI::RetrieveIcon()
	{
		return NULL;
	}

	void TinyFrameUI::CenterWindow(HWND parent, HWND window, TinySize size) throw()
	{
		RECT window_bounds;
		RECT center_bounds = { 0 };
		if (parent)
		{
			::GetWindowRect(parent, &center_bounds);
		}
		else
		{
			HMONITOR monitor = MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST);
			if (monitor != NULL)
			{
				MONITORINFO mi = { 0 };
				mi.cbSize = sizeof(mi);
				GetMonitorInfo(monitor, &mi);
				center_bounds = mi.rcWork;
			}
		}
		window_bounds.left = center_bounds.left + (center_bounds.right - center_bounds.left - size.cx) / 2;
		window_bounds.right = window_bounds.left + size.cx;
		window_bounds.top = center_bounds.top + (center_bounds.bottom - center_bounds.top - size.cy) / 2;
		window_bounds.bottom = window_bounds.top + size.cy;
		if (::GetWindowLong(window, GWL_STYLE) & WS_CHILD)
		{
			POINT topleft = { window_bounds.left, window_bounds.top };
			::MapWindowPoints(HWND_DESKTOP, parent, &topleft, 1);
			window_bounds.left = topleft.x;
			window_bounds.top = topleft.y;
			window_bounds.right = window_bounds.left + size.cx;
			window_bounds.bottom = window_bounds.top + size.cy;
		}
		WINDOWINFO win_info = { 0 };
		win_info.cbSize = sizeof(WINDOWINFO);
		GetWindowInfo(window, &win_info);
		if (AdjustWindowRectEx(&window_bounds, win_info.dwStyle, FALSE, win_info.dwExStyle))
		{
			SetWindowPos(window, 0, window_bounds.left, window_bounds.top,
				window_bounds.right - window_bounds.left,
				window_bounds.bottom - window_bounds.top,
				SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}
	LRESULT TinyFrameUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_scroll.Create(m_hWND, 10, 10, 12, 350);
		m_fs_PosChange.BindDelegate(this, &TinyFrameUI::PosChanges);
		m_scroll.PosChange += &m_fs_PosChange;

		m_lblPos.Create(m_hWND, 100, 10, 40, 23);
		m_lblPos.SetText("Pos:");
		m_txtPos.Create(m_hWND, 150, 10, 100, 23);
		m_txtPos.SetText("0");

		m_lblPage.Create(m_hWND, 100, 45, 40, 23);
		m_lblPage.SetText("Page:");
		m_txtPage.Create(m_hWND, 150, 45, 100, 23);
		m_txtPage.SetText("10");

		m_lblMax.Create(m_hWND, 100, 80, 40, 23);
		m_lblMax.SetText("Max:");
		m_txtMax.Create(m_hWND, 150, 80, 100, 23);
		m_txtMax.SetText("100");

		m_lblMin.Create(m_hWND, 100, 115, 40, 23);
		m_lblMin.SetText("Min:");
		m_txtMin.Create(m_hWND, 150, 115, 100, 23);
		m_txtMin.SetText("0");

		m_btn.Create(m_hWND, 250, 10, 100, 23);
		m_btn.SetText("设置");

		m_btnPop.Create(m_hWND, 250, 40, 100, 23);
		m_btnPop.SetText("弹出菜单");

		m_fs_Click.BindDelegate(this, &TinyFrameUI::ClickSetting);
		m_btn.Click += &m_fs_Click;

		m_fs_Pop.BindDelegate(this, &TinyFrameUI::ClickPop);
		m_btnPop.Click += &m_fs_Pop;



		return TRUE;
	}

	void TinyFrameUI::CreateMenuBox()
	{
		/*	m_menuBox1.Create(m_hWND, 100, 150, 150, 250);
			m_menuBox1.Unpopup();
			m_menuItem1.Reset(new TinyMenuItem());
			m_menuItem1->SetText("图标显示1");
			m_menuItem1->SetCheck(TRUE);

			m_menuItem2.Reset(new TinyMenuItem());
			m_menuItem2->SetText("图标显示2");
			m_menuItem3.Reset(new TinyMenuItem());
			m_menuItem3->SetText("图标显示3");
			m_menuItem3->SetCheck(TRUE);
			m_menuItem4.Reset(new TinyMenuItem(TRUE));
			m_menuItem5.Reset(new TinyMenuItem());
			m_menuItem5->SetText("图标显示4");
			m_menuItem6.Reset(new TinyMenuItem());
			m_menuItem6->SetText("图标显示5");
			m_menuItem7.Reset(new TinyMenuItem());
			m_menuItem7->SetText("图标显示6");
			m_menuItem8.Reset(new TinyMenuItem(TRUE));
			m_menuItem9.Reset(new TinyMenuItem());
			m_menuItem9->SetText("图标显示7");
			m_menuItem9->SetCheck(TRUE);
			m_menuItem10.Reset(new TinyMenuItem());
			m_menuItem10->SetText("图标显示8");
			m_menuBox1.AddItem(m_menuItem1);
			m_menuBox1.AddItem(m_menuItem2);
			m_menuBox1.AddItem(m_menuItem3);
			m_menuBox1.AddItem(m_menuItem4);
			m_menuBox1.AddItem(m_menuItem5);
			m_menuBox1.AddItem(m_menuItem6);
			m_menuBox1.AddItem(m_menuItem7);
			m_menuBox1.AddItem(m_menuItem8);
			m_menuBox1.AddItem(m_menuItem9);
			m_menuBox1.AddItem(m_menuItem10);

			m_menuBox2.Create(m_hWND, 100, 150, 150, 250);
			m_menuBox2.Unpopup();

			m_menuBox3.Create(m_hWND, 100, 150, 150, 250);
			m_menuBox3.Unpopup();

			m_menuBox4.Create(m_hWND, 100, 150, 150, 250);
			m_menuBox4.Unpopup();

			m_menuItem11.Reset(new TinyMenuItem());
			m_menuItem11->SetText("图标显示11");
			m_menuItem12.Reset(new TinyMenuItem());
			m_menuItem12->SetText("图标显示12");
			m_menuItem13.Reset(new TinyMenuItem());
			m_menuItem13->SetText("图标显示13");
			m_menuItem14.Reset(new TinyMenuItem());
			m_menuItem14->SetText("图标显示14");
			m_menuItem15.Reset(new TinyMenuItem());
			m_menuItem15->SetText("图标显示15");
			m_menuBox2.AddItem(m_menuItem11);
			m_menuBox2.AddItem(m_menuItem12);
			m_menuBox2.AddItem(m_menuItem13);
			m_menuBox2.AddItem(m_menuItem14);
			m_menuBox2.AddItem(m_menuItem15);

			m_menuItem111.Reset(new TinyMenuItem());
			m_menuItem111->SetText("图标显示11");
			m_menuItem121.Reset(new TinyMenuItem());
			m_menuItem121->SetText("图标显示12");
			m_menuItem131.Reset(new TinyMenuItem());
			m_menuItem131->SetText("图标显示13");
			m_menuItem141.Reset(new TinyMenuItem());
			m_menuItem141->SetText("图标显示14");
			m_menuItem151.Reset(new TinyMenuItem());
			m_menuItem151->SetText("图标显示15");
			m_menuBox3.AddItem(m_menuItem111);
			m_menuBox3.AddItem(m_menuItem121);
			m_menuBox3.AddItem(m_menuItem131);
			m_menuBox3.AddItem(m_menuItem141);
			m_menuBox3.AddItem(m_menuItem151);

			m_menuItem112.Reset(new TinyMenuItem());
			m_menuItem112->SetText("图标显示11");
			m_menuItem122.Reset(new TinyMenuItem());
			m_menuItem122->SetText("图标显示12");
			m_menuItem132.Reset(new TinyMenuItem());
			m_menuItem132->SetText("图标显示13");
			m_menuItem142.Reset(new TinyMenuItem());
			m_menuItem142->SetText("图标显示14");
			m_menuItem152.Reset(new TinyMenuItem());
			m_menuItem152->SetText("图标显示15");
			m_menuBox4.AddItem(m_menuItem112);
			m_menuBox4.AddItem(m_menuItem122);
			m_menuBox4.AddItem(m_menuItem132);
			m_menuBox4.AddItem(m_menuItem142);
			m_menuBox4.AddItem(m_menuItem152);

			m_menuItem2->SetChild(&m_menuBox2);
			m_menuItem11->SetChild(&m_menuBox3);
			m_menuItem111->SetChild(&m_menuBox4);*/
	}

	LRESULT TinyFrameUI::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_scroll.PosChange -= &m_fs_PosChange;
		m_btn.Click -= &m_fs_Click;

		return FALSE;
	}

	LRESULT TinyFrameUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		PAINTSTRUCT s;
		HDC hDC = BeginPaint(m_hWND, &s);
		EndPaint(m_hWND, &s);

		return FALSE;
	}

	LRESULT TinyFrameUI::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyFrameUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	void TinyFrameUI::PosChanges(INT oldPos, INT newPos)
	{
		TinyString str = TinyString::Format("%d", newPos);
		m_txtPos.SetText(str.STR());
	}
	void TinyFrameUI::ClickPop(void* ps, INT cmd)
	{
		RECT rect = { 0 };
		::GetWindowRect(m_btnPop.Handle(), &rect);
		POINT pt = { 0 };
		pt.x = rect.left;
		pt.y = rect.bottom;

		m_pMenuBox1 = new TinyMenuBox();
		m_pMenuBox1->Create(m_hWND, 0, 0, 200, 100);
		m_menuItem1.Reset(new TinyMenuItem());
		m_menuItem2.Reset(new TinyMenuItem());
		m_menuItem3.Reset(new TinyMenuItem(TRUE));
		m_menuItem4.Reset(new TinyMenuItem());
		m_menuItem5.Reset(new TinyMenuItem());
		m_pMenuBox1->AddItem(m_menuItem1);
		m_pMenuBox1->AddItem(m_menuItem2);
		m_pMenuBox1->AddItem(m_menuItem3);
		m_pMenuBox1->AddItem(m_menuItem4);
		m_pMenuBox1->AddItem(m_menuItem5);

		m_pMenuBox2 = new TinyMenuBox();
		m_pMenuBox2->Create(m_hWND, 0, 0, 200, 100);
		m_menuItem11.Reset(new TinyMenuItem());
		m_menuItem21.Reset(new TinyMenuItem());
		m_menuItem31.Reset(new TinyMenuItem(TRUE));
		m_menuItem41.Reset(new TinyMenuItem());
		m_menuItem51.Reset(new TinyMenuItem());
		m_pMenuBox2->AddItem(m_menuItem11);
		m_pMenuBox2->AddItem(m_menuItem21);
		m_pMenuBox2->AddItem(m_menuItem31);
		m_pMenuBox2->AddItem(m_menuItem41);
		m_pMenuBox2->AddItem(m_menuItem51);

		m_menuItem4->SetChild(m_pMenuBox2);

		m_pMenuBox1->Popup(pt);
	}
	void TinyFrameUI::ClickSetting(void* ps, INT cmd)
	{
		TinyString str(20);
		m_txtPos.GetText(str.STR(), str.GetSize());
		INT iPos = atoi(str.STR());
		m_txtPage.GetText(str.STR(), str.GetSize());
		INT iPage = atoi(str.STR());
		m_txtMax.GetText(str.STR(), str.GetSize());
		INT iMax = atoi(str.STR());
		m_txtMin.GetText(str.STR(), str.GetSize());
		INT iMin = atoi(str.STR());
		m_scroll.SetScrollInfo(iMin, iMax, iPage, iPos);
	}
}

