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
	typedef struct tagVisual
	{
		tagVisual*		parent;
		tagVisual*		last_active;//�����Ԫ��
		LIST			children;//��Ԫ��
		UINT			zorder;//���Ԫ�ص�z->˳��,zorderԽ��Խ����ʾ
		UINT			style;//Ԫ�ط��
		RECT			window_rectangle;//Ԫ�ؾ����������Ļ
		RECT			client_rectangle;//�ͻ��˾���
		RECT			visible_rectangle;//�ɼ��ľ���
		HRGN			region;//�ɼ�����
		LIST			entry;//ռλ�������������ָ���ȡ�����ṹ��ָ��
	}Visual;
	/// <summary>
	/// ���ӻ��� 
	/// </summary>
	class TinyVisual : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisual)
	public:
		TinyVisual();
		virtual ~TinyVisual();
	public:
		virtual void Render(HDC hDC);

		//��̬
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
		static inline Visual* GetTopClippingVisual(Visual *val);
		static inline BOOL IntersectRegion(HRGN hRgn, Visual *val);
		static BOOL SetVisualPos(Visual* val, Visual* previous, UINT swpFlags);
		static HRGN	GetVisibleRegion(Visual* val, UINT flags);
		static BOOL ClipChildren(Visual *parent, Visual *last, HRGN hRgn, INT offset_x, INT offset_y);
		static inline void MirrorRectangle(const RECT *client_rect, RECT *rect);
		static inline INT IntersectRectangle(RECT *dst, const RECT *src1, const RECT *src2);
	protected:
		Visual m_visual;
	};
}



