#pragma once
#include "TinyControl.h"

namespace TinyUI
{
	/// <summary>
	/// ÈÈ¼ü¿Ø¼þ
	/// </summary>
	class TinyHotKey :public TinyControl
	{
		DECLARE_DYNAMIC(TinyHotKey)
	public:
		TinyHotKey();
		virtual ~TinyHotKey();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
		void SetHotKey(WORD wVirtualKeyCode, WORD wModifiers);
		DWORD GetHotKey() const;
		void GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const;
		void SetRules(WORD wInvalidComb, WORD wModifiers);
	};
}
