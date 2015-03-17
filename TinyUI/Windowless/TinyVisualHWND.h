#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
	class TinyVisualEvent;
	class TinyVisual;
	/// <summary>
	/// 可视化窗口,管理所有可视化元素 
	/// </summary>HTCLOSE
	class TinyVisualHWND : public TinyControl
	{
		friend class TinyVisual;
		DECLARE_DYNAMIC(TinyVisualHWND)
	public:
		TinyVisualHWND();
		virtual ~TinyVisualHWND();
		virtual DWORD	RetrieveStyle();
		virtual DWORD	RetrieveExStyle();
		virtual LPCSTR	RetrieveClassName();
		virtual LPCSTR	RetrieveTitle();
		virtual HICON	RetrieveIcon();
		virtual BOOL	ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	public:
		BOOL			Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	private:
		TinyVisual*		m_pDesktop;//桌面根节点
		TinyVisual*		m_pCapture;//捕获鼠标的
		TinyVisual*		m_pFocus;//有焦点的
		TinyRectangle	m_windowRectangle;//缓冲的矩形大小
		TinyDC			m_canvas;//画布
	};
}



