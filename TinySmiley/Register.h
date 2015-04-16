#pragma once

namespace Tiny
{
	HRESULT RegisterServer(HMODULE hModule,
		const CLSID& clsid,
		LPCTSTR szFriendlyName,
		LPCTSTR szVerIndProgID,
		LPCTSTR szProgID);
	HRESULT UnregisterServer(const CLSID& clsid,
		LPCTSTR szVerIndProgID,
		LPCTSTR szProgID);
}

