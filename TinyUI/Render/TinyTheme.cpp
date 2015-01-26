#include "../stdafx.h"
#include "TinyTheme.h"

namespace TinyUI
{
	TinyTheme::TinyTheme(HWND hWND)
		:m_hTheme(NULL),
		m_hWND(hWND)
	{

	}
	TinyTheme::~TinyTheme()
	{

	}
	BOOL TinyTheme::Open()
	{
		return TRUE;
	}
	void TinyTheme::Close()
	{

	}
}
