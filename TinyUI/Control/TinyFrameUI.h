#pragma once
#include "TinyControl.h"
#include "TinyButton.h"
#include "TinyListBox.h"

namespace TinyUI
{
	/// <summary>
	/// ���ڿ��
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
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		//�¼�
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	public:
		BOOL ShowWindow(int nCmdShow) throw();
		BOOL UpdateWindow() throw();
	private:
		TinyButton button;
		TinyListBox listBox;
	};
}
