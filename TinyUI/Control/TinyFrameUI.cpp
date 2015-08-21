#include "../stdafx.h"
#include "TinyFrameUI.h"

namespace TinyUI
{
	TinyFrameUI::TinyFrameUI()
	{
		m_index = 0;
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

	LRESULT TinyFrameUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		/*m_btn.Create(m_hWND, 250, 10, 100, 23);
		m_btn.SetText("设置");
		m_fs_Click.BindDelegate(this, &TinyFrameUI::ClickSetting);
		m_btn.Click += &m_fs_Click;

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

		CreateMenuBox();*/

		//m_image.Load("E:\\123.png");

		return TRUE;
	}

	void TinyFrameUI::CreateMenuBox()
	{
		m_menuBox1.Create(m_hWND, 0, 0, 0, 0);
		m_menuItem1.Reset(new TinyMenuItem());
		m_menuItem1->SetText("menuItem1");
		m_menuItem2.Reset(new TinyMenuItem());
		m_menuItem2->SetText("menuItem2");
		m_menuItem3.Reset(new TinyMenuItem(TRUE));
		m_menuItem4.Reset(new TinyMenuItem());
		m_menuItem4->SetText("menuItem4");
		m_menuItem5.Reset(new TinyMenuItem());
		m_menuItem5->SetText("menuItem5");
		m_menuBox1.AddItem(m_menuItem1);
		m_menuBox1.AddItem(m_menuItem2);
		m_menuBox1.AddItem(m_menuItem3);
		m_menuBox1.AddItem(m_menuItem4);
		m_menuBox1.AddItem(m_menuItem5);

		m_menuBox2.Create(m_hWND, 0, 0, 0, 0);
		m_menuItem11.Reset(new TinyMenuItem());
		m_menuItem11->SetText("menuItem11");
		m_menuItem21.Reset(new TinyMenuItem());
		m_menuItem21->SetText("menuItem21");
		m_menuItem31.Reset(new TinyMenuItem(TRUE));
		m_menuItem41.Reset(new TinyMenuItem());
		m_menuItem41->SetText("menuItem41");
		m_menuItem51.Reset(new TinyMenuItem());
		m_menuItem51->SetText("menuItem51");
		m_menuBox2.AddItem(m_menuItem11);
		m_menuBox2.AddItem(m_menuItem21);
		m_menuBox2.AddItem(m_menuItem31);
		m_menuBox2.AddItem(m_menuItem41);
		m_menuBox2.AddItem(m_menuItem51);

		m_menuBox3.Create(m_hWND, 0, 0, 0, 0);
		m_menuItem12.Reset(new TinyMenuItem());
		m_menuItem12->SetText("menuItem12");
		m_menuItem22.Reset(new TinyMenuItem());
		m_menuItem22->SetText("menuItem22");
		m_menuItem32.Reset(new TinyMenuItem(TRUE));
		m_menuItem42.Reset(new TinyMenuItem());
		m_menuItem42->SetText("menuItem42");
		m_menuItem52.Reset(new TinyMenuItem());
		m_menuItem52->SetText("menuItem52");
		m_menuBox3.AddItem(m_menuItem12);
		m_menuBox3.AddItem(m_menuItem22);
		m_menuBox3.AddItem(m_menuItem32);
		m_menuBox3.AddItem(m_menuItem42);
		m_menuBox3.AddItem(m_menuItem52);

		m_menuItem4->SetChild(&m_menuBox2);
		m_menuItem51->SetChild(&m_menuBox3);
	}

	LRESULT TinyFrameUI::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		//m_scroll.PosChange -= &m_fs_PosChange;
		m_btn.Click -= &m_fs_Click;

		return FALSE;
	}

	LRESULT TinyFrameUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		PAINTSTRUCT s;
		HDC hDC = BeginPaint(m_hWND, &s);

		//TinyDC dc;
		//dc.Attach(hDC);

		//TinyDC dcMem;
		//dcMem.CreateCompatibleDC(hDC);
		//BITMAP bitmap = { 0 };
		//GetObject(m_image.GetFrame(m_index), sizeof(BITMAP), (LPSTR)&bitmap);
		//DWORD a = sizeof(BITMAPFILEHEADER);
		///*DWORD scanline = (bitmap.bmWidth * bitmap.bmBitsPixel + 31) / 32 * 4;
		//DWORD size = scanline  * bitmap.bmHeight;*/

		//HBITMAP hOldBmp = (HBITMAP)dcMem.SelectObject(m_image.GetFrame(m_index));
		//dc.BitBlt(0, 0, 274, 274, dcMem, 0, 0, SRCCOPY);
		//dcMem.SelectObject(hOldBmp);

		///*TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		//TinyMemDC memdc1(memdc, m_image[1]);
		//RECT rect = { 0, 0, 97, 97 };
		//memdc1.Render(rect, m_image.GetRectangle(), TRUE);*/

		//dc.Detach();

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


		if (m_menuBox1.IsPopup())
		{
			m_menuBox1.Unpopup();
		}
		else
		{
			m_menuBox1.Popup(pt);
		}
	}
	void TinyFrameUI::ClickSetting(void* ps, INT cmd)
	{
		/*if (m_index == (m_image.GetFrameCount() - 1))
		{
			m_index = 0;
		}
		else
		{
			m_index++;
		}
		::InvalidateRect(m_hWND, NULL, FALSE);*/
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

