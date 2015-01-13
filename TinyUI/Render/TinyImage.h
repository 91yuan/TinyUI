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
		operator HBITMAP() const;
		BOOL		Load(LPCSTR pz);
		BOOL		Load(BYTE* p, DWORD size);
		TinySize	GetSize();
	protected:
		HBITMAP		m_hBitmap;
		INT			m_cx;
		INT			m_cy;
		INT			m_comp;//位数1.2.3.4
	};

}

