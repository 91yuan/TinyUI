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
#define VS_CLIPSIBLINGS     0x04000000L
#define VS_CLIPCHILDREN     0x02000000L
#define VISUAL_TOP			((Visual*)1L)
#define VISUAL_BOTTOM		((Visual*)2L)
#define VISUAL_TOPMOST		((Visual*)3L)
#define VISUAL_NOTOPMOST	((Visual*)4L)

	DECLARE_HANDLE(HELM);

	typedef struct tagVisual
	{
		tagVisual*		parent;//父元素
		LIST			children;//子元素列表
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
	public:
		virtual ~TinyVisual();
	public:
		static inline Visual* GetNextVisual(Visual *val);
		static inline Visual* GetPrevVisual(Visual *val);
		static inline Visual* GetFirstChild(Visual *val);
		static inline Visual* GetLastChild(Visual *val);
		static inline BOOL IsTop(const Visual *val);
		static inline BOOL IsVisible(const Visual *val);
		static BOOL	SetParent(Visual* val, Visual* parent);
		static BOOL	SetVisualPos(Visual* val, Visual* valAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags);
	};
}



