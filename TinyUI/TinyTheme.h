#pragma once
#include "../Common/TinyApplication.h"

namespace TinyUI
{
	/// <summary>
	/// ������
	/// </summary>
	class TinyTheme
	{
	public:
		TinyTheme();
		~TinyTheme();
	private:
		HMODULE m_hThemeDll;
	};
}


