#pragma once
#include "../Common/TinyCommon.h"
#include <vssym32.h>
#include <uxtheme.h>

#pragma comment(lib, "UxTheme.lib")

namespace TinyUI
{
	class TinyTheme
	{
	public:
		TinyTheme(HWND hWND);
		~TinyTheme();
		BOOL Open();
		void Close();
	private:
		HTHEME  m_hTheme;
		HWND	m_hWND;
	};
}