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

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Comctl32.lib")

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

#define IS_VALID_STRING_PTR(ptr, type) \
	(!IsBadStringPtr((ptr), (UINT)-1))

#define DISALLOW_COPY(TypeName) \
private:\
	TypeName(const TypeName&)

#define DISALLOW_ASSIGN(TypeName) \
private:\
	void operator=(const TypeName&)

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private:\
	TypeName(const TypeName&);               \
	void operator=(const TypeName&)

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
	/// 线程安全的引用计数类
	/// </summary>
	class TinyReference
	{
	public:
		TinyReference();
		virtual ~TinyReference();
		/// <summary>
		/// 获得当前的引用计数
		/// </summary>
		LONG GetReference();
		/// <summary>
		/// 引用+1
		/// </summary>
		void AddRef();
		/// <summary>
		/// 释放
		/// </summary>
		void Release();
	protected:
		LONG	m_cRef;
	};
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
		if (_ptr != _myP)
			delete _myP;
		_myP = _ptr;
	}
	template<class T>
	T& TinyScopedPtr<T>::operator*() const throw()
	{
		return (*_myP);
	}
	template<class T>
	T* TinyScopedPtr<T>::operator->() const throw()
	{
		return (_myP);
	}
	template<class T>
	T* TinyScopedPtr<T>::Ptr() const throw()
	{
		return (_myP);
	}
	/// <summary>
	/// 引用计数智能指针 
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
		T* Release();
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
	{}
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
	/// <summary>
	/// 释放指针.
	/// 返回对象当前拥有的指针. 如果指针为NULL, 返回NULL.
	/// 操作完成后, 对象拥有一个NULL指针, 不再拥有任何对象.
	/// </summary>
	template<class T>
	T* TinyScopedReferencePtr<T>::Release()
	{
		T* _ps = m_myP;
		m_myP = NULL;
		return _ps;
	}
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(T* ps)
	{
		if (ps != NULL)
		{
			ps->AddRef();
		}
		if (m_myP != NULL)
		{
			m_myP->Release();
		}
		m_myP = ps;
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
		T* p = ptr_;
		m_myP = *pp;
		*pp = p;
	}
	template<class T>
	void TinyScopedReferencePtr<T>::Swap(TinyScopedReferencePtr<T>& s)
	{
		swap(&s.m_myP);
	}
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

	struct LIST
	{
		struct LIST *NEXT;
		struct LIST *PREV;
	};

	static inline void LIST_ADD_AFTER(LIST *elem, LIST *to_add)
	{
		to_add->NEXT = elem->NEXT;
		to_add->PREV = elem;
		elem->NEXT->PREV = to_add;
		elem->NEXT = to_add;
	}

	static inline void LIST_ADD_BEFORE(LIST *elem, LIST *to_add)
	{
		to_add->NEXT = elem;
		to_add->PREV = elem->PREV;
		elem->PREV->NEXT = to_add;
		elem->PREV = to_add;
	}

	static inline void LIST_ADD_HEAD(LIST *list, LIST *elem)
	{
		LIST_ADD_AFTER(list, elem);
	}

	static inline void LIST_ADD_TAIL(LIST *list, LIST *elem)
	{
		LIST_ADD_BEFORE(list, elem);
	}

	static inline void LIST_REMOVE(LIST *elem)
	{
		elem->NEXT->PREV = elem->PREV;
		elem->PREV->NEXT = elem->NEXT;
	}

	static inline struct LIST *LIST_NEXT(const LIST *list, const LIST *elem)
	{
		struct LIST *ret = elem->NEXT;
		if (elem->NEXT == list) ret = NULL;
		return ret;
	}

	static inline struct LIST *LIST_PREV(const LIST *list, const LIST *elem)
	{
		struct LIST *ret = elem->PREV;
		if (elem->PREV == list) ret = NULL;
		return ret;
	}

	static inline struct LIST *LIST_HEAD(const  LIST *list)
	{
		return LIST_NEXT(list, list);
	}

	static inline struct LIST *LIST_TAIL(const  LIST *list)
	{
		return LIST_PREV(list, list);
	}

	static inline int LIST_EMPTY(const  LIST *list)
	{
		return list->NEXT == list;
	}

	static inline void LIST_INIT( LIST *list)
	{
		list->NEXT = list->PREV = list;
	}

	static inline unsigned int LIST_COUNT(const  LIST *list)
	{
		unsigned count = 0;
		const LIST *ps = NULL;
		for (ps = list->NEXT; ps != list; ps = ps->NEXT) count++;
		return count;
	}

	static inline void LIST_MOVE_TAIL(struct LIST *dst, struct LIST *src)
	{
		if (LIST_EMPTY(src)) return;

		dst->PREV->NEXT = src->NEXT;
		src->NEXT->PREV = dst->PREV;
		dst->PREV = src->PREV;
		src->PREV->NEXT = dst;
		LIST_INIT(src);
	}

	static inline void LIST_MOVE_HEAD(struct LIST *dst, struct LIST *src)
	{
		if (LIST_EMPTY(src)) return;

		dst->NEXT->PREV = src->PREV;
		src->PREV->NEXT = dst->NEXT;
		dst->NEXT = src->NEXT;
		src->NEXT->PREV = dst;
		LIST_INIT(src);
	}

