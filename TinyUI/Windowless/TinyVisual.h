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
	//#define VISUAL_TOP			((Visual*)1L)
	//#define VISUAL_BOTTOM		((Visual*)2L)
	//#define VISUAL_TOPMOST		((Visual*)3L)
	//#define VISUAL_NOTOPMOST	((Visual*)4L)

	//typedef struct tagVisual
	//{
	//	tagVisual*		parent;//父元素
	//	LIST			children;//子元素列表Z-ORDER
	//	LIST			unlink;//没有链接到Z-ORDER
	//	UINT			style;//元素风格
	//	BOOL			islink;//是否链接
	//	RECT			window_rectangle;//元素矩形
	//	RECT			visible_rectangle;//可见的矩形
	//	HRGN			region;//可见区域
	//	LIST			entry;//占位符根据这个变量指针获取整个结构体指针
	//}Visual;
	/*inline Visual* GetNextVisual(Visual *val);
	inline Visual* GetPrevVisual(Visual *val);
	inline Visual* GetFirstChild(Visual *val);
	inline Visual* GetLastChild(Visual *val);
	inline BOOL IsTopMost(const Visual *val);
	inline BOOL IsVisible(const Visual *val);
	void LinkVisual(Visual *win, Visual *previous);
	BOOL	SetParent(Visual* val, Visual* parent);
	BOOL	SetVisualPos(Visual* val, Visual* valAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags);
	Visual* CreateVisual(Visual* parent);
	void DestoryVisual(Visual* win);*/
	/// <summary>
	/// 可视化类双向链表 
	/// </summary>
	class TinyVisual : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisual)
	public:
		TinyVisual();
	public:
		virtual ~TinyVisual();
	private:
		TinyVisual* m_pParent;
		TinyVisual* m_pNext;
		TinyVisual* m_pPrev;
		DWORD		m_dwStyle;
		RECT		m_windowRectangle;
		RECT		m_visibleRectangle;
	};
}



