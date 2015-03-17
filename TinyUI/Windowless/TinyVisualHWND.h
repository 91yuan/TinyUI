#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
	class TinyVisualEvent;
	class TinyVisual;
	/// <summary>
	/// ���ӻ�����,�������п��ӻ�Ԫ�� 
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
		TinyVisual*		m_pDesktop;//������ڵ�
		TinyVisual*		m_pCapture;//��������
		TinyVisual*		m_pFocus;//�н����
		TinyRectangle	m_windowRectangle;//����ľ��δ�С
		TinyDC			m_canvas;//����
	};
}



