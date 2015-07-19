#pragma once
#include "TinyCommon.h"

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
	/// Plex内存池
	/// </summary>
	struct NO_VTABLE TinyPlex
	{
		TinyPlex* nextPtr;
		void* data() { return this + 1; }
		static TinyPlex* PASCAL Create(TinyPlex*& ps, UINT_PTR max, UINT_PTR size);
		void Destory();
	};
	/// <summary>
	/// TreeMap结构红黑树实现
	/// </summary>
	template<class K, class V>
	class TinyTreeMap
	{
		DISALLOW_COPY_AND_ASSIGN(TinyTreeMap)
		class TreeEntry
		{
		public:
			BOOL	   color_;
			K	   key_;
			V     value_;
			TreeEntry* left_;
			TreeEntry* right_;
			TreeEntry* parent_;
		public:
			TreeEntry(K key, V value)
				:left_(NULL),
				right_(NULL),
				parent_(NULL),
				key_(key),
				value_(value),
				color_(FALSE)
			{

			}
		};
	private:
		TreeEntry* root_;
		TinyPlex*  plex_;
	private:
		void RotateL(TreeEntry* node);
		void RotateR(TreeEntry* node);
		void Add(TreeEntry* node);
		void AddFixup(TreeEntry* node);
		void Remove(TreeEntry* node);
		void RemoveFixup(TreeEntry* node, TreeEntry* parent);
		void Destory(TreeEntry* node);
		typename TinyTreeMap<K, V>::TreeEntry* Find(TreeEntry* node, K key);
	public:
		TinyTreeMap();
		~TinyTreeMap();
		void inOrder(TreeEntry* node) const;
		void inOrder() const;
		void Add(K key, V value);
		void Remove(K key);
		V* Lookup(K key);
		void SetValue(K key, V value);
		V* operator[](K key);
	};
	template<class K, class V>
	TinyTreeMap<K, V>::TinyTreeMap()
		:root_(NULL),
		plex_(NULL)
	{

	}
	template<class K, class V>
	TinyTreeMap<K, V>::~TinyTreeMap()
	{
		Destory(root_);
	}

	template<class K, class V>
	void TinyTreeMap<K, V>::inOrder(TreeEntry* node) const
	{
		if (node != NULL)
		{
			inOrder(node->left_);
			TRACE("node key:%d,value:%d\n", node->key_, node->value_);
			inOrder(node->right_);
		}
	}

	template<class K, class V>
	void TinyTreeMap<K, V>::inOrder() const
	{
		inOrder(root_);
	}

	template<class K, class V>
	void TinyTreeMap<K, V>::Add(K key, V value)
	{
		TreeEntry* entry = new TreeEntry(key, value);
		if (entry != NULL)
		{
			Add(entry);
		}
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::Remove(K key)
	{
		TreeEntry* node = Find(root_, key);
		if (node != NULL)
		{
			Remove(node);
		}
	}
	template<class K, class V>
	V* TinyTreeMap<K, V>::Lookup(K key)
	{
		TreeEntry* node = Find(root_, key);
		if (node != NULL)
		{
			return node->value_;
		}
	}
	template<class K, class V>
	V* TinyTreeMap<K, V>::operator[](K key)
	{
		TreeEntry* node = Find(root_, key);
		if (node != NULL)
		{
			return node->value_;
		}
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::SetValue(K key, V value)
	{
		TreeEntry* node = Find(root_, key);
		if (node != NULL)
		{
			node->value_ = value;
		}
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::Add(TreeEntry* node)
	{
		TreeEntry* x = this->root_;
		TreeEntry* y = NULL;
		while (x != NULL)
		{
			y = x;
			//重复的不处理
			if (node->key_ == x->key_)
			{
				return;
			}
			if (node->key_ < x->key_)
			{
				x = x->left_;
			}
			else
			{
				x = x->right_;
			}
		}
		node->parent_ = y;
		if (y != NULL)
		{
			//重复的不处理
			if (node->key_ == y->key_)
			{
				return;
			}

			if (node->key_ < y->key_)
			{
				y->left_ = node;
			}
			else
			{
				y->right_ = node;
			}
		}
		else
		{
			root_ = node;
		}
		node->color_ = TRUE;
		AddFixup(node);
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::AddFixup(TreeEntry* node)
	{
		TreeEntry *parent = NULL;
		TreeEntry *gparent = NULL;
		while ((parent = node->parent_) && parent->color_)
		{
			gparent = parent->parent_;
			if (parent == gparent->left_)
			{
				TreeEntry *uncle = gparent->right_;
				if (uncle && uncle->color_)
				{
					uncle->color_ = FALSE;
					parent->color_ = FALSE;
					gparent->color_ = TRUE;
					node = gparent;
					continue;
				}
				if (parent->right_ == node)
				{
					TreeEntry *ps = NULL;
					RotateL(parent);
					ps = parent;
					parent = node;
					node = ps;
				}
				parent->color_ = FALSE;
				gparent->color_ = TRUE;
				RotateR(gparent);
			}
			else
			{
				TreeEntry *uncle = gparent->left_;
				if (uncle && uncle->color_)
				{
					uncle->color_ = FALSE;
					parent->color_ = FALSE;
					gparent->color_ = TRUE;
					node = gparent;
					continue;
				}
				if (parent->left_ == node)
				{
					TreeEntry *ps = NULL;
					RotateR(parent);
					ps = parent;
					parent = node;
					node = ps;
				}
				parent->color_ = FALSE;
				gparent->color_ = TRUE;
				RotateL(gparent);
			}
		}
		root_->color_ = FALSE;
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::Remove(TreeEntry* node)
	{
		TreeEntry *child = NULL;
		TreeEntry *parent = NULL;
		BOOL color = FALSE;
		if (!node->left_)
		{
			child = node->right_;
		}
		else if (!node->right_)
		{
			child = node->left_;
		}
		else
		{
			TreeEntry *old = node;
			TreeEntry *left = NULL;
			node = node->right_;
			while ((left = node->left_) != NULL)
			{
				node = left;
			}
			if (old->parent_)
			{
				if (old->parent_->left_ == old)
				{
					old->parent_->left_ = node;
				}
				else
				{
					old->parent_->right_ = node;
				}
			}
			else
			{
				root_ = node;
			}
			child = node->right_;
			parent = node->parent_;
			color = node->color_;
			if (parent == old)
			{
				parent = node;
			}
			else
			{
				if (child)
				{
					child->parent_ = parent;
				}
				parent->left_ = child;

				node->right_ = old->right_;
				old->right_->parent_ = node;
			}
			node->parent_ = old->parent_;
			node->color_ = old->color_;
			node->left_ = old->left_;
			old->left_->parent_ = node;
			goto color;
		}

		parent = node->parent_;
		color = node->color_;
		if (child)
		{
			child->parent_ = parent;
		}
		if (parent)
		{
			if (parent->left_ == node)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		else
		{
			root_ = child;
		}
	color:
		if (color == FALSE)
		{
			RemoveFixup(child, parent);
		}
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::RemoveFixup(TreeEntry* node, TreeEntry* parent)
	{
		TreeEntry *other = NULL;
		while ((!node || !node->color_)
			&& node != root_)
		{
			if (parent->left_ == node)
			{
				other = parent->right_;
				if (other->color_)
				{
					other->color_ = FALSE;
					parent->color_ = TRUE;
					RotateL(parent);
					other = parent->right_;
				}
				if ((!other->left_ || !other->left_->color_)
					&& (!other->right_ || !other->right_->color_))
				{
					other->color_ = TRUE;
					node = parent;
					parent = node->parent_;
				}
				else
				{
					if (!other->right_ || !other->right_->color_)
					{
						other->left_->color_ = FALSE;
						other->color_ = TRUE;
						RotateR(other);
						other = parent->right_;
					}
					other->color_ = parent->color_;
					parent->color_ = FALSE;
					other->right_->color_ = FALSE;
					RotateL(parent);
					node = root_;
					break;
				}
			}
			else
			{
				other = parent->left_;
				if (other->color_)
				{
					other->color_ = FALSE;
					parent->color_ = TRUE;
					RotateR(parent);
					other = parent->left_;
				}
				if ((!other->left_ || !other->left_->color_)
					&& (!other->right_ || !other->right_->color_))
				{
					other->color_ = TRUE;
					node = parent;
					parent = node->parent_;
				}
				else
				{
					if (!other->left_ || !other->left_->color_)
					{
						other->right_->color_ = FALSE;
						other->color_ = TRUE;
						RotateL(other);
						other = parent->left_;
					}
					other->color_ = parent->color_;
					parent->color_ = FALSE;
					other->left_->color_ = FALSE;
					RotateR(parent);
					node = root_;
					break;
				}
			}
		}
		if (node)
		{
			node->color_ = FALSE;
		}
	};
	template<class K, class V>
	typename TinyTreeMap<K, V>::TreeEntry* TinyTreeMap<K, V>::Find(TreeEntry* node, K key)
	{
		while (node != NULL &&  node->key_ != key)
		{
			if (key < node->key_)
			{
				node = node->left_;
			}
			else
			{
				node = node->right_;
			}
		}
		return node;
	};
	template<class K, class V>
	void TinyTreeMap<K, V>::RotateL(TreeEntry* node)
	{
		TreeEntry* right = node->right_;
		TreeEntry* parent = node->parent_;
		if (node->right_ = right->left_)
		{
			right->left_->parent_ = node;
		}
		right->left_ = node;
		right->parent_ = parent;
		if (parent)
		{
			if (node == parent->left_)
			{
				parent->left_ = right;
			}
			else
			{
				parent->right_ = right;
			}
		}
		else
		{
			root_ = right;
		}
		node->parent_ = right;
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::RotateR(TreeEntry* node)
	{
		TreeEntry *left = node->left_;
		TreeEntry *parent = node->parent_;
		if ((node->left_ = left->right_))
		{
			left->right_->parent_ = node;
		}
		left->right_ = node;
		left->parent_ = parent;
		if (parent)
		{
			if (node == parent->right_)
			{
				parent->right_ = left;
			}
			else
			{
				parent->left_ = left;
			}
		}
		else
		{
			root_ = left;
		}
		node->parent_ = left;
	}
	template<class K, class V>
	void TinyTreeMap<K, V>::Destory(TreeEntry* node)
	{
		if (node == NULL) return;
		if (node->left_ != NULL)
			return Destory(node->left_);
		if (node->right_ != NULL)
			return Destory(node->right_);
		SAFE_DELETE(node);
	}
}
