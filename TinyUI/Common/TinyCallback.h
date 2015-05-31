#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	/// <summary>
	/// 运行时适配器类型萃取
	/// </summary>
	template <typename T>
	class RunnableAdapter;
	template <typename R>
	class RunnableAdapter < R(*)() >
	{
	public:
		typedef R ReturnType;
		typedef R(*RunType)();

		typedef typename NullType A1Type;
		typedef typename NullType A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;

	};
	template <typename R, typename T>
	class RunnableAdapter < R(T::*)() >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)();

		typedef typename NullType A1Type;
		typedef typename NullType A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename T>
	class RunnableAdapter < R(T::*)() const >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)() const;

		typedef typename NullType A1Type;
		typedef typename NullType A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;

	};
	template <typename R, typename A1>
	class RunnableAdapter < R(*)(A1) >
	{
	public:
		typedef R ReturnType;
		typedef R(*RunType)(A1);

		typedef typename A1 A1Type;
		typedef typename NullType A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename T>
	class RunnableAdapter < R(T::*)(A1) >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1);

		typedef typename A1 A1Type;
		typedef typename NullType A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename T, typename A1>
	class RunnableAdapter < R(T::*)(A1) const >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1) const;

		typedef typename A1 A1Type;
		typedef typename NullType A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2>
	class RunnableAdapter < R(*)(A1, A2) >
	{
	public:
		typedef R ReturnType;
		typedef R(*RunType)(A1, A2);

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2, typename T>
	class RunnableAdapter < R(T::*)(A1, A2) >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1, A2);

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2, typename T>
	class RunnableAdapter < R(T::*)(A1, A2) const >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1, A2) const;

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename NullType A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2, typename A3>
	class RunnableAdapter < R(*)(A1, A2, A3) >
	{
	public:
		typedef R ReturnType;
		typedef R(*RunType)(A1, A2, A3);

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2, typename A3, typename T>
	class RunnableAdapter < R(T::*)(A1, A2, A3) >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1, A2, A3);

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2, typename A3, typename T>
	class RunnableAdapter < R(T::*)(A1, A2, A3) const >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1, A2, A3) const;

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename NullType A4Type;
	};
	template <typename R, typename A1, typename A2, typename A3, typename A4>
	class RunnableAdapter < R(*)(A1, A2, A3, A4) >
	{
	public:
		typedef R ReturnType;
		typedef R(*RunType)(A1, A2, A3, A4);

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename A4 A4Type;
	};
	template <typename R, typename A1, typename A2, typename A3, typename A4, typename T>
	class RunnableAdapter < R(T::*)(A1, A2, A3, A4) >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1, A2, A3, A4);

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename A4 A4Type;
	};
	template <typename R, typename A1, typename A2, typename A3, typename A4, typename T>
	class RunnableAdapter < R(T::*)(A1, A2, A3, A4) const >
	{
	public:
		typedef R ReturnType;
		typedef R(T::*RunType)(A1, A2, A3, A4) const;

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename A4 A4Type;
	};
	//////////////////////////////////////////////////////////////////////////
	class InvokerStorageBase : public TinyReference < InvokerStorageBase >
	{
	public:
		virtual ~InvokerStorageBase() {}
	};
	//////////////////////////////////////////////////////////////////////////
	template <typename InvokerStorage, typename T>
	struct Invoker;
	template <typename InvokerStorage, typename R>
	struct Invoker < InvokerStorage, R(*)() >
	{
		static R DoInvoke(InvokerStorageBase* base)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return (*call->m_runnable)();
		}
	};
	template <typename InvokerStorage, typename R, typename A1>
	struct Invoker < InvokerStorage, R(*)(A1) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return (*call->m_runnable)(a1);
		}
	};
	template <typename InvokerStorage, typename R, typename A1, typename A2>
	struct Invoker < InvokerStorage, R(*)(A1, A2) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1, A2 a2)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return (*call->m_runnable)(a1, a2);
		}
	};
	template <typename InvokerStorage, typename R, typename A1, typename A2, typename A3>
	struct Invoker < InvokerStorage, R(*)(A1, A2, A3) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1, A2 a2, A3 a3)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return (*call->m_runnable)(a1, a2, a3);
		}
	};
	template <typename InvokerStorage, typename R, typename A1, typename A2, typename A3, typename A4>
	struct Invoker < InvokerStorage, R(*)(A1, A2, A3, A4) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1, A2 a2, A3 a3, A4  a4)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return (*call->m_runnable)(a1, a2, a3, a4);
		}
	};
	template <typename InvokerStorage, typename R, typename T>
	struct Invoker < InvokerStorage, R(T::*)() >
	{
		static R DoInvoke(InvokerStorageBase* base)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return ((call->m_instance)->*call->m_runnable)();
		}
	};
	template <typename InvokerStorage, typename R, typename T, typename A1>
	struct Invoker < InvokerStorage, R(T::*)(A1) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1);
		}
	};
	template <typename InvokerStorage, typename R, typename T, typename A1, typename A2>
	struct Invoker < InvokerStorage, R(T::*)(A1, A2) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1, A2 a2)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1, a2);
		}
	};
	template <typename InvokerStorage, typename R, typename T, typename A1, typename A2, typename A3>
	struct Invoker < InvokerStorage, R(T::*)(A1, A2, A3) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1, A2 a2, A3 a3)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1, a2, a3);
		}
	};
	template <typename InvokerStorage, typename R, typename T, typename A1, typename A2, typename A3, typename A4>
	struct Invoker < InvokerStorage, R(T::*)(A1, A2, A3, A4) >
	{
		static R DoInvoke(InvokerStorageBase* base, A1 a1, A2 a2, A3 a3, A4 a4)
		{
			InvokerStorage* call = static_cast<InvokerStorage*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1, a2, a3, a4);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename FunctionType, typename InstanceType, typename TList>
	class InvokerStorage;
	template <typename FunctionType>
	class InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()> : public InvokerStorageBase
	{
	public:
		typedef InvokerStorage SelfType;
		typedef typename RunnableAdapter<FunctionType>::RunType RunType;
		typedef Invoker<SelfType, RunType> InvokerType;

		InvokerStorage(const FunctionType& runnable)
			: m_runnable(runnable)
		{
		}

		virtual ~InvokerStorage()
		{
		}
		FunctionType m_runnable;
	};
	template <typename FunctionType, typename InstanceType>
	class InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()> : public InvokerStorageBase
	{
	public:
		typedef InvokerStorage SelfType;
		typedef typename RunnableAdapter<FunctionType>::RunType RunType;
		typedef Invoker<SelfType, RunType> InvokerType;
		InvokerStorage(const FunctionType& runnable, const InstanceType& instance)
			: m_runnable(runnable),
			m_instance(instance)
		{
		}
		virtual ~InvokerStorage()
		{
		}
		FunctionType m_runnable;
		InstanceType m_instance;
	};
	/// <summary>
	/// 回调基类
	/// </summary>
	class CallbackBase
	{
	protected:
		typedef void(*InvokeBase)(void);
	public:
		CallbackBase(InvokeBase invoke, InvokerStorageBase* storage);
		CallbackBase(const CallbackBase& callbackBase);
		CallbackBase& operator=(const CallbackBase& callbackBase);
		virtual ~CallbackBase();
	public:
		BOOL operator == (const CallbackBase& other) const;
		BOOL IsNull() const;
		void Reset();
	protected:
		TinyScopedReferencePtr<InvokerStorageBase> m_storage;
		InvokeBase m_invoke;
	};
	/// <summary>
	/// 类型擦除
	/// </summary>
	template<typename InvokerStorage>
	class Caller
	{
	public:
		Caller(InvokerStorage* storage) : m_storage(static_cast<InvokerStorageBase*>(storage))
		{

		}
		mutable TinyScopedReferencePtr < InvokerStorageBase > m_storage;
	};
	template<typename T>
	Caller<T> MakeCaller(T* o)
	{
		return Caller<T>(o);
	}
	/// <summary>
	/// 回调实现类
	/// </summary>
	template<typename Runnable>
	class Callback;
	template<typename R>
	class Callback<R()> : public CallbackBase
	{
		typedef R(*InvokeFunction)(InvokerStorageBase*);
	public:
		Callback() : CallbackBase(NULL, NULL)
		{

		}
		template<typename InvokerStorage>
		Callback(const Caller<InvokerStorage>& caller) : CallbackBase(reinterpret_cast<InvokeBase>(&InvokerStorage::InvokerType::DoInvoke), &caller.m_storage)
		{

		}
		Callback(const Callback& callback) : CallbackBase(callback)
		{

		}
		Callback& operator=(const Callback& other)
		{
			CallbackBase::operator=(other);
			return *this;
		}
		BOOL operator == (const Callback& other) const
		{
			return CallbackBase::operator==(other);
		}
		template <typename FunctionType>
		static Callback MakeCallback(const FunctionType& runnable)
		{
			return Callback(new InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()>(runnable, instance));
		}
		template <typename FunctionType, typename InstanceType>
		static Callback MakeCallback(const FunctionType& runnable, const InstanceType& instance)
		{
			return Callback(new InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()>(runnable, instance));
		}
	public:
		R operator()() const
		{
			InvokeFunction invoke = reinterpret_cast<InvokeFunction>(m_invoke);
			return invoke(m_storage.Ptr());
		}
	};
	template<typename R, typename A1>
	class Callback<R(A1)> : public CallbackBase
	{
		typedef R(*InvokeFunction)(InvokerStorageBase*, A1);
	public:
		Callback() : CallbackBase(NULL, NULL)
		{

		}
		template<typename InvokerStorage>
		Callback(const Caller<InvokerStorage>& caller) : CallbackBase(reinterpret_cast<InvokeBase>(&InvokerStorage::InvokerType::DoInvoke), &caller.m_storage)
		{

		}
		Callback(const Callback& callback) : CallbackBase(callback)
		{

		}
		Callback& operator=(const Callback& other)
		{
			CallbackBase::operator=(other);
			return *this;
		}
		BOOL operator == (const Callback& other) const
		{
			return CallbackBase::operator==(other);
		}
		template <typename FunctionType>
		static Callback MakeCallback(const FunctionType& runnable)
		{
			return Callback(new InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()>(runnable, instance));
		}
		template <typename FunctionType, typename InstanceType>
		static Callback MakeCallback(const FunctionType& runnable, const InstanceType& instance)
		{
			return Callback(new InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()>(runnable, instance));
		}
	public:
		R operator()(A1 a1) const
		{
			InvokeFunction invoke = reinterpret_cast<InvokeFunction>(m_invoke);
			return invoke(m_storage.Ptr(), a1);
		}
	};
	template<typename R, typename A1, typename A2>
	class Callback<R(A1, A2)> : public CallbackBase
	{
		typedef R(*InvokeFunction)(InvokerStorageBase*, A1, A2);
	public:
		Callback() : CallbackBase(NULL, NULL)
		{

		}
		template<typename InvokerStorage>
		Callback(const Caller<InvokerStorage>& caller) : CallbackBase(reinterpret_cast<InvokeBase>(&InvokerStorage::InvokerType::DoInvoke), caller.m_storage.Ptr())
		{

		}
		Callback(const Callback& callback) : CallbackBase(callback)
		{

		}
		Callback& operator=(const Callback& other)
		{
			CallbackBase::operator=(other);
			return *this;
		}
		BOOL operator == (const Callback& other) const
		{
			return CallbackBase::operator==(other);
		}
		template <typename FunctionType>
		static Callback MakeCallback(const FunctionType& runnable)
		{
			return Callback(new InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()>(runnable, instance));
		}
		template <typename FunctionType, typename InstanceType>
		static Callback MakeCallback(const FunctionType& runnable, const InstanceType& instance)
		{
			return Callback(new InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()>(runnable, instance));
		}
	public:
		R operator()(A1 a1, A2 a2) const
		{
			InvokeFunction invoke = reinterpret_cast<InvokeFunction>(m_invoke);
			return invoke(m_storage.Ptr(), a1, a2);
		}
	};
	template<typename R, typename A1, typename A2, typename A3>
	class Callback<R(A1, A2, A3)> : public CallbackBase
	{
		typedef R(*InvokeFunction)(InvokerStorageBase*, A1, A2, A3);
	public:
		Callback() : CallbackBase(NULL, NULL)
		{

		}
		template<typename InvokerStorage>
		Callback(const Caller<InvokerStorage>& caller) : CallbackBase(reinterpret_cast<InvokeBase>(&InvokerStorage::InvokerType::DoInvoke), &caller.m_storage)
		{

		}
		Callback(const Callback& callback) : CallbackBase(callback)
		{

		}
		Callback& operator=(const Callback& other)
		{
			CallbackBase::operator=(other);
			return *this;
		}
		BOOL operator == (const Callback& other) const
		{
			return CallbackBase::operator==(other);
		}
	public:
		R operator()(A1 a1, A2 a2, A3 a3) const
		{
			InvokeFunction invoke = reinterpret_cast<InvokeFunction>(m_invoke);
			return invoke(m_storage.Ptr(), a1, a2, a3);
		}
	};
	template<typename R, typename A1, typename A2, typename A3, typename A4>
	class Callback<R(A1, A2, A3, A4)> : public CallbackBase
	{
		typedef R(*InvokeFunction)(InvokerStorageBase*, A1, A2, A3, A4);
	public:
		Callback() : CallbackBase(NULL, NULL)
		{

		}
		template<typename InvokerStorage>
		Callback(const Caller<InvokerStorage>& caller) : CallbackBase(reinterpret_cast<InvokeBase>(&InvokerStorage::InvokerType::DoInvoke), &caller.m_storage)
		{

		}
		Callback(const Callback& callback) : CallbackBase(callback)
		{

		}
		Callback& operator=(const Callback& other)
		{
			CallbackBase::operator=(other);
			return *this;
		}
		BOOL operator == (const Callback& other) const
		{
			return CallbackBase::operator==(other);
		}
		template <typename FunctionType>
		static Callback MakeCallback(const FunctionType& runnable)
		{
			return Callback(new InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()>(runnable, instance));
		}
		template <typename FunctionType, typename InstanceType>
		static Callback MakeCallback(const FunctionType& runnable, const InstanceType& instance)
		{
			return Callback(new InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()>(runnable, instance));
		}
	public:
		R operator()(A1 a1, A2 a2, A3 a3, A4 a4) const
		{
			InvokeFunction invoke = reinterpret_cast<InvokeFunction>(m_invoke);
			return invoke(m_storage.Ptr(), a1, a2, a3, a4);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 绑定函数
	/// </summary>
	template <typename FunctionType>
	Caller<InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()>> Bind(const FunctionType& runnable)
	{
		return MakeCaller(new InvokerStorage<FunctionType, TYPE_LIST0(), TYPE_LIST0()>(runnable));
	};
	/// <summary>
	/// 绑定成员函数
	/// </summary>
	template <typename FunctionType, typename InstanceType>
	Caller<InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()>> Bind(const FunctionType& runnable, const InstanceType& instance)
	{
		return MakeCaller(new InvokerStorage<FunctionType, InstanceType, TYPE_LIST0()>(runnable, instance));
	};
};

