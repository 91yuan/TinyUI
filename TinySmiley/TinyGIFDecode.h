#pragma once

namespace Tiny
{
	/// <summary>
	/// GIF½âÂë
	/// </summary>
	class TinyGIFDecode
	{
	public:
		TinyGIFDecode();
		~TinyGIFDecode();
		BOOL Load(LPCSTR paFile);
		BOOL Load(char* pv, int size);
	};
}



