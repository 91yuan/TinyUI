// TinyApp.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TinyApp.h"
#include "Control/TinyFrameUI.h"
#include "Windowless/TinyVisualHWND.h"
#include "Database/TinyAdo.h"
#include "Network/TinyConnector.h"
#include <algorithm>
#include "TinySmiley.h"
#include <map>

#include <boost/intrusive/rbtree.hpp>

#pragma comment(lib,"TinyUI.lib")
using namespace TinyUI;

INT APIENTRY _tWinMain(HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	INT       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*WSADATA   wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);*/


	srand(1000);
	TinyTreeMap<INT, INT> map(10);
	DWORD dwTime = GetTickCount();
	int rand1 = 0;
	int rand2 = 0;
	for (INT i = 0; i < 1000; i++)
	{
		rand1 = i;
		rand2 = i;
		//TRACE("rand1:%d,rand2:%d\n", rand1, rand2);
		map.Add(rand1, rand2);
		//map.inOrder();
	}
	ITERATOR pos = NULL;
	for (pos = map.First(); pos != NULL; pos = map.Next(pos))
	{
		int a = map.GetKeyAt(pos);
		int b = map.GetValueAt(pos);
		TRACE("Key:%d,Value:%d\n", a, b);
	}
	int a = 10;
	int* b = map.Lookup(a);
	TRACE("%d\n", *b);
	/*DWORD dwTime1 = GetTickCount();
	TRACE("TinyTreeMap秒数: %d\n", (dwTime1 - dwTime) / 1000);

	dwTime = GetTickCount();
	map.RemoveAll();
	dwTime1 = GetTickCount();
	TRACE("TinyTreeMap RemoveAll秒数: %d\n", (dwTime1 - dwTime) / 1000);

	std::map<INT, INT> maps;
	dwTime = GetTickCount();
	for (INT i = 0; i < 1000000; i++)
	{
	maps.insert(make_pair(rand(), rand()));
	}
	dwTime1 = GetTickCount();
	TRACE("std::map秒数: %d\n", (dwTime1 - dwTime) / 1000);

	dwTime = GetTickCount();
	maps.erase(maps.begin(), maps.end());
	dwTime1 = GetTickCount();
	TRACE("std::map clear秒数: %d\n", (dwTime1 - dwTime) / 1000);*/
	//map.inOrder();

	/*INT abc[10] = { 11, 2, 13, 14, 25, 36, 17, 98, 49, 10 };
	INT abc1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	INT abc3 = 100;
	TinyTreeMap<INT, INT> map;
	srand(1000);
	for (INT i = 0; i < 1000; i++)
	{
	map.Add(rand(), rand());
	}
	map.inOrder();*/
	//map1.Add(abc[0], abc1[0]);
	//map1.Add(abc[1], abc1[1]);
	//map1.Add(abc[2], abc1[2]);
	//map1.Add(abc[2], abc1[3]);
	//map1.inOrder();
	//map.Add(abc[3], abc1[3]);
	//map.Add(abc[4], abc1[4]);
	//map.Add(abc[5], abc1[5]);
	//map.Add(abc[6], abc1[6]);
	//map.Add(abc[7], abc1[7]);
	//map.Add(abc[8], abc1[8]);
	//map.SetValue(abc[2], abc3);
	HRESULT hRes = OleInitialize(NULL);

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