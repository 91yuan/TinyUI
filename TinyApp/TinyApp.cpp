// TinyApp.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TinyApp.h"
#include "Control/TinyFrameUI.h"
#include "Windowless/TinyVisualHWND.h"
#include "Database/TinyAdo.h"
#include "Network/TinyConnector.h"
#include <algorithm>

#pragma comment(lib,"TinyUI.lib")
using namespace TinyUI;

class ListV
{
public:
	ListV()
	{
		TRACE("ListV默认构造函数\n");
	}
	ListV(const ListV& other)
	{
		TRACE("ListV拷贝构造函数\n");
	}
	ListV& operator=(const ListV& other)
	{
		TRACE("ListV赋值构造函数\n");
	}
};
template<>
class DefaultTraits < ListV >
{
public:
	typedef const ListV&	CONST_ARGTYPE;
	typedef ListV&			ARGTYPE;
	static INT  Compare(const ListV& element1, const ListV& element2)
	{
		return 0;
	}
};


INT APIENTRY _tWinMain(HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	INT       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WSADATA   wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);

	HRESULT hRes = OleInitialize(NULL);

	ListV listV1;

	TinyLinkList<ListV> linkList;
	linkList.AddFirst(listV1);

	const ListV& abc = linkList.GetAt(linkList.Lookup(listV1, NULL));
	TRACE("listV1:%d,abc:%d\n",&listV1,&abc);

	::DefWindowProc(NULL, 0, 0, 0L);

	TinyApplication::GetInstance()->Initialize(hInstance, lpCmdLine, nCmdShow, MAKEINTRESOURCE(IDC_TINYAPP));

	TinyMessageLoop theLoop;
	TinyApplication::GetInstance()->AddMessageLoop(&theLoop);
	TinyFrameUI uiImpl;
	uiImpl.Create(NULL, 50, 50, 400, 500);
	uiImpl.ShowWindow(nCmdShow);
	uiImpl.UpdateWindow();

	INT loopRes = theLoop.MessageLoop();

	TinyApplication::GetInstance()->RemoveMessageLoop();
	TinyApplication::GetInstance()->Uninitialize();

	OleUninitialize();

	WSACleanup();

	return loopRes;
};