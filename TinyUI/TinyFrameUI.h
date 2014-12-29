#pragma once
#include "TinyControl.h"
#include "TinyButton.h"

namespace TinyUI
{
	/// <summary>
	/// ´°¿Ú¿ò¼Ü
	/// </summary>
	class TinyFrameUI : public TinyControl
	{
		DECLARE_DYNAMIC(TinyFrameUI)
	public:
		TinyFrameUI();
		virtual ~TinyFrameUI();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	public:
		BOOL Create(HWND hParent, int x, int y, int cx, int cy);
	private:
		TinyButton btn;
	};
}
