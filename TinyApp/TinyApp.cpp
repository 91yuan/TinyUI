// TinyApp.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TinyApp.h"
#include "TinyFrameUI.h"
#include "TinyEvent.h"
#pragma comment(lib,"TinyUI.lib")
using namespace TinyUI;

#pragma region old
//template <typename R>
//class FunctionBase0
//{
//public:
//	virtual R Invoke() = 0;
//	virtual ~FunctionBase0() {}
//};
//
//template <typename R, typename T>
//class Function0 : public FunctionBase0<R>
//{
//public:
//	Function0(const T &fun)
//		: m_Fun(fun)
//	{
//	}
//public:
//	R Invoke()
//	{
//		return m_Fun();
//	}
//
//private:
//	T m_Fun;
//};
//
//template <typename R>
//class Function;
//template <typename R>
//class Function<R()>
//{
//public:
//	template<typename T>
//	Function(const T &fun)
//		: m_pFunBase(new Function0<R, T>(fun))
//	{
//
//	}
//
//	~Function()
//	{
//		delete m_pFunBase;
//	}
//
//	R operator ()()
//	{
//		return m_pFunBase->Invoke();
//	}
//
//private:
//	FunctionBase0<R> *m_pFunBase;
//};
//
//template <typename _R, typename _P1>
//struct handler_base
//{
//	virtual _R operator() (_P1) = 0;
//};
//
//template <typename _R, typename _P1, typename _FuncType>
//class handler : public handler_base<_R, _P1>
//{
//public:
//	typedef _FuncType func_type;
//public:
//	handler(const func_type &func) :
//		_func(func)
//	{
//	}
//
//	_R operator() (_P1 p)
//	{
//		return _func(p);
//	}
//
//public:
//	func_type _func;
//};
//
//template <typename _R, typename _P1>
//class functor
//{
//public:
//	typedef handler_base<_R, _P1> handler_type;
//public:
//	template <typename _FuncType>
//	functor(_FuncType func)
//		: _handler(new handler<_R, _P1, _FuncType>(func))
//	{
//	}
//
//	~functor()
//	{
//		delete _handler;
//	}
//	_R operator() (_P1 p)
//	{
//		return (*_handler)(p);
//	}
//
//private:
//	handler_type *_handler;
//};
//
//
//
//template <typename Signature>
//struct FunctionTraits
//{
//	typedef Signature ParamType;
//};
//
//template <typename RetType>
//struct FunctionTraits<RetType()>
//{
//	typedef RetType(&ParamType)();
//};
//
//
//INT Test11(INT a, INT b)
//{
//	MessageBox(NULL, "OK", "OK", MB_OK);
//	return 1;
//}
//
//INT Test12(INT a)
//{
//	MessageBox(NULL, "OK", "OK", MB_OK);
//	return 1;
//}
//
//template <class FuncType>
//int doMath(int x, int y, FuncType func)
//{
//	return func(x, y);
//}

#pragma endregion

class Demo11
{
public:
	INT A;
	Demo11()
	{
		A = 10;
	}
	INT ShowDemo(LPTSTR pz)
	{
		MessageBox(NULL, pz, "��ʾ", MB_OK);
		return 1;
	}
};

INT TestEvent1(INT& a)
{
	MessageBox(NULL, "TestEvent1", "��ʾ", MB_OK);
	return 1;
}
INT TestEvent2(INT& a)
{
	MessageBox(NULL, "TestEvent2", "��ʾ", MB_OK);
	return 2;
}

//class DemoAbs11
//{
//public:
//	DemoAbs11(){};
//
//	virtual DemoAbs11& operator=(const DemoAbs11& db)
//	{
//		A = db.A;
//		return (*this);
//	};
//	INT A;
//};
//class DemoAbs12 : public DemoAbs11
//{
//public:
//	DemoAbs12(){};
//	DemoAbs12(const DemoAbs12& s)
//	{
//		DemoAbs11::operator=(s);
//	}
//};

class Point1
{
public:
	Point1()
		:m_x(0), m_y(0), m_pzName("Default")
	{
		TRACE("����PointĬ�Ϲ��캯��!");
		TRACE(m_pzName);
		TRACE("Address:%d\n", this);
	}
	Point1(int x, int y, LPTSTR pzName)
		:m_x(x), m_y(y), m_pzName(pzName)
	{
		TRACE("����Point�Զ��幹�캯��!");
		TRACE(m_pzName);
		TRACE("-Address:%d\n", this);
	}

	Point1(const Point1& p)
		:m_x(p.m_x), m_y(p.m_y), m_pzName(p.m_pzName)
	{
		TRACE("����Point�������캯��!");
		TRACE(m_pzName);
		TRACE("-Address:%d\n", this);
	}

	Point1& operator=(const Point1& p1)
	{
		TRACE("����Point��ֵ���캯��!");
		m_x = p1.m_x;
		m_y = p1.m_y;
		TRACE(p1.m_pzName);
		TRACE("=�ұ�Address:%d\n", &p1);
		TRACE("����Point��ֵ���캯��!");
		TRACE(m_pzName);
		m_pzName = p1.m_pzName;
		TRACE("=���Address:%d\n", this);
		return (*this);
	}

	~Point1()
	{
		TRACE("����Point��������!");
		TRACE(m_pzName);
		TRACE("-Address:%d\n", this);
	}

