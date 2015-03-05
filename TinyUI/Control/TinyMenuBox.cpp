#include "../stdafx.h"
#include "TinyMenuBox.h"

namespace TinyUI
{
	TinyMenuBox::TinyMenuBox()
	{

	}
	TinyMenuBox::~TinyMenuBox()
	{

	}
	BOOL TinyMenuBox::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}

	LRESULT TinyMenuBox::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_images[0].Load("E:\\Menu\\menu_bkg_board.png");
		m_images[1].Load("E:\\Menu\\menu_bkg.png");
		m_images[2].Load("E:\\Menu\\menu_highlight.png");
		m_images[3].Load("E:\\Menu\\menu_check.png");
		m_images[4].Load("E:\\Menu\\menu_cutling.png");
		m_images[5].Load("E:\\Menu\\menu_arrow.png");
		return FALSE;
	}

	LRESULT TinyMenuBox::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	LRESULT TinyMenuBox::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		return TRUE;
	}

	LRESULT TinyMenuBox::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyMenuBox::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyMenuBox::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyMenuBox::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyMenuBox::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}

	LRESULT TinyMenuBox::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PAINTSTRUCT ps = { 0 };
		HDC hDC = BeginPaint(m_hWND, &ps);

		TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));

		DrawMenu(memdc);

		memdc.Render(paintRC, paintRC, FALSE);
		EndPaint(m_hWND, &ps);
		return FALSE;
	}
	void TinyMenuBox::DrawMenu(TinyMemDC& dc)
	{
		//DrawBoard(dc);
		DrawBkg(dc);
	}
	void TinyMenuBox::DrawBoard(TinyMemDC& dc)
	{
		TinyMemDC memdc(dc, m_images[0]);
		SIZE size = { m_size.cx + 2, m_size.cy + 2 };
		RECT dstPaint = { -3, -3, size.cx, size.cy };
		RECT dstCenter = { 5, 5, size.cx - 5, size.cy - 5 };
		RECT srcPaint = m_images[0].GetRectangle();
		RECT srcCenter = { srcPaint.left + 5, srcPaint.top + 5, srcPaint.right - 5, srcPaint.bottom - 5 };
		memdc.Render(dstPaint, dstCenter, srcPaint, srcCenter, TRUE);
	}
	void TinyMenuBox::DrawBkg(TinyMemDC& dc)
	{
		TinyMemDC memdc(dc, m_images[1]);
		SIZE size = { m_size.cx, m_size.cy };
		RECT dstPaint = { 0, 0, size.cx, size.cy };
		RECT dstCenter = { 7, 7, size.cx - 7, size.cy - 7 };
		RECT srcPaint = m_images[1].GetRectangle();
		RECT srcCenter = { srcPaint.left + 7, srcPaint.top + 7, srcPaint.right - 7, srcPaint.bottom - 7 };
		memdc.Render(dstPaint, dstCenter, srcPaint, srcCenter, TRUE);
	}
}