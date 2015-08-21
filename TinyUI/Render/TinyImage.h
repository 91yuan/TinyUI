#pragma once
#include "../IO/TinyIO.h"
#include "TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// 图片类
	///     N=#comp     components
	///       1           grey
	///       2           grey, alpha
	///       3           red, green, blue
	///       4           red, green, blue, alpha
	/// 只支持24和32位
	/// </summary>
	class TinyImage
	{
	public:
		TinyImage();
		~TinyImage();
		operator HBITMAP() const;//默认第一帧
		BOOL			Load(LPCSTR pz);
		BOOL			Load(BYTE* p, DWORD size);
		BOOL			Save(LPCSTR pz);//保存成BMP
		size_t			GetFrameCount();
		INT				GetFrameDelay(INT index);
		HBITMAP			GetFrame(INT index);
		TinySize		GetSize();
		TinyRectangle	GetRectangle();
	protected:
		TinyArray<HBITMAP>   m_images;
		TinyArray<UINT>		 m_delays;//延时
		HBITMAP				 m_hBitmap;
		size_t				 m_count;//帧个数
		INT					 m_cx;
		INT					 m_cy;
	};
}

