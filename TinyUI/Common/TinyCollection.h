#pragma once
#include "TinyCommon.h"
#include <math.h>

namespace TinyUI
{
	/// <summary>
	/// T是对象调用拷贝构造函数,否则直接赋值
	/// </summary>
	template<class T>
	class TinyPlaceNew
	{
	public:
		TinyPlaceNew(const T& _myT) :
			m_myT(_myT)
		{
		};
		template <class _Ty>
		void * __cdecl operator new(size_t, _Ty* p)
		{
			return p;
		};
		template <class _Ty>
		void __cdecl operator delete(void*, _Ty*)
		{
		};
		T m_myT;
	};
	/// <summary>
	/// 简单的Map, Key-Value一一对应,内存中对齐排列
	/// <summary>
	template<class K, class V>
	class TinyMap
	{
	public:
		TinyMap();
		~TinyMap();
		BOOL Add(K myKey, V myValue);
		BOOL Remove(K myKey);
		BOOL RemoveAt(INT index);
		void RemoveAll();
		INT	 GetSize() const;
		INT	 FindKey(K myKey) const;
		INT  FindValue(V myValue) const;
		K&	 GetKeyAt(INT index);
		V&	 GetValueAt(INT index);
		V	 Lookup(K key) const;
		V operator[](K myKey);
		V& operator[](K& myKey);
		INT		m_size;
		K*		m_myKey;
		V*		m_myValue;
	};
	template<class K, class V>
	TinyMap<K, V>::TinyMap()
		:m_myKey(NULL),
		m_myValue(NULL),
		m_size(0)
	{

	}
	template<class K, class V>
	TinyMap<K, V>::~TinyMap()
	{
		RemoveAll();
	}
	template<class K, class V>
	INT	 TinyMap<K, V>::GetSize() const
	{
		return m_size;
	}
	template<class K, class V>
	BOOL TinyMap<K, V>::Add(K myKey, V myValue)
	{
		K* _myKey = NULL;
		_myKey = (K*)_recalloc(m_myKey, m_size + 1, sizeof(K));
		if (_myKey == NULL)
		{
			return FALSE;
		}
		m_myKey = _myKey;
		new(m_myKey + m_size) TinyPlaceNew<K>(myKey);
		V* _myValue = NULL;
		_myValue = (V*)_recalloc(m_myValue, m_size + 1, sizeof(V));
		if (_myValue == NULL)
		{
			return FALSE;
		}
		m_myValue = _myValue;
#pragma push_macro("new")
#undef new
		::new(m_myValue + m_size) TinyPlaceNew<V>(myValue);
#pragma pop_macro("new")
		m_size++;
		return TRUE;
	}
	template<class K, class V>
	BOOL TinyMap<K, V>::Remove(K myKey)
	{
		INT index = FindKey(myKey);
		if (index < 0)
		{
			return FALSE;
		}
		return RemoveAt(index);
	}
	template<class K, class V>
	INT TinyMap<K, V>::FindKey(K myKey) const
	{
		for (INT i = 0; i < m_size; i++)
		{
			if (m_myKey[i] == myKey)
			{
				return i;
			}
		}
		return -1;
	}
	template<class K, class V>
	INT TinyMap<K, V>::FindValue(V myValue) const
	{
		for (INT i = 0; i < m_size; i++)
		{
			if (m_myValue[i] == myValue)
			{
				return i;
			}
		}
		return -1;
	}
	template<class K, class V>
	V TinyMap<K, V>::Lookup(K key) const
	{
		INT index = FindKey(key);
		if (index < 0)
		{
			return NULL;
		}
		return m_myValue[index];
	}
	template<class K, class V>
	K& TinyMap<K, V>::GetKeyAt(INT index)
	{
		if (index < 0 || index >= m_size)
			throw("无效的index");
		return m_myKey[index];
	}
	template<class K, class V>
	V& TinyMap<K, V>::GetValueAt(INT index)
	{
		if (index < 0 || index >= m_size)
			throw("无效的index");
		return m_myValue[index];
	}
	template<class K, class V>
	BOOL TinyMap<K, V>::RemoveAt(INT index)
	{
		if (index < 0 || index >= m_size)
		{
			return FALSE;
		}
		m_myKey[index].~K();
		m_myValue[index].~V();
		//移动内存
		if (index != (m_size - 1))
		{
			memmove_s((void*)(m_myKey + index), (m_size - index) * sizeof(K), (void*)(m_myKey + index + 1), (m_size - (index + 1)) * sizeof(K));
			memmove_s((void*)(m_myValue + index), (m_size - index) * sizeof(V), (void*)(m_myValue + index + 1), (m_size - (index + 1)) * sizeof(V));
		}
		//重新分配内存 
		K* myKey;
		myKey = (K*)_recalloc(m_myKey, (m_size - 1), sizeof(K));
		if (myKey != NULL || m_size == 1)
		{
			m_myKey = myKey;
		}
		V* myValue;
		myValue = (V*)_recalloc(m_myValue, (m_size - 1), sizeof(V));
		if (myValue != NULL || m_size == 1)
		{
			m_myValue = myValue;
		}
		m_size--;
		return TRUE;
	}
	template<class K, class V>
	void TinyMap<K, V>::RemoveAll()
	{
		if (m_myKey != NULL)
		{
			for (INT i = 0; i < m_size; i++)
			{
				m_myKey[i].~K();
				m_myValue[i].~V();
			}
			SAFE_FREE(m_myKey);
		}
		if (m_myValue != NULL)
		{
			SAFE_FREE(m_myValue);
		}
		m_size = 0;
	}
	template<class K, class V>
	V TinyMap<K, V>::operator[](K myKey)
	{
		INT index = FindKey(myKey);
		if (index < 0) throw("无效的Key");
		return m_myValue[index];
	}
	template<class K, class V>
	V& TinyMap<K, V>::operator[](K& myKey)
	{
		INT index = FindKey(myKey);
		if (index < 0) throw("无效的Key");
		return m_myValue[index];
	}
	/// <summary>
	/// 简单的动态数组
	/// <summary>
	template<class T>
	class TinyArray
	{
	public:
		TinyArray();
		TinyArray(const TinyArray<T>& myT);
		TinyArray<T>& operator=(const TinyArray<T>& myT);
		~TinyArray();
		BOOL	Add(const T& myT);
		BOOL	Insert(INT index, const T& myT);
		BOOL	Remove(const T& myT);
		BOOL	RemoveAt(INT index);
		void	RemoveAll();
		INT		Lookup(const T& myT) const;
		T*		GetDate() const;
		INT		GetSize() const;
		const T& operator[](INT index) const;
		T&	operator[](INT index);
		T*	m_value;
		INT m_size;
		INT m_alloc_size;
	};
	template<class T>
	TinyArray<T>::TinyArray()
		:m_value(NULL),
		m_size(0),
		m_alloc_size(0)
	{

	}
	template<class T>
	TinyArray<T>::TinyArray(const TinyArray<T>& myT)
		:m_value(NULL),
		m_size(0),
		m_alloc_size(0)
	{
		INT size = myT.GetSize();
		if (size > 0)
		{
			m_value = (T*)calloc(size, sizeof(T));
			if (m_value != NULL)
			{
				m_alloc_size = size;
				for (INT i = 0; i < size; i++)
				{
					Add(myT[i]);
				}
			}
		}
	}
	template<class T>
	TinyArray<T>& TinyArray<T>::operator=(const TinyArray<T>& myT)
	{
		INT size = myT.GetSize();
		if (m_size != size)
		{
			RemoveAll();
			m_value = (T*)calloc(size, sizeof(T));
			if (m_value != NULL)
			{
				m_alloc_size = m_size;
			}
		}
		else
		{
			for (INT i = m_size; i > 0; i--)
			{
				RemoveAt(i - 1);
			}
		}
		for (INT i = 0; i < size; i++)
		{
			Add(myT[i]);
		}
		return *this;
	}
	template<class T>
	TinyArray<T>::~TinyArray()
	{
		RemoveAll();
	}
	template<class T>
	T*	TinyArray<T>::GetDate() const
	{
		return m_value;
	}
	template<class T>
	INT	TinyArray<T>::GetSize() const
	{
		return m_size;
	}
	template<class T>
	BOOL TinyArray<T>::Add(const T& myT)
	{
		if (m_size == m_alloc_size)//需要重新分配内存
		{
			T* _myP = NULL;
			INT size = (m_alloc_size == 0) ? 1 : (m_size * 2);
			if (size < 0 || size >(INT_MAX / sizeof(T)))
			{
				return FALSE;
			}
			_myP = (T*)_recalloc(m_value, size, sizeof(T));
			if (_myP == NULL)
			{
				return FALSE;
			}
			m_alloc_size = size;
			m_value = _myP;
		}
#pragma push_macro("new")
#undef new
		::new(m_value + m_size) TinyPlaceNew<T>(myT);
#pragma pop_macro("new")
		m_size++;
		return TRUE;
	}
	template<class T>
	BOOL TinyArray<T>::Remove(const T& myT)
	{
		INT index = Lookup(myT);
		if (index == -1)
		{
			return FALSE;
		}
		return RemoveAt(index);
	}
	template<class T>
	BOOL TinyArray<T>::RemoveAt(INT index)
	{
		if (index < 0 || index >= m_size)
		{
			return FALSE;
		}
		m_value[index].~T();
		if (index != (m_size - 1))
		{
			//移动内存
			memmove_s((void*)(m_value + index),
				(m_size - index) * sizeof(T),
				(void*)(m_value + index + 1),
				(m_size - (index + 1)) * sizeof(T));
		}
		m_size--;
		return TRUE;
	}
	template<class T>
	void TinyArray<T>::RemoveAll()
	{
		if (m_value != NULL)
		{
			for (INT i = 0; i < m_size; i++)
			{
				m_value[i].~T();
			}
			SAFE_FREE(m_value);
		}
		m_size = 0;
		m_alloc_size = 0;
	}
	template<class T>
	BOOL TinyArray<T>::Insert(INT index, const T& myT)
	{
		//Index超出范围
		if (index < 0 || index > m_size)
		{
			return FALSE;
		}
		//需要重新分配内存
		if (m_size == m_alloc_size)
		{
			T* _myP = NULL;
			INT size = (m_alloc_size == 0) ? 1 : (m_size * 2);
			if (size < 0 || size >(INT_MAX / sizeof(T)))
			{
				return FALSE;
			}
			_myP = (T*)_recalloc(m_value, size, sizeof(T));
			if (_myP == NULL)
			{
				return FALSE;
			}
			m_alloc_size = size;
			m_value = _myP;
		}
		//向后移动一个T大小内存
		memmove_s((void*)(m_value + index + 1),
			(m_size - index) * sizeof(T),
			(void*)(m_value + index),
			(m_size - index) * sizeof(T));
#pragma push_macro("new")
#undef new
		::new(m_value + index) TinyPlaceNew<T>(myT);
#pragma pop_macro("new")
		m_size++;
		return TRUE;
	}
	template<class T>
	INT	TinyArray<T>::Lookup(const T& myT) const
	{
		for (INT i = 0; i < m_size; i++)
		{
			if (m_value[i] == myT)
			{
				return i;
			}
		}
		return -1;
	}
	template<class T>
	const T& TinyArray<T>::operator[](INT index) const
	{
		if (index < 0 || index >= m_size)
			throw("无效的index");
		return m_value[index];
	}
	template<class T>
	T&	TinyArray<T>::operator[](INT index)
	{
		if (index < 0 || index >= m_size)
			throw("无效的index");
		return m_value[index];
	}
	/// <summary>
	/// 内存池
	/// </summary>
#pragma pack(push, 4)
	struct NO_VTABLE TinyPlex
	{
		TinyPlex* pNext;
		void* data() { return this + 1; }
		static TinyPlex* PASCAL Create(TinyPlex*& ps, UINT_PTR nMax, UINT_PTR nElementSize);
		void Destory();
	};
#pragma pack(pop)
	/// <summary>
	/// 迭代器的内部指针
	/// </summary>
	struct __ITERATOR{};
	typedef __ITERATOR* ITERATOR;
	/// <summary>
	/// 类型萃取器
	/// </summary>
	template<typename T>
	class DefaultTraits
	{
	public:
		static INT  Compare(const T& value1, const T& value2)
		{
			if (value1 < value2)
				return (-1);
			else if (value1 == value2)
				return (0);
			else
				return (1);
		}
	};
	/// <summary>
	/// 链表结构
	/// </summary>
	template<typename T, typename Traits = DefaultTraits<T>>
	class TinyLinkList
	{
		DISALLOW_COPY_AND_ASSIGN(TinyLinkList)
	private:
		class TinyEntry : public __ITERATOR
		{
		public:
			T			m_value;
			TinyEntry*	m_pNext;
			TinyEntry*	m_pPrev;
			TinyEntry*	m_pEntry;
		public:
			TinyEntry(const T& value)
				:m_value(value),
				m_pNext(NULL),
				m_pPrev(NULL)
			{

			}
		};
	public:
		explicit TinyLinkList(DWORD dwSize = 10);
		~TinyLinkList();
		ITERATOR operator[](const T& value) const;
		DWORD GetCount() const;
		BOOL IsEmpty() const;
		ITERATOR InsertFirst(const T& value);
		ITERATOR InsertLast(const T& value);
		ITERATOR InsertBefore(ITERATOR pos, const T& value);
		ITERATOR InsertAfter(ITERATOR pos, const T& value);
		ITERATOR Lookup(const T& value, ITERATOR pos) const;
		ITERATOR First() const;
		ITERATOR Last() const;
		ITERATOR Next(ITERATOR pos) const;
		ITERATOR Prev(ITERATOR pos) const;
		T& GetAt(ITERATOR pos);
		const T& GetAt(ITERATOR pos) const;
		void RemoveAt(ITERATOR pos);
		void RemoveAll();
	private:
		typename TinyLinkList<T, Traits>::TinyEntry* New(TinyEntry* pPrev, TinyEntry* pNext, const T& value);
		void Delete(TinyEntry* ps);
	private:
		DWORD		m_dwBlockSize;
		DWORD		m_dwCount;
		TinyEntry*	m_pFirst;
		TinyEntry*	m_pLast;
		TinyEntry*  m_pEntry;
		TinyPlex*	m_pBlocks;
	};
	template<typename T, typename Traits>
	TinyLinkList<T, Traits>::~TinyLinkList()
	{
		RemoveAll();
	}
	template<typename T, typename Traits>
	TinyLinkList<T, Traits>::TinyLinkList(DWORD dwBlockSize)
		:m_dwBlockSize(dwBlockSize),
		m_dwCount(0),
		m_pFirst(NULL),
		m_pLast(NULL),
		m_pEntry(NULL),
		m_pBlocks(NULL)
	{

	}
	template<typename T, typename Traits>
	typename TinyLinkList<T, Traits>::TinyEntry* TinyLinkList<T, Traits>::New(TinyEntry* pPrev, TinyEntry* pNext, const T& value)
	{
		if (m_pEntry == NULL)
		{
			TinyPlex* pPlex = TinyPlex::Create(m_pBlocks, m_dwBlockSize, sizeof(TinyEntry));
			if (pPlex == NULL) return NULL;
			TinyEntry* ps = static_cast<TinyEntry*>(pPlex->data());
			ps += m_dwBlockSize - 1;
			for (INT_PTR iBlock = m_dwBlockSize - 1; iBlock >= 0; iBlock--)
			{
				ps->m_pEntry = m_pEntry;
				m_pEntry = ps;
				ps--;
			}
		}
		TinyEntry* pNew = m_pEntry;
		m_pEntry = m_pEntry->m_pEntry;
		pNew->m_pPrev = pPrev;
		pNew->m_pNext = pNext;
		m_dwCount++;
		::new(pNew)TinyEntry(value);
		return(pNew);
	}
	template<typename T, typename Traits>
	void TinyLinkList<T, Traits>::Delete(TinyEntry* ps)
	{
		ps->~TinyEntry();
		ps->m_pNext = m_pEntry;
		m_pEntry = ps;
		m_dwCount--;
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList<T, Traits>::InsertFirst(const T& value)
	{
		TinyEntry* ps = New(NULL, m_pFirst, value);
		if (m_pFirst != NULL)
			m_pFirst->m_pPrev = ps;
		else
			m_pLast = ps;
		m_pFirst = ps;
		return(ITERATOR(ps));
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList<T, Traits>::InsertLast(const T& value)
	{
		TinyEntry* ps = New(m_pLast, NULL, value);
		if (m_pLast != NULL)
			m_pLast->m_pNext = ps;
		else
			m_pFirst = ps;
		m_pLast = ps;
		return(ITERATOR(ps));
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList<T, Traits>::InsertBefore(ITERATOR pos, const T& value)
	{
		if (pos == NULL)
			return InsertFirst(value);
		TinyEntry* pOld = static_cast<TinyEntry*>(pos);
		TinyEntry* pNew = New(pOld->m_pPrev, pOld, value);
		if (pOld->m_pPrev != NULL)
			pOld->m_pPrev->m_pNext = pNew;
		else
			m_pFirst = pNew;
		pOld->m_pPrev = pNew;
		return(ITERATOR(pNew));
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList<T, Traits>::InsertAfter(ITERATOR pos, const T& value)
	{
		if (pos == NULL)
			return InsertLast(value);
		TinyEntry* pOld = static_cast<TinyEntry*>(pos);
		TinyEntry* pNew = New(value, pOld, pOld->m_pNext);
		if (pOld->m_pNext != NULL)
			pOld->m_pNext->m_pPrev = pNew;
		else
			m_pLast = pNew;
		pOld->m_pNext = pNew;
		return(ITERATOR(pNew));
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList<T, Traits>::Lookup(const T& value, ITERATOR pos) const
	{
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps == NULL)
			ps = m_pFirst;
		else
			ps = ps->m_pNext;
		for (; ps != NULL; ps = ps->m_pNext)
		{
			if (Traits::Compare(ps->m_value, value) == 0)
				return(ITERATOR(ps));
		}
		return(NULL);
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList< T, Traits>::First() const
	{
		return ITERATOR(m_pFirst);
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList< T, Traits>::Last() const
	{
		return ITERATOR(m_pLast);
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList< T, Traits>::Next(ITERATOR pos) const
	{
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps != NULL)
		{
			return ITERATOR(ps->m_pNext);
		}
		return NULL;
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList< T, Traits>::Prev(ITERATOR pos) const
	{
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps != NULL)
		{
			return ITERATOR(ps->m_pPrev);
		}
		return NULL;
	}
	template<typename T, typename Traits>
	const T& TinyLinkList< T, Traits>::GetAt(ITERATOR pos) const
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		return ps->m_value;
	}
	template<typename T, typename Traits>
	T& TinyLinkList< T, Traits>::GetAt(ITERATOR pos)
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		return ps->m_value;
	}
	template<typename T, typename Traits>
	void TinyLinkList< T, Traits>::RemoveAt(ITERATOR pos)
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps == m_pFirst)
			m_pFirst = ps->m_pNext;
		else
			ps->m_pPrev->m_pNext = ps->m_pNext;
		if (ps == m_pLast)
			m_pLast = ps->m_pPrev;
		else
			ps->m_pNext->m_pPrev = ps->m_pPrev;
		Delete(ps);
	}
	template<typename T, typename Traits>
	void TinyLinkList< T, Traits>::RemoveAll()
	{
		for (TinyEntry* ps = m_pFirst; ps != NULL; ps = ps->m_pEntry)
		{
			Delete(ps);
		}
		m_pFirst = NULL;
		m_pLast = NULL;
		m_pEntry = NULL;
		m_pBlocks->Destory();
		m_pBlocks = NULL;
	}
	template<typename T, typename Traits>
	DWORD TinyLinkList< T, Traits>::GetCount() const
	{
		return m_dwCount;
	}
	template<typename T, typename Traits>
	BOOL TinyLinkList< T, Traits>::IsEmpty() const
	{
		return m_dwCount == 0;
	}
	template<typename T, typename Traits>
	ITERATOR TinyLinkList< T, Traits>::operator[](const T& value) const
	{
		return Lookup(value, NULL);
	}
	/// <summary>
	/// 红黑树Map 
	/// </summary>
	template<class K, class V, class KTraits = DefaultTraits< K >, class VTraits = DefaultTraits< V >>
	class TinyTreeMap
	{
		DISALLOW_COPY_AND_ASSIGN(TinyTreeMap);
	private:
		class TinyEntry : public __ITERATOR
		{
		public:
			const K		m_key;
			V			m_value;
			BOOL		m_bColor;
			TinyEntry*	m_pLeft;
			TinyEntry*	m_pRight;
			TinyEntry*	m_pParent;
			TinyEntry*	m_pEntry;
		public:
			TinyEntry(const K& key, V& value)
				:m_key(key),
				m_value(value),
				m_bColor(FALSE),
				m_pLeft(NULL),
				m_pRight(NULL),
				m_pParent(NULL)
			{

			}
		};
	public:
		explicit TinyTreeMap(DWORD dwBlockSize = 10);
		~TinyTreeMap();
		ITERATOR operator[](const K& key) const;
		DWORD GetCount() const;
		BOOL IsEmpty() const;
		ITERATOR Add(const K& key, V& value);
		void Remove(const K& key);
		void RemoveAll();
		ITERATOR Lookup(const K& key);
		ITERATOR SetAt(const K& key, V& value);
		K& GetKeyAt(ITERATOR pos);
		V& GetValueAt(ITERATOR pos);
		const K& GetKeyAt(ITERATOR pos) const;
		const V& GetValueAt(ITERATOR pos) const;
		ITERATOR First() const;
		ITERATOR Last() const;
		ITERATOR Next(ITERATOR pos) const;
		ITERATOR Prev(ITERATOR pos) const;
	private:
		typename TinyTreeMap<K, V, KTraits, VTraits>::TinyEntry* New(const K& key, V& value);
		void Delete(TinyEntry* ps);
		typename TinyTreeMap<K, V, KTraits, VTraits>::TinyEntry* Lookup(TinyEntry* ps, const K& key);
		void RotateL(TinyEntry* ps);
		void RotateR(TinyEntry* ps);
		void Add(TinyEntry* ps);
		void AddFixup(TinyEntry* ps);
		void RemoveRecursion(TinyEntry* ps);
		void Remove(TinyEntry* ps);
		void RemoveFixup(TinyEntry* ps, TinyEntry* pParent);
	private:
		DWORD		m_dwBlockSize;
		DWORD		m_dwCount;
		TinyEntry*	m_pRoot;
		TinyEntry*	m_pEntry;
		TinyPlex*	m_pBlocks;
	};
	template<class K, class V, class KTraits, class VTraits>
	TinyTreeMap<K, V, KTraits, VTraits>::TinyTreeMap(DWORD dwBlockSize)
		:m_dwBlockSize(dwBlockSize),
		m_dwCount(0),
		m_pBlocks(NULL),
		m_pEntry(NULL),
		m_pRoot(NULL)
	{

	}
	template<class K, class V, class KTraits, class VTraits>
	TinyTreeMap<K, V, KTraits, VTraits>::~TinyTreeMap()
	{
		RemoveAll();
	}
	template<class K, class V, class KTraits, class VTraits>
	DWORD TinyTreeMap<K, V, KTraits, VTraits>::GetCount() const
	{
		return m_dwCount;
	}
	template<class K, class V, class KTraits, class VTraits>
	BOOL TinyTreeMap<K, V, KTraits, VTraits>::IsEmpty() const
	{
		return m_dwCount == 0;
	}
	template<class K, class V, class KTraits, class VTraits>
	typename TinyTreeMap<K, V, KTraits, VTraits>::TinyEntry* New(const K& key, V& value)
	{
		if (m_pEntry == NULL)
		{
			TinyPlex* pPlex = TinyPlex::Create(m_pBlocks, m_dwBlockSize, sizeof(TinyEntry));
			if (pPlex == NULL) return NULL;
			TinyEntry* ps = static_cast<TinyEntry*>(pPlex->data());
			ps += m_dwBlockSize - 1;
			for (INT_PTR iBlock = m_dwBlockSize - 1; iBlock >= 0; iBlock--)
			{
				ps->m_pEntry = m_pEntry;
				m_pEntry = ps;
				ps--;
			}
		}
		TinyNode* pNew = m_pEntry;
		::new(pNew)TinyNode(key, value);
		m_pEntry = m_pEntry->m_pEntry;
		m_dwCount++;
		return pNew;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Delete(TinyEntry* ps)
	{
		ps->~TinyEntry();
		ps->m_pEntry = m_pEntry;
		m_pEntry = ps;
		m_dwCount--;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Remove(const K& key)
	{
		TinyEntry* ps = Lookup(m_pRoot, key);
		if (ps != NULL)
		{
			Remove(ps);
		}
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RemoveAll()
	{
		RemoveRecursion(m_pRoot);
		m_dwCount = 0;
		m_pBlocks->Destory();
		m_pBlocks = NULL;
		m_pFree = NULL;
		m_pRoot = NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Add(const K& key, V& value)
	{
		TinyEntry* ps = Lookup(m_pRoot, key);
		if (ps == NULL)
		{
			TinyEntry* pNew = New(key, value);
			if (pNew != NULL)
			{
				Add(pNew);
				return ITERATOR(pNew);
			}
		}
		return NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Add(TinyEntry* ps)
	{
		TinyEntry* pX = m_pRoot;
		TinyEntry* pY = NULL;
		while (pX != NULL)
		{
			pY = pX;
			if (KTraits::Compare(pNew->m_key, pX->m_key) <= 0)
				pX = pX->m_pLeft;
			else
				pX = pX->m_pRight;
		}
		pNew->m_pParent = pY;
		if (pY == NULL)
		{
			m_pRoot = pNew;
		}
		else if (KTraits::Compare(pNew->m_key, pY->m_key) <= 0)
		{
			pY->m_pLeft = pNew;
		}
		else
		{
			pY->m_pRight = pNew;
		}
		pNew->m_bColor = TRUE;
		AddFixup(pNew);
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::AddFixup(TinyEntry* ps)
	{
		TinyEntry *pParent = NULL;
		TinyEntry *pGparent = NULL;
		while ((pParent = ps->m_pParent) && pParent->m_bColor)
		{
			pGparent = pParent->m_pParent;
			if (pParent == pGparent->m_pLeft)
			{
				register TinyEntry *pUncle = pGparent->m_pRight;
				if (pUncle && pUncle->m_bColor)
				{
					pUncle->m_bColor = FALSE;
					pParent->m_bColor = FALSE;
					pGparent->m_bColor = TRUE;
					ps = pGparent;
					continue;
				}
				if (pParent->m_pRight == ps)
				{
					RotateL(pParent);
					register TinyEntry *pEntry = NULL;
					pEntry = pParent;
					pParent = ps;
					ps = pEntry;
				}
				pParent->m_bColor = FALSE;
				pGparent->m_bColor = TRUE;
				RotateR(pGparent);
			}
			else
			{
				register TinyNode *pUncle = pGparent->m_pLeft;
				if (pUncle && pUncle->m_bColor)
				{
					pUncle->m_bColor = FALSE;
					pParent->m_bColor = FALSE;
					pGparent->m_bColor = TRUE;
					ps = pGparent;
					continue;
				}
				if (pParent->m_pLeft == ps)
				{
					register TinyNode *ps = NULL;
					RotateR(pParent);
					ps = pParent;
					pParent = ps;
					ps = ps;
				}
				pParent->m_bColor = FALSE;
				pGparent->m_bColor = TRUE;
				RotateL(pGparent);
			}
		}
		m_pRoot->m_bColor = FALSE;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RemoveRecursion(TinyEntry* ps)
	{
		if (ps == NULL) return;
		RemoveRecursion(ps->m_pLeft);
		RemoveRecursion(ps->m_pRight);
		Delete(ps);
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Remove(TinyEntry* ps)
	{
		TinyNode *pChild = NULL;
		TinyNode *pParent = NULL;
		BOOL bColor = FALSE;
		if (!ps->m_pLeft)
		{
			pChild = ps->m_pRight;
		}
		else if (!ps->m_pRight)
		{
			pChild = ps->m_pLeft;
		}
		else
		{
			TinyNode *pOld = ps;
			TinyNode *pLeft = NULL;
			ps = ps->m_pRight;
			while ((pLeft = ps->m_pLeft) != NULL)
			{
				ps = pLeft;
			}
			if (pOld->m_pParent != NULL)
			{
				if (pOld->m_pParent->m_pLeft == pOld)
					pOld->m_pParent->m_pLeft = ps;
				else
					pOld->m_pParent->m_pRight = ps;
			}
			else
			{
				m_pRoot = ps;
			}
			pChild = ps->m_pRight;
			pParent = ps->m_pParent;
			bColor = ps->m_bColor;
			if (pParent == pOld)
			{
				pParent = ps;
			}
			else
			{
				if (pChild != NULL)
				{
					pChild->m_pParent = pParent;
				}
				pParent->m_pLeft = pChild;
				ps->m_pRight = pOld->m_pRight;
				pOld->m_pRight->m_pParent = ps;
			}
			ps->m_pParent = pOld->m_pParent;
			ps->m_bColor = pOld->m_bColor;
			ps->m_pLeft = pOld->m_pLeft;
			pOld->m_pLeft->m_pParent = ps;
			goto LABEL;
		}

		pParent = ps->m_pParent;
		bColor = ps->m_bColor;
		if (pChild != NULL)
		{
			pChild->m_pParent = pParent;
		}
		if (pParent != NULL)
		{
			if (pParent->m_pLeft == ps)
				pParent->m_pLeft = pChild;
			else
				pParent->m_pRight = pChild;
		}
		else
		{
			m_pRoot = pChild;
		}
	LABEL:
		if (bColor == FALSE)
		{
			RemoveFixup(pChild, pParent);
		}
		Delete(ps);
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RemoveFixup(TinyEntry* ps, TinyEntry* pParent)
	{
		TinyEntry *pOther = NULL;
		while ((!ps || !ps->m_bColor) && ps != m_pRoot)
		{
			if (pParent->m_pLeft == ps)
			{
				pOther = pParent->m_pRight;
				if (pOther->m_bColor)
				{
					pOther->m_bColor = FALSE;
					pParent->m_bColor = TRUE;
					RotateL(pParent);
					pOther = pParent->m_pRight;
				}
				if ((!pOther->m_pLeft || !pOther->m_pLeft->m_bColor) && (!pOther->m_pRight || !pOther->m_pRight->m_bColor))
				{
					pOther->m_bColor = TRUE;
					ps = pParent;
					pParent = ps->m_pParent;
				}
				else
				{
					if (!pOther->m_pRight || !pOther->m_pRight->m_bColor)
					{
						pOther->m_pLeft->m_bColor = FALSE;
						pOther->m_bColor = TRUE;
						RotateR(pOther);
						pOther = pParent->m_pRight;
					}
					pOther->m_bColor = pParent->m_bColor;
					pParent->m_bColor = FALSE;
					pOther->m_pRight->m_bColor = FALSE;
					RotateL(pParent);
					ps = m_pRoot;
					break;
				}
			}
			else
			{
				pOther = pParent->m_pLeft;
				if (pOther->m_bColor)
				{
					pOther->m_bColor = FALSE;
					pParent->m_bColor = TRUE;
					RotateR(pParent);
					pOther = pParent->m_pLeft;
				}
				if ((!pOther->m_pLeft || !pOther->m_pLeft->m_bColor) && (!pOther->m_pRight || !pOther->m_pRight->m_bColor))
				{
					pOther->m_bColor = TRUE;
					ps = pParent;
					pParent = ps->m_pParent;
				}
				else
				{
					if (!pOther->m_pLeft || !pOther->m_pLeft->m_bColor)
					{
						pOther->m_pRight->m_bColor = FALSE;
						pOther->m_bColor = TRUE;
						RotateL(pOther);
						pOther = pParent->m_pLeft;
					}
					pOther->m_bColor = pParent->m_bColor;
					pParent->m_bColor = FALSE;
					pOther->m_pLeft->m_bColor = FALSE;
					RotateR(pParent);
					ps = m_pRoot;
					break;
				}
			}
		}
		if (ps)
		{
			ps->m_bColor = FALSE;
		}
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RotateL(TinyEntry* ps)
	{
		TinyEntry* pRight = ps->m_pRight;
		TinyEntry* pParent = ps->m_pParent;
		if (ps->m_pRight = pRight->m_pLeft)
		{
			pRight->m_pLeft->m_pParent = ps;
		}
		pRight->m_pLeft = ps;
		pRight->m_pParent = pParent;
		if (pParent != NULL)
		{
			if (ps == pParent->m_pLeft)
				pParent->m_pLeft = pRight;
			else
				pParent->m_pRight = pRight;
		}
		else
		{
			m_pRoot = pRight;
		}
		ps->m_pParent = pRight;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RotateR(TinyEntry* ps)
	{
		TinyEntry *pLeft = ps->m_pLeft;
		TinyEntry *pParent = ps->m_pParent;
		if ((ps->m_pLeft = pLeft->m_pRight))
		{
			pLeft->m_pRight->m_pParent = ps;
		}
		pLeft->m_pRight = ps;
		pLeft->m_pParent = pParent;
		if (pParent != NULL)
		{
			if (ps == pParent->m_pRight)
				pParent->m_pRight = pLeft;
			else
				pParent->m_pLeft = pLeft;
		}
		else
		{
			m_pRoot = pLeft;
		}
		ps->m_pParent = pLeft;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Lookup(const K& key)
	{
		if (!m_pRoot) return NULL;
		return Lookup(key, ITERATOR(m_pRoot));
	}
	template<class K, class V, class KTraits, class VTraits>
	typename TinyTreeMap<K, V, KTraits, VTraits>::TinyEntry* TinyTreeMap<K, V, KTraits, VTraits>::Lookup(TinyEntry* ps, const K& key)
	{
		ASSERT(ps);
		while (ps != NULL && KTraits::Compare(key, ps->m_key) != 0)
		{
			if (KTraits::Compare(key, ps->m_key) < 0)
			{
				ps = ps->m_pLeft;
			}
			else
			{
				ps = ps->m_pRight;
			}
		}
		return ps;
	}
	template<class K, class V, class KTraits, class VTraits>
	K& TinyTreeMap<K, V, KTraits, VTraits>::GetKeyAt(ITERATOR pos)
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast <TinyEntry*>(pos);
		return ps->m_key;
	}
	template<class K, class V, class KTraits, class VTraits>
	V& TinyTreeMap<K, V, KTraits, VTraits>::GetValueAt(ITERATOR pos)
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast <TinyEntry*>(pos);
		return ps->m_value;
	}
	template<class K, class V, class KTraits, class VTraits>
	const K& TinyTreeMap<K, V, KTraits, VTraits>::GetKeyAt(ITERATOR pos) const
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast <TinyEntry*>(pos);
		return ps->m_key;
	}
	template<class K, class V, class KTraits, class VTraits>
	const V& TinyTreeMap<K, V, KTraits, VTraits>::GetValueAt(ITERATOR pos) const
	{
		ASSERT(pos);
		TinyEntry* ps = static_cast <TinyEntry*>(pos);
		return ps->m_value;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::First() const
	{
		if (!m_pRoot) return NULL;
		TinyEntry* ps = m_pRoot;
		while (ps->m_pLeft != NULL)
			ps = ps->m_pLeft;
		return ps;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Last() const
	{
		if (!m_pRoot) return NULL;
		TinyEntry* ps = m_pRoot;
		while (ps->m_pRight != NULL)
			ps = ps->m_pRight;
		return ps;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Next(ITERATOR pos) const
	{
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps->m_pParent == ps)
			return NULL;
		if (ps->m_pRight != NULL)
		{
			ps = ps->m_pRight;
			while (ps->m_pLeft != NULL)
				ps = ps->m_pLeft;
			return ps;
		}
		TinyEntry* pParent = NULL;
		while ((pParent = ps->m_pParent) && ps == pParent->m_pRight)
			ps = pParent;
		return pParent;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Prev(ITERATOR pos) const
	{
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps->m_pParent == ps)
			return NULL;
		if (ps->m_pLeft != NULL)
		{
			ps = ps->m_pLeft;
			while (ps->m_pRight != NULL)
				ps = ps->m_pRight;
			return ps;
		}
		TinyEntry* pParent = NULL;
		while ((pParent = ps->m_pParent) && ps == pParent->m_pLeft)
			ps = pParent;
		return pParent;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::operator[](const K& key) const
	{
		return Lookup(key);
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::SetAt(const K& key, V& value)
	{
		ITERATOR pos = Lookup(key);
		TinyEntry* ps = static_cast<TinyEntry*>(pos);
		if (ps != NULL)
		{
			ps->m_value = value;
		}
		else
		{
			pos = Add(key, value);
		}
		return pos;
	}
	/// <summary>
	/// HashMap结构
	/// </summary>
	template<typename T, typename Traits>
	class TinyHashMap
	{

	};
}
