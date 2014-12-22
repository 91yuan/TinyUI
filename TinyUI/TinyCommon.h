#pragma once
#include <Windows.h>
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

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Winmm.lib")

using namespace Gdiplus;

namespace TinyUI
{
	//////////////////////////////////////////////////////////////////////////
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
	//////////////////////////////////////////////////////////////////////////
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)  { if (p) { delete (p);  (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }
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

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((int)(short)LOWORD(lParam))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((int)(short)HIWORD(lParam))
#endif

#define IS_VALID_STRING_PTR(ptr, type) \
	(!IsBadStringPtr((ptr), (UINT)-1))
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// ����ָ��
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
		//�ͷŵ�ǰ��ָ��
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
	/// COM����ָ��
	/// </summary>
	template <class T>
	class TinyComPtr
	{
	public:
		T* _myP;
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
};