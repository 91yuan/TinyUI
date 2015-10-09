#include "../stdafx.h"
#include "vld.h"
#include <process.h>
#include "TinyTask.h"

namespace TinyUI
{
	namespace IO
	{
		TinyBasicTask::TinyBasicTask(FunctionType functionType)
			:m_functionType(functionType)
		{
			Reset();
		}
		TinyBasicTask::~TinyBasicTask()
		{
			Destory();
		}
		void TinyBasicTask::Complete(void* owner, const error_code& ec, UINT bytes_transferred)
		{
			m_functionType(owner, this, ec, bytes_transferred);
		}
		void TinyBasicTask::Destory()
		{
			m_functionType(NULL, this, error_code(), 0);
		}
		void TinyBasicTask::Reset()
		{
			Internal = 0;
			InternalHigh = 0;
			Offset = 0;
			OffsetHigh = 0;
			hEvent = 0;
		}
	}
}
