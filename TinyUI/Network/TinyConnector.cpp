#include "../stdafx.h"
#include "TinyConnector.h"
#include <process.h>

namespace TinyUI
{
	namespace Network
	{
		TinyConnector::TinyConnector(SOCKET socket)
			:m_socket(socket)
		{

		}
		BOOL TinyConnector::BeginConnect(SOCKADDR_IN address)
		{
			return FALSE;
		}
	}
}