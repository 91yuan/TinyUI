#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
#define MAX_STRING 256
	//元素风格
#define VS_VISIBLE 0x0001
#define VS_DISABLE 0x0002
	//元素状态
#define VST_CHECK  0x0001
#define VST_HOT    0x0002
#define VST_PRESS  0x0004

	//typedef struct tagVisual
	//{
	//	tagVisual*		parent;
	//	LIST			entry;//占位符根据这个变量指针获取整个结构体指针
	//	LIST			children;//子元素
	//	UINT			zorder;//层叠元素的z->顺序,zorder越大越先显示
	//	UINT			style;//元素风格
	//	RECT			visualrectangle;//元素位置和大小
	//	HRGN			visualregion;//元素矩形
	//}Visual;
	///// <summary>
	///// 可视化类 
	///// </summary>
	//class TinyVisual : public TinyObject
	//{
	//	DECLARE_DYNAMIC(TinyVisual)
	//public:
	//	TinyVisual();
	//	virtual ~TinyVisual();
	//public:
	//	virtual void Render(HDC hDC);
	//	static inline Visual* GetNextVisual(Visual *val);
	//	static inline Visual* GetPrevVisual(Visual *val);
	//	static inline Visual* GetFirstChild(Visual *val);
	//	static inline Visual* GetLastChild(Visual *val);
	//	static void LinkVisual(Visual* val, Visual* previous);
	//	static BOOL SetParentVisual(Visual *val, Visual *parent);
	//	static BOOL IsVisible(const Visual *val);
	//};
}



