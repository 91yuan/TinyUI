#pragma once
#include "../IO/TinyIO.h"
#include "TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// 图片类只支持单针
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
		operator HBITMAP() const;
		BOOL			Load(LPCSTR pz);
		BOOL			Load(BYTE* p, DWORD size);
		BOOL			Save(LPCSTR pz);//保存成BMP
		TinySize		GetSize();
		TinyRectangle	GetRectangle();
	protected:
		HBITMAP		m_hBitmap;
		INT			m_cx;
		INT			m_cy;
	};
	/// <summary>
	/// 多帧GIF解码,解码成32位
	/// </summary>
	class TinyGIFDecode
	{
	public:
		TinyGIFDecode();
		~TinyGIFDecode();
		BOOL			Load(LPCSTR pz);
		BOOL			Load(BYTE* pv, DWORD size);
		TinySize		GetSize();
		size_t			GetFrameCount();
		UINT			GetFrameDelay(INT index);
		HBITMAP			GetFrame(INT index);
		TinyRectangle	GetRectangle();
	protected:
		TinyArray<HBITMAP>   m_images;//解码后的GIF
		TinyArray<UINT>		 m_delays;//延时
		size_t				 m_count;//帧个数
		INT					 m_cx;
		INT					 m_cy;
	};
}