#define LIST_FOR_EACH(cursor,list) \
	for ((cursor) = (list)->NEXT; (cursor) != (list); (cursor) = (cursor)->NEXT)

#define LIST_FOR_EACH_SAFE(cursor, cursor2, list) \
	for ((cursor) = (list)->NEXT, (cursor2) = (cursor)->NEXT; \
	(cursor) != (list); \
	(cursor) = (cursor2), (cursor2) = (cursor)->NEXT)

#define LIST_FOR_EACH_ENTRY(elem, list, type, field) \
	for ((elem) = LIST_ENTRY((list)->NEXT, type, field); \
	&(elem)->field != (list); \
	(elem) = LIST_ENTRY((elem)->field.NEXT, type, field))

#define LIST_FOR_EACH_ENTRY_SAFE(cursor, cursor2, list, type, field) \
	for ((cursor) = LIST_ENTRY((list)->NEXT, type, field), \
	(cursor2) = LIST_ENTRY((cursor)->field.NEXT, type, field); \
	&(cursor)->field != (list); \
	(cursor) = (cursor2), \
	(cursor2) = LIST_ENTRY((cursor)->field.NEXT, type, field))

#define LIST_FOR_EACH_REV(cursor,list) \
	for ((cursor) = (list)->PREV; (cursor) != (list); (cursor) = (cursor)->PREV)

#define LIST_FOR_EACH_SAFE_REV(cursor, cursor2, list) \
	for ((cursor) = (list)->PREV, (cursor2) = (cursor)->PREV; \
	(cursor) != (list); \
	(cursor) = (cursor2), (cursor2) = (cursor)->PREV)

#define LIST_FOR_EACH_ENTRY_REV(elem, list, type, field) \
	for ((elem) = LIST_ENTRY((list)->PREV, type, field); \
	&(elem)->field != (list); \
	(elem) = LIST_ENTRY((elem)->field.PREV, type, field))

#define LIST_FOR_EACH_ENTRY_SAFE_REV(cursor, cursor2, list, type, field) \
	for ((cursor) = LIST_ENTRY((list)->PREV, type, field), \
	(cursor2) = LIST_ENTRY((cursor)->field.PREV, type, field); \
	&(cursor)->field != (list); \
	(cursor) = (cursor2), \
	(cursor2) = LIST_ENTRY((cursor)->field.PREV, type, field))

#undef LIST_INIT
#define LIST_INIT(list)  { &(list), &(list) }

#undef LIST_ENTRY
#define LIST_ENTRY(elem, type, field) \
	((type *)((char *)(elem)-offsetof(type, field)))
};
