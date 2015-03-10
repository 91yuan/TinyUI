#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
#define BORDER_MARGIN_LEFT		2
#define BORDER_MARGIN_TOP		2
#define BORDER_MARGIN_RIGHT		2
#define BORDER_MARGIN_BOTTOM	2
#define TINY_CXCLOSEIMIZED		25
#define TINY_CYCLOSEIMIZED		26
#define TINY_CXMAXIMIZED		25
#define TINY_CYMAXIMIZED		26
#define TINY_CXMINIMIZED		25
#define TINY_CYMINIMIZED		26
#define TINY_CXBORDER			1
#define TINY_CYBORDER			1
	//#define PART_NOWHERE			0
	//#define PART_MINBUTTON          1
	//#define PART_MAXBUTTON          2
	//#define PART_TOP                3
	//#define PART_TOPLEFT            4
	//#define PART_TOPRIGHT           5
	//#define PART_LEFT               6
	//#define PART_RIGHT              7
	//#define PART_BOTTOM             8
	//#define PART_BOTTOMLEFT         9
	//#define PART_BOTTOMRIGHT        10
	//#define PART_REDUCE            PART_MINBUTTON
	//#define PART_ZOOM              PART_MAXBUTTON
	//#define PART_CLOSE              11
	/// <summary>
	/// 可视化窗口,管理所有可视化元素 
	/// </summary>HTCLOSE
	class TinyVisualHWND : public TinyControl
	{
		DECLARE_DYNAMIC(TinyVisualHWND)
	public:
		TinyVisualHWND();
		virtual ~TinyVisualHWND();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	public:
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	private:
		void ParseUI();//解析UI
	protected:
		BOOL		m_bMouseTracking;
		TinySize	m_size;
	};
}



