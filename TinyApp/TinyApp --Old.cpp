// TinyApp.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TinyApp.h"
#include "Control/TinyFrameUI.h"
#include "Windowless/TinyVisualHWND.h"
#include "Database/TinyAdo.h"
#include <algorithm>
#include "TinySmiley.h"
#include "Common/TinyCallback.h"

#pragma comment(lib,"TinyUI.lib")
using namespace TinyUI;

//class Test1
//{
//
//public:
//	Test1(LPCSTR pz)
//		:m_pz(pz)
//	{
//		TRACE("调用Test1构造函数地址:%d\n", this);
//	}
//
//	Test1(const Test1& test1)
//	{
//		m_pz = test1.m_pz;
//		TRACE("调用Test1拷贝构造函数地址:%d\n", this);
//	}
//	~Test1()
//	{
//		TRACE("调用Test1析构函数地址:%d\n", this);
//	}
//private:
//	LPCSTR m_pz;
//};
//Test1 Create()
//{
//	/*Test1 test("123");
//	return test;*/
//	return Test1("123");
//}
//void toUpper(const Test1& str)
//{
//
//};
//
//class OnlyHeapClass
//{
//public:
//	OnlyHeapClass()
//	{
//	}
//
//	void Destroy()
//	{
//		delete this;
//	}
//
//protected:
//	~OnlyHeapClass()
//	{
//	}
//};
//
//char buffer[] = "hazirguo";

//class Resource;   // 代表需要被封装的资源类   
//class NoHashObject
//{
//private:
//	Resource *ptr; // 指向被封装的资源   
//	// ...  //其它数据成员 
//
//	void*   operator   new(size_t   size) //非严格实现, 仅作示意之用   
//	{
//		return malloc(size);
//	}
//
//		void operator delete(void* pp) //非严格实现, 仅作示意之用   
//	{
//		free(pp);
//	}
//
//public:
//	NoHashObject()
//	{
//		// 此处可以获得需要封装的资源, 并让ptr指针指向该资源   
//		ptr = new Resource();
//	}
//
//	~NoHashObject()
//	{
//		delete ptr;   // 释放封装的资源   
//	}
//};

//void InsertSort(INT ps[], INT size)
//{
//	for (INT i = 1; i < size; i++)
//	{
//		INT temp = ps[i];
//		INT j = i;
//		while (j >= 1 && temp < ps[j - 1])
//		{
//			ps[j] = ps[j - 1];
//			j--;
//		}
//		ps[j] = temp;
//	}
//}
//
//void BubbleSort(INT ps[], INT size)
//{
//	for (INT i = 0; i < size; i++)
//	{
//		for (INT j = i; j < size; j++)
//		{
//			if (ps[i] > ps[j])
//			{
//				INT temp = ps[i];
//				ps[i] = ps[j];
//				ps[j] = temp;
//			}
//		}
//	}
//}
//
//INT Search2(INT ps[], INT size, INT key)
//{
//	INT min = 0;
//	INT max = size;
//	while (min <= max)
//	{
//		INT mid = (max + min) / 2;
//		INT value = ps[mid];
//		if (value == key)
//		{
//			return mid;
//		}
//		if (value > key)
//		{
//			max = mid - 1;
//		}
//		if (value < key)
//		{
//			min = mid + 1;
//		}
//	}
//	return -1;
//}

//class Base
//{
//public:
//	Base()
//	{
//		TRACE("Base()\n");
//	};
//private:
//	Base(const Base&)
//	{
//		TRACE("Base(const Base&)\n");
//	};
//};

//class A : public Base
//{
//public:
//	A()
//	{
//		TRACE("A()\n");
//	};
//	A(const A&)
//	{
//		TRACE("A(const A&)\n");
//	};
//};
//#include "boost/utility.hpp"
//using namespace boost;

//class A : public boost::noncopyable
//{
//public:
//	INT COUNT;
//public:
//	A() :COUNT(1)
//	{
//		TRACE("调用A构造函数\n", COUNT);
//	};
//	~A()
//	{
//		TRACE("调用A析构函数\n", COUNT);
//	}
//};

class TestA
{
public:
	TestA(int a)
		:m_a(a)
	{
		TRACE("TestA构造函数\n");
	}

	void AddRef() const
	{

	}
	void Release() const
	{

	}

public:
	static TestA createTestA(int a)
	{
		TRACE("createTestA\n");
		return TestA(a);
	}

	TestA(const TestA& a)
	{
		TRACE("TestA拷贝构造函数\n");
	}
	TestA& operator=(const TestA& a)
	{
		TRACE("TestA赋值构造函数\n");
		return *this;
	}
public:
	int m_a;
};

class TestB
{
public:
	TestB()
		:testA(TestA::createTestA(1))
	{

	}
private:
	TestA testA;
};

class TestC
{
public:
	TestC(TestA* test1)
		:m_test1(test1)
	{

	}

	TestC()
	{

	}

	void ShowA()
	{

	}

	int ShowC(int& a, int& b)
	{
		TRACE("ShowC\n");
		return a + b;
	}

	TinyScopedReferencePtr<TestA> m_test1;
};

TestA TestFun2()
{
	TRACE("TestFun2\n");
	TestA x(3);
	return x;
}

