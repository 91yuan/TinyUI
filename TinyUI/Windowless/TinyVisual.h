#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// 可视化元素
	/// </summary>
	class TinyVisual
	{
	public:
		TinyVisual();
	private:
		TinyVisual*		m_pParent;
		TinyVisual*		m_pChildren;
		TinyVisual*		m_pNextFocus;
		TinyVisual*		m_pPrevFocus;
		BOOL			m_visible;
		BOOL			m_enable;
		TinyLinkList<TinyVisual*> m_visuals;//UI元素链表
	};
}



