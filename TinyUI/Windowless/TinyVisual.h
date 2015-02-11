#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
#define MAX_STRING 256
#define VS_CHILD            0x40000000L
#define VS_MINIMIZE         0x20000000L
#define VS_VISIBLE          0x10000000L
#define VS_DISABLED         0x08000000L
#define VS_TOPMOST			0x00000008L
#define VISUAL_TOP       ((Visual*)1L)
#define VISUAL_BOTTOM    ((Visual*)2L)
#define VISUAL_TOPMOST   ((Visual*)3L)
#define VISUAL_NOTOPMOST ((Visual*)4L)
	typedef struct tagVisual
	{
		tagVisual*		parent;
		tagVisual*		last_active;//激活的元素
		LIST			children;//子元素
		UINT			zorder;//层叠元素的z->顺序,zorder越大越先显示
		UINT			style;//元素风格
		RECT			window_rectangle;//元素矩形
		RECT			visible_rectangle;//可见的矩形
		HRGN			region;//可见区域
		LIST			entry;//占位符根据这个变量指针获取整个结构体指针
	}Visual;
	/// <summary>
	/// 可视化类 
	/// </summary>
	class TinyVisual : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisual)
	public:
		TinyVisual();
		virtual ~TinyVisual();
	public:
		virtual void Render(HDC hDC);

		//静态
		static inline Visual* GetNextVisual(Visual *val);
		static inline Visual* GetPrevVisual(Visual *val);
		static inline Visual* GetFirstChild(Visual *val);
		static inline Visual* GetLastChild(Visual *val);
		static void LinkVisual(Visual* val, Visual* previous);
		static BOOL SetParent(Visual *val, Visual *parent);
		static inline BOOL IsVisible(const Visual *val);
		static inline BOOL	IsTop(const Visual *val);
		static inline BOOL GetVisibleRectangle(const Visual* val, TinyRectangle& rect);
		static inline HRGN GetVisibleRegion(const Visual* val, UINT flags);
		static inline BOOL PtInVisual(const Visual* val, INT x, INT y);
		static inline BOOL SetRegion(Visual *val, HRGN region, INT redraw);
		static BOOL SetVisualPos(Visual* val, Visual* previous, UINT swpFlags);
	protected:
		Visual m_visual;
	};
}



