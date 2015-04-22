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

#ifndef COMPILE_ASSERT
#define COMPILE_ASSERT(exp, name) typedef int dummy##name [(exp) ? 1 : -1]
#endif

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
	template<class T>
	class DefaultTinyReferenceTraits;
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
	/// <summary>
	/// 线程安全的引用计数类,可以显示提供引用析构的机会
	/// </summary>
	template<class T, typename Traits = DefaultTinyReferenceTraits<T>>
	class TinyReference : public TinyReferenceBase
	{
		DISALLOW_COPY_AND_ASSIGN(TinyReference);
	public:
		TinyReference();
		void AddRef() const;
		void Release() const;
	protected:
		~TinyReference();
	private:
		friend struct DefaultTinyReferenceTraits<T>;
		static void Delete(const T* x);
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
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(T* ps)
	{
		if (ps) 
			ps->AddRef();
		T* oldMyP = m_myP;
		m_myP = p;
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

	//////////////////////////////////////////////////////////////////////////
	struct list
	{
		list *NEXT;
		list *PREV;
	};
#define LIST_POISON1	(( list *)0x00100100)
#define LIST_POISON2	(( list *)0x00200200)
	static inline void INIT_LIST(list *_list)
	{
		_list->NEXT = _list;
		_list->PREV = _list;
	}
	static inline void __LIST_ADD(list *_new, list *prev, list *next)
	{
		next->PREV = _new;
		_new->NEXT = next;
		_new->PREV = prev;
		prev->NEXT = _new;
	}
	/// <summary>
	/// 添加到元素之后
	/// </summary>
	static inline void LIST_ADD_AFTER(list *_new, list *node)
	{
		__LIST_ADD(_new, node, node->NEXT);
	}
	/// <summary>
	/// 添加到列表末尾
	/// </summary>
	static inline void LIST_ADD_BEFORE(list *_new, list *node)
	{
		__LIST_ADD(_new, node->PREV, node);
	}

	static inline void __LIST_DEL(list * prev, list * next)
	{
		next->PREV = prev;
		prev->NEXT = next;
	}
	static inline void __LIST_DEL_ENTRY(list *entry)
	{
		__LIST_DEL(entry->PREV, entry->NEXT);
	}
	/// <summary>
	/// 删除元素
	/// </summary>
	static inline void LIST_DEL(list *entry)
	{
		__LIST_DEL(entry->PREV, entry->NEXT);
		entry->NEXT = LIST_POISON1;
		entry->PREV = LIST_POISON2;
	}
	static inline void LIST_DEL_INIT(list *entry)
	{
		__LIST_DEL_ENTRY(entry);
		INIT_LIST(entry);
	}
	/// <summary>
	/// 移动节点到 node 之后
	/// </summary>
	static inline void LIST_MOVE_AFTER(list *_list, list *node)
	{
		__LIST_DEL_ENTRY(_list);
		LIST_ADD_AFTER(_list, node);
	}
	/// <summary>
	/// 移动节点到 node 之前
	/// </summary>
	static inline void LIST_MOVE_BEFORE(list *_list, list *node)
	{
		__LIST_DEL_ENTRY(_list);
		LIST_ADD_BEFORE(_list, node);
	}
	/// <summary>
	/// 是否最后一个节点
	/// </summary>
	static inline BOOL IS_LIST_LAST(const  list *_list, const  list *node)
	{
		return _list->NEXT == node;
	}
	/// <summary>
	/// 列表是否为空
	/// </summary>
	static inline BOOL IS_LIST_EMPTY(const  list *node)
	{
		return node->NEXT == node;
	}
	/// <summary>
	/// 旋转整个链表
	/// </summary>
	static inline void LIST_ROTATE_LEFT(list *node)
	{
		list *first;
		if (!IS_LIST_EMPTY(node))
		{
			first = node->NEXT;
			LIST_MOVE_BEFORE(first, node);
		}
	}
	/// <summary>
	/// 下一个节点
	/// </summary>
	static inline  list *LIST_NEXT(const  list *_list, const  list *entry)
	{
		list *res = entry->NEXT;
		if (entry->NEXT == _list) res = NULL;
		return res;
	}
	/// <summary>
	/// 上一个节点
	/// </summary>
	static inline list *LIST_PREV(const  list *_list, const  list *entry)
	{
		list *res = entry->PREV;
		if (entry->PREV == _list) res = NULL;
		return res;
	}
	/// <summary>
	/// 判断链表中是否只有一个节点
	/// </summary>
	static inline int IS_LIST_SINGULAR(const  list *node)
	{
		return !IS_LIST_EMPTY(node) && (node->NEXT == node->PREV);
	}
	static inline void __LIST_CUT_POSITION(list *_list, list *node, list *entry)
	{
		list *new_first = entry->NEXT;
		_list->NEXT = node->NEXT;
		_list->NEXT->PREV = _list;
		_list->PREV = entry;
		entry->NEXT = _list;
		node->NEXT = new_first;
		new_first->PREV = node;
	}
	/// <summary>
	/// 将1个链表截断为2个链表
	/// </summary>
	static inline void LIST_CUT_POSITION(list *_list, list *node, list *entry)
	{
		if (IS_LIST_EMPTY(node))
			return;
		if (IS_LIST_SINGULAR(node) &&
			(node->NEXT != entry && node != entry))
			return;
		if (entry == node)
			INIT_LIST(_list);
		else
			__LIST_CUT_POSITION(_list, node, entry);
	}
	static inline void __LIST_SPLICE(const  list *_list, list *prev, list *next)
	{
		list *first = _list->NEXT;
		list *last = _list->PREV;
		first->PREV = prev;
		prev->NEXT = first;
		last->NEXT = next;
		next->PREV = last;
	}
	/// <summary>
	/// 将2个链表合并为1个链表, @list中的所有节点(不包括list)加入到 node 之后
	/// </summary>
	static inline void LIST_SPLICE_AFTER(const  list *_list, list *node)
	{
		if (!IS_LIST_EMPTY(_list))
			__LIST_SPLICE(_list, node, node->NEXT);
	}
	/// <summary>
	/// 将2个链表合并为1个链表, @list中的所有节点(不包括list)加入到 node 之前
	/// </summary>
	static inline void LIST_SPLICE_BEFORE(list *_list, list *node)
	{
		if (!IS_LIST_EMPTY(_list))
			__LIST_SPLICE(_list, node->PREV, node);
	}
	static inline void LIST_SPLICE_AFTER_INIT(list *_list, list *node)
	{
		if (!IS_LIST_EMPTY(_list))
		{
			__LIST_SPLICE(_list, node, node->NEXT);
			INIT_LIST(_list);
		}
	}
	static inline void LIST_SPLICE_BEFORE_INIT(list *_list, list *node)
	{
		if (!IS_LIST_EMPTY(_list))
		{
			__LIST_SPLICE(_list, node->PREV, node);
			INIT_LIST(_list);
		}
	}
#define LIST_INIT(name) { &(name), &(name) }
#define LIST_ENTRY(ptr, type, member) \
	((type *)((char *)(ptr)-offsetof(type, member)))

#define LIST_FIRST_ENTRY(ptr, type, member) \
	LIST_ENTRY((ptr)->NEXT, type, member)

#define LIST_LAST_ENTRY(ptr, type, member) \
	LIST_ENTRY((ptr)->PREV, type, member)

#define LIST_NEXT_ENTRY(pos,type, member) \
	LIST_ENTRY((pos)->member.NEXT, type, member)

#define LIST_PREV_ENTRY(pos,type, member) \
	LIST_ENTRY((pos)->member.PREV, type, member)

#define LIST_FOR_EACH(pos, node) \
	for (pos = (node)->NEXT; pos != (node); pos = pos->NEXT)

#define LIST_FOR_EACH_PREV(pos, node) \
	for (pos = (node)->PREV; pos != (node); pos = pos->PREV)

#define LIST_FOR_EACH_ENTRY(pos, node, type, member)	\
	for (pos = LIST_FIRST_ENTRY(node, type, member);	\
	&pos->member != (node);								\
	pos = LIST_NEXT_ENTRY(pos, type, member))
};
