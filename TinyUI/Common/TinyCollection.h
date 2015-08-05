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
	struct __ITERATOR{};//保存迭代器的内部指针
	typedef __ITERATOR* ITERATOR;
	/// <summary>
	/// 类型萃取
	/// </summary>
	template<class T>
	class DefaultTraits
	{
	public:
		typedef const T&	CONST_ARGTYPE;
		typedef T&			ARGTYPE;
		static INT  Compare(const T& element1, const T& element2)
		{
			if (element1 < element2)
				return (-1);
			else if (element1 == element2)
				return (0);
			else
				return (1);
		}
	};
	/// <summary>
	/// TreeMap红黑树实现
	/// </summary>
	template<class K, class V, class KTraits = DefaultTraits< K >, class VTraits = DefaultTraits< V >>
	class TinyTreeMap
	{
		DISALLOW_COPY_AND_ASSIGN(TinyTreeMap)
	protected:
		typedef typename KTraits::CONST_ARGTYPE	CONST_KTYPE;
		typedef typename KTraits::ARGTYPE		KTYPE;
		typedef typename VTraits::CONST_ARGTYPE	CONST_VTYPE;
		typedef typename VTraits::ARGTYPE		VTYPE;
	protected:
		class TinyNode : public __ITERATOR
		{
			DISALLOW_COPY_AND_ASSIGN(TinyNode)
		public:
			const K		m_key;
			V			m_value;
			BOOL		m_bColor;
			TinyNode*	m_pLeft;
			TinyNode*	m_pRight;
			TinyNode*	m_pParent;
			TinyNode*	m_pFree;
		public:
			TinyNode(CONST_KTYPE key, VTYPE value)
				: m_key(key),
				m_value(value),
				m_pLeft(NULL),
				m_pRight(NULL),
				m_pParent(NULL),
				m_bColor(FALSE)
			{

			}
		};
	protected:
		TinyPlex*	m_pBlocks;
		TinyNode*	m_pRoot;
		TinyNode*	m_pFree;
		DWORD		m_dwBlockSize;
		DWORD		m_dwCount;
	protected:
		void RotateL(TinyNode* pNode);
		void RotateR(TinyNode* pNode);
		void Add(TinyNode* pNode);
		void AddFixup(TinyNode* pNode);
		void Remove(TinyNode* pNode);
		void RemoveFixup(TinyNode* pNode, TinyNode* parent);
		void RemovePostOrder(TinyNode* pNode);//后序遍历
		typename TinyTreeMap<K, V, KTraits, VTraits>::TinyNode* Find(TinyNode* pNode, CONST_KTYPE key);
		typename TinyTreeMap<K, V, KTraits, VTraits>::TinyNode* NewNode(CONST_KTYPE key, VTYPE value);
		void FreeNode(TinyNode* pNode);
	public:
		explicit TinyTreeMap(DWORD dwBlockSize = 10);
		~TinyTreeMap();
		DWORD GetCount() const;
		BOOL IsEmpty() const;
		void Add(CONST_KTYPE key, VTYPE value);
		void Remove(CONST_KTYPE key);
		void RemoveAll();
		void SetAt(CONST_KTYPE key, VTYPE value);
		V* Lookup(CONST_KTYPE key);
		const V* Lookup(CONST_KTYPE key) const;
		V* operator[](CONST_KTYPE key);
		const V* operator[](CONST_KTYPE key) const;
		const K& GetKeyAt(ITERATOR pos) const;
		const V& GetValueAt(ITERATOR pos) const;
		ITERATOR Find(CONST_KTYPE key);
		ITERATOR First() const;
		ITERATOR Last() const;
		ITERATOR Next(ITERATOR pos) const;
		ITERATOR Prev(ITERATOR pos) const;
	};
	template<class K, class V, class KTraits, class VTraits>
	TinyTreeMap<K, V, KTraits, VTraits>::TinyTreeMap(DWORD dwBlockSize)
		:m_pRoot(NULL),
		m_pBlocks(NULL),
		m_dwBlockSize(dwBlockSize),
		m_dwCount(0),
		m_pFree(NULL)
	{

	}
	template<class K, class V, class KTraits, class VTraits>
	TinyTreeMap<K, V, KTraits, VTraits>::~TinyTreeMap()
	{
		RemoveAll();
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Remove(CONST_KTYPE key)
	{
		TinyNode* node = Find(m_pRoot, key);
		if (node != NULL)
		{
			Remove(node);
		}
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RemoveAll()
	{
		RemovePostOrder(m_pRoot);
		m_dwCount = 0;
		m_pBlocks->Destory();
		m_pBlocks = NULL;
		m_pFree = NULL;
		m_pRoot = NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	V* TinyTreeMap<K, V, KTraits, VTraits>::Lookup(CONST_KTYPE key)
	{
		TinyNode* node = Find(m_pRoot, key);
		if (node != NULL)
		{
			return &(node->m_value);
		}
		return NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	const V* TinyTreeMap<K, V, KTraits, VTraits>::Lookup(CONST_KTYPE key) const
	{
		TinyNode* node = Find(m_pRoot, key);
		if (node != NULL)
		{
			return &(node->m_value);
		}
		return NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	V* TinyTreeMap<K, V, KTraits, VTraits>::operator[](CONST_KTYPE key)
	{
		TinyNode* node = Find(m_pRoot, key);
		if (node != NULL)
		{
			return &(node->m_value);
		}
		return NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	const V* TinyTreeMap<K, V, KTraits, VTraits>::operator[](CONST_KTYPE key) const
	{
		TinyNode* node = Find(m_pRoot, key);
		if (node != NULL)
		{
			return &(node->m_value);
		}
		return NULL;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::SetAt(CONST_KTYPE key, VTYPE value)
	{
		TinyNode* node = Find(m_pRoot, key);
		if (node != NULL)
		{
			node->m_value = value;
		}
	}
	template<class K, class V, class KTraits, class VTraits>
	typename TinyTreeMap<K, V, KTraits, VTraits>::TinyNode* TinyTreeMap<K, V, KTraits, VTraits>::NewNode(CONST_KTYPE key, VTYPE value)
	{
		if (m_pFree == NULL)
		{
			TinyPlex* pPlex = TinyPlex::Create(m_pBlocks, m_dwBlockSize, sizeof(TinyNode));
			if (pPlex == NULL) return NULL;
			TinyNode* pNode = static_cast<TinyNode*>(pPlex->data());
			pNode += m_dwBlockSize - 1;
			for (INT_PTR iBlock = m_dwBlockSize - 1; iBlock >= 0; iBlock--)
			{
				pNode->m_pFree = m_pFree;
				m_pFree = pNode;
				pNode--;
			}
		}
		TinyNode* pNew = m_pFree;
		::new(pNew)TinyNode(key, value);
		m_pFree = m_pFree->m_pFree;
		m_dwCount++;
		return pNew;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::FreeNode(TinyNode* pNode)
	{
		pNode->~TinyNode();
		pNode->m_pFree = m_pFree;
		m_pFree = pNode;
		m_dwCount--;
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
	void TinyTreeMap<K, V, KTraits, VTraits>::Add(CONST_KTYPE key, VTYPE value)
	{
		TinyNode* pNode = Find(m_pRoot, key);
		if (pNode == NULL)
		{
			TinyNode* pNew = NewNode(key, value);
			if (pNew != NULL)
			{
				Add(pNew);
			}
		}
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Add(TinyNode* pNew)
	{
		TinyNode* pX = this->m_pRoot;
		TinyNode* pY = NULL;
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
	void TinyTreeMap<K, V, KTraits, VTraits>::AddFixup(TinyNode* pNode)
	{
		TinyNode *pParent = NULL;
		TinyNode *pGparent = NULL;
		while ((pParent = pNode->m_pParent) && pParent->m_bColor)
		{
			pGparent = pParent->m_pParent;
			if (pParent == pGparent->m_pLeft)
			{
				register TinyNode *pUncle = pGparent->m_pRight;
				if (pUncle && pUncle->m_bColor)
				{
					pUncle->m_bColor = FALSE;
					pParent->m_bColor = FALSE;
					pGparent->m_bColor = TRUE;
					pNode = pGparent;
					continue;
				}
				if (pParent->m_pRight == pNode)
				{
					register TinyNode *pTemp = NULL;
					RotateL(pParent);
					pTemp = pParent;
					pParent = pNode;
					pNode = pTemp;
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
					pNode = pGparent;
					continue;
				}
				if (pParent->m_pLeft == pNode)
				{
					register TinyNode *ps = NULL;
					RotateR(pParent);
					ps = pParent;
					pParent = pNode;
					pNode = ps;
				}
				pParent->m_bColor = FALSE;
				pGparent->m_bColor = TRUE;
				RotateL(pGparent);
			}
		}
		m_pRoot->m_bColor = FALSE;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::Remove(TinyNode* pNode)
	{
		TinyNode *pChild = NULL;
		TinyNode *pParent = NULL;
		BOOL bColor = FALSE;
		if (!pNode->m_pLeft)
		{
			pChild = pNode->m_pRight;
		}
		else if (!pNode->m_pRight)
		{
			pChild = pNode->m_pLeft;
		}
		else
		{
			TinyNode *pOld = pNode;
			TinyNode *pLeft = NULL;
			pNode = pNode->m_pRight;
			while ((pLeft = pNode->m_pLeft) != NULL)
			{
				pNode = pLeft;
			}
			if (pOld->m_pParent != NULL)
			{
				if (pOld->m_pParent->m_pLeft == pOld)
					pOld->m_pParent->m_pLeft = pNode;
				else
					pOld->m_pParent->m_pRight = pNode;
			}
			else
			{
				m_pRoot = pNode;
			}
			pChild = pNode->m_pRight;
			pParent = pNode->m_pParent;
			bColor = pNode->m_bColor;
			if (pParent == pOld)
			{
				pParent = pNode;
			}
			else
			{
				if (pChild != NULL)
				{
					pChild->m_pParent = pParent;
				}
				pParent->m_pLeft = pChild;
				pNode->m_pRight = pOld->m_pRight;
				pOld->m_pRight->m_pParent = pNode;
			}
			pNode->m_pParent = pOld->m_pParent;
			pNode->m_bColor = pOld->m_bColor;
			pNode->m_pLeft = pOld->m_pLeft;
			pOld->m_pLeft->m_pParent = pNode;
			goto LABEL;
		}

		pParent = pNode->m_pParent;
		bColor = pNode->m_bColor;
		if (pChild != NULL)
		{
			pChild->m_pParent = pParent;
		}
		if (pParent != NULL)
		{
			if (pParent->m_pLeft == pNode)
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
		FreeNode(pNode);
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RemoveFixup(TinyNode* pNode, TinyNode* pParent)
	{
		TinyNode *pOther = NULL;
		while ((!pNode || !pNode->m_bColor) && pNode != m_pRoot)
		{
			if (pParent->m_pLeft == pNode)
			{
				pOther = pParent->m_pRight;
				if (pOther->m_bColor)
				{
					pOther->m_bColor = FALSE;
					pParent->m_bColor = TRUE;
					RotateL(pParent);
					pOther = pParent->m_pRight;
				}
				if ((!pOther->m_pLeft || !pOther->m_pLeft->m_bColor)
					&& (!pOther->m_pRight || !pOther->m_pRight->m_bColor))
				{
					pOther->m_bColor = TRUE;
					pNode = pParent;
					pParent = pNode->m_pParent;
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
					pNode = m_pRoot;
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
				if ((!pOther->m_pLeft || !pOther->m_pLeft->m_bColor)
					&& (!pOther->m_pRight || !pOther->m_pRight->m_bColor))
				{
					pOther->m_bColor = TRUE;
					pNode = pParent;
					pParent = pNode->m_pParent;
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
					pNode = m_pRoot;
					break;
				}
			}
		}
		if (pNode)
		{
			pNode->m_bColor = FALSE;
		}
	};
	template<class K, class V, class KTraits, class VTraits>
	typename TinyTreeMap<K, V, KTraits, VTraits>::TinyNode* TinyTreeMap<K, V, KTraits, VTraits>::Find(TinyNode* pNode, CONST_KTYPE key)
	{
		while (pNode != NULL && KTraits::Compare(key, pNode->m_key) != 0)
		{
			if (KTraits::Compare(key, pNode->m_key) < 0)
			{
				pNode = pNode->m_pLeft;
			}
			else
			{
				pNode = pNode->m_pRight;
			}
		}
		return pNode;
	};
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RotateL(TinyNode* pNode)
	{
		TinyNode* pRight = pNode->m_pRight;
		TinyNode* pParent = pNode->m_pParent;
		if (pNode->m_pRight = pRight->m_pLeft)
		{
			pRight->m_pLeft->m_pParent = pNode;
		}
		pRight->m_pLeft = pNode;
		pRight->m_pParent = pParent;
		if (pParent != NULL)
		{
			if (pNode == pParent->m_pLeft)
				pParent->m_pLeft = pRight;
			else
				pParent->m_pRight = pRight;
		}
		else
		{
			m_pRoot = pRight;
		}
		pNode->m_pParent = pRight;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RotateR(TinyNode* pNode)
	{
		TinyNode *pLeft = pNode->m_pLeft;
		TinyNode *pParent = pNode->m_pParent;
		if ((pNode->m_pLeft = pLeft->m_pRight))
		{
			pLeft->m_pRight->m_pParent = pNode;
		}
		pLeft->m_pRight = pNode;
		pLeft->m_pParent = pParent;
		if (pParent != NULL)
		{
			if (pNode == pParent->m_pRight)
				pParent->m_pRight = pLeft;
			else
				pParent->m_pLeft = pLeft;
		}
		else
		{
			m_pRoot = pLeft;
		}
		pNode->m_pParent = pLeft;
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyTreeMap<K, V, KTraits, VTraits>::RemovePostOrder(TinyNode* pNode)
	{
		if (pNode == NULL) return;
		RemovePostOrder(pNode->m_pLeft);
		RemovePostOrder(pNode->m_pRight);
		FreeNode(pNode);
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Find(CONST_KTYPE key)
	{
		return static_cast<ITERATOR>(Find(m_pRoot, key));
	}
	template<class K, class V, class KTraits, class VTraits>
	const K& TinyTreeMap<K, V, KTraits, VTraits>::GetKeyAt(ITERATOR pos) const
	{
		ASSERT(pos);
		TinyNode* pNode = static_cast <TinyNode*>(pos);
		return pNode->m_key;
	}
	template<class K, class V, class KTraits, class VTraits>
	const V& TinyTreeMap<K, V, KTraits, VTraits>::GetValueAt(ITERATOR pos) const
	{
		ASSERT(pos);
		TinyNode* pNode = static_cast <TinyNode*>(pos);
		return pNode->m_value;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::First() const
	{
		TinyNode* pNode = NULL;
		pNode = m_pRoot;
		if (!pNode)
			return NULL;
		while (pNode->m_pLeft != NULL)
			pNode = pNode->m_pLeft;
		return pNode;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Last() const
	{
		TinyNode* pNode = NULL;
		pNode = m_pRoot;
		if (!pNode)
			return NULL;
		while (pNode->m_pRight != NULL)
			pNode = pNode->m_pRight;
		return pNode;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Next(ITERATOR pos) const
	{
		TinyNode* pNode = static_cast<TinyNode*>(pos);
		if (pNode->m_pParent == pNode)
			return NULL;
		if (pNode->m_pRight != NULL)
		{
			pNode = pNode->m_pRight;
			while (pNode->m_pLeft != NULL)
				pNode = pNode->m_pLeft;
			return pNode;
		}
		TinyNode* pParent = NULL;
		while ((pParent = pNode->m_pParent) && pNode == pParent->m_pRight)
			pNode = pParent;
		return pParent;
	}
	template<class K, class V, class KTraits, class VTraits>
	ITERATOR TinyTreeMap<K, V, KTraits, VTraits>::Prev(ITERATOR pos) const
	{
		TinyNode* pNode = static_cast<TinyNode*>(pos);
		if (pNode->m_pParent == pNode)
			return NULL;
		if (pNode->m_pLeft != NULL)
		{
			pNode = pNode->m_pLeft;
			while (pNode->m_pRight != NULL)
				pNode = pNode->m_pRight;
			return pNode;
		}
		TinyNode* pParent = NULL;
		while ((pParent = pNode->m_pParent) && pNode == pParent->m_pLeft)
			pNode = pParent;
		return pParent;
	}
	/// <summary>
	/// Prime类
	/// </summary>
	INT primes[] = {
		3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
		1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591,
		17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
		187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
		1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369 };
	class TinyPrime
	{
	public:
		static const INT MaxValue = 0x7FFFFFFF;
		static const INT HashPrime = 101;
		static const int MaxPrimeArrayLength = 0x7FEFFFFD;
	public:
		static BOOL IsPrime(INT candidate);
		static INT GetPrime(INT min);
		static INT GetMinPrime();
		static INT ExpandPrime(INT oldSize);
	};
	/// <summary>
	/// HashMap实现
	/// </summary>
	template<class K, class V, class KTraits = DefaultTraits< K >, class VTraits = DefaultTraits< V >>
	class TinyHashMap
	{
		DISALLOW_COPY_AND_ASSIGN(TinyHashMap)
	protected:
		typedef typename KTraits::CONST_ARGTYPE	CONST_KTYPE;
		typedef typename KTraits::ARGTYPE		KTYPE;
		typedef typename VTraits::CONST_ARGTYPE	CONST_VTYPE;
		typedef typename VTraits::ARGTYPE		VTYPE;
	protected:
		class TinyHashNode :public __ITERATOR
		{
			DISALLOW_COPY_AND_ASSIGN(TinyHashNode)
		public:
			const K			m_key;
			V				m_value;
			INT				m_hashCode;
			INT				m_nextIndex;
		public:
			TinyHashNode(CONST_KTYPE key, VTYPE value)
				: m_key(key),
				m_value(value),
				m_pNext(NULL)
			{
			}
		};
	protected:
		TinyPlex*	m_pBlocks;
		DWORD		m_dwBlockSize;
		DWORD		m_dwCount;
	protected:

	public:
		explicit TinyHashMap(DWORD dwBlockSize = 10);
		~TinyHashMap();
		void RemoveAll();
	};
	template<class K, class V, class KTraits, class VTraits>
	TinyHashMap<K, V, KTraits, VTraits>::TinyHashMap(DWORD dwBlockSize)
		:m_dwBlockSize(dwBlockSize),
		m_dwCount(0),
		m_pBlocks(NULL)
	{

	}
	template<class K, class V, class KTraits, class VTraits>
	TinyHashMap<K, V, KTraits, VTraits>::~TinyHashMap()
	{
		RemoveAll();
	}
	template<class K, class V, class KTraits, class VTraits>
	void TinyHashMap<K, V, KTraits, VTraits>::RemoveAll()
	{
		m_dwCount = 0;
		m_pBlocks->Destory();
		m_pBlocks = NULL;
		m_pFree = NULL;
		m_pRoot = NULL;
	}
}