TestA TestFun3()
{
	TRACE("TestFun3\n");
	return TestA(3);
}

int ABCFunction(int a, int b)
{
	MessageBox(NULL, "", "", MB_OK);
	return a + b;
}
void RunAB()
{
	TRACE("RunAB\n");
}
void RunA(int a)
{

}
template <typename Functor>
void BindFunctor(Functor functor)
{
	TRACE(typeid(Functor).name());
}

//template <class T, class T1>
//class TestClass
//{
//public:
//	TestClass()
//	{
//		TRACE("T, T1\n");
//	}
//};
//
//// 针对普通指针的偏特化设计
//template <class T, class T1>
//class TestClass < T*, T1* >
//{
//public:
//	TestClass()
//	{
//		TRACE("T*, T1*\n");
//	}
//};
//
//// 针对const指针的偏特化设计
//template <class T, class T1>
//class TestClass < const T*, T1* >
//{
//public:
//	TestClass()
//	{
//		TRACE("const T*, T1*\n");
//	}
//};

template<typename F>
class ClassA
{
public:
	template<typename V, typename SS, typename VV>
	ClassA(const V& v)
	{
		TRACE("F:%s\b", typeid(F).name());
		TRACE("V:%s\b", typeid(V).name());
	}

	template<typename S>
	void Show(S s)
	{
		TRACE("F:%s\b", typeid(S).name());
	}
};


INT APIENTRY _tWinMain(HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	INT       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*shared_ptr<A> ptr1(new A());
	TRACE("ptr1 COUNT:%d\n",ptr1.use_count());
	shared_ptr<A> ptr2 = ptr1;
	TRACE("ptr1 COUNT:%d\n", ptr1.use_count());
	TRACE("ptr2 COUNT:%d\n", ptr2.use_count());
	ptr1.reset();
	TRACE("ptr1 reset\n");
	TRACE("ptr1 COUNT:%d\n", ptr1.use_count());
	TRACE("ptr2 COUNT:%d\n", ptr2.use_count());
	ptr2.reset();
	TRACE("ptr2 reset\n");
	TRACE("ptr1 COUNT:%d\n", ptr1.use_count());
	TRACE("ptr2 COUNT:%d\n", ptr2.use_count());*/
	//A a;
	//A b = a;
	/*vector<int> bc;
	bc.push_back(10);
	bc.push_back(5);
	bc.push_back(4);
	bc.push_back(1);
	bc.push_back(7);
	bc.push_back(19);
	vector<int>::iterator val = remove(bc.begin(), bc.end(), 5);
	bc.erase(val);
	bc.erase(find(bc.begin(), bc.end(), 4));*/
	//INT ps[9] = { 1, 5, 9, 11, 15, 18, 24, 29, 35 };
	//INT val = Search2(ps, 9, 245);
	//OnlyHeapClass *pInst = new OnlyHeapClass();
	//pInst->Destroy();
	//Test1 test2 = Create();
	/*char s1[] = { '1', '2', '3' };
	int a = sizeof(s1);*/
	//Test1 test("123");
	//toUpper("123");
	//TestC testC;
	//RunnableAdapter<int(TestC::*)(int&, int&)> adapter(&TestC::ShowC);
	//TRACE(typeid(RunnableAdapter<int(TestC::*)(int&, int&)>::RunType).name());
	//TestC testC;
	//Callback<int(int, int)> abc = Make(&TestC::ShowC);
	//int val = abc.DoInvoke(10, 10);
	//TRACE("%s\n", typeid(FunctionTraits<RunnableAdapter<void(TestC::*)(int&, int&)>::RunType>).name());
	//Callback<void(int)> abc = Bind(&RunA, 10);

	/*TestA testA(1);
	TestC testC(&testA);*/

	/*Test1 test2 = Create();
	TRACE("地址:%d\n", &test2);*/
	//const int abc = 5;
	//int *p = const_cast<int*>(&abc);
	//*p = 6;
	//int abcd = abc;
	//int a = sizeof(MyStruct);

	/*typedef void(*InvokeFuncStorage)(void);
	InvokeFuncStorage a = reinterpret_cast<InvokeFuncStorage>(ABCFunction);
	a();*/
	//TestB testB;
	//TestFun2();
	//TestFun3();
	//TestB testB;
	//TestA a;
	//TestA b = a;
	//TestA c;
	//c = a;

	//RunnableAdapter<int(TestC::*)(int&, int&)> abc(&TestC::ShowC);
	//vector<const TestA*> arrays;
	//arrays.push_back(&a);
	//arrays.push_back(&b);
	//arrays.push_back(&c);

	//Callback<void(int)> callback = 
	/*Callback<int(int, int)> abc = Callback<int(int, int)>::MakeCallback(&ABCFunction);
	abc.DoInvoke(10, 10);*/
	/*vector<string> strs;
	SplitString("O1=O2,O2=O1,T1=T1", ',', &strs);*/

	//ClassA<void> cb(&TestC::ShowC);
	//ClassA<void> cb(&TestC::ShowC);
	//cb.Show(10);

	//TestClass<int, char> obj;
	//TestClass<int *, char *> obj1;
	//TestClass<const int *, char *> obj2;
	//callback<void(int)> cb(&TestC::ShowC);

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

	return loopRes;
};