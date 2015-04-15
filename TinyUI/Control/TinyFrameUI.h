#pragma once
#include "TinyScrollBox.h"
#include "TinyTextBox.h"
#include "TinyLabel.h"
#include "TinyButton.h"
#include "TinyContextMenu.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
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


		TinyContextMenu		m_menuBox1;
		TinyContextMenu		m_menuBox2;
		TinyContextMenu		m_menuBox3;

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

		TinyScopedPtr<TinyMenuItem> m_menuItem12;
		TinyScopedPtr<TinyMenuItem> m_menuItem22;
		TinyScopedPtr<TinyMenuItem> m_menuItem32;
		TinyScopedPtr<TinyMenuItem> m_menuItem42;
		TinyScopedPtr<TinyMenuItem> m_menuItem52;

		TinyGIFDecode m_image;
		INT m_index;
	};
}
