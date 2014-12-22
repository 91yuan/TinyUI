#pragma once
#include "TinyObject.h"
#include "TinyCollection.h"

/// <summary>
/// ��Ϣ���� ������Ϣ��,��Ϣɸѡ��,��Ϣӳ���
/// </summary>
namespace TinyUI
{
	/// <summary>
	/// Msg����
	/// </summary>
	class TinyMsg : public MSG
	{
	public:
		int cbSize;
		BOOL bHandled;
		TinyMsg();
		TinyMsg(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, DWORD dwTime, POINT ptIn, BOOL bHandledIn);
		TinyMsg(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, BOOL bHandledIn = TRUE);
		TinyMsg(MSG& msg, BOOL bHandledIn = TRUE);
	};
	/// <summary>
	/// ��Ϣӳ��
	/// </summary>
	class TINY_NO_VTABLE TinyMessageMap
	{
	public:
		virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
		{
			return FALSE;
		};
	};
	/// <summary>
	/// ��Ϣɸѡ��
	/// </summary>
	class TINY_NO_VTABLE TinyMessageFilter
	{
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg) = 0;
	};
	/// <summary>
	/// ��Ϣɸѡ������
	/// </summary>
	class TinyMessageFilters
	{
	public:
		TinyMessageFilters();
		~TinyMessageFilters();
		BOOL Add(TinyMessageFilter* element);
		BOOL Remove(TinyMessageFilter* element);
		BOOL RemoveAt(INT index);
		void RemoveAll();
		INT  GetSize() const;
		const TinyMessageFilter* operator[] (INT index) const;
		TinyMessageFilter* operator[] (INT index);
		INT Lookup(TinyMessageFilter* element) const;
	private:
		TinyArray<TinyMessageFilter*> m_array;
	};
	/// <summary>
	/// ��Ϣѭ��
	/// </summary>
	class TinyMessageLoop
	{
	public:
		MSG m_msg;
		TinyMessageFilters mFilters;
	public:
		BOOL AddMessageFilter(TinyMessageFilter* pMessageFilter);
		BOOL RemoveMessageFilter(TinyMessageFilter* pMessageFilter);
		INT MessageLoop();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	};
#define BEGIN_MSG_MAP(theClass,theBaseClass) \
	typedef theBaseClass TheBaseClass; \
public: \
	virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult) \
	{ \
	BOOL bHandled = TRUE; \
	(hWnd); \
	(uMsg); \
	(wParam); \
	(lParam); \
	(lResult); \
	(bHandled);
#define MESSAGE_HANDLER(msgs, func) \
	if (uMsg == msgs) \
	{ \
	bHandled = TRUE; \
	lResult = func(uMsg, wParam, lParam, bHandled); \
	if (bHandled) \
	return TRUE; \
	}
#define MESSAGE_RANGE_HANDLER(msgFirst, msgLast, func) \
	if (uMsg >= msgFirst && uMsg <= msgLast) \
	{ \
	bHandled = TRUE; \
	lResult = func(uMsg, wParam, lParam, bHandled); \
	if (bHandled) \
	return TRUE; \
	}
#define COMMAND_HANDLER(id, code, func) \
	if (uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if (bHandled) \
	return TRUE; \
	}
#define CHAIN_MSG_MAP(theBaseClass) \
	{ \
	if (theBaseClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
	return TRUE; \
	}
#define END_MSG_MAP() \
	{ \
	if (TheBaseClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
	return TRUE; \
	}\
	return FALSE; \
	}
}

