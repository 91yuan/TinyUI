#pragma once
#include "../Common/TinyEvent.h"
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
	/// <summary>
	/// TabÏî
	/// </summary>
	class TinyTabItem :public TinyObject
	{
		DECLARE_DYNAMIC(TinyTabItem)
	public:
		TinyTabItem();
		~TinyTabItem();
	public:
		void	Render(TinyMemDC& dc);
	};
	/// <summary>
	/// ×Ô»æTab¿Ø¼þ
	/// </summary>
	class TinyTabBox : public TinyControl
	{
		DECLARE_DYNAMIC(TinyTabBox)
	public:
		TinyTabBox();
		~TinyTabBox();
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
	public:
		BOOL Add(TinyTabItem* ps);
		BOOL Remove(TinyTabItem* ps);
		BOOL RemoveAt(INT index);
	private:
		TinyArray<TinyTabItem*> m_tabs;
	};
}