	void Push(Point1 pt)
	{

	}

	void Push1(Point1& pt)
	{

	}


	Point1 GetPoint2(Point1& p1)
	{
		Point1 pt(p1);
		return pt;
		//Point1 pt(m_x, m_y, "��ʱP1");
		//return pt;
	}

	Point1 GetPoint()
	{
		Point1 pt(m_x, m_y, "��ʱP1");
		return pt;
	}
	Point1 GetPoint1()
	{
		return Point1(m_x, m_y, "��ʱP2");
	}
private:
	int m_x;
	int m_y;
	LPTSTR m_pzName;
};

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*DelegateBase<INT, TYPE_LIST1(INT)> _base(&Test12);
	_base(10);*/
	/*DemoAbs12 a11;
	a11.A = 10;
	DemoAbs12 a12(a11);*/


#pragma region oldcode
	//DelegateImplBase<INT, INT(*)(INT, INT), INT, INT> del1;
	//TRACE(typeid(FunctionTraits<INT(INT)>::ParamType).name());
	//int a = IsFunctionPointer<FunctionTraits<INT(*)(INT)>::ParamType>::result;
	//Function111<INT(INT)> _vals(&Test11);
	//functor<int, int> cmd1(&Test11);
	//cmd1(1);
	/*Function0<INT, INT(*)()> func(&Test11);
	func.Invoke();*/
	//AreaINT int1;
	//INT a = 10;
	//int1.Attach(a);
	/*map<INT, CHAR> maps;
	maps.insert(pair<INT, CHAR>(10, 'A'));
	maps.insert(pair<INT, CHAR>(11, 'B'));
	maps.insert(pair<INT, CHAR>(12, 'C'));
	maps.insert(pair<INT, CHAR>(13, 'D'));
	maps.insert(pair<INT, CHAR>(14, 'E'));
	INT size1 = maps.size();
	map<INT, CHAR>::iterator pos = maps.find(10);
	maps.erase(pos);
	size1 = maps.size();*/
	/*TinyArray<INT> arrays;
	for (INT i = 0; i < 10000; i++)
	{
	arrays.Add(i);
	}
	for (INT i = 0; i < 10000; i++)
	{
	TRACE("%d\n", arrays[i]);
	}*/
	/*TinyMap<INT,INT> arrays;
	for (INT i = 0; i < 100000; i++)
	{
	arrays.Add(i,i);
	}
	for (INT i = 0; i < 100000; i++)
	{
	TRACE("Value%d\n", arrays.Lookup(i));
	}*/
	/*const int count = 5;
	int* pss3 = (int*)&count;
	*pss3 = 6;
	int var = count;
	TRACE("%d",var);*/
	//qptrdiff offset;
	//Test1 test1(10);
	//Test2 test2(20);
	//Test3 test3(test1, test2);
	//INT a1 = sizeof(Test3);
	//CHAR* ps = new CHAR[100];
	//Demo demo('A');
	//TinyPlaceNew<Demo>* ps1 = new(ps)TinyPlaceNew<Demo>(demo);
	//TinyPlaceNew<Demo>* ps2 = (TinyPlaceNew<Demo>*)ps;
	//Demo* ps3 = (Demo*)ps;
	//INT a = sizeof(Demo);
	//INT b = sizeof(TinyPlaceNew<Demo>);
	/*Function<INT()> abc(&Test1);
	abc();*/
	/*Demo* ps1 = new(ps) Demo('A');
	CHAR a = ps[0];
	a = ps1->m_value;
	delete[] ps;*/
	//Delegate<INT()> delegate1;
	//delegate1.BindDelegate(&test1);
	//delegate1();
#pragma endregion

	//Point1 pt1(10, 10, "׷��P1");
	////Point1 pt2 = pt.GetPoint();
	//Point1 pt2(20, 20, "׷��P2");
	//TRACE("------------\n");
	//pt2 = pt1.GetPoint1();

	/*Point1 pt1(10, 10, "׷��P1");
	TRACE("------------1\n");
	pt1.GetPoint();
	TRACE("------------2\n");
	Point1 pt2 = pt1.GetPoint();*/

	//INT a = 10;
	//Delegate<INT(INT&)> del1(&TestEvent1);
	//Delegate<INT(INT&)> del2(&TestEvent2);
	//Event<INT(INT&)> evl1;
	////evl1 += &del1;
	//evl1 += &del2;
	//INT b = evl1(a);
	//evl1 -= &del2;
	//evl1 -= &del1;

	HRESULT hRes = OleInitialize(NULL);

	::DefWindowProc(NULL, 0, 0, 0L);

	TinyApplication::Instance()->Initialize(hInstance, lpCmdLine, nCmdShow, MAKEINTRESOURCE(IDC_TINYAPP));

	TinyMessageLoop theLoop;
	TinyApplication::Instance()->AddMessageLoop(&theLoop);
	TinyFrameUI uiImpl;
	uiImpl.Create(NULL, 10, 10, 500, 400);
	uiImpl.ShowWindow(nCmdShow);
	uiImpl.UpdateWindow();

	INT loopRes = theLoop.MessageLoop();

	TinyApplication::Instance()->RemoveMessageLoop();
	TinyApplication::Instance()->Uninitialize();

	OleUninitialize();

	return loopRes;
};