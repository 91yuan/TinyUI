#pragma once
#include "../IO/TinyIO.h"

namespace TinyUI
{
	template <typename Operation>
	class TaskQueue;
	/// <summary>
	/// C++ �������
	/// </summary>
	template <typename Operation>
	class TaskQueue
	{
		DISALLOW_COPY_AND_ASSIGN(TaskQueue);
	public:
		TaskQueue();
		void Pop();
		void Push();
	};
};

