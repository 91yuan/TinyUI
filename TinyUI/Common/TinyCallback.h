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
		typedef NullType RunnableType;

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
		typedef T RunnableType;

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
		typedef T RunnableType;

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
		typedef NullType RunnableType;

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
		typedef T RunnableType;

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
		typedef T RunnableType;

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
		typedef NullType RunnableType;

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
		typedef T RunnableType;

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
		typedef T RunnableType;

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
		typedef NullType RunnableType;

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
		typedef T RunnableType;

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
		typedef T RunnableType;

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
		typedef NullType RunnableType;

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
		typedef T RunnableType;

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
		typedef T RunnableType;

		typedef typename A1 A1Type;
		typedef typename A2 A2Type;
		typedef typename A3 A3Type;
		typedef typename A4 A4Type;
	};
	/// <summary>
	/// 回调运行时基类
	/// </summary>
	class CallbackRunnableBase : public TinyReference < CallbackRunnableBase >
	{
	protected:
		friend class TinyReference < CallbackRunnableBase > ;
		virtual ~CallbackRunnableBase() {}
	};

	template <typename CallbackRunnableType, typename R>
	struct Caller;
	template <typename CallbackRunnableType, typename R>
	struct Caller < CallbackRunnableType, R(*)() >
	{
		static R DoInvoke(CallbackRunnableBase* base)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return (*call->m_runnable)();
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1>
	struct Caller < CallbackRunnableType, R(*)(A1) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return (*call->m_runnable)(a1);
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1, typename A2>
	struct Caller < CallbackRunnableType, R(*)(A1, A2) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return (*call->m_runnable)(a1, a2);
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1, typename A2, typename A3>
	struct Caller < CallbackRunnableType, R(*)(A1, A2, A3) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return (*call->m_runnable)(a1, a2, a3);
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1, typename A2, typename A3, typename A4>
	struct Caller < CallbackRunnableType, R(*)(A1, A2, A3, A4) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3, A4  a4)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return (*call->m_runnable)(a1, a2, a3, a4);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T>
	struct Caller < CallbackRunnableType, R(T::*)() >
	{
		static R DoInvoke(CallbackRunnableBase* base)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return ((call->m_instance)->*call->m_runnable)();
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1>
	struct Caller < CallbackRunnableType, R(T::*)(A1) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1, typename A2>
	struct Caller < CallbackRunnableType, R(T::*)(A1, A2) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1, a2);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1, typename A2, typename A3>
	struct Caller < CallbackRunnableType, R(T::*)(A1, A2, A3) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1, a2, a3);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1, typename A2, typename A3, typename A4>
	struct Caller < CallbackRunnableType, R(T::*)(A1, A2, A3, A4) >
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3, A4 a4)
		{
			CallbackRunnableType* call = static_cast<CallbackRunnableType*>(base);
			return ((call->m_instance)->*call->m_runnable)(a1, a2, a3, a4);
		}
	};
	/// <summary>
	/// 普通函数
	/// </summary>
	template <typename Runnable>
	class CallbackRunnable0 : public CallbackRunnableBase
	{
	public:
		typedef CallbackRunnable0 CallbackRunnableType;
		typedef typename RunnableAdapter<Runnable>::RunType RunType;
		typedef Caller<CallbackRunnableType, RunType> CallerType;

		CallbackRunnable0(const Runnable& runnable)
			: m_runnable(runnable)
		{
		}

		virtual ~CallbackRunnable0()
		{
		}
		Runnable m_runnable;
	};
	/// <summary>
	/// 类成员函数
	/// </summary>
	template <typename Runnable, typename Instance>
	class CallbackRunnable1 : public CallbackRunnableBase
	{
	public:
		typedef CallbackRunnable1 CallbackRunnableType;
		typedef typename RunnableAdapter<Runnable>::RunType RunType;
		typedef Caller<CallbackRunnableType, RunType> CallerType;
		CallbackRunnable1(const Runnable& runnable, const Instance& instance)
			: m_runnable(runnable),
			m_instance(instance)
		{
		}
		virtual ~CallbackRunnable1()
		{
		}
		Runnable m_runnable;
		Instance m_instance;
	};
	/// <summary>
	/// 回调基类
	/// </summary>
	class CallbackBase
	{
	public:
		BOOL IsNull() const;
		void Reset();
	protected:
		BOOL Equals(const CallbackBase& other) const;
		typedef void(*CallbackInvokeBase)(void);
		CallbackBase(CallbackInvokeBase invoke, TinyScopedReferencePtr<CallbackRunnableBase>* caller);
		~CallbackBase();
		TinyScopedReferencePtr<CallbackRunnableBase> m_caller;
		CallbackInvokeBase m_invoke;
	};
	template<typename T>
	struct CallbackHost
	{
		explicit CallbackHost(T* caller)
			: m_caller(caller)
		{
			TRACE("调用CallbackHost构造函数\n");
		}

		mutable TinyScopedReferencePtr<CallbackRunnableBase> m_caller;
	};
	template<typename T>
	CallbackHost<T> MakeCallback(T* o)
	{
		return CallbackHost<T>(o);
	}
	/// <summary>
	/// 回调
	/// </summary>
	template<typename Runnable>
	class Callback;
	template<typename R>
	class Callback<R()> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*);
		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackHost<T>& host)
			: CallbackBase(reinterpret_cast<CallbackInvokeBase>(&T::CallerType::DoInvoke), &host.m_caller)
		{
			TRACE("调用Callback构造函数\n");
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run() const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(m_invoke);
			return invoke(m_caller.Ptr());
		}
	};
	template<typename R, typename A1>
	class Callback<R(A1)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackHost<T>& host)
			: CallbackBase(reinterpret_cast<CallbackInvokeBase>(&T::CallerType::DoInvoke), &host.m_caller)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(m_invoke);
			return invoke(m_caller.Ptr(), a1);
		}
	};
	template<typename R, typename A1, typename A2>
	class Callback<R(A1, A2)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1, A2);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackHost<T>& host)
			: CallbackBase(reinterpret_cast<CallbackInvokeBase>(&T::CallerType::DoInvoke), &host.m_caller)
		{

		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1, A2 a2) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(m_invoke);
			return invoke(m_caller.Ptr(), a1, a2);
		}
	};
	template<typename R, typename A1, typename A2, typename A3>
	class Callback<R(A1, A2, A3)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1, A2, A3);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackHost<T>& host)
			: CallbackBase(reinterpret_cast<CallbackInvokeBase>(&T::CallerType::DoInvoke), &host.m_caller)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1, A2 a2, A3 a3) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(m_invoke);
			return invoke(m_caller.Ptr(), a1, a2, a3);
		}
	};
	template<typename R, typename A1, typename A2, typename A3, typename A4>
	class Callback<R(A1, A2, A3, A4)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1, A2, A3, A4);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackHost<T>& host)
			: CallbackBase(reinterpret_cast<CallbackInvokeBase>(&T::CallerType::DoInvoke), &host.m_caller)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1, A2 a2, A3 a3, A4 a4) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(m_invoke);
			return invoke(m_caller.Ptr(), a1, a2, a3, a4);
		}
	};

	template<typename Runnable, typename Instance>
	CallbackHost<CallbackRunnable1<Runnable, Instance> > Bind(const Runnable& runnable, const Instance& instance)
	{
		return MakeCallback(new CallbackRunnable1<Runnable, Instance>(runnable, instance));
	}
	template<typename Runnable>
	CallbackHost<CallbackRunnable0<Runnable> > Bind(const Runnable& runnable)
	{
		return MakeCallback(new CallbackRunnable0<Runnable>(runnable));
	}
};

