#include "../stdafx.h"
#include "TinyVisualHWND.h"
#include "../Render/TinyTransform.h"
#include "../Render/TinyCanvas.h"

namespace TinyUI
{
	TinyVisualHWND::TinyVisualHWND()
	{

	}
	TinyVisualHWND::~TinyVisualHWND()
	{

	}
	BOOL TinyVisualHWND::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
	{
		return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
	}
	DWORD TinyVisualHWND::RetrieveStyle()
	{
		return (WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW);
	}
	DWORD TinyVisualHWND::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR);
	}
	LPCSTR TinyVisualHWND::RetrieveClassName()
	{
		return TEXT("TinyVisualHWND");
	}
	LPCSTR TinyVisualHWND::RetrieveTitle()
	{
		return TEXT("FramwUI");
	}
	HICON TinyVisualHWND::RetrieveIcon()
	{
		return NULL;
	}
	LRESULT TinyVisualHWND::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		PAINTSTRUCT ps = { 0 };
		HDC hDC = BeginPaint(m_hWND, &ps);

		TinyCanvas canvas(hDC);

		POINT pts[5];
		pts[0].x = 10; 
		pts[0].y  = 10; 
		pts[1].x  = 60;
		pts[1].y  = 10;  
		pts[2].x  = 10; 
		pts[2].y  = 100;
		pts[3].x = 60;
		pts[3].y = 100; 

		canvas.DrawBeziers(pts, 3);
		//canvas.DrawRectangle(100, 100, 100, 100);
		//canvas.DrawArc(100, 100, 100, 100, 0, 30);
		//canvas.DrawLine(10, 10, 100, 100);

		//POINT pos[5];
		//pos[0].x = 10;
		//pos[0].y = 15;

		//pos[1].x = 56;
		//pos[1].y = 70;

		//pos[2].x = 100;
		//pos[2].y = 100;

		//pos[3].x = 100;
		//pos[3].y = 200;

		//canvas.DrawLines(pos,4);
		/*canvas.Translate(100, 100);
		canvas.Rotate(45);
		canvas.DrawImage(m_image, 0, 0);*/
		/*TinyRectangle dst(10, 10, 82, 65);
		canvas.DrawImage(m_image, dst, 0, 0, 72, 55);*/
		//INT iSave = SaveDC(hDC);
		//TinyMemDC memdc(hDC, m_size.cx, m_size.cy);
		//RECT paintRC = { 0, 0, m_size.cx, m_size.cy };
		//FillRect(memdc, &paintRC, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//DrawImage(memdc, m_image);
		//memdc.Render(paintRC, paintRC, FALSE);
		//RestoreDC(hDC, iSave);

		EndPaint(m_hWND, &ps);
		return FALSE;
	}
	LRESULT TinyVisualHWND::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyVisualHWND::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_size.cx = LOWORD(lParam);
		m_size.cy = HIWORD(lParam);
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);//退出应用程序
		return FALSE;
	}

	LRESULT TinyVisualHWND::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		m_image.Load("D:\\sunflower.png");
		return FALSE;
	}

	void TinyVisualHWND::DrawImage(TinyDC& dc, TinyImage& image)
	{

		/*TinyMemDC memdc1(dc, image);
		INT iSave = dc.SaveDC();
		dc.SetGraphicsMode(GM_ADVANCED);
		TinyMatrix marix;
		dc.GetWorldTransform(&marix);
		marix.SetTranslate(200, 200);
		marix.SetScale(1, 1);
		marix.SetRotate(180);
		dc.SetWorldTransform(&marix);
		TinyRectangle rect = image.GetRectangle();
		dc.SetBkColor(RGB(128, 128, 128));
		dc.Rectangle(&rect);
		dc.MoveTo(0, 0);
		dc.LineTo(200, 200);
		memdc1.Render(rect, rect, TRUE);
		dc.RestoreDC(iSave);*/
	}
}
