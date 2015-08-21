#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
		:m_pParent(NULL),
		m_pChildren(NULL),
		m_pNextFocus(NULL),
		m_pPrevFocus(NULL),
		m_visible(TRUE),
		m_enable(TRUE)
	{

	}
}
