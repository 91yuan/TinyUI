#pragma once
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

namespace TinyUI
{
	class Socket
	{
	public:
		typedef std::vector<Socket> SocketList;
		enum SelectMode
		{
			SELECT_READ = 1,
			SELECT_WRITE = 2,
			SELECT_ERROR = 4
		};
		Socket();
		Socket(const Socket& socket);
		Socket& operator = (const Socket& socket);
		virtual ~Socket();
	public:
		BOOL operator == (const Socket& socket) const;
		BOOL operator != (const Socket& socket) const;
		BOOL operator <  (const Socket& socket) const;
		BOOL operator <= (const Socket& socket) const;
		BOOL operator >  (const Socket& socket) const;
		BOOL operator >= (const Socket& socket) const;
	public:
		void Close();
		static int select(SocketList& readList, SocketList& writeList, SocketList& exceptList, const Timespan& timeout);
	};

}

