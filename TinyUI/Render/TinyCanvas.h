#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "TinyImage.h"
#include "TinyTransform.h"

namespace TinyUI
{
	/// <summary>
	/// ������
	/// </summary>
	class TinyCanvas
	{
	public:
		TinyCanvas();
		TinyCanvas(HDC hDC);
		~TinyCanvas();
		BOOL InitializeDC(HDC hDC);
		/// <summary>
		/// ƽ�Ʊ任
		/// </summary>
		BOOL TranslateTransform(FLOAT x, FLOAT y);
		/// <summary>
		/// ��ת�任
		/// </summary>
		BOOL RotateTransform(FLOAT angle);
		/// <summary>
		/// ���ű任
		/// </summary>
		BOOL ScaleTransform(FLOAT sx, FLOAT sy);
		/// <summary>
		/// ���б任
		/// </summary>
		BOOL ShearTransform(FLOAT sh, FLOAT sv);
		/// <summary>
		/// ���þ���
		/// </summary>
		BOOL ResetTransform();
		/// <summary>
		/// ��ָ��λ�û���ԭʼ��Image
		/// </summary>
		BOOL DrawImage(TinyImage& image, INT x, INT y);
		/// <summary>
		/// ��ָ��λ�û���ָ����С��Image
		/// </summary>
		BOOL DrawImage(TinyImage& image, INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// ��ָ��λ�û���ԭʼImage�Ĳ�����������Ӧ
		/// </summary>
		BOOL DrawImage(TinyImage& image, RECT destRect, INT srcX, INT srcY, INT srcCX, INT srcCY);
		/// <summary>
		/// ������
		/// </summary>
		BOOL DrawLine(INT sx, INT sy, INT dx, INT dy);
		/// <summary>
		/// ������
		/// </summary>
		BOOL DrawLine(POINT pt1, POINT pt2);
		/// <summary>
		/// ���ƶ�������
		/// </summary>
		BOOL DrawLines(POINT* pts, INT size);
		/// <summary>
		/// ���ƾ���
		/// </summary>
		BOOL DrawRectangle(RECT rect);
		/// <summary>
		/// ���ƾ���
		/// </summary>
		BOOL DrawRectangle(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// ����Բ��
		/// </summary>
		BOOL DrawArc(RECT rect, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// ����Բ��
		/// </summary>
		BOOL DrawArc(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// ���Ʊ���������
		/// </summary>
		BOOL DrawBeziers(POINT* pts, INT size);
		/// <summary>
		/// ������Բ
		/// </summary>
		BOOL DrawEllipse(RECT rect);
		/// <summary>
		/// ������Բ
		/// </summary>
		BOOL DrawEllipse(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// ���òü�����
		/// </summary>
		BOOL SetClip(RECT rect);
		/// <summary>
		/// ���òü�����
		/// </summary>
		BOOL SetClip(HRGN hRgn);
		/// <summary>
		/// ���òü�����
		/// </summary>
		BOOL SetClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// ���òü�����
		/// </summary>
		BOOL SetClip(RECT rect, INT iCombineMode);
		/// <summary>
		/// ���òü�����
		/// </summary>
		BOOL SetClip(HRGN hRgn, INT iCombineMode);
		/// <summary>
		/// ���òü�����
		/// </summary>
		BOOL SetClip(INT x, INT y, INT cx, INT cy, INT iCombineMode);
		/// <summary>
		/// �Ӳü�������ȥ����Ӿ���
		/// </summary>
		BOOL IntersectClip(RECT rect);
		/// <summary>
		/// �Ӳü�������ȥ����Ӿ���
		/// </summary>
		BOOL IntersectClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// �Ӳü�������ȥ���������
		/// </summary>
		BOOL IntersectClip(HRGN hRgn);
		/// <summary>
		/// �Ӳü�������ȥ��ȥ������
		/// </summary>
		BOOL ExcludeClip(RECT rect);
		/// <summary>
		/// �Ӳü�������ȥ��ȥ������
		/// </summary>
		BOOL ExcludeClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// �Ӳü�������ȥ��ȥ������
		/// </summary>
		BOOL ExcludeClip(HRGN hRgn);
		/// <summary>
		/// ��ֵ�ü�����
		/// </summary>
		BOOL ResetClip();
		/// <summary>
		/// ���زü������Ƿ�Ϊ��
		/// </summary>
		BOOL IsClipEmpty() const;
		/// <summary>
		/// ���ؿɼ��Ĳü������Ƿ�Ϊ��
		/// </summary>
		BOOL IsVisibleClipEmpty() const;
	private:
		HDC			m_hDC;
		INT			m_iSave;
		TinyMatrix	m_matrix;
	};
};



