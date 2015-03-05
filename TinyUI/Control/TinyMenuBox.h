#pragma once
#include "../Common/TinyEvent.h"
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
	/// <summary>
	/// ×Ô»æ²Ëµ¥¿Ø¼þ
	/// </summary>
	class TinyMenuBox : public TinyControl
	{
	public:
		TinyMenuBox();
		~TinyMenuBox();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	private:
		void DrawMenu(TinyMemDC& dc);
		void DrawBoard(TinyMemDC& dc);
		void DrawBkg(TinyMemDC& dc);
	private:
		SIZE	m_size;
		//Í¼Æ¬
		TinyImage m_images[6];
	};
}