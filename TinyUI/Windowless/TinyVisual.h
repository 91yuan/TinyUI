#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
#define MAX_STRING 256
	//Ԫ�ط��
#define VS_VISIBLE 0x0001
#define VS_DISABLE 0x0002
	//Ԫ��״̬
#define VST_CHECK  0x0001
#define VST_HOT    0x0002
#define VST_PRESS  0x0004

	//typedef struct tagVisual
	//{
	//	tagVisual*		parent;
	//	LIST			entry;//ռλ�������������ָ���ȡ�����ṹ��ָ��
	//	LIST			children;//��Ԫ��
	//	UINT			zorder;//���Ԫ�ص�z->˳��,zorderԽ��Խ����ʾ
	//	UINT			style;//Ԫ�ط��
	//	RECT			visualrectangle;//Ԫ��λ�úʹ�С
	//	HRGN			visualregion;//Ԫ�ؾ���
	//}Visual;
	///// <summary>
	///// ���ӻ��� 
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



