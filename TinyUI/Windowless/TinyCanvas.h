#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// ª≠≤º¿‡
	/// </summary>
	class TinyCanvas
	{
	public:
		TinyCanvas();
		~TinyCanvas();
		BOOL InitializeDC(HDC hDC);
	private:
		HDC m_hDC;
	};
};



