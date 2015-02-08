#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// XML SkinΩ‚Œˆ¿‡ 
	/// </summary>
	class TinyXMLParse : public TinyObject
	{
		DECLARE_DYNAMIC(TinyXMLParse)
	public:
		TinyXMLParse();
		virtual ~TinyXMLParse();
	public:
		BOOL	LoadFile(LPCSTR pzFile);
		BOOL	LoadStream(IStream* ps);
	};
}



