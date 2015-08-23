#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "TinyImage.h"
#include "TinyTransform.h"

namespace TinyUI
{
	/// <summary>
	/// 画布类
	/// </summary>
	class TinyCanvas
	{
	public:
		TinyCanvas();
		TinyCanvas(HDC hDC);
		~TinyCanvas();
		BOOL InitializeDC(HDC hDC);
		/// <summary>
		/// 平移变换
		/// </summary>
		BOOL TranslateTransform(FLOAT x, FLOAT y);
		/// <summary>
		/// 旋转变换
		/// </summary>
		BOOL RotateTransform(FLOAT angle);
		/// <summary>
		/// 缩放变换
		/// </summary>
		BOOL ScaleTransform(FLOAT sx, FLOAT sy);
		/// <summary>
		/// 剪切变换
		/// </summary>
		BOOL ShearTransform(FLOAT sh, FLOAT sv);
		/// <summary>
		/// 重置矩阵
		/// </summary>
		BOOL ResetTransform();
		/// <summary>
		/// 在指定位置绘制原始的Image
		/// </summary>
		BOOL DrawImage(TinyImage& image, INT x, INT y);
		/// <summary>
		/// 在指定位置绘制指定大小的Image
		/// </summary>
		BOOL DrawImage(TinyImage& image, INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 在指定位置绘制原始Image的部分缩放自适应
		/// </summary>
		BOOL DrawImage(TinyImage& image, RECT destRect, INT srcX, INT srcY, INT srcCX, INT srcCY);
		/// <summary>
		/// 绘制线
		/// </summary>
		BOOL DrawLine(INT sx, INT sy, INT dx, INT dy);
		/// <summary>
		/// 绘制线
		/// </summary>
		BOOL DrawLine(POINT pt1, POINT pt2);
		/// <summary>
		/// 绘制多条曲线
		/// </summary>
		BOOL DrawLines(POINT* pts, INT size);
		/// <summary>
		/// 绘制矩形
		/// </summary>
		BOOL DrawRectangle(RECT rect);
		/// <summary>
		/// 绘制矩形
		/// </summary>
		BOOL DrawRectangle(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 绘制圆弧
		/// </summary>
		BOOL DrawArc(RECT rect, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 绘制圆弧
		/// </summary>
		BOOL DrawArc(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 绘制贝塞尔曲线
		/// </summary>
		BOOL DrawBeziers(POINT* pts, INT size);
		/// <summary>
		/// 绘制椭圆
		/// </summary>
		BOOL DrawEllipse(RECT rect);
		/// <summary>
		/// 绘制椭圆
		/// </summary>
		BOOL DrawEllipse(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(RECT rect);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(HRGN hRgn);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(RECT rect, INT iCombineMode);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(HRGN hRgn, INT iCombineMode);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(INT x, INT y, INT cx, INT cy, INT iCombineMode);
		/// <summary>
		/// 从裁剪区域中去掉添加矩形
		/// </summary>
		BOOL IntersectClip(RECT rect);
		/// <summary>
		/// 从裁剪区域中去掉添加矩形
		/// </summary>
		BOOL IntersectClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 从裁剪区域中去掉添加区域
		/// </summary>
		BOOL IntersectClip(HRGN hRgn);
		/// <summary>
		/// 从裁剪区域中去掉去掉矩形
		/// </summary>
		BOOL ExcludeClip(RECT rect);
		/// <summary>
		/// 从裁剪区域中去掉去掉矩形
		/// </summary>
		BOOL ExcludeClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 从裁剪区域中去掉去掉区域
		/// </summary>
		BOOL ExcludeClip(HRGN hRgn);
		/// <summary>
		/// 充值裁剪区域
		/// </summary>
		BOOL ResetClip();
		/// <summary>
		/// 返回裁剪区域是否为空
		/// </summary>
		BOOL IsClipEmpty() const;
		/// <summary>
		/// 返回可见的裁剪区域是否为空
		/// </summary>
		BOOL IsVisibleClipEmpty() const;
	private:
		HDC			m_hDC;
		INT			m_iSave;
		TinyMatrix	m_matrix;
	};
};



