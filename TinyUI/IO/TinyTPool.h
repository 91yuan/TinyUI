#pragma once
#include "../IO/TinyIO.h"

namespace TinyUI
{
	/// <summary>
	/// C++ Win 32Ïß³Ì³Ø
	/// </summary>
	class TinyTPool
	{
	public:
		TinyTPool(INT iCorePoolSize, INT iMaximumPoolSize)
			:m_iCorePoolSize(iCorePoolSize), m_iMaximumPoolSize(iMaximumPoolSize)
		{

		}
		virtual void Run();
	private:
		INT m_iCorePoolSize;
		INT m_iMaximumPoolSize;
	};
}

