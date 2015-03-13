#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "TinyVisual.h"

namespace TinyUI
{
	class TinyVisual;
	/// <summary>
	/// ÔªËØÊÂ¼þ
	/// </summary>
	class TinyVisualEvent
	{
	public:
		TinyVisual*	sender;
		TinyMsg*	msg;
		DWORD		dwTime;
	};
}



