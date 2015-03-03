#pragma once
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
#define TINY_SM_CXSCROLL				  12 //��������ͷ�Ŀ��
#define TINY_SM_CYSCROLL				  12 //��������ͷ�ĸ߶�
#define TINY_SCROLL_MINTHUMB_SIZE		  10
#define TINY_SCROLL_MARGIN_LEFT			  1 
#define TINY_SCROLL_MARGIN_TOP			  1 
#define TINY_SCROLL_MARGIN_RIGHT		  1 
#define TINY_SCROLL_MARGIN_BOTTOM		  1 
	//HITTEST
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
		RECT	rectangle;//����������
		RECT	arrowRectangle[2];//����Arrow�ľ���
		RECT	thumbRectangle;//����ľ���
		RECT	pageRectangle[2];//����Page�ľ���
	} SCROLLCALC, *LPSCROLLCALC;
	/// <summary>
	/// �Ի������
	/// </summary>
	class TinyScroll : public TinyControl
	{
	public:
		TinyScroll();
		~TinyScroll();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	private:
		INT		ScrollHitTest(POINT& pt);
		void	ScrollCalculate(SCROLLCALC* ps);//���㻮���С
		void	ScrollTrackThumb(POINT& pt);
		void	DrawScrollBar(TinyMemDC& dc, INT iHitTest);
		void	DrawArrow(TinyMemDC& dc, SCROLLCALC* ps);
		void	DrawThumb(TinyMemDC& dc, SCROLLCALC* ps);
		void	DrawGroove(TinyMemDC& dc, SCROLLCALC* ps);
	public:
		void	SetScrollInfo(INT iMax, INT iMin, INT iPage, INT iPos);//���ù�������Ϣ
	private:
		SIZE		m_size;
		SCROLLINFO	m_si;
		BOOL		m_bTracking;
		INT			m_iOffsetPos;
		INT			m_iTrackingCode;
		INT			m_iLastCode;
		TinyImage	m_images[9];
	};
}


