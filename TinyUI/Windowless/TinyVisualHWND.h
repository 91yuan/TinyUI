#pragma once
#include "../Control/TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// 可视化窗口,管理所有可视化元素 
	/// </summary>
	class TinyVisualHWND : public TinyObject
	{
		DECLARE_DYNAMIC(TinyVisualHWND)
	public:
		TinyVisualHWND(TinyControl* host);
		virtual ~TinyVisualHWND();
	public:
		BOOL	HandleMsg();
	private:
		TinyControl* m_host;
	};
}



