#pragma once
#include "../Common/TinyEvent.h"
#include "TinyControl.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
#define MENUITEM_DEFAULT_WIDTH	    150
#define MENUITEM_DEFAULT_HEIGHT		28
#define MENUITEM_BREAK_HEIGHT		3
	class TinyMenuItem;
	class TinyContextMenu;
	/// <summary>
	/// 菜单项
	/// </summary>
	class TinyMenuItem : public TinyObject
	{
		friend class TinyContextMenu;
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
		void	SetChild(TinyContextMenu* ps);
		void	SetSize(SIZE size);
	private:
		SIZE				m_size;
		RECT				m_rectangle;
		BOOL				m_bBreak;
		CHAR				m_pzText[150];//菜单项显示的文本
		TinyContextMenu*	m_pOwner;//菜单项所在的菜单
		TinyContextMenu*	m_pChild;//菜单项所包含的子菜单
		UINT				m_fState;
	};
	/// <summary>
	/// 自绘菜单控件
	/// </summary>
	class TinyContextMenu : public TinyControl
	{
		friend class TinyMenuItem;
		DECLARE_DYNAMIC(TinyContextMenu)
	public:
		TinyContextMenu();
		~TinyContextMenu();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveClassName();
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
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
		BOOL Unpopup();
		Event<void(TinyMenuItem*)> Click;
	private:
		TinyMenuItem*		GetAt(POINT& pt);
		BOOL InstallMessageHook();
		BOOL UninstallMessageHook();
		void Recalculate(RECT& rect);
		void DrawMenu(TinyMemDC& dc, TinyMenuItem* hotItem = NULL);
		void DrawMenuItems(TinyMemDC& dc, TinyMenuItem* hotItem = NULL);
		void RedrawMenu();
	private:
		SIZE								m_size;
		BOOL								m_bMouseTracking;
		BOOL								m_bMouseDown;
		TinyMenuItem*						m_pFocusItem;//鼠标
		TinyImage							m_images[5];
		TinyArray<TinyMenuItem*>			m_items;
		TinyContextMenu*					m_pNext;
		TinyContextMenu*					m_pPrev;
		static HHOOK m_pMessageHook;
		static LRESULT CALLBACK MessageFilterHook(INT code, WPARAM wParam, LPARAM lParam);
	};
	__declspec(selectany) HHOOK TinyContextMenu::m_pMessageHook = NULL;
}