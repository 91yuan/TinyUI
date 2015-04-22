#pragma once
#include "../IO/TinyIO.h"
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

namespace TinyUI
{
	/// <summary>
	/// Soekct类,基于重叠模型的socket
	/// </summary>
	class TinySocket
	{
	public:
		TinySocket();
		~TinySocket();
	private:
		SOCKET m_socket;
	};
}

