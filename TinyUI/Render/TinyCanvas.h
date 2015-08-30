#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "TinyImage.h"
#include "TinyTransform.h"

namespace TinyUI
{
#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2	1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4	0.785398163397448309616
#endif
#define  HSLMAX			255   
#define  RGBMAX			255  
#define HSLUNDEFINED	(HSLMAX*2/3)
	/// <summary>
	/// RGBtoHSL
	/// </summary>
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor);
	/// <summary>
	/// HUEtoRGB
	/// </summary>
	FLOAT HUEtoRGB(FLOAT n1, FLOAT n2, FLOAT hue);
	/// <summary>
	/// HSLtoRGB
	/// </summary>
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor);
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
		/// ���û���Ǧ��
		/// </summary>
		HPEN SetPen(HPEN hPen);
		/// <summary>
		/// ���û��廭ˢ
		/// </summary>
		HBRUSH SetBrush(HBRUSH hBrush);
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
		/// ����9�����м���κ�4���Ǵ�С�������������
		/// </summary>
		BOOL DrawImage(TinyImage& image, RECT dstPaint, RECT srcPaint, RECT srcCenter);
		/// <summary>
		/// ������(��������Ǧ��)
		/// </summary>
		BOOL DrawLine(INT sx, INT sy, INT dx, INT dy);
		/// <summary>
		/// ������(��������Ǧ��)
		/// </summary>
		BOOL DrawLine(POINT pt1, POINT pt2);
		/// <summary>
		/// ���ƶ�������(��������Ǧ��)
		/// </summary>
		BOOL DrawLines(POINT* pts, INT size);
		/// <summary>
		/// ���ƶ�������(��������Ǧ��)
		/// </summary>
		BOOL DrawPolygon(POINT* pts, INT size);
		/// <summary>
		/// ������(��������Ǧ��)
		/// </summary>
		BOOL DrawRectangle(RECT rect);
		/// <summary>
		/// ���ƾ���(��������Ǧ��)
		/// </summary>
		BOOL DrawRectangle(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// ����Բ��(��������Ǧ��)
		/// </summary>
		BOOL DrawArc(INT x, INT y, INT radius, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// ���ƻ���(��������Ǧ��)
		/// </summary>
		BOOL DrawArc(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// ����Բ����(��������Ǧ��)
		/// </summary>
		BOOL DrawPie(INT x, INT y, INT radius, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// ��������(��������Ǧ��)
		/// </summary>
		BOOL DrawPie(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// ���Ʊ���������(��������Ǧ��)
		/// </summary>
		BOOL DrawBeziers(POINT* pts, INT size);
		/// <summary>
		/// ������Բ(��������Ǧ��)
		/// </summary>
		BOOL DrawEllipse(RECT rect);
		/// <summary>
		/// ������Բ(��������Ǧ��)
		/// </summary>
		BOOL DrawEllipse(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// �������(�������û�ˢ)
		/// </summary>
		BOOL FillPie(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// �������(�������û�ˢ)
		/// </summary>
		BOOL FillPolygon(POINT* pts, INT size);
		/// <summary>
		/// ������(�������û�ˢ)
		/// </summary>
		BOOL FillRectangle(RECT rect);
		/// <summary>
		/// ������(�������û�ˢ)
		/// </summary>
		BOOL FillRectangle(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// �����Բ(�������û�ˢ)
		/// </summary>
		BOOL FillEllipse(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// �����Բ(�������û�ˢ)
		/// </summary>
		BOOL FillEllipse(RECT rect);
		/// <summary>
		/// �������(�������û�ˢ)
		/// </summary>
		BOOL FillRegion(HRGN hRgn);
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
		/// <summary>
		/// ���ص�ǰ���������Ƿ�ɼ�
		/// </summary>
		BOOL IsVisible(RECT rect);
		/// <summary>
		/// ���ص�ǰ���������Ƿ�ɼ�
		/// </summary>
		BOOL IsVisible(POINT pt);
	private:
		HDC			m_hDC;
		HPEN		m_hPen;
		HBRUSH		m_hBrush;
		INT			m_iSave;
		TinyMatrix	m_matrix;
	};
};



