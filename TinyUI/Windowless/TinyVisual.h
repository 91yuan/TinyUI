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
		tagVisual*		parent;//��Ԫ��
		LIST			children;//��Ԫ���б�
		UINT			style;//Ԫ�ط��
		RECT			window_rectangle;//Ԫ�ؾ���
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



