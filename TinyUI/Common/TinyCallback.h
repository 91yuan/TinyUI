#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	/// <summary>
	/// 运行时适配器
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
	//////////////////////////////////////////////////////////////////////////
	class CallbackRunnableBase;
	template <typename CallbackRunnableType, typename R>
	struct Invoker;
	template <typename CallbackRunnableType, typename R>
	struct Invoker<CallbackRunnableType, R(*)()>
	{
		static R DoInvoke(CallbackRunnableBase* base)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return (*invoker->m_runnable)();
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1>
	struct Invoker<CallbackRunnableType, R(*)(A1)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return (*invoker->m_runnable)(a1);
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1, typename A2>
	struct Invoker<CallbackRunnableType, R(*)(A1, A2)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return (*invoker->m_runnable)(a1, a2);
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1, typename A2, typename A3>
	struct Invoker<CallbackRunnableType, R(*)(A1, A2, A3)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return (*invoker->m_runnable)(a1, a2, a3);
		}
	};
	template <typename CallbackRunnableType, typename R, typename A1, typename A2, typename A3, typename A4>
	struct Invoker<CallbackRunnableType, R(*)(A1, A2, A3, A4)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3, A4  a4)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return (*invoker->m_runnable)(a1, a2, a3, a4);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T>
	struct Invoker<CallbackRunnableType, R(T::*)()>
	{
		static R DoInvoke(CallbackRunnableBase* base)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return ((invoker->m_instance)->*invoker->m_runnable)();
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1>
	struct Invoker<CallbackRunnableType, R(T::*)(A1)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return ((invoker->m_instance)->*invoker->m_runnable)(a1);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1, typename A2>
	struct Invoker<CallbackRunnableType, R(T::*)(A1, A2)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return ((invoker->m_instance)->*invoker->m_runnable)(a1, a2);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1, typename A2, typename A3>
	struct Invoker<CallbackRunnableType, R(T::*)(A1, A2, A3)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return ((invoker->m_instance)->*invoker->m_runnable)(a1, a2, a3);
		}
	};
	template <typename CallbackRunnableType, typename R, typename T, typename A1, typename A2, typename A3, typename A4>
	struct Invoker<CallbackRunnableType, R(T::*)(A1, A2, A3, A4)>
	{
		static R DoInvoke(CallbackRunnableBase* base, A1 a1, A2 a2, A3 a3, A4 a4)
		{
			CallbackRunnableType* invoker = static_cast<CallbackRunnableType*>(base);
			return ((invoker->m_instance)->*invoker->m_runnable)(a1, a2, a3, a4);
		}
	};

	class CallbackRunnableBase : public TinyReference<CallbackRunnableBase>
	{
	protected:
		friend class TinyReference<CallbackRunnableBase>;
		virtual ~CallbackRunnableBase() {}
	};
	template <typename Runnable>
	class CallbackRunnable0 : public CallbackRunnableBase
	{
	public:
		typedef CallbackRunnable0 CallbackRunnableType;
		typedef typename RunnableAdapter<Runnable>::RunType RunType;
		typedef Invoker<CallbackRunnableType, RunType> Invoker;

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
		typedef Invoker<CallbackRunnableType, RunType> Invoker;

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
	class CallbackBase
	{
	public:
		BOOL IsNull() const;
		void Reset();
	protected:
		BOOL Equals(const CallbackBase& other) const;
		typedef void(*InvokeFuncStorage)(void);
		CallbackBase(InvokeFuncStorage polymorphic_invoke, TinyScopedReferencePtr<CallbackRunnableBase>* invoker_storage);
		~CallbackBase();
		TinyScopedReferencePtr<CallbackRunnableBase> invoker_storage_;
		InvokeFuncStorage polymorphic_invoke_;
	};

	template<typename T>
	struct CallbackOwner
	{
		explicit CallbackOwner(T* invoker_storage)
		: invoker_storage_(invoker_storage) {}
		mutable TinyScopedReferencePtr<CallbackRunnableBase> invoker_storage_;
	};

	template<typename T>
	CallbackOwner<T> MakeCallback(T* o)
	{
		return CallbackOwner<T>(o);
	}


	template<typename Runnable>
	class Callback;
	template<typename R>
	class Callback<R()> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackOwner<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run() const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(polymorphic_invoke_);
			return invoke(invoker_storage_.Ptr());
		}
	};
	template<typename R, typename A1>
	class Callback<R(A1)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackOwner<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(polymorphic_invoke_);
			return invoke(invoker_storage_.Ptr(), a1);
		}
	};
	template<typename R, typename A1, typename A2>
	class Callback<R(A1, A2)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1, A2);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackOwner<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1, A2 a2) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(polymorphic_invoke_);
			return invoke(invoker_storage_.Ptr(), a1, a2);
		}
	};
	template<typename R, typename A1, typename A2, typename A3>
	class Callback<R(A1, A2, A3)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1, A2, A3);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackOwner<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1, A2 a2, A3 a3) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(polymorphic_invoke_);
			return invoke(invoker_storage_.Ptr(), a1, a2, a3);
		}
	};
	template<typename R, typename A1, typename A2, typename A3, typename A4>
	class Callback<R(A1, A2, A3, A4)> : public CallbackBase
	{
	public:
		typedef R(*CallbackInvoke)(CallbackRunnableBase*, A1, A2, A3, A4);

		Callback() : CallbackBase(NULL, NULL) {}
		template <typename T>
		Callback(const CallbackOwner<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{
		}

		BOOL Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(A1 a1, A2 a2, A3 a3, A4 a4) const
		{
			CallbackInvoke invoke = reinterpret_cast<CallbackInvoke>(polymorphic_invoke_);
			return invoke(invoker_storage_.Ptr(), a1, a2, a3, a4);
		}
	};

	template<typename Runnable, typename Instance>
	CallbackOwner<CallbackRunnable1<Runnable, Instance> >
		Bind(const Runnable& runnable, const Instance& instance)
	{
			return MakeCallback(new CallbackRunnable1<Runnable, Instance>(runnable, instance));
		}
	template<typename Runnable>
	CallbackOwner<CallbackRunnable0<Runnable> >
		Bind(const Runnable& runnable)
	{
			return MakeCallback(new CallbackRunnable0<Runnable>(runnable));
		}
};

