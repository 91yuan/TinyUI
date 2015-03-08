#pragma once
#include "../Common/TinyEvent.h"
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{

#define MENUITEM_DEFAULT_HEIGHT		28
#define MENUITEM_BREAK_HEIGHT		3

	class TinyMenuItem;
	class TinyMenuBox;
	/// <summary>
	/// 菜单项
	/// </summary>
	class TinyMenuItem : public TinyObject
	{
		friend class TinyMenuBox;
		DECLARE_DYNAMIC(TinyMenuItem)
	public:
		TinyMenuItem(BOOL bBreak = FALSE);
		~TinyMenuItem();
	public:
		void	SetText(LPCSTR pzText);
		LPCSTR	GetText() const;
		void	SetCheck(BOOL bFlag);
		BOOL	IsChecked();
		void	SetDisable(BOOL bFlag);
		BOOL	IsDisabled();
		void	SetChild(TinyMenuBox* ps);
	private:
		RECT			m_rectangle;
		INT				m_cy;
		BOOL			m_bBreak;
		CHAR			m_pzText[150];//菜单项显示的文本
		TinyMenuBox*	m_pOwner;//菜单项所在的菜单
		TinyMenuBox*	m_pChild;//菜单项所包含的子菜单
		UINT			m_fState;
	};
	/// <summary>
	/// 自绘菜单控件
	/// </summary>
	class TinyMenuBox : public TinyControl
	{
		friend class TinyMenuItem;
		DECLARE_DYNAMIC(TinyMenuBox)
	public:
		TinyMenuBox();
		~TinyMenuBox();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle() override;
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	public:
		BOOL AddItem(TinyMenuItem* pz);
		BOOL InsertItem(INT index, TinyMenuItem* pz);
		BOOL RemoveItem(TinyMenuItem* pz);
		BOOL RemoveAt(INT index);
		void RemoveAll();
		BOOL Popup(POINT& pt);
		BOOL IsPopup();
		Event<void(TinyMenuItem*)> Click;
	private:
		TinyMenuItem*	GetAt(POINT& pt);
		void Recalculate();
		void DrawMenu(TinyMemDC& dc, TinyMenuItem* hotItem = NULL);
		void DrawMenuItems(TinyMemDC& dc, TinyMenuItem* hotItem = NULL);
		void RedrawMenu();
	private:
		SIZE						m_size;
		BOOL						m_bMouseTracking;
		BOOL						m_bMouseDown;
		TinyMenuItem*				m_pHoverItem;//当前鼠标悬停的菜单项
		TinyMenuBox*				m_pParent;//父菜单
		TinyMenuBox*				m_pChild;//子菜单
		TinyArray<TinyMenuItem*>	m_items;
		TinyImage					m_images[5];
	};
}