#pragma once
#include "../IO/TinyIO.h"
#include "TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// ͼƬ��
	///     N=#comp     components
	///       1           grey
	///       2           grey, alpha
	///       3           red, green, blue
	///       4           red, green, blue, alpha
	/// ֻ֧��24��32λ
	/// </summary>
	class TinyImage
	{
	public:
		TinyImage();
		~TinyImage();
		operator HBITMAP() const;//Ĭ�ϵ�һ֡
		BOOL			Load(LPCSTR pz);
		BOOL			Load(BYTE* p, DWORD size);
		BOOL			Save(LPCSTR pz);//�����BMP
		size_t			GetFrameCount();
		INT				GetFrameDelay(INT index);
		HBITMAP			GetFrame(INT index);
		TinySize		GetSize();
		TinyRectangle	GetRectangle();
	protected:
		TinyArray<HBITMAP>   m_images;
		TinyArray<UINT>		 m_delays;//��ʱ
		HBITMAP				 m_hBitmap;
		size_t				 m_count;//֡����
		INT					 m_cx;
		INT					 m_cy;
	};
}

