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
	class TinyVisualHWND;
	class TinyVisualEvent;
	class TinyVisual;
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
		friend class TinyVisualHWND;
		DECLARE_DYNAMIC(TinyVisual)
		DISALLOW_IMPLICIT_CONSTRUCTORS(TinyVisual)
	private:
		TinyVisual(TinyVisualHWND* hostHWND);
		TinyVisual(TinyVisual* parent, INT x, INT y, INT cx, INT cy);
	public:
		virtual ~TinyVisual();
	public:
		TinyVisualHWND* m_hostHWND;
		TinyVisual*		m_parent;//父元素
		Visual			m_visuals;//孩子元素
		TinyRectangle	m_rectangle;//矩形大小
		CHAR			m_name[MAX_STRING];
		CHAR			m_text[MAX_STRING];
		BOOL			m_bVisible;
		BOOL			m_bEnable;
		BOOL			m_bFocus;
	public:
		LPCSTR			GetName();
		void			SetName(LPCSTR pzName);
		LPCSTR			GetText();
		void			SetText(LPCSTR pzText);
		BOOL			IsVisible() const;
		BOOL			IsEnable() const;
		BOOL			IsFocus() const;
		void			SetVisible(BOOL bVisible = TRUE);
		void			SetEnable(BOOL bEnable = TRUE);
	public:
		static TinyVisual* New(TinyVisual* parent, INT x, INT y, INT cx, INT cy);
		static void	Delete(TinyVisual* ps);
		static BOOL IsEmpty(Visual* list);
		static Visual* GetNext(const Visual *list, const Visual *elem);
		static Visual* GetPrev(const Visual *list, const Visual *elem);
		static inline Visual *GetFirst(const Visual *list);
		static inline Visual *GetLast(const Visual *list);
		static void Remove(struct Visual *elem);
	};
}



