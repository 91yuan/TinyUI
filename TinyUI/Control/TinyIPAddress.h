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
		INT GetAddress( BYTE& nField0,  BYTE& nField1,  BYTE& nField2,  BYTE& nField3) const;
		INT GetAddress( DWORD& dwAddress) const;
		void SetAddress( DWORD dwAddress);
		void SetAddress( BYTE nField0,  BYTE nField1,  BYTE nField2,  BYTE nField3);
		void SetFieldFocus( WORD nField);
		void SetFieldRange( INT nField,  BYTE nLower,  BYTE nUpper);
	};
}



