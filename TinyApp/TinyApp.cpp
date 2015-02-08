// TinyApp.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TinyApp.h"
#include "Control/TinyFrameUI.h"

#pragma comment(lib,"TinyUI.lib")
using namespace TinyUI;
#include <vector>
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
//INT doMath(INT x, INT y, FuncType func)
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
		MessageBox(NULL, pz, "显示", MB_OK);
		return 1;
	}
};

INT TestEvent1(INT& a)
{
	MessageBox(NULL, "TestEvent1", "显示", MB_OK);
	return 1;
}
INT TestEvent2(INT& a)
{
	MessageBox(NULL, "TestEvent2", "显示", MB_OK);
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
		TRACE("调用Point默认构造函数!");
		TRACE(m_pzName);
		TRACE("Address:%d\n", this);
	}
	Point1(INT x, INT y, LPTSTR pzName)
		:m_x(x), m_y(y), m_pzName(pzName)
	{
		TRACE("调用Point自定义构造函数!");
		TRACE(m_pzName);
		TRACE("-Address:%d\n", this);
	}

	Point1(const Point1& p)
		:m_x(p.m_x), m_y(p.m_y), m_pzName(p.m_pzName)
	{
		TRACE("调用Point拷贝构造函数!");
		TRACE(m_pzName);
		TRACE("-Address:%d\n", this);
	}

	Point1& operator=(const Point1& p1)
	{
		TRACE("调用Point赋值构造函数!");
		m_x = p1.m_x;
		m_y = p1.m_y;
		TRACE(p1.m_pzName);
		TRACE("=右边Address:%d\n", &p1);
		TRACE("调用Point赋值构造函数!");
		TRACE(m_pzName);
		m_pzName = p1.m_pzName;
		TRACE("=左边Address:%d\n", this);
		return (*this);
	}

	~Point1()
	{
		TRACE("调用Point析构函数!");
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
		//Point1 pt(m_x, m_y, "临时P1");
		//return pt;
	}

	Point1 GetPoint()
	{
		Point1 pt(m_x, m_y, "临时P1");
		return pt;
	}
	Point1 GetPoint1()
	{
		return Point1(m_x, m_y, "临时P2");
	}
private:
	INT m_x;
	INT m_y;
	LPTSTR m_pzName;
};

class Base1
{
public:
	Base1()
	{
		TRACE("调用Base1构造函数\n");
	}
	virtual ~Base1()
	{
		TRACE("调用Base1析构函数\n");
		Print();
	}

	virtual void Print()
	{
		TRACE("调用Base1-Print\n");
	}

	void CallPrintABC()
	{
		PrintABC();
	}

	virtual void PrintABC()
	{
		TRACE("调用Base1-PrintABC\n");
	}

};
class Base2 : public Base1
{
public:
	Base2()
	{
		TRACE("调用Base2构造函数\n");
	}
	virtual ~Base2()
	{
		TRACE("调用Base2析构函数\n");
	}
	virtual void Print()
	{
		TRACE("调用Base2-Print\n");
	}

	virtual void PrintABC()
	{
		TRACE("调用Base2-PrintABC\n");
	}
};



