#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
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
	/// <summary>
	/// 可视化元素类
	/// </summary>
	class TinyVisual : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisual)
	private:
		TinyVisual();
	public:
		static TinyVisual* New(TinyVisual* parent, INT x, INT y, INT cx, INT cy);
		static void Delete(TinyVisual* val);
		virtual ~TinyVisual();
	public:
		virtual		BOOL HandleEvent(TinyVisualEvent* pEvent, BOOL& bHandle);
		void		SetVisualPos(INT x, INT y, INT cx, INT cy, UINT fFlag);
		BOOL		SetParent(TinyVisual* parent);
		void		GetRectangle(RECT& rect);
		void		SetName(LPCSTR pzName);
		LPCSTR		GetName();
		TinyVisual* FindVisual(TinyVisual* val, POINT pos);
	private:
		RECT	m_window_rectangle;
		RECT	m_visible_rectangle;
		HRGN	m_window_region;
		UINT	m_style;
		UINT	m_alpha;
		CHAR	m_name[128];
	};
}



