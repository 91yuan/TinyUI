#pragma once
#include "../IO/TinyIO.h"

namespace TinyUI
{
	/// <summary>
	/// C++ IO·þÎñ
	/// </summary>
	class IOService
	{
		DISALLOW_COPY_AND_ASSIGN(IOService)
	public:
		explicit IOService(DWORD concurrency);
		virtual INT Run();
		virtual INT Post();
		virtual void Stop();
	private:
		DWORD m_concurrency;
	};
}

