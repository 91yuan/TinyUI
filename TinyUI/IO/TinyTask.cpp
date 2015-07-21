#include "../stdafx.h"
//#include "vld.h"
#include <process.h>
#include "TinyTask.h"

namespace TinyUI
{
	TinyTask::TinyTask()
	{
		Reset();
	}
	TinyTask::~TinyTask()
	{

	}
	void TinyTask::Destory()
	{

	}
	void TinyTask::Reset()
	{
		Internal = 0;
		InternalHigh = 0;
		Offset = 0;
		OffsetHigh = 0;
		hEvent = 0;
	}
}
