#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// ���ӻ�Ԫ��
	/// </summary>
	class TinyVisual
	{
	public:
		TinyVisual();
	private:
		BOOL			m_visible;
		BOOL			m_enable;
		TinyVisual*		m_pParent;
		TinyVisual*		m_pChildren;
		TinyVisual*		m_pNext;
		TinyVisual*		m_pPrev;
	};
}



