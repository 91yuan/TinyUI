#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// ������
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



