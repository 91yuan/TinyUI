#pragma once
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
#define MINTHUMB_SIZE				  10
#define SM_CXVSCROLL				  12
#define SM_CYVSCROLL				  12
#define HTSCROLL_NONE                 0x00000000L
#define HTSCROLL_LINEUP               0x00000001L
#define HTSCROLL_LINEDOWN             0x00000002L
#define HTSCROLL_THUMB                0x00000003L
#define HTSCROLL_PAGEUP               0x00000004L
#define HTSCROLL_PAGEDOWN             0x00000005L
	//STATE
#define	SB_STATE_DEFAULT              0x00000000L
#define	SB_STATE_NORMAL               0x00000001L
#define	SB_STATE_HOTTRACKED           0x00000002L
#define	SB_STATE_PRESSED              0x00000003L
#define	SB_STATE_DISABLED             0x00000004L
	typedef struct tagSCROLLCALC {
		RECT	scrollRectangle;
		INT		arrow[2];//LEFT-UP,RIGHT-DOWN
		INT		thumb[2];//LEFT-TOP,RIGHT-BOTTOM

	} SCROLLCALC, *LPSCROLLCALC;
	/// <summary>
	/// ×Ô»æ¹ö¶¯Ìõ
	/// </summary>
	class TinyScroll : public TinyControl
	{
	public:
		TinyScroll(BOOL bVert = TRUE);
		~TinyScroll();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	private:
		TinyImage m_arrow_down_hover;
		TinyImage m_arrow_down_normal;
		TinyImage m_arrow_down_press;
		TinyImage m_arrow_up_hover;
		TinyImage m_arrow_up_normal;
		TinyImage m_arrow_up_press;
		TinyImage m_scrollbar_groove;
		TinyImage m_scrollbar_hover;
		TinyImage m_scrollbar_normal;
	};
}


