#pragma once
#include "../Control/TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ���ӻ�����,�������п��ӻ�Ԫ�� 
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



