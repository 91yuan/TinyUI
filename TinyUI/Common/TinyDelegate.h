#pragma once
#include "TinyCollection.h"
#include <memory>

namespace TinyUI
{
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// emplate_class< type( type1, type2, ... ) > a_class;
	/// http://blog.csdn.net/pongba/article/details/1560773
	/// C++ 类型擦除 类似boost::any, 参考了Loki库实现
	/// 模板R(T1,T2,...)函数类型退化成函数指针
	/// 仿函数基类
	/// </summary>
	template<typename R>
	class FunctorBase
	{
	public:
		typedef FunctorBase<R>	SelfType;
		typedef R				ReturnType;
		typedef NullType		A1Type;
		typedef NullType		A2Type;
		typedef NullType		A3Type;
		typedef NullType		A4Type;
	public:
		FunctorBase() = default;
		FunctorBase(const FunctorBase&) = default;
		FunctorBase& operator=(const FunctorBase&) = default;
		virtual ~FunctorBase(){};
	public:
		virtual FunctorBase* DoClone() const = 0;
		virtual BOOL operator==(const FunctorBase&) const = 0;
	public:
		template <class U>
		static U* Clone(U* pObj)
		{
			if (!pObj) return 0;
			U* pClone = static_cast<U*>(pObj->DoClone());
			assert(typeid(*pClone) == typeid(*pObj));
			return pClone;
		}
	};
	/// <summary>
	/// 仿函数实现类
	/// </summary>
	template<typename R, typename TList>
	class Functor;
	template<typename R>
	class Functor<R, TYPE_LIST0()> : public FunctorBase < R >
	{
	public:
		typedef R	ReturnType;
		virtual R operator()() = 0;
	};
	template <typename R, typename A1>
	class Functor<R, TYPE_LIST1(A1)> : public FunctorBase < R >
	{
	public:
		typedef R	ReturnType;
		typedef A1  A1Type;
		virtual R operator()(A1) = 0;
	};
	template <typename R, typename A1, typename A2>
	class Functor<R, TYPE_LIST2(A1, A2)> : public FunctorBase < R >
	{
	public:
		typedef R	ReturnType;
		typedef A1  A1Type;
		typedef A2  A2Type;
		virtual R operator()(A1, A2) = 0;
	};
	template <typename R, typename A1, typename A2, typename A3>
	class Functor<R, TYPE_LIST3(A1, A2, A3)> : public FunctorBase < R >
	{
	public:
		typedef R	ReturnType;
		typedef A1  A1Type;
		typedef A2  A2Type;
		typedef A3  A3Type;
		virtual R operator()(A1, A2, A3) = 0;
	};
	template <typename R, typename A1, typename A2, typename A3, typename A4>
	class Functor<R, TYPE_LIST4(A1, A2, A3, A4)> : public FunctorBase < R >
	{
	public:
		typedef R	ReturnType;
		typedef A1  A1Type;
		typedef A2  A2Type;
		typedef A3  A3Type;
		typedef A4  A4Type;
		virtual R operator()(A1, A2, A3, A4) = 0;
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename R, typename TList, typename FunctionType, typename InstanceType, typename Placeholder>
	class Function;
	template<typename R, typename TList, typename FunctionType>
	class Function<R, TList, FunctionType, TYPE_LIST0(), TYPE_LIST0()> : public Functor < R, TList >
	{
	public:
		typedef Functor<R, TList> FunctorType;
		typedef typename FunctorType::ReturnType	ReturnType;
		typedef typename FunctorType::A1Type		A1Type;
		typedef typename FunctorType::A2Type		A2Type;
		typedef typename FunctorType::A3Type		A3Type;
		typedef typename FunctorType::A4Type		A4Type;
	public:
		Function(const FunctionType& fType)
			: m_fType(fType)
		{

		}
		Function(const Function& other)
			:m_fType(other.m_fType)
		{
		}
		Function& operator = (const Function& other)
		{
			if (&other != this)
			{
				m_fType = other.m_fType;
			}
			return *this;
		}
		virtual Function* DoClone() const
		{
			return new Function(*this);
		}
	public:
		BOOL operator==(const typename FunctorType::SelfType& fType) const
		{
			if (typeid(*this) != typeid(fType))
			{
				return FALSE;
			}
			const Function& s = static_cast<const Function&>(fType);
			return  m_fType == s.m_fType;
		}
		ReturnType operator()()
		{
			return m_fType();
		}
		ReturnType operator()(A1Type p1)
		{
			return m_fType(p1);
		}
		ReturnType operator()(A1Type p1, A2Type p2)
		{
			return m_fType(p1, p2);
		}
		ReturnType operator()(A1Type p1, A2Type p2, A3Type p3)
		{
			return m_fType(p1, p2, p3);
		}
		ReturnType operator()(A1Type p1, A2Type p2, A3Type p3, A4Type p4)
		{
			return m_fType(p1, p2, p3, p4);
		}
	private:
		FunctionType m_fType;
	};
	/// <summary>
	/// 成员函数
	/// </summary>
	template <typename R, typename TList, typename InstanceType, typename FunctionType>
	class Function<R, TList, InstanceType, FunctionType, TYPE_LIST0()> : public Functor < R, TList >
	{
	public:
		typedef Functor<R, TList> FunctorType;
		typedef typename FunctorType::ReturnType	ReturnType;
		typedef typename FunctorType::A1Type		A1Type;
		typedef typename FunctorType::A2Type		A2Type;
		typedef typename FunctorType::A3Type		A3Type;
		typedef typename FunctorType::A4Type		A4Type;
	public:
		Function(const InstanceType& iType, FunctionType mType)
			: m_iType(iType), m_mType(mType)

