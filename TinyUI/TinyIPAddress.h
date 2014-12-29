#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	class TinyIPAddress :public TinyControl
	{
		DECLARE_DYNAMIC(TinyIPAddress)
	public:
		TinyIPAddress();
		virtual ~TinyIPAddress();
		LPCSTR RetrieveClassName();
		LPCSTR RetrieveTitle();
		DWORD RetrieveStyle();
		DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		BOOL IsBlank() const;
		void ClearAddress();
		INT GetAddress(_Out_ BYTE& nField0, _Out_ BYTE& nField1, _Out_ BYTE& nField2, _Out_ BYTE& nField3) const;
		INT GetAddress(_Out_ DWORD& dwAddress) const;
		void SetAddress(_In_ DWORD dwAddress);
		void SetAddress(_In_ BYTE nField0, _In_ BYTE nField1, _In_ BYTE nField2, _In_ BYTE nField3);
		void SetFieldFocus(_In_ WORD nField);
		void SetFieldRange(_In_ INT nField, _In_ BYTE nLower, _In_ BYTE nUpper);
	};
}



