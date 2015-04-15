#pragma once
#include "../IO/TinyIO.h"
#include "TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// ͼƬ��ֻ֧�ֵ���
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
		operator HBITMAP() const;
		BOOL			Load(LPCSTR pz);
		BOOL			Load(BYTE* p, DWORD size);
		BOOL			Save(LPCSTR pz);//�����BMP
		TinySize		GetSize();
		TinyRectangle	GetRectangle();
	protected:
		HBITMAP		m_hBitmap;
		INT			m_cx;
		INT			m_cy;
	};
	typedef struct tagGIFFrame
	{
		HBITMAP bitmap;
		INT		delay;
	}GIFFrame;
	/// <summary>
	/// ��֡GIF����,�����32λ
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
		TinyRectangle	GetRectangle();
		GIFFrame*		operator[](INT index);
	protected:
		TinyArray<GIFFrame*> m_images;//������GIF
		size_t				 m_count;//֡����
		INT					 m_cx;
		INT					 m_cy;
	};
}