INT APIENTRY _tWinMain(HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	INT       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#pragma region old
	/*DelegateBase<INT, TYPE_LIST1(INT)> _base(&Test12);
	_base(10);*/
	/*DemoAbs12 a11;
	a11.A = 10;
	DemoAbs12 a12(a11);*/

	//baseclass2::print();
#pragma region oldcode
	//DelegateImplBase<INT, INT(*)(INT, INT), INT, INT> del1;
	//TRACE(typeid(FunctionTraits<INT(INT)>::ParamType).name());
	//INT a = IsFunctionPointer<FunctionTraits<INT(*)(INT)>::ParamType>::result;
	//Function111<INT(INT)> _vals(&Test11);
	//functor<INT, INT> cmd1(&Test11);
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
	/*TinyArray1<INT> arrays;
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
	/*const INT count = 5;
	INT* pss3 = (INT*)&count;
	*pss3 = 6;
	INT var = count;
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

	//Point1 pt1(10, 10, "追踪P1");
	////Point1 pt2 = pt.GetPoint();
	//Point1 pt2(20, 20, "追踪P2");
	//TRACE("------------\n");
	//pt2 = pt1.GetPoint1();

	/*Point1 pt1(10, 10, "追踪P1");
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
	/*std::string base = "The quick brown fox jumps over a lazy dog.";*/
	/*std::string base = "The quick brown fox jumps over a lazy dog.";
	std::string base1 = "ansdaskdas.";
	base.append(base, 17, 6);*/
	//base.assign("The quick brown fox jumps 1123123123123123123123123123123123123");
	//std::string str = "The quick brown fox jumps 1123123123123123123123123123123123123";
	//base.assign(base, 20, 10);
	//base.assign(str, 17, 20);
	//base.append("abcdefghijk", 6);
	//base.insert(10, "that is cool", 8);
	//base.append("pangrams");
	//base.assign("pangrams are cool", 7);
	//std::string base = "The quick brown fox jumps over a lazy dog.";
	//base.assign("123");

	/*std::string base = "The quick";
	std::string base1 = "1234567890-1234567890-1234567890";
	base.insert(1, base1, 1, 18);*/
	//TinyString str;
	//str.Assign("The quick");
	//str.Assign("The quick brown fox jumps over a lazy dog.");
	//TinyString str1("The quick brown fox jumps over a lazy dog.");
	//str1.Insert(1, "12345", 4);
	//str1.Insert(1, "1234567890-1234567890-1234567890", 18);
	//str.Append(str1, 10, 10);
	//TinyString str1(str);
	/*TinyString base("The quick");
	TinyString base1("1234567890-1234567890-1234567890");
	base.Insert(1, base1, 1, 18);*/
	//std::string base1 = "1234567890-1234567890-1234567890";
	//INT s = base1.find("The");
	//std::string base1 = "1234567890-1234567890-1234567890";
	//base1.compare("123");
	//TinyString base("The quick brown fox jumps over a lazy dog.");
	//INT s = base.Find("jumps");
	//BOOL b = base.Compare(5, 10, "The quick brown fox jumps over a lazy dog.", 3);
	//std::string base2 = "";
	//std::string base1 = "1234567890-1234567890-1234567890";
	//base2 += base1;
	//std::string str1("The quick brown fox jumps over a lazy dog.");
	//std::string base = "this is a test string.";
	//base.replace(8, 6, str1, 0, 30);
	/*TinyString str1("The quick brown fox jumps over a lazy dog.");
	TinyString base = "this is a test string.";

	base.Replace(8, 6, str1, 0, 30);*/
	/*std::vector<INT> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.insert(v.begin() + 6, 7);*/
	/*class Obj
	{
	public:
	Obj()
	:m_index(0)
	{
	TRACE("Obj默认构造函数:%d\n", m_index);
	}
	Obj(INT index)
	:m_index(index)
	{
	TRACE("Obj构造函数:%d\n", m_index);
	}
	Obj(const Obj& obj)
	{
	this->m_index = obj.m_index;
	TRACE("Obj拷贝构造函数:%d\n", m_index);
	}
	Obj& operator = (const Obj& obj)
	{
	m_index = obj.m_index;
	TRACE("Obj赋值构造函数:%d\n", m_index);
	return (*this);
	}
	~Obj()
	{
	TRACE("Obj析构函数:%d\n", m_index);
	}
	INT m_index;
	};

	class Object1
	{
	public:
	Object1(Obj& obj)
	:_obj(obj)
	{

	}
	private:
	Obj& _obj;
	};
	*/
	/*Obj obj0(0);
	Obj obj1(1);
	Obj obj2(2);
	Obj obj3(3);
	Obj obj4(4);*/
	//char memory[sizeof(Obj)];     // Line #1
	//void* place = memory;          // Line #2
	//Obj* f = new(place)Obj;
	//TinyArray1<Obj> _array;
	//_array.Insert(0, Obj(0));
	//TRACE("1:%d\n", &obj0);
	//TRACE("2:%d\n", &_array[0]);
	//_array.Add(obj1);
	//_array.Add(obj2);
	//_array.Add(obj3);
	//_array.Add(obj4);
	/*_array.Insert(0, 1);
	_array.Insert(0, 2);
	_array.Insert(0, 3);
	_array.Insert(0, 4);
	_array.Insert(0, 5);*/
	/*for (INT i = 0; i < _array.GetSize(); i++)
	{
	TRACE("Value:%d\n", _array[i]);
	}*/
	//std::string base = "this is a test string.";
	//TinyString str = TinyString::Format("Msg:%d", 10);
	//TinyString base1 = "this is a test string.";
	//base1.Replace(8, 6, "The quick brown fox jumps over a lazy dog.", 30);
	//base.substr(2, 10);
	/*vector<INT> _array;
	_array.push_back(10);
	_array.push_back(11);*/
	/*Obj obj1(10);
	Object1 obj(obj1);*/
	/*Obj obj1(10);
	Obj obj2(20);
	TRACE("%d\n", &obj1);
	TinyArray1<Obj> _array;
	_array.Add(obj1);
	_array.Add(obj2);
	TRACE("%d\n", &_array[0]);*/
#pragma endregion

	Base2* base2 = new Base2();
	base2->CallPrintABC();
	delete base2;

	HRESULT hRes = OleInitialize(NULL);

	::DefWindowProc(NULL, 0, 0, 0L);

	TinyApplication::Instance()->Initialize(hInstance, lpCmdLine, nCmdShow, MAKEINTRESOURCE(IDC_TINYAPP));

	TinyMessageLoop theLoop;
	TinyApplication::Instance()->AddMessageLoop(&theLoop);
	TinyFrameUI uiImpl;
	uiImpl.Create(NULL, 10, 10, 300, 400);
	uiImpl.ShowWindow(nCmdShow);
	uiImpl.UpdateWindow();

	INT loopRes = theLoop.MessageLoop();

	TinyApplication::Instance()->RemoveMessageLoop();
	TinyApplication::Instance()->Uninitialize();

	OleUninitialize();

	return loopRes;
};