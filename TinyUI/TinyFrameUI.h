#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ´°¿Ú¿ò¼Ü
	/// </summary>
	class TinyFrameUI : public TinyControl
	{
	public:
		TinyFrameUI();
		virtual ~TinyFrameUI();
		virtual BOOL Create(HWND hParent, int x, int y, int cx, int cy);
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	};
}
