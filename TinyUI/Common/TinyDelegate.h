#pragma once
#include "TinyCollection.h"
#include <memory>

namespace TinyUI
{
	/// <summary>
	/// 占位符空类型
	/// </summary>
	class NullType {};
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
	template<typename T>
	struct IsVoidType
	{
		enum{ Result = 0 };
	};
	template<>
	struct IsVoidType<void>
	{
		enum{ Result = 1 };
	};
	template<typename T>
	struct IsBoolType
	{
		enum{ Result = 0 };
	};
	template<>
	struct IsBoolType<bool>
	{
		enum{ Result = 1 };
	};
	template <typename T>
	struct IsReference
	{
		enum{ Result = 0 };
	};
	template <typename T>
	struct IsReference<T&>
	{
		enum{ Result = 1 };
	};
	template <typename T>
	struct IsPointer
	{
		enum { Result = 0 };
	};
	template <class T>
	struct IsPointer<T*>
	{
		enum { Result = 1 };
	};
	template <class T>
	struct IsPointer<T*&>
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsFunctionPointer
	{
		enum{ Result = 0 };
	};
	template <typename T>
	struct IsFunctionPointer<T(*)()>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01>
	struct IsFunctionPointer<T(*)(P01)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02>
	struct IsFunctionPointer<T(*)(P01, P02)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03>
	struct IsFunctionPointer<T(*)(P01, P02, P03)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03, typename P04>
	struct IsFunctionPointer<T(*)(P01, P02, P03, P04)>
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsFunctionPointer<T(*)(...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01>
	struct IsFunctionPointer<T(*)(P01, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02>
	struct IsFunctionPointer<T(*)(P01, P02, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03>
	struct IsFunctionPointer<T(*)(P01, P02, P03, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03, typename P04>
	struct IsFunctionPointer<T(*)(P01, P02, P03, P04, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsMemberFunctionPointer
	{
		enum{ Result = 0 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)()>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer<T(S::*)(P01)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03, P04)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)(...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer<T(S::*)(P01, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03, P04, ...)>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)() const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer<T(S::*)(P01) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03, P04) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer<T(S::*)(...) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer<T(S::*)(P01, ...) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, ...) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03, ...) const>
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer<T(S::*)(P01, P02, P03, P04, ...) const>
	{
		enum { Result = 1 };
	};

	template<typename T>
	struct IsArrayType
	{
		enum { Result = 0 };
	};
	template<typename T>
	struct IsArrayType<T[]>
	{
		enum { Result = 1 };
	};
	template<typename T, size_t n>
	struct IsArrayType<T[n]>
	{
		enum { Result = 1 };
	};

#define TYPE_LIST0() NullType
#define TYPE_LIST1(P1) TypeList<P1, NullType>
#define TYPE_LIST2(P1, P2) TypeList<P1, TYPE_LIST1(P2)>
#define TYPE_LIST3(P1, P2, P3) TypeList<P1, TYPE_LIST2(P2, P3)>
#define TYPE_LIST4(P1, P2, P3, P4) TypeList<P1, TYPE_LIST3(P2, P3, P4)>
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// emplate_class< type( type1, type2, ... ) > a_class;
	/// http://blog.csdn.net/pongba/article/details/1560773
	/// C++ 类型擦除 类似boost::any, 参考了Loki库实现
	/// 模板R(T1,T2,...)函数类型退化成函数指针
	/// </summary>
	template<typename R>
	class DelegateImplBase
	{
	public:
		typedef DelegateImplBase<R> ImplType;
		typedef R ReturnType;
		typedef NullType Arg1;
		typedef NullType Arg2;
		typedef NullType Arg3;
		typedef NullType Arg4;

		DelegateImplBase(){};
		virtual ~DelegateImplBase(){};
		virtual DelegateImplBase* DoClone() const = 0;
		virtual BOOL operator==(const DelegateImplBase&) const = 0;

		template <class U>
		static U* Clone(U* pObj)
		{
			if (!pObj) return 0;
			U* pClone = static_cast<U*>(pObj->DoClone());
			assert(typeid(*pClone) == typeid(*pObj));
			return pClone;
		}
	};
	template<typename R, typename TList>
	class DelegateImpl;
	template<typename R>
	class DelegateImpl<R, TYPE_LIST0()> : public DelegateImplBase<R>
	{
	public:
		typedef R ReturnType;
		virtual R operator()() = 0;
	};
	template <typename R, typename P1>
	class DelegateImpl<R, TYPE_LIST1(P1)>: public DelegateImplBase<R>
	{
	public:
		typedef R ReturnType;
		typedef typename P1 Arg1;
		virtual R operator()(Arg1) = 0;
	};
	template <typename R, typename P1, typename P2>
	class DelegateImpl<R, TYPE_LIST2(P1, P2)>: public DelegateImplBase<R>
	{
	public:
		typedef R ReturnType;
		typedef typename P1 Arg1;
		typedef typename P2 Arg2;
		virtual R operator()(Arg1, Arg2) = 0;
	};
	template <typename R, typename P1, typename P2, typename P3>
	class DelegateImpl<R, TYPE_LIST3(P1, P2, P3)>: public DelegateImplBase<R>
	{
	public:
		typedef R ReturnType;
		typedef typename P1 Arg1;
		typedef typename P2 Arg2;
		typedef typename P3 Arg3;
		virtual R operator()(Arg1, Arg2, Arg3) = 0;
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4>
	class DelegateImpl<R, TYPE_LIST4(P1, P2, P3, P4)>: public DelegateImplBase<R>
	{
	public:
		typedef R ReturnType;
		typedef typename P1 Arg1;
		typedef typename P2 Arg2;
		typedef typename P3 Arg3;
		typedef typename P4 Arg4;
		virtual R operator()(Arg1, Arg2, Arg3, Arg4) = 0;
	};
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 普通函数
	/// </summary>
	template<typename R, typename TList, typename FunctionType>
	class Function1 : public DelegateImpl<R, TList>
	{
	public:
		typedef DelegateImpl<R, TList> BaseType;//基类类型
		typedef typename BaseType::ReturnType ReturnType;
		typedef typename BaseType::Arg1 Arg1;
		typedef typename BaseType::Arg2 Arg2;
		typedef typename BaseType::Arg3 Arg3;
		typedef typename BaseType::Arg4 Arg4;

		Function1(const FunctionType& fType)
			: m_fType(fType)
		{

		}
		Function1(const Function1& _other)
			:m_fType(_other.m_fType)
		{

		}
		virtual Function1* DoClone() const
		{
			return new Function1(*this);
		}

		BOOL operator==(const typename BaseType::ImplType& implType) const
		{
			if (typeid(*this) != typeid(implType))
			{
				return FALSE;
			}

			const Function1& s = static_cast<const Function1&>(implType);
			return  m_fType == s.m_fType;
		}

		ReturnType operator()()
		{
			return m_fType();
		}
		ReturnType operator()(Arg1 p1)
		{
			return m_fType(p1);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2)
		{
			return m_fType(p1, p2);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2, Arg3 p3)
		{
			return m_fType(p1, p2, p3);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2, Arg3 p3, Arg4 p4)
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
	class Function2 : public DelegateImpl<R, TList>
	{
	public:
		typedef DelegateImpl<R, TList> BaseType;//基类类型
		typedef typename BaseType::ReturnType ReturnType;
		typedef typename BaseType::Arg1 Arg1;
		typedef typename BaseType::Arg2 Arg2;
		typedef typename BaseType::Arg3 Arg3;
		typedef typename BaseType::Arg4 Arg4;

		Function2(const InstanceType& iType, FunctionType mType)
			: m_iType(iType), m_mType(mType)

		{
		}
		Function2(const Function2& f2)
			:m_iType(f2.m_iType), m_mType(f2.m_mType)
		{
		}
		virtual Function2* DoClone() const
		{
			return new Function2(*this);
		}
		BOOL operator==(const typename BaseType::ImplType& implType) const
		{
			if (typeid(*this) != typeid(implType))
			{
				return FALSE;
			}
			const Function2& s = static_cast<const Function2&>(implType);
			return  m_iType == s.m_iType && m_mType == s.m_mType;
		}

		ReturnType operator()()
		{
			return ((*m_iType).*m_mType)();
		}
		ReturnType operator()(Arg1 p1)
		{
			return ((*m_iType).*m_mType)(p1);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2)
		{
			return ((*m_iType).*m_mType)(p1, p2);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2, Arg3 p3)
		{
			return ((*m_iType).*m_mType)(p1, p2, p3);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2, Arg3 p3, Arg4 p4)
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
		typedef R ReturnType;
		typedef DelegateImpl<R, TList> ImplType;
		typedef typename ImplType::Arg1 Arg1;
		typedef typename ImplType::Arg2 Arg2;
		typedef typename ImplType::Arg3 Arg3;
		typedef typename ImplType::Arg4 Arg4;

		DelegateBase()
			:m_my(NULL)
		{

		}
		DelegateBase(const DelegateBase& db)
			:m_my(ImplType::Clone(db.m_my.Ptr()))
		{
		}
		/// <summary>
		/// 普通函数类型
		/// </summary>
		template <typename FunctionType>
		DelegateBase(FunctionType fType)
			: m_my(new Function1<R, TList, FunctionType>(fType))
		{

		}
		/// <summary>
		/// 成员函数类型
		/// </summary>
		template <class InstanceType, typename FunctionType>
		DelegateBase(const InstanceType& iType, FunctionType mType)
			: m_my(new Function2<R, TList, InstanceType, FunctionType>(iType, mType))
		{

		}
		/// <summary>
		/// 绑定普通函数
		/// </summary>
		template <typename FunctionType>
		void BindDelegate(FunctionType fType)
		{
			m_my.Reset(new Function1<R, TList, FunctionType>(fType));
		}
		/// <summary>
		/// 绑定成员函数
		/// </summary>
		template <class InstanceType, typename FunctionType>
		void BindDelegate(const InstanceType& iType, FunctionType mType)
		{
			m_my.Reset(new Function2<R, TList, InstanceType, FunctionType>(iType, mType));
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
		DelegateBase& operator=(const DelegateBase& os)
		{
			DelegateBase copy(os);
			ImplType* ps = m_my.Release();
			m_my.Reset(copy.m_my.Release());
			copy.m_my.Reset(ps);
			return *this;
		}
		BOOL operator==(const DelegateBase& os) const
		{
			if (m_my.Ptr() == NULL && os.m_my.Ptr() == NULL)
			{
				return TRUE;
			}
			if (m_my.Ptr() != NULL && os.m_my.Ptr() != NULL)
			{
				return (*m_my.Ptr()) == *(os.m_my.Ptr());
			}
			return FALSE;
		}
		BOOL operator!=(const DelegateBase& os) const
		{
			return !(*this == os);
		}
		ReturnType operator()() const
		{
			return (*m_my)();
		}
		ReturnType operator()(Arg1 p1) const
		{
			return (*m_my)(p1);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2) const
		{
			return (*m_my)(p1, p2);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2, Arg3 p3) const
		{
			return (*m_my)(p1, p2, p3);
		}
		ReturnType operator()(Arg1 p1, Arg2 p2, Arg3 p3, Arg4 p4) const
		{
			return (*m_my)(p1, p2, p3, p4);
		}
	private:
		TinyAutoPtr<ImplType>	m_my;
	};
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 委托类
	/// </summary>
	template<typename R = void>
	class Delegate;
	template<typename R>
	class Delegate<R()> : public DelegateBase<R, TYPE_LIST0()>
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
				//显示调用基类赋值函数
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
	class Delegate<R(P1)>:public DelegateBase<R, TYPE_LIST1(P1)>
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
	class Delegate<R(P1, P2)>:public DelegateBase<R, TYPE_LIST2(P1, P2)>
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
	class Delegate<R(P1, P2, P3)>:public DelegateBase<R, TYPE_LIST3(P1, P2, P3)>
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
	class Delegate<R(P1, P2, P3, P4)> : public DelegateBase<R, TYPE_LIST4(P1, P2, P3, P4)>
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
				//显示调用基类赋值函数
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

