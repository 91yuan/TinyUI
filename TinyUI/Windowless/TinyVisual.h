#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
#define MAX_STRING 256
#define VS_CHILD            0x40000000L
#define VS_MINIMIZE         0x20000000L
#define VS_VISIBLE          0x10000000L
#define VS_DISABLED         0x08000000L
#define VS_TOPMOST			0x00000008L
#define VS_CLIPSIBLINGS     0x04000000L
#define VS_CLIPCHILDREN     0x02000000L
	/// <summary>
	/// 可视化元素
	/// </summary>
	class TinyUIElement : public TinyObject
	{

	};
}



