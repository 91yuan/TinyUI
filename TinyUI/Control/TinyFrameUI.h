#pragma once
#include "TinyScrollBox.h"
#include "TinyTextBox.h"
#include "TinyLabel.h"
#include "TinyButton.h"
#include "TinyMenuBox.h"
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
	/// ���ڿ��,�ޱ߿�
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
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		//����
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	public:
		BOOL ShowWindow(INT nCmdShow) throw();
		BOOL UpdateWindow() throw();
		void CenterWindow(HWND parent, HWND window, TinySize pref) throw();
		void PosChanges(INT oldPos, INT newPos);
		void ClickSetting(void* ps, INT cmd);
		void ClickPop(void* ps, INT cmd);
	protected:
		//�������ʽ
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

		TinyMenuBox		m_menuBox;
		TinyAutoPtr<TinyMenuItem> m_menuItem1;
		TinyAutoPtr<TinyMenuItem> m_menuItem2;
		TinyAutoPtr<TinyMenuItem> m_menuItem3;
		TinyAutoPtr<TinyMenuItem> m_menuItem4;
		TinyAutoPtr<TinyMenuItem> m_menuItem5;
		TinyAutoPtr<TinyMenuItem> m_menuItem6;
		TinyAutoPtr<TinyMenuItem> m_menuItem7;
		TinyAutoPtr<TinyMenuItem> m_menuItem8;
		TinyAutoPtr<TinyMenuItem> m_menuItem9;
		TinyAutoPtr<TinyMenuItem> m_menuItem10;
	};
}
