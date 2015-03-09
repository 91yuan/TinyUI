#pragma once
#include "../Common/TinyEvent.h"
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
#define TINY_SM_CXSCROLL				  12 //��������ͷ�Ŀ��
#define TINY_SM_CYSCROLL				  12 //��������ͷ�ĸ߶�
#define TINY_SCROLL_MINTHUMB_SIZE		  10
#define TINY_SCROLL_MARGIN_LEFT			  0 
#define TINY_SCROLL_MARGIN_TOP			  0 
#define TINY_SCROLL_MARGIN_RIGHT		  0 
#define TINY_SCROLL_MARGIN_BOTTOM		  0 
#define SB_TIMER_DELAY                65533
#define SB_TIMER_SCROLL               65534
#define SB_SCROLL_DELAY               300
#define SB_SCROLL_INTERVAL            40
	//HITTEST
#define HTSCROLL_NONE                 0x00000000L
#define HTSCROLL_LINEUP               0x00000001L
#define HTSCROLL_LINEDOWN             0x00000002L
#define HTSCROLL_THUMB                0x00000003L
#define HTSCROLL_PAGEUP               0x00000004L
#define HTSCROLL_PAGEDOWN             0x00000005L
	typedef struct tagSCROLLCALC {
		RECT	rectangle;//����������
		RECT	arrowRectangle[2];//����Arrow�ľ���
		RECT	thumbRectangle;//����ľ���
		RECT	pageRectangle[2];//����Page�ľ���
	} SCROLLCALC, *LPSCROLLCALC;
	typedef struct tagSCROLLBOXINFO
	{
		INT     iMin;
		INT     iMax;
		INT		iPage;
		INT     iPos;
		INT		iThumbOffset;
		INT		iLatestHitTest;
		INT		iTrackHitTest;
	}SCROLLBOXINFO, *LPSCROLLBOXINFO;
	/// <summary>
	/// �Ի������
	/// </summary>
	class TinyScrollBox : public TinyControl
	{
	public:
		TinyScrollBox();
		~TinyScrollBox();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual LPCSTR RetrieveClassName();
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	public:
		INT		GetScrollPos();
		void	SetScrollInfo(INT iMin, INT iMax, INT iPage, INT iPos);//���ù�������Ϣ
		Event<void(INT, INT)> PosChange;
	private:
		INT		ScrollHitTest(POINT& pt);
		void	ScrollCalculate(SCROLLCALC* ps);//���㻮���С
		void	ScrollTrackThumb(POINT& pt, SCROLLCALC* ps);
		void	DrawScrollBar(TinyMemDC& dc, INT iHitTest, BOOL bMouseDown);
		void	DrawArrow(TinyMemDC& dc, SCROLLCALC* ps, INT iHitTest, BOOL bMouseDown);
		void	DrawThumb(TinyMemDC& dc, SCROLLCALC* ps, INT iHitTest);
		void	DrawGroove(TinyMemDC& dc, SCROLLCALC* ps);
	private:
		SIZE			m_size;
		SCROLLBOXINFO	m_si;
		BOOL			m_bMouseTracking;
		BOOL			m_bTracking;//�Ƿ񻬶�
		TinyImage		m_images[9];
	};
}


