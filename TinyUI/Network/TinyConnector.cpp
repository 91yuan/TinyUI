#include "../stdafx.h"
#include "TinyAcceptor.h"
#include "vld.h"
#include <process.h>

namespace TinyUI
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