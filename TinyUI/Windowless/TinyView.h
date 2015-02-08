#pragma once
#include "../Control/TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// �޿ͻ��˴���
	/// </summary>
	class TinyView : public TinyControl
	{
		DECLARE_DYNAMIC(TinyView)
	public:
		TinyView();
		virtual ~TinyView();
		//5����������
		virtual HICON	RetrieveIcon();
		virtual DWORD	RetrieveStyle();
		virtual DWORD	RetrieveExStyle();
		virtual LPCSTR	RetrieveClassName();
		virtual LPCSTR	RetrieveTitle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	};
}



