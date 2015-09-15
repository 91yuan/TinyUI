#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
	class TinyVisual;
	class TinyVisualHWND : public TinyControl, public TinyVisual
	{
		DECLARE_DYNAMIC(TinyVisualHWND)
	public:
		TinyVisualHWND();
		~TinyVisualHWND();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual DWORD RetrieveStyle() OVERRIDE;
		virtual DWORD RetrieveExStyle() OVERRIDE;
		virtual LPCSTR RetrieveClassName() OVERRIDE;
		virtual LPCSTR RetrieveTitle() OVERRIDE;
		virtual HICON RetrieveIcon() OVERRIDE;
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	private:
		SIZE		m_size;
	};
}



