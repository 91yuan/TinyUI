#pragma once
#include "../IO/TinyIO.h"
#include "TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// Õº∆¨¿‡
	///     N=#comp     components
	///       1           grey
	///       2           grey, alpha
	///       3           red, green, blue
	///       4           red, green, blue, alpha
	/// </summary>
	class TinyImage
	{
	public:
		TinyImage();
		~TinyImage();
		BOOL Load(LPCSTR pz, INT req_comp);
		BOOL Load(BYTE* data, DWORD size, INT req_comp);
		void Render(TinyDC& dc, INT x, INT y, INT cx, INT cy);
		void Render(HDC dc, INT x, INT y, INT cx, INT cy);
	private:
		HBITMAP	m_hBitmap;
	};

}

