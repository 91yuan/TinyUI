#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
	class TinyVisualHWND : public TinyControl
	{
		DECLARE_DYNAMIC(TinyVisualHWND)
	public:
		TinyVisualHWND();
		~TinyVisualHWND();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	public:
		BOOL	Add(TinyVisual* ps);
		BOOL	Remove(TinyVisual* ps);
		void	RemoveAll();
	private:
		SIZE		m_size;
		TinyVisual*	m_desktop;
		static TinyLinkList<TinyVisual*> m_visuals;
	};
}



