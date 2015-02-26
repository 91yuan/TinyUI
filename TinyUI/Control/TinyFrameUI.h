#pragma once
#include "TinyScroll.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
	//ϵͳ����
#define CAPTION_HEIGHT			32
#define CLIENT_MARGIN_LEFT		2
#define CLIENT_MARGIN_TOP		2
#define CLIENT_MARGIN_RIGHT		2
#define CLIENT_MARGIN_BOTTOM	2
#define BUTTON_SIZE_CX			30
#define BUTTON_SIZE_CY			30
	/// <summary>
	/// ���ڿ��,�޴���
	/// </summary>
	class TinyFrameUI : public TinyControl
	{
		DECLARE_DYNAMIC(TinyFrameUI)
	public:
		TinyFrameUI();
		virtual ~TinyFrameUI();
		//5����������
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		//�¼�
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		//����
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	public:
		BOOL ShowWindow(INT nCmdShow) throw();
		BOOL UpdateWindow() throw();
		void CenterWindow(HWND parent, HWND window, TinySize pref) throw();
	protected:
		//�������ʽ
		TinySize m_size;
	private:
		TinyScroll m_scroll;
	};
}
