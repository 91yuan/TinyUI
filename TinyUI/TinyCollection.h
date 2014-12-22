#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	template<class T>
	class TinyPlaceNew
	{
	public:
		TinyPlaceNew(_In_ const T& _myT) :
			m_myT(_myT)
		{
		}
		template <class _Ty>
		void * __cdecl operator new(_In_ size_t, _In_ _Ty* p)
		{
			return p;
		}
		template <class _Ty>
		void __cdecl operator delete(_In_ void*, _In_ _Ty*)
		{
		}
		T m_myT;
	};

	/// <summary>
	/// 简单的Map, Key-Value一一对应,没存中对齐排列
	/// <summary>
	template<class K, class V>
	class TinyMap
	{
	public:
		TinyMap();
		~TinyMap();
		BOOL Add(const K& myKey, const V& myValue);
		BOOL Remove(const K& myKey);
		BOOL RemoveAt(INT index);
		void RemoveAll();
		INT	 GetSize() const;
		INT	 FindKey(const K& myKey) const;
		INT  FindValue(const V& myValue) const;
		K&	 GetKeyAt(INT index);
		V&	 GetValueAt(INT index);
		V	 Lookup(const K& key) const;
		const V& operator[](const K& myKey);
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
	BOOL TinyMap<K, V>::Add(const K& myKey, const V& myValue)
	{
		K* _myKey = NULL;
		_myKey = (K*)_recalloc(m_myKey, m_size + 1, sizeof(K));
		if (_myKey == NULL)
			return FALSE;
		m_myKey = _myKey;
		new(m_myKey + m_size) TinyPlaceNew<K>(myKey);

		V* _myValue = NULL;
		_myValue = (V*)_recalloc(m_myValue, m_size + 1, sizeof(V));
		if (_myValue == NULL)
			return FALSE;
		m_myValue = _myValue;
		new(m_myValue + m_size) TinyPlaceNew<V>(myValue);

		m_size++;

		return TRUE;
	}
	template<class K, class V>
	BOOL TinyMap<K, V>::Remove(const K& myKey)
	{
		INT index = FindKey(myKey);
		if (index < 0) return FALSE;
		return RemoveAt(index);
	}
	template<class K, class V>
	INT TinyMap<K, V>::FindKey(const K& myKey) const
	{
		for (INT i = 0; i < m_size; i++)
		{
			if (m_myKey[i] == myKey)
				return i;
		}
		return -1;
	}
	template<class K, class V>
	INT TinyMap<K, V>::FindValue(const V& myValue) const
	{
		for (INT i = 0; i < m_size; i++)
		{
			if (m_myValue[i] == myValue)
				return i;
		}
		return -1;
	}
	template<class K, class V>
	V TinyMap<K, V>::Lookup(const K& key) const
	{
		INT index = FindKey(key);
		if (index < 0) return NULL;
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
			return FALSE;
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
			m_myKey = myKey;
		V* myValue;
		myValue = (V*)_recalloc(m_myValue, (m_size - 1), sizeof(V));
		if (myValue != NULL || m_size == 1)
			m_myValue = myValue;
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
			free(m_myKey);
			m_myKey = NULL;
		}
		if (m_myValue != NULL)
		{
			free(m_myValue);
			m_myValue = NULL;
		}
		m_size = 0;
	}
	template<class K, class V>
	const V& TinyMap<K, V>::operator[](const K& myKey)
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
		INT size = myT.GetSize()
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
				RemoveAt(i - 1);
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
				return FALSE;
			m_alloc_size = size;
			m_value = _myP;
		}
		new(m_value + m_size) TinyPlaceNew<T>(myT);
		m_size++;
		return TRUE;
	}
	template<class T>
	BOOL TinyArray<T>::Remove(const T& myT)
	{
		INT index = Lookup(myT);
		if (index == -1)
			return FALSE;
		return RemoveAt(index);
	}
	template<class T>
	BOOL TinyArray<T>::RemoveAt(INT index)
	{
		if (index < 0 || index >= m_size)
			return FALSE;
		m_value[index].~T();
		if (index != (m_size - 1))
		{
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
			free(m_value);
			m_value = NULL;
		}
		m_size = 0;
		m_alloc_size = 0;
	}
	template<class T>
	INT	TinyArray<T>::Lookup(const T& myT) const
	{
		for (INT i = 0; i < m_size; i++)
		{
			if (m_value[i] == myT)
				return i;
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
	/// 智能指针
	/// <summary>
	template<class T>
	class SmartPtr
	{
	public:
		explicit SmartPtr(T* myP = NULL);
		explicit SmartPtr(SmartPtr<T>& myP);//拷贝构造函数可以不加const
		~SmartPtr();
		operator T*() const;
		SmartPtr<T>& operator = (SmartPtr<T>& myP);
		T*	operator->() const;
		T&	operator*() const;
		T*	Release();
		void Reset(T* _ptr);
	private:
		T* _myP;
	};
	template<typename T>
	SmartPtr<T>::SmartPtr(T* myP)
		:_myP(myP)
	{

	}
	template<class T>
	SmartPtr<T>::SmartPtr(SmartPtr<T>& myP)
		: _myP(myP.Release())
	{

	}
	template<class T>
	SmartPtr<T>::~SmartPtr()
	{
		if (_myP != NULL)
		{
			delete _myP;
			_myP = NULL;
		}
	}
	template<class T>
	T*	SmartPtr<T>::Release()
	{
		T* ps = _myP;
		_myP = NULL;
		return ps;
	}
	template<class T>
	void SmartPtr<T>::Reset(T* _ptr)
	{
		if (_ptr != _myP)
		{
			delete _myP;
			_myP = NULL;
		}
		_myP = _ptr;
	}
	template<class T>
	SmartPtr<T>::operator T*() const
	{
		return _myP;
	}
	template<class T>
	T* SmartPtr<T>::operator->() const
	{
		return _myP;
	}
	template<class T>
	T& SmartPtr<T>::operator*() const
	{
		if (_myP == NULL)
			throw("_myP is null!");
		return *_myP;
	}
	template<class T>
	SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr<T>& myP)
	{
		Reset(myP.Release());
		return (*this);
	}
	/// <summary>
	/// COM指针
	/// <summary>
	template<class T>
	class ComPtr
	{
	public:
		ComPtr(T* myP = NULL);
		ComPtr(const ComPtr<T>& myP);
		~ComPtr();
		void Release();
		operator T*() const;
		T** operator&();
		T* operator->();
		T* operator=(T* myP);
		T* operator=(const ComPtr<T>& myP);
		T* _myP;
	};
	template<class T>
	ComPtr<T>::ComPtr(T* myP)
	{
		if ((_myP = myP) != NULL)
		{
			_myP->AddRef();
		}
	}
	template<class T>
	ComPtr<T>::ComPtr(const ComPtr<T>& myP)
	{
		if ((_myP = myP._myP) != NULL)
		{
			_myP->AddRef();
		}
	}
	template<class T>
	void ComPtr<T>::Release()
	{
		if (_myP != NULL)
		{
			_myP->Release();
			_myP = NULL;
		}
	}
	template<class T>
	ComPtr<T>::operator T *() const
	{
		return (T*)_myP;
	}
	template<class T>
	T* ComPtr<T>::operator->()
	{
		return (T*)_myP;
	}
	template<class T>
	T** ComPtr<T>::operator&()
	{
		if (_myP == NULL)
			throw("_myP is null");
		return &_myP;
	}
	template<class T>
	T*	ComPtr<T>::operator=(T* myP)
	{
		return (T*)ComPtrAssign((IUnknown**)&_myP, myP);
	}
	template<class T>
	T* ComPtr<T>::operator=(const ComPtr<T>& myP)
	{
		return (T*)ComPtrAssign((IUnknown**)&_myP, myP._myP);
	}
	template<class T>
	ComPtr<T>::~ComPtr()
	{
		Release();
	}
}
