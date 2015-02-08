#pragma once
#include "../Control/TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// 无客户端窗口
	/// </summary>
	class TinyView : public TinyControl
	{
		DECLARE_DYNAMIC(TinyView)
	public:
		TinyView();
		virtual ~TinyView();
		//5个创建函数
		virtual HICON	RetrieveIcon();
		virtual DWORD	RetrieveStyle();
		virtual DWORD	RetrieveExStyle();
		virtual LPCSTR	RetrieveClassName();
		virtual LPCSTR	RetrieveTitle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	};
}



