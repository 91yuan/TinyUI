#pragma once
#include "TinyScrollBox.h"
#include "TinyTextBox.h"
#include "TinyLabel.h"
#include "TinyButton.h"
#include "TinyMenuBox.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
	//系统参数
#define CAPTION_HEIGHT			32
#define CLIENT_MARGIN_LEFT		2
#define CLIENT_MARGIN_TOP		2
#define CLIENT_MARGIN_RIGHT		2
#define CLIENT_MARGIN_BOTTOM	2
#define BUTTON_SIZE_CX			30
#define BUTTON_SIZE_CY			30
	/// <summary>
	/// 窗口框架,无边框
	/// </summary>
	class TinyFrameUI : public TinyControl
	{
		DECLARE_DYNAMIC(TinyFrameUI)
	public:
		TinyFrameUI();
		virtual ~TinyFrameUI();
		//5个创建函数
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		//事件
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		//方法
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	public:
		BOOL ShowWindow(INT nCmdShow) throw();
		BOOL UpdateWindow() throw();
		void CenterWindow(HWND parent, HWND window, TinySize pref) throw();
		void PosChanges(INT oldPos, INT newPos);
		void ClickSetting(void* ps, INT cmd);
		void ClickPop(void* ps, INT cmd);
		void CreateMenuBox();
	protected:
		//缓冲的样式
		TinySize m_size;
	private:
		TinyScrollBox m_scroll;
		TinyTextBox m_txtPos;
		TinyTextBox m_txtPage;
		TinyTextBox m_txtMax;
		TinyTextBox m_txtMin;
		TinyLabel	m_lblPos;
		TinyLabel	m_lblPage;
		TinyLabel	m_lblMax;
		TinyLabel	m_lblMin;
		TinyButton	m_btn;
		TinyButton	m_btnPop;
		Delegate<void(INT, INT)> m_fs_PosChange;
		Delegate<void(void*, INT)> m_fs_Click;
		Delegate<void(void*, INT)> m_fs_Pop;


		TinyMenuBox*		m_pMenuBox1;
		TinyMenuBox*		m_pMenuBox2;

		TinyScopedPtr<TinyMenuItem> m_menuItem1;
		TinyScopedPtr<TinyMenuItem> m_menuItem2;
		TinyScopedPtr<TinyMenuItem> m_menuItem3;
		TinyScopedPtr<TinyMenuItem> m_menuItem4;
		TinyScopedPtr<TinyMenuItem> m_menuItem5;

		TinyScopedPtr<TinyMenuItem> m_menuItem11;
		TinyScopedPtr<TinyMenuItem> m_menuItem21;
		TinyScopedPtr<TinyMenuItem> m_menuItem31;
		TinyScopedPtr<TinyMenuItem> m_menuItem41;
		TinyScopedPtr<TinyMenuItem> m_menuItem51;
		/*TinyMenuBox		m_menuBox1;
		TinyMenuBox		m_menuBox2;
		TinyMenuBox		m_menuBox3;
		TinyMenuBox		m_menuBox4;
		TinyScopedPtr<TinyMenuItem> m_menuItem1;
		TinyScopedPtr<TinyMenuItem> m_menuItem2;
		TinyScopedPtr<TinyMenuItem> m_menuItem3;
		TinyScopedPtr<TinyMenuItem> m_menuItem4;
		TinyScopedPtr<TinyMenuItem> m_menuItem5;
		TinyScopedPtr<TinyMenuItem> m_menuItem6;
		TinyScopedPtr<TinyMenuItem> m_menuItem7;
		TinyScopedPtr<TinyMenuItem> m_menuItem8;
		TinyScopedPtr<TinyMenuItem> m_menuItem9;
		TinyScopedPtr<TinyMenuItem> m_menuItem10;

		TinyScopedPtr<TinyMenuItem> m_menuItem11;
		TinyScopedPtr<TinyMenuItem> m_menuItem12;
		TinyScopedPtr<TinyMenuItem> m_menuItem13;
		TinyScopedPtr<TinyMenuItem> m_menuItem14;
		TinyScopedPtr<TinyMenuItem> m_menuItem15;

		TinyScopedPtr<TinyMenuItem> m_menuItem111;
		TinyScopedPtr<TinyMenuItem> m_menuItem121;
		TinyScopedPtr<TinyMenuItem> m_menuItem131;
		TinyScopedPtr<TinyMenuItem> m_menuItem141;
		TinyScopedPtr<TinyMenuItem> m_menuItem151;

		TinyScopedPtr<TinyMenuItem> m_menuItem112;
		TinyScopedPtr<TinyMenuItem> m_menuItem122;
		TinyScopedPtr<TinyMenuItem> m_menuItem132;
		TinyScopedPtr<TinyMenuItem> m_menuItem142;
		TinyScopedPtr<TinyMenuItem> m_menuItem152;*/
	};
}
