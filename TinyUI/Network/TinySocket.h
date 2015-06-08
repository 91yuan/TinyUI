#pragma once
#include "../IO/TinyIO.h"
#include "../Common/TinyCallback.h"
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

namespace TinyUI
{
	typedef Callback<void(INT)> CompleteCallback;
	/// <summary>
	/// IO»º³å
	/// </summary>
	class ScopeIO : public TinyReference < ScopeIO >
	{
	public:
		ScopeIO();
		explicit ScopeIO(INT size);
		CHAR* Ptr();
	protected:
		explicit ScopeIO(CHAR* data);
		virtual ~ScopeIO();
		CHAR* m_data;
	};
	/// <summary>
	/// Soekct»ùÀà
	/// </summary>
	class TinySocket
	{
		DISALLOW_COPY_AND_ASSIGN(TinySocket);
	public:
		BOOL		Open();
		BOOL		Close();
		BOOL		Accept(TinySocket& socket, sockaddr& address);
		BOOL		Bind(sockaddr& address);
		BOOL		Connect(sockaddr& address, CompleteCallback);
		BOOL		Listen(INT backlog);
		virtual INT Read(ScopeIO* ps, INT size, const CompleteCallback& callback) = 0;
		virtual INT Write(ScopeIO* ps, INT size, const CompleteCallback& callback) = 0;
		INT			GetLastError();
	public:
		operator SOCKET() const;
		BOOL operator==(TinySocket& socket);
	protected:
		SOCKET		m_socket;
		INT			m_addressFamily;
		INT			m_type;
		INT			m_protocol;
	};
}