		{
		}
		Function(const Function& other)
			:m_iType(other.m_iType), m_mType(other.m_mType)
		{
		}
		Function& operator = (const Function& other)
		{
			if (&other != this)
			{
				m_fType = other.m_fType;
				m_iType = other.m_iType;
			}
			return *this;
		}
		virtual Function* DoClone() const
		{
			return new Function(*this);
		}
	public:
		BOOL operator==(const typename FunctorType::SelfType& fType) const
		{
			if (typeid(*this) != typeid(fType))
			{
				return FALSE;
			}
			const Function& s = static_cast<const Function&>(fType);
			return  m_iType == s.m_iType && m_mType == s.m_mType;
		}
		ReturnType operator()()
		{
			return ((*m_iType).*m_mType)();
		}
		ReturnType operator()(A1Type p1)
		{
			return ((*m_iType).*m_mType)(p1);
		}
		ReturnType operator()(A1Type p1, A2Type p2)
		{
			return ((*m_iType).*m_mType)(p1, p2);
		}
		ReturnType operator()(A1Type p1, A2Type p2, A3Type p3)
		{
			return ((*m_iType).*m_mType)(p1, p2, p3);
		}
		ReturnType operator()(A1Type p1, A2Type p2, A3Type p3, A4Type p4)
		{
			return ((*m_iType).*m_mType)(p1, p2, p3, p4);
		}
	private:
		InstanceType	m_iType;
		FunctionType	m_mType;
	};
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 实现委托类型擦除器
	/// </summary>
	template <typename R = void, typename TList = NullType>
	class DelegateBase
	{
	public:
		typedef R								ReturnType;
		typedef Functor<R, TList>				FunctorType;
		typedef typename FunctorType::A1Type	A1Type;
		typedef typename FunctorType::A2Type	A2Type;
		typedef typename FunctorType::A3Type	A3Type;
		typedef typename FunctorType::A4Type	A4Type;
	public:
		DelegateBase()
			:m_my(NULL)
		{

		}
		DelegateBase(const DelegateBase& db)
			:m_my(FunctorType::Clone(db.m_my.Ptr()))
		{
		}
		DelegateBase& operator=(const DelegateBase& other)
		{
			if (&other != this)
			{
				DelegateBase copy(other);
				FunctorType* ps = m_my.Release();
				m_my.Reset(copy.m_my.Release());
				copy.m_my.Reset(ps);
			}
			return *this;
		}
		/// <summary>
		/// 普通函数类型
		/// </summary>
		template <typename FunctionType>
		DelegateBase(FunctionType fType)
			: m_my(new Function<R, TList, FunctionType, TYPE_LIST0(), TYPE_LIST0()>(fType))
		{

		}
		/// <summary>
		/// 成员函数类型
		/// </summary>
		template <class InstanceType, typename FunctionType>
		DelegateBase(const InstanceType& iType, FunctionType mType)
			: m_my(new Function<R, TList, InstanceType, FunctionType, TYPE_LIST0()>(iType, mType))
		{

		}
		/// <summary>
		/// 绑定普通函数
		/// </summary>
		template <typename FunctionType>
		void BindDelegate(FunctionType fType)
		{
			m_my.Reset(new Function<R, TList, FunctionType, TYPE_LIST0(), TYPE_LIST0()>(fType));
		}
		/// <summary>
		/// 绑定成员函数
		/// </summary>
		template <class InstanceType, typename FunctionType>
		void BindDelegate(const InstanceType& iType, FunctionType mType)
		{
			m_my.Reset(new Function<R, TList, InstanceType, FunctionType, TYPE_LIST0()>(iType, mType));
		}
		/// <summary>
		/// 判断是都为空
		/// </summary>
		BOOL IsEmpty() const
		{
			return m_my.Ptr() == NULL;
		}
		/// <summary>
		/// 释放
		/// </summary>
		void Release()
		{
			m_my.Reset(NULL);
		}
	public:
		BOOL operator==(const DelegateBase& other) const
		{
			if (m_my.Ptr() == NULL && other.m_my.Ptr() == NULL)
			{
				return TRUE;
			}
			if (m_my.Ptr() != NULL && other.m_my.Ptr() != NULL)
			{
				return (*m_my.Ptr()) == *(other.m_my.Ptr());
			}
			return FALSE;
		}
		BOOL operator!=(const DelegateBase& other) const
		{
			return !(*this == other);
		}
		ReturnType operator()() const
		{
			return (*m_my)();
		}
		ReturnType operator()(A1Type p1) const
		{
			return (*m_my)(p1);
		}
		ReturnType operator()(A1Type p1, A2Type p2) const
		{
			return (*m_my)(p1, p2);
		}
		ReturnType operator()(A1Type p1, A2Type p2, A3Type p3) const
		{
			return (*m_my)(p1, p2, p3);
		}
		ReturnType operator()(A1Type p1, A2Type p2, A3Type p3, A4Type p4) const
		{
			return (*m_my)(p1, p2, p3, p4);
		}
	private:
		TinyAutoPtr<FunctorType>	m_my;
	};
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 委托类
	/// </summary>
	template<typename R = void>
	class Delegate;
	template<typename R>
	class Delegate<R()> : public DelegateBase < R, TYPE_LIST0() >
	{
	public:
		typedef DelegateBase<R, TYPE_LIST0()> BaseType;
		Delegate() : BaseType()
		{
		}
		Delegate(const Delegate& os) : BaseType()
		{
			if (!os.IsEmpty())
			{
				BaseType::operator=(os);
			}
		}
		template<class FunctionType>
		Delegate(FunctionType fType) : BaseType(fType)
		{
		}
		template<class InstanceType, class FunctionType>
		Delegate(const InstanceType& iType, const FunctionType& fType) : BaseType(iType, fType)
		{
		}
	};
	template<typename R, typename P1>
	class Delegate<R(P1)> :public DelegateBase < R, TYPE_LIST1(P1) >
	{
	public:
		typedef DelegateBase<R, TYPE_LIST1(P1)> BaseType;
		Delegate() : BaseType()
		{
		}
		Delegate(const Delegate& os) : BaseType()
		{
			if (!os.IsEmpty())
			{
				BaseType::operator=(os);
			}
		}
		template<class FunctionType>
		Delegate(FunctionType fType) : BaseType(fType)
		{
		}
		template<class InstanceType, class FunctionType>
		Delegate(const InstanceType& iType, const FunctionType& fType) : BaseType(iType, fType)
		{
		}
	};
	template<typename R, typename P1, typename P2>
	class Delegate<R(P1, P2)> :public DelegateBase < R, TYPE_LIST2(P1, P2) >
	{
	public:
		typedef DelegateBase<R, TYPE_LIST2(P1, P2)> BaseType;
		Delegate() : BaseType()
		{
		}
		Delegate(const Delegate& os) : BaseType()
		{
			if (!os.IsEmpty())
			{
				BaseType::operator=(os);
			}
		}
		template<class FunctionType>
		Delegate(FunctionType fType) : BaseType(fType)
		{
		}
		template<class InstanceType, class FunctionType>
		Delegate(const InstanceType& iType, const FunctionType& fType) : BaseType(iType, fType)
		{
		}
	};
	template<typename R, typename P1, typename P2, typename P3>
	class Delegate<R(P1, P2, P3)> :public DelegateBase < R, TYPE_LIST3(P1, P2, P3) >
	{
	public:
		typedef DelegateBase<R, TYPE_LIST3(P1, P2, P3)> BaseType;
		Delegate() : BaseType()
		{
		}
		Delegate(const Delegate& os) : BaseType()
		{
			if (!os.IsEmpty())
			{
				BaseType::operator=(os);
			}
		}
		template<class FunctionType>
		Delegate(FunctionType fType) : BaseType(fType)
		{
		}
		template<class InstanceType, class FunctionType>
		Delegate(const InstanceType& iType, const FunctionType& fType) : BaseType(iType, fType)
		{
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class Delegate<R(P1, P2, P3, P4)> : public DelegateBase < R, TYPE_LIST4(P1, P2, P3, P4) >
	{
	public:
		typedef DelegateBase<R, TYPE_LIST4(P1, P2, P3, P4)> BaseType;
		Delegate() : BaseType()
		{
		}
		Delegate(const Delegate& os) : BaseType()
		{
			if (!os.IsEmpty())
			{
				BaseType::operator=(os);
			}
		}
		template<class FunctionType>
		Delegate(FunctionType fType) : BaseType(fType)
		{
		}
		template<class InstanceType, class FunctionType>
		Delegate(const InstanceType& iType, const FunctionType& fType) : BaseType(iType, fType)
		{
		}
	};
};

