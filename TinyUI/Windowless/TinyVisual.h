#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	class TinyVisualHWND;
	class TinyVisualEvent;
	class TinyVisual;
#define MAX_STRING 256
#define VS_CHILD            0x40000000L
#define VS_MINIMIZE         0x20000000L
#define VS_VISIBLE          0x10000000L
#define VS_DISABLED         0x08000000L
#define VS_TOPMOST			0x00000008L
#define VS_CLIPSIBLINGS     0x04000000L
#define VS_CLIPCHILDREN     0x02000000L
#define WINPTR_TOP       (( TinyVisual *)1L)
#define WINPTR_BOTTOM    (( TinyVisual *)2L)
#define WINPTR_TOPMOST   (( TinyVisual *)3L)
#define WINPTR_NOTOPMOST (( TinyVisual *)4L)
	struct Visual
	{
		Visual*		NEXT;
		Visual*		PREV;
		TinyVisual*	OWNER;
	};
	/// <summary>
	/// 可视化元素类
	/// </summary>
	class TinyVisual : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisual)
	private:
		DISALLOW_IMPLICIT_CONSTRUCTORS(TinyVisual)
	public:
		static TinyVisual* New(TinyVisual* parent, INT x, INT y, INT cx, INT cy);
		static void Delete(TinyVisual* val);
		virtual ~TinyVisual();
	public:
		virtual		BOOL HandleEvent(TinyVisualEvent* pEvent, BOOL& bHandle);
		void		GetRectangle(RECT& rect);
		void		SetName(LPCSTR pzName);
		LPCSTR		GetName();
		BOOL		SetParent(TinyVisual* parent);
		BOOL		IsVisible(const  TinyVisual *win);//元素是否可见
		BOOL		IsTop(const TinyVisual *win);//是否顶层元素
	public:
		static BOOL	SetVisualPos(TinyVisual* ps, TinyVisual* insertAfter, INT x, INT y, INT cx, INT cy, UINT fFlag);
		static BOOL	PtInVisual(const TinyVisual *win, INT x, INT y);
	private:
		static inline void _ADD(Visual *newVal, Visual *prevVal, Visual *nextVal);
		static inline void _ADD_AFTER(Visual *newVal, Visual *nodeVal);
		static inline void _ADD_BEFORE(Visual *newVal, Visual *nodeVal);
		static inline void _MOVE_AFTER(Visual *val, Visual *nodeVal);
		static inline void _MOVE_BEFORE(Visual *val, Visual *nodeVal);
		static void _DEL(Visual * prevVal, Visual * nextVal);
		static void _DEL_ENTRY(Visual *entry);
	public:
		TinyVisualHWND* m_host;
		TinyVisual*		m_parent;
		Visual			m_visuals;//孩子元素
		RECT			m_window_rectangle;
		RECT			m_visible_rectangle;
		HRGN			m_window_region;
		UINT			m_style;
		UINT			m_alpha;
		CHAR			m_name[MAX_STRING];
	};
}



