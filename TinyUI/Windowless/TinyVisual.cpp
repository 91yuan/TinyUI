#include "../stdafx.h"
#include "TinyVisual.h"

namespace TinyUI
{
	TinyVisual::TinyVisual()
		:m_pParent(NULL),
		m_pChildren(NULL),
		m_pNext(NULL),
		m_pPrev(NULL),
		m_visible(TRUE),
		m_enable(TRUE)
	{

	}
}
