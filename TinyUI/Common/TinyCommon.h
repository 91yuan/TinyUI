#pragma once
#include <Windows.h>
#include <Shellapi.h>
#include <Commdlg.h>
#include <comdef.h>
#include <Mmsystem.h>
#include <new.h>
#include <WinGDI.h>
#include <GdiPlus.h>
#include <Shlwapi.h> 
#include <commctrl.inl>
#include <Psapi.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <crtdbg.h>
#include <utility>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Comctl32.lib")

using namespace Gdiplus;
using namespace std;

namespace TinyUI
{
	//////////////////////////////////////////////////////////////////////////

#define OVERRIDE override
#define NO_VTABLE _declspec(novtable)
#ifndef ASSERT
#define ASSERT(expr) _ASSERTE(expr)
#endif 
	void Trace(LPCTSTR lpszFormat, ...);
#ifndef TRACE
#define TRACE Trace
#endif
#ifndef ASSUME
#define ASSUME(expr) do { ASSERT(expr); __analysis_assume(!!(expr)); } while(0)
#endif // ASSUME
	template<bool>
	struct CompileAssert {};
#undef COMPILE_ASSERT
#define COMPILE_ASSERT(expr, msg) \
    typedef CompileAssert<(bool(expr))> msg[bool(expr)?1:-1]

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)  { if (p) { delete (p);  (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_OBJECT
#define SAFE_DELETE_OBJECT(p) { if (p) { DeleteObject(p); (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)  { if (p) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p)  { if (p) { free(p); (p)=NULL; } }
#endif
#ifndef SAFE_LOCAL_DELETE
#define SAFE_LOCAL_DELETE(p)  { if (p) { LocalFree(p); (p)=NULL; } }
#endif 
#ifndef TINY_EXPORT
#define TINY_EXPORT __declspec(dllexport)
#endif // TINY_EXPORT

#ifndef TINY_IMPORT
#define TINY_IMPORT __declspec(dllimport)
#endif // TINY_IMPORT

#ifndef TINY_NO_VTABLE
#define TINY_NO_VTABLE __declspec(novtable)
#endif

#ifndef WM_REFLECT
#define WM_REFLECT (WM_USER + 0x1C00)
#endif

#ifndef WM_COMMANDREFLECT
#define WM_COMMANDREFLECT (WM_COMMAND+WM_REFLECT)
#endif

#ifndef WM_NOTIFYREFLECT
#define WM_NOTIFYREFLECT (WM_NOTIFY+WM_REFLECT)
#endif

#ifndef WM_DRAWITEMREFLECT
#define WM_DRAWITEMREFLECT (WM_DRAWITEM + WM_REFLECT)
#endif

#ifndef WM_MEASUREITEMREFLECT
#define WM_MEASUREITEMREFLECT (WM_MEASUREITEM + WM_REFLECT)
#endif

#ifndef WM_DELETEITEMREFLECT
#define WM_DELETEITEMREFLECT (WM_DELETEITEM + WM_REFLECT)
#endif

#define WM_NCMOUSEFIRST WM_NCMOUSEMOVE
#define WM_NCMOUSELAST  WM_NCMBUTTONDBLCLK

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((INT)(short)LOWORD(lParam))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((INT)(short)HIWORD(lParam))
#endif

#ifndef TO_CX
#define TO_CX(rect)    abs(rect.right-rect.left)
#endif

#ifndef TO_CY
#define TO_CY(rect)    abs(rect.bottom-rect.top)
#endif

#define IS_VALID_STRING_PTR(ptr, type) \
	(!IsBadStringPtr((ptr), (UINT)-1))

#define DISALLOW_COPY(TypeName) \
private:\
	TypeName(const TypeName&);

#define DISALLOW_ASSIGN(TypeName) \
private:\
	void operator=(const TypeName&);

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private:\
	TypeName(const TypeName&);               \
	void operator=(const TypeName&);

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
private:\
	TypeName();                                    \
	DISALLOW_COPY_AND_ASSIGN(TypeName)

	template<typename T, size_t N>
	char(&ArraySizeHelper(T(&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define ARRAYSIZE_UNSAFE(a) \
	((sizeof(a) / sizeof(*(a))) / \
	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 占位符空类型
	/// </summary>
	class NullType {};
	template<typename T>
	struct IsVoidType
	{
		enum{ Result = 0 };
	};
	template<>
	struct IsVoidType < void >
	{
		enum{ Result = 1 };
	};
	template<typename T>
	struct IsBoolType
	{
		enum{ Result = 0 };
	};
	template<>
	struct IsBoolType < bool >
	{
		enum{ Result = 1 };
	};
	template <typename T>
	struct IsReference
	{
		enum{ Result = 0 };
	};
	template <typename T>
	struct IsReference < T& >
	{
		enum{ Result = 1 };
	};
	template <typename T>
	struct IsPointer
	{
		enum { Result = 0 };
	};
	template <class T>
	struct IsPointer < T* >
	{
		enum { Result = 1 };
	};
	template <class T>
	struct IsPointer < T*& >
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsFunctionPointer
	{
		enum{ Result = 0 };
	};
	template <typename T>
	struct IsFunctionPointer < T(*)() >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01>
	struct IsFunctionPointer < T(*)(P01) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02>
	struct IsFunctionPointer < T(*)(P01, P02) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03>
	struct IsFunctionPointer < T(*)(P01, P02, P03) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03, typename P04>
	struct IsFunctionPointer < T(*)(P01, P02, P03, P04) >
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsFunctionPointer < T(*)(...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01>
	struct IsFunctionPointer < T(*)(P01, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02>
	struct IsFunctionPointer < T(*)(P01, P02, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03>
	struct IsFunctionPointer < T(*)(P01, P02, P03, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03, typename P04>
	struct IsFunctionPointer < T(*)(P01, P02, P03, P04, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsMemberFunctionPointer
	{
		enum{ Result = 0 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)() >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)(...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)() const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)(...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01, ...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, ...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, ...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04, ...) const >
	{
		enum { Result = 1 };
	};
	template<typename T>
	struct IsArrayType
	{
		enum { Result = 0 };
	};
	template<typename T>
	struct IsArrayType < T[] >
	{
		enum { Result = 1 };
	};
	template<typename T, size_t n>
	struct IsArrayType < T[n] >
	{
		enum { Result = 1 };
	};
	template <typename T, typename U>
	struct IsSameType
	{
		enum { Result = 0 };
	};
	template <typename T>
	struct IsSameType < T, T >
	{
		enum { Result = 1 };
	};
	/// <summary>
	/// 类型列表
	/// </summary>
	template<class T1, class T2>
	class TypeList
	{
		typedef T1 T1Type;
		typedef T2 T2Type;
	};
	//////////////////////////////////////////////////////////////////////////
#define TYPE_LIST0() NullType
#define TYPE_LIST1(P1) TypeList<P1, NullType>
#define TYPE_LIST2(P1, P2) TypeList<P1, TYPE_LIST1(P2)>
#define TYPE_LIST3(P1, P2, P3) TypeList<P1, TYPE_LIST2(P2, P3)>
#define TYPE_LIST4(P1, P2, P3, P4) TypeList<P1, TYPE_LIST3(P2, P3, P4)>
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 线程安全的引用计数基类类
	/// </summary>
	class TinyReferenceBase
	{
		DISALLOW_COPY_AND_ASSIGN(TinyReferenceBase);
	public:
		/// <summary>
		/// 获得当前的引用计数
		/// </summary>
		LONG GetReference() const;
		/// <summary>
		/// 引用+1
		/// </summary>
		void AddRef() const;
		/// <summary>
		/// 释放
		/// </summary>
		BOOL Release() const;
	protected:
		TinyReferenceBase();
		virtual ~TinyReferenceBase();
		mutable LONG	m_cRef;
	};
	template<class T>
	class DefaultTinyReferenceTraits
	{
	public:
		static void Destruct(const T* x)
		{
			TinyReference<T, DefaultTinyReferenceTraits>::Delete(x);
		}
	};
	/// <summary>
	/// 线程安全的引用计数类,可以显示提供引用析构的机会
	/// </summary>
	template<typename T, typename Traits = DefaultTinyReferenceTraits<T>>
	class TinyReference : public TinyReferenceBase
	{
		friend class DefaultTinyReferenceTraits < T > ;
		DISALLOW_COPY_AND_ASSIGN(TinyReference);
	public:
		TinyReference();
		void AddRef() const;
		void Release() const;
	protected:
		~TinyReference();
	private:
		static void Delete(const T* x);
	};
	template<class T, typename Traits>
	TinyReference<T, Traits>::TinyReference()
	{

	}
	template<class T, typename Traits>
	TinyReference<T, Traits>::~TinyReference()
	{

	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::AddRef() const
	{
		TinyReferenceBase::AddRef();
	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::Release() const
	{
		if (TinyReferenceBase::Release())
		{
			Traits::Destruct(static_cast<const T*>(this));
		}
	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::Delete(const T* x)
	{
		SAFE_DELETE(x);
	}
	/// <summary>
	/// 智能指针
	/// </summary>
	template<class T>
	class TinyAutoPtr
	{
	public:
		T* _myP;
		explicit TinyAutoPtr(T* _rP = NULL);
		explicit TinyAutoPtr(TinyAutoPtr<T>& _rP);
		~TinyAutoPtr();
		TinyAutoPtr<T>& operator = (TinyAutoPtr<T>& _rP);
		T*	Release() throw();
		void Reset(T* _ptr) throw();
		T*	Ptr() const throw();
		operator T*() const throw();
		T&	operator*() const throw();
		T*	operator->() const throw();
	};
	template<class T>
	TinyAutoPtr<T>::TinyAutoPtr(T* lp)
		: _myP(lp)
	{

	}
	template<class T>
	TinyAutoPtr<T>::TinyAutoPtr(TinyAutoPtr<T>& _rP)
		: _myP(_rP.Release())
	{

	}
	template<class T>
	TinyAutoPtr<T>& TinyAutoPtr<T>::operator = (TinyAutoPtr<T>& _rP)
	{
		//释放当前的指针
		Reset(_rP.Release());
		return (*this);
	}
	template<class T>
	T*	TinyAutoPtr<T>::Release() throw()
	{
		T* ps = _myP;
		_myP = NULL;
		return ps;
	}
	template<class T>
	void TinyAutoPtr<T>::Reset(T* _ptr) throw()
	{
		if (_ptr != _myP)
			delete _myP;
		_myP = _ptr;
	}
	template<class T>
	T*	TinyAutoPtr<T>::Ptr() const throw()
	{
		return (_myP);
	}
	template<class T>
	TinyAutoPtr<T>::~TinyAutoPtr()
	{
		if (_myP != NULL)
		{
			delete _myP;
			_myP = NULL;
		}
	}
	template<class T>
	T& TinyAutoPtr<T>::operator*() const throw()
	{
		return *_myP;
	}
	template<class T>
	T*	TinyAutoPtr<T>::operator->() const throw()
	{
		return _myP;
	}
	template<class T>
	TinyAutoPtr<T>::operator T*() const throw()
	{
		return _myP;
	}
	/// <summary>
	/// 智能指针但不能转让所有权
	/// </summary>
	template <class T>
	class TinyScopedPtr
	{
	public:
		explicit TinyScopedPtr(T* ps = 0);
		~TinyScopedPtr();
		void Reset(T* ps = 0) throw();
		operator T*() const throw();
		T& operator*() const throw();
		T* operator->() const throw();
		T* Ptr() const throw();
	public:
		T* _myP;
	};
	template<class T>
	TinyScopedPtr<T>::TinyScopedPtr(T* ps)
		: _myP(ps)
	{

	}
	template<class T>
	TinyScopedPtr<T>::~TinyScopedPtr()
	{
		if (_myP != NULL)
		{
			delete _myP;
			_myP = NULL;
		}
	}
	template<class T>
	void TinyScopedPtr<T>::Reset(T* ps) throw()
	{
		if (ps != _myP)
			delete _myP;
		_myP = ps;
	}
	template<class T>
	T& TinyScopedPtr<T>::operator*() const throw()
	{
		return (*_myP);
	}
	template<class T>
	T* TinyScopedPtr<T>::operator->() const throw()
	{
		return _myP;
	}
	template<class T>
	T* TinyScopedPtr<T>::Ptr() const throw()
	{
		return _myP;
	}
	template<class T>
	TinyScopedPtr<T>::operator T*() const throw()
	{
		return _myP;
	}
	/// <summary>
	/// Scope数组
	/// </summary>
	template <class T>
	class TinyScopedArray
	{
	public:
		explicit TinyScopedArray(T* ps = 0);
		~TinyScopedArray();
		void Reset(T* ps = 0) throw();
		T& operator[](INT i) const;
		BOOL operator==(T* ps) const;
		BOOL operator!=(T* ps) const;
		T* Ptr() const throw();
	public:
		T* _myP;
	};
	template<class T>
	TinyScopedArray<T>::TinyScopedArray(T* ps)
		: _myP(ps)
	{

	}
	template<class T>
	TinyScopedArray<T>::~TinyScopedArray()
	{
		SAFE_DELETE_ARRAY(_myP);
	}
	template<class T>
	T& TinyScopedArray<T>::operator[](INT i) const
	{
		ASSERT(i >= 0);
		ASSERT(_myP != NULL);
		return _myP[i];
	}
	template<class T>
	BOOL TinyScopedArray<T>::operator==(T* ps) const
	{
		return _myP == ps;
	}
	template<class T>
	BOOL TinyScopedArray<T>::operator!=(T* ps) const
	{
		return _myP != ps;
	}
	template<class T>
	void TinyScopedArray<T>::Reset(T* ps) throw()
	{
		if (ps != _myP)
			delete[] _myP;
		_myP = ps;
	}
	template<class T>
	T* TinyScopedArray<T>::Ptr() const throw()
	{
		return _myP;
	}
	/// <summary>
	/// 引用计数智能指针,T必须显示实现AddRef,Release接口 
	/// </summary>
	template<class T>
	class TinyScopedReferencePtr
	{
	public:
		TinyScopedReferencePtr();
		TinyScopedReferencePtr(T* myP);
		TinyScopedReferencePtr(const TinyScopedReferencePtr<T>& s);
		template<typename U>
		TinyScopedReferencePtr(const TinyScopedReferencePtr<U>& s) : m_myP(s.Ptr())
		{
			if (m_myP != NULL)
			{
				m_myP->AddRef();
			}
		}
		~TinyScopedReferencePtr();
		T* Ptr() const;
		operator T*() const;
		T* operator->() const;
		TinyScopedReferencePtr<T>& operator=(T* ps);
		TinyScopedReferencePtr<T>& operator=(const TinyScopedReferencePtr<T>& s);
		template<typename U>
		TinyScopedReferencePtr<T>& operator=(const TinyScopedReferencePtr<U>& s)
		{
			return *this = s.Ptr();
		}
		void Swap(T** pp);
		void Swap(TinyScopedReferencePtr<T>& s);
	protected:
		T* m_myP;
	};
	template<class T>
	TinyScopedReferencePtr<T>::TinyScopedReferencePtr()
		:m_myP(NULL)
	{

	}
	template<class T>
	TinyScopedReferencePtr<T>::TinyScopedReferencePtr(T* myP)
		: m_myP(myP)
	{
		if (m_myP)
		{
			m_myP->AddRef();
		}
	}
	template<class T>
	TinyScopedReferencePtr<T>::TinyScopedReferencePtr(const TinyScopedReferencePtr<T>& s)
		: m_myP(s.m_myP)
	{
		if (m_myP)
		{
			m_myP->AddRef();
		}
	}
	template<class T>
	TinyScopedReferencePtr<T>::~TinyScopedReferencePtr()
	{
		if (m_myP != NULL)
		{
			m_myP->Release();
		}
	}
	template<class T>
	T* TinyScopedReferencePtr<T>::Ptr() const
	{
		return m_myP;
	}
	template<class T>
	TinyScopedReferencePtr<T>::operator T*() const
	{
		return m_myP;
	}
	template<class T>
	T* TinyScopedReferencePtr<T>::operator->() const
	{
		return m_myP;
	}
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(T* ps)
	{
		if (ps)
			ps->AddRef();
		T* oldMyP = m_myP;
		m_myP = ps;
		if (oldMyP)
			oldMyP->Release();
		return *this;
	}
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(const TinyScopedReferencePtr<T>& s)
	{
		return *this = s.m_myP;
	}
	template<class T>
	void TinyScopedReferencePtr<T>::Swap(T** pp)
	{
		T* p = m_myP;
		m_myP = *pp;
		*pp = p;
	}
	template<class T>
	void TinyScopedReferencePtr<T>::Swap(TinyScopedReferencePtr<T>& s)
	{
		Swap(&s.m_myP);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <summary>
	/// COM智能指针
	/// </summary>
	template <class T>
	class TinyComPtr
	{
	public:
		T* _myP;
	public:
		TinyComPtr(T* lp = NULL);
		TinyComPtr(const TinyComPtr<T>& lp);
		~TinyComPtr();
		void Release();
		operator T*() const;
		T& operator*() const;
		T** operator&();
		T* operator->();
		T* operator=(T* lp);
		T* operator=(const TinyComPtr<T>& lp);
		BOOL operator!();
	private:
		static IUnknown*  ComPtrAssign(IUnknown** pp, IUnknown* lp);
	};
	template<class T>
	TinyComPtr<T>::TinyComPtr(T* lp)
	{
		if ((_myP = lp) != NULL)
			_myP->AddRef();
	}
	template<class T>
	TinyComPtr<T>::TinyComPtr(const TinyComPtr<T>& lp)
	{
		if ((_myP = lp._myP) != NULL)
			_myP->AddRef();
	}
	template<class T>
	TinyComPtr<T>::~TinyComPtr()
	{
		if (_myP)
			_myP->Release();
	}
	template<class T>
	void TinyComPtr<T>::Release()
	{
		if (_myP)
			_myP->Release();
		_myP = NULL;
	}
	template<class T>
	TinyComPtr<T>::operator T*() const
	{
		return (T*)_myP;
	}
	template<class T>
	T& TinyComPtr<T>::operator*() const
	{
		ASSERT(_myP != NULL);
		return *_myP;
	}
	template<class T>
	T** TinyComPtr<T>::operator&()
	{
		ASSERT(_myP == NULL);
		return &_myP;
	}
	template<class T>
	T* TinyComPtr<T>::operator->()
	{
		ASSERT(_myP != NULL);
		return _myP;
	}
	template<class T>
	T* TinyComPtr<T>::operator=(T* lp)
	{
		return (T*)ComPtrAssign((IUnknown**)&_myP, lp);
	}
	template<class T>
	T* TinyComPtr<T>::operator=(const TinyComPtr<T>& lp)
	{
		return (T*)ComPtrAssign((IUnknown**)&_myP, lp.p);
	}
	template<class T>
	BOOL TinyComPtr<T>::operator!()
	{
		return (_myP == NULL) ? TRUE : FALSE;
	}
	template<class T>
	IUnknown*  TinyComPtr<T>::ComPtrAssign(IUnknown** pp, IUnknown* lp)
	{
		if (lp != NULL)
			lp->AddRef();
		if (*pp)
			(*pp)->Release();
		*pp = lp;
		return lp;
	}
	/// <summary>
	/// 禁止拷贝赋值类
	/// </summary>
	class noncopyable
	{
	protected:
		noncopyable() = default;//函数定义编译器自动生成 C++11特性
		~noncopyable() = default;
	private:
		noncopyable(const noncopyable& a) = delete;
		noncopyable& operator=(const noncopyable&) = delete;
	};
};
