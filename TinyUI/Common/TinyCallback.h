#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	template <typename T>
	struct FunctionTraits;
	/// <summary>
	/// 0个参数的普通函数
	/// </summary>
	template <typename R>
	struct FunctionTraits<R(*)()>
	{
		enum { IsFunction = TRUE };
		typedef R(*Function)();
		typedef R ReturnType;
	};
	/// <summary>
	/// 0个参数的const成员函数
	/// </summary>
	template <typename R, typename T>
	struct FunctionTraits<R(T::*)()>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)();
		typedef R ReturnType;
		typedef T ThisType;
	};
	/// <summary>
	/// 0个参数的const成员函数
	/// </summary>
	template <typename R, typename T>
	struct FunctionTraits<R(T::*)() const>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)();
		typedef R ReturnType;
		typedef T ThisType;
	};
	/// <summary>
	/// 1个参数的普通函数
	/// </summary>
	template <typename R, typename P1>
	struct FunctionTraits<R(*)(P1)>
	{
		enum { IsFunction = TRUE };
		typedef R(*Function)(P1);
		typedef R ReturnType;
		typedef P1 Arg1Type;
	};
	/// <summary>
	/// 1个参数的成员函数
	/// </summary>
	template <typename R, typename T, typename P1>
	struct FunctionTraits<R(T::*)(P1)>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
	};
	/// <summary>
	/// 1个参数的const成员函数
	/// </summary>
	template <typename R, typename T, typename P1>
	struct FunctionTraits<R(T::*)(P1) const>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
	};
	/// <summary>
	/// 2个参数的普通函数
	/// </summary>
	template <typename R, typename P1, typename P2>
	struct FunctionTraits<R(*)(P1, P2)>
	{
		enum { IsFunction = TRUE };
		typedef R(*Function)(P1, P2);
		typedef R ReturnType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
	};
	/// <summary>
	/// 2个参数的成员函数
	/// </summary>
	template <typename R, typename T, typename P1, typename P2>
	struct FunctionTraits<R(T::*)(P1, P2)>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1, P2);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
	};
	/// <summary>
	/// 2个参数的const成员函数
	/// </summary>
	template <typename R, typename T, typename P1, typename P2>
	struct FunctionTraits<R(T::*)(P1, P2) const>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1, P2);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
	};
	/// <summary>
	/// 3个参数的普通函数
	/// </summary>
	template <typename R, typename P1, typename P2, typename P3>
	struct FunctionTraits<R(*)(P1, P2, P3)>
	{
		enum { IsFunction = TRUE };
		typedef R(*Function)(P1, P2, P3);
		typedef R ReturnType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
		typedef P3 Arg3Type;
	};
	/// <summary>
	/// 3个参数的成员函数
	/// </summary>
	template <typename R, typename T, typename P1, typename P2, typename P3>
	struct FunctionTraits<R(T::*)(P1, P2, P3)>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1, P2, P3);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
		typedef P3 Arg3Type;
	};
	/// <summary>
	/// 3个参数的const成员函数
	/// </summary>
	template <typename R, typename T, typename P1, typename P2, typename P3>
	struct FunctionTraits<R(T::*)(P1, P2, P3) const>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1, P2, P3);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
		typedef P3 Arg3Type;
	};
	/// <summary>
	/// 4个参数的普通函数
	/// </summary>
	template <typename R, typename P1, typename P2, typename P3, typename P4>
	struct FunctionTraits<R(*)(P1, P2, P3, P4)>
	{
		enum { IsFunction = TRUE };
		typedef R(*Function)(P1, P2, P3, P4);
		typedef R ReturnType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
		typedef P3 Arg3Type;
		typedef P4 Arg4Type;
	};
	/// <summary>
	/// 4个参数的成员函数
	/// </summary>
	template <typename R, typename T, typename P1, typename P2, typename P3, typename P4>
	struct FunctionTraits<R(T::*)(P1, P2, P3, P4)>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1, P2, P3, P4);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
		typedef P3 Arg3Type;
		typedef P4 Arg4Type;
	};
	/// <summary>
	/// 4个参数的const成员函数
	/// </summary>
	template <typename R, typename T, typename P1, typename P2, typename P3, typename P4>
	struct FunctionTraits<R(T::*)(P1, P2, P3, P4) const>
	{
		enum { IsFunction = TRUE };
		typedef R(T::*Function)(P1, P2, P3, P4);
		typedef R ReturnType;
		typedef T ThisType;
		typedef P1 Arg1Type;
		typedef P2 Arg2Type;
		typedef P3 Arg3Type;
		typedef P4 Arg4Type;
	};
	template<typename T>
	struct CallbackParamTraits
	{
		typedef const T& ForwardType;
		typedef T StorageType;
	};
	template<typename T>
	struct CallbackParamTraits<T&>
	{
		typedef T& ForwardType;
		typedef T StorageType;
	};
	template<typename T, size_t n>
	struct CallbackParamTraits<T[n]>
	{
		typedef const T* ForwardType;
		typedef const T* StorageType;
	};
	template<typename T>
	struct CallbackParamTraits<T[]>
	{
		typedef const T* ForwardType;
		typedef const T* StorageType;
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct MaybeRefcount;

	template<typename T>
	struct MaybeRefcount<T&>
	{
		static void AddRef(const T&) {}
		static void Release(const T&) {}
	};

	template<typename T, size_t n>
	struct MaybeRefcount<T[n]>
	{
		static void AddRef(const T*) {}
		static void Release(const T*) {}
	};

	template<typename T>
	struct MaybeRefcount<T*>
	{
		static void AddRef(T* o) { o->AddRef(); }
		static void Release(T* o) { o->Release(); }
	};

	template<typename T>
	struct MaybeRefcount<const T*>
	{
		static void AddRef(const T* o) { o->AddRef(); }
		static void Release(const T* o) { o->Release(); }
	};
	//////////////////////////////////////////////////////////////////////////
	class InvokerStorageBase : public TinyReference<InvokerStorageBase>
	{
	protected:
		friend class TinyReference<InvokerStorageBase>;
		virtual ~InvokerStorageBase() {}
	};
	template <typename T, typename R>
	struct Invoke;
	template <typename T, typename R>
	struct Invoke<T, R(*)()>
	{
		typedef R(*DoInvokeType)(InvokerStorageBase*);
		static R DoInvoke(InvokerStorageBase* base)
		{
			T* ps = static_cast<T*>(base);
			if (!ps) throw("无效的invoke!");
			return ps->f_();
		}
	};
	template <typename T, typename R, typename P1>
	struct Invoke<T, R(*)(P1)>
	{
		typedef typename CallbackParamTraits<P1>::ForwardType ForwardType1;
		typedef R(*DoInvokeType)(InvokerStorageBase*, ForwardType1);
		static R DoInvoke(InvokerStorageBase* base, ForwardType1 p1)
		{
			T* ps = static_cast<T*>(base);
			if (!ps)throw("无效的invoke!");
			return ps->f_(p1);
		}
	};
	template <typename T, typename R, typename P1, typename P2>
	struct Invoke<T, R(*)(P1, P2)>
	{
		typedef typename CallbackParamTraits<P1>::ForwardType ForwardType1;
		typedef typename CallbackParamTraits<P2>::ForwardType ForwardType2;
		typedef R(*DoInvokeType)(InvokerStorageBase*, ForwardType1, ForwardType2);
		static R DoInvoke(InvokerStorageBase* base, ForwardType1 p1, ForwardType2 p2)
		{
			T* ps = static_cast<T*>(base);
			if (!ps) throw("无效的invoke!");
			return ps->f_(p1, p2);
		}
	};
	template <typename T, typename R, typename P1, typename P2, typename P3>
	struct Invoke<T, R(*)(P1, P2, P3)>
	{
		typedef typename CallbackParamTraits<P1>::ForwardType ForwardType1;
		typedef typename CallbackParamTraits<P2>::ForwardType ForwardType2;
		typedef typename CallbackParamTraits<P3>::ForwardType ForwardType3;
		typedef R(*DoInvokeType)(InvokerStorageBase*, ForwardType1, ForwardType2, ForwardType3);
		static R DoInvoke(InvokerStorageBase* base, ForwardType1 p1, ForwardType2 p2, ForwardType3 p3)
		{
			T* ps = static_cast<T*>(base);
			if (!ps) throw("无效的invoke!");
			return ps->f_(p1, p2, p3);
		}
	};
	template <typename T, typename R, typename P1, typename P2, typename P3, typename P4>
	struct Invoke<T, R(*)(P1, P2, P3, P4)>
	{
		typedef typename CallbackParamTraits<P1>::ForwardType ForwardType1;
		typedef typename CallbackParamTraits<P2>::ForwardType ForwardType2;
		typedef typename CallbackParamTraits<P3>::ForwardType ForwardType3;
		typedef typename CallbackParamTraits<P4>::ForwardType ForwardType4;
		typedef R(*DoInvokeType)(InvokerStorageBase*, ForwardType1, ForwardType2, ForwardType3, ForwardType4);
		static R DoInvoke(InvokerStorageBase* base, ForwardType1 p1, ForwardType2 p2, ForwardType3 p3, ForwardType4 p4)
		{
			T* ps = static_cast<T*>(base);
			if (!ps) throw("无效的invoke!");
			return ps->f_(p1, p2, p3, p4);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	template <typename Sig>
	class InvokerStorage0 : public InvokerStorageBase {
	public:
		typedef InvokerStorage0 StorageType;
		typedef FunctionTraits<Sig> TargetTraits;
		typedef Sig Signature;
		typedef Invoke< StorageType, typename TargetTraits::Function> Invoker;
		InvokerStorage0(Sig f)
			: f_(f)
		{
		}

		virtual ~InvokerStorage0() {  }

		Sig f_;
	};
	template <typename Sig, typename P1>
	class InvokerStorage1 : public InvokerStorageBase
	{
	public:
		typedef InvokerStorage1 StorageType;
		typedef FunctionTraits<Sig> TargetTraits;
		typedef Sig Signature;
		typedef CallbackParamTraits<P1> P1Traits;
		typedef Invoke<StorageType, typename TargetTraits::Function> Invoker;

		InvokerStorage1(Sig f, const P1& p1)
			: f_(f), p1_(static_cast<typename CallbackParamTraits<P1>::StorageType>(p1))
		{
			MaybeRefcount<P1>::AddRef(p1_);
		}

		virtual ~InvokerStorage1()
		{
			MaybeRefcount<P1>::Release(p1_);
		}

		Sig f_;
		typename CallbackParamTraits<P1>::StorageType p1_;
	};

	template <typename Sig, typename P1, typename P2>
	class InvokerStorage2 : public InvokerStorageBase {
	public:
		typedef InvokerStorage2 StorageType;
		typedef FunctionTraits<Sig> TargetTraits;
		typedef Sig Signature;
		typedef CallbackParamTraits<P1> P1Traits;
		typedef CallbackParamTraits<P2> P2Traits;
		typedef Invoke<StorageType, typename TargetTraits::Function> Invoker;

		InvokerStorage2(Sig f, const P1& p1, const P2& p2)
			: f_(f), p1_(static_cast<typename CallbackParamTraits<P1>::StorageType>(p1)),
			p2_(static_cast<typename CallbackParamTraits<P2>::StorageType>(p2))
		{
			MaybeRefcount<P1>::AddRef(p1_);
		}

		virtual ~InvokerStorage2()
		{
			MaybeRefcount<P1>::Release(p1_);
		}

		Sig f_;
		typename CallbackParamTraits<P1>::StorageType p1_;
		typename CallbackParamTraits<P2>::StorageType p2_;
	};

	template <typename Sig, typename P1, typename P2, typename P3>
	class InvokerStorage3 : public InvokerStorageBase
	{
	public:
		typedef InvokerStorage3 StorageType;
		typedef FunctionTraits<Sig> TargetTraits;
		typedef Sig Signature;
		typedef CallbackParamTraits<P1> P1Traits;
		typedef CallbackParamTraits<P2> P2Traits;
		typedef CallbackParamTraits<P3> P3Traits;
		typedef Invoke<StorageType, typename TargetTraits::Function> Invoker;


		InvokerStorage3(Sig f, const P1& p1, const P2& p2, const P3& p3)
			: f_(f), p1_(static_cast<typename CallbackParamTraits<P1>::StorageType>(p1)),
			p2_(static_cast<typename CallbackParamTraits<P2>::StorageType>(p2)),
			p3_(static_cast<typename CallbackParamTraits<P3>::StorageType>(p3))
		{
			MaybeRefcount<P1>::AddRef(p1_);
		}

		virtual ~InvokerStorage3() {
			MaybeRefcount<P1>::Release(p1_);
		}

		Sig f_;
		typename CallbackParamTraits<P1>::StorageType p1_;
		typename CallbackParamTraits<P2>::StorageType p2_;
		typename CallbackParamTraits<P3>::StorageType p3_;
	};

	template <typename Sig, typename P1, typename P2, typename P3, typename P4>
	class InvokerStorage4 : public InvokerStorageBase
	{
	public:
		typedef InvokerStorage4 StorageType;
		typedef FunctionTraits<Sig> TargetTraits;
		typedef Sig Signature;
		typedef CallbackParamTraits<P1> P1Traits;
		typedef CallbackParamTraits<P2> P2Traits;
		typedef CallbackParamTraits<P3> P3Traits;
		typedef CallbackParamTraits<P4> P4Traits;
		typedef Invoke<StorageType, typename TargetTraits::Function> Invoker;

		InvokerStorage4(Sig f, const P1& p1, const P2& p2, const P3& p3, const P4& p4)
			: f_(f), p1_(static_cast<typename CallbackParamTraits<P1>::StorageType>(p1)),
			p2_(static_cast<typename CallbackParamTraits<P2>::StorageType>(p2)),
			p3_(static_cast<typename CallbackParamTraits<P3>::StorageType>(p3)),
			p4_(static_cast<typename CallbackParamTraits<P4>::StorageType>(p4))
		{
			MaybeRefcount<P1>::AddRef(p1_);
		}

		virtual ~InvokerStorage4()
		{
			MaybeRefcount<P1>::Release(p1_);
		}

		Sig f_;
		typename CallbackParamTraits<P1>::StorageType p1_;
		typename CallbackParamTraits<P2>::StorageType p2_;
		typename CallbackParamTraits<P3>::StorageType p3_;
		typename CallbackParamTraits<P4>::StorageType p4_;
	};
	template<typename T>
	struct InvokerStorageHolder
	{
		explicit InvokerStorageHolder(T* invoker_storage)
		: invoker_storage_(invoker_storage) {}

		mutable TinyScopedReferencePtr<InvokerStorageBase> invoker_storage_;
	};

	template<typename T>
	InvokerStorageHolder<T> MakeInvokerStorageHolder(T* o)
	{
		return InvokerStorageHolder<T>(o);
	}
	//////////////////////////////////////////////////////////////////////////
	class CallbackBase
	{
	public:
		bool is_null() const;
		void Reset();

	protected:
		bool Equals(const CallbackBase& other) const;
		typedef void(*InvokeFuncStorage)(void);
		CallbackBase(InvokeFuncStorage polymorphic_invoke, TinyScopedReferencePtr<InvokerStorageBase>* invoker_storage);
		~CallbackBase();
		TinyScopedReferencePtr<InvokerStorageBase> invoker_storage_;
		InvokeFuncStorage polymorphic_invoke_;
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename Sig>
	class Callback;

	template<typename R>
	class Callback<R(void)> : public CallbackBase
	{
	public:
		typedef R(*PolymorphicInvoke)(InvokerStorageBase*);

		Callback() : CallbackBase(NULL, NULL) {}

		template<typename T>
		Callback(const InvokerStorageHolder<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{

		}

		bool Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run() const
		{
			PolymorphicInvoke f = reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);
			return f(invoker_storage_.Ptr());
		}
	};

	template<typename R, typename A1>
	class Callback<R(A1)> : public CallbackBase
	{
	public:
		typedef R(*PolymorphicInvoke)(InvokerStorageBase*, typename CallbackParamTraits<A1>::ForwardType);

		Callback() : CallbackBase(NULL, NULL) {}

		template<typename T>
		Callback(const InvokerStorageHolder<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{

		}

		bool Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(typename CallbackParamTraits<A1>::ForwardType a1) const
		{
			PolymorphicInvoke f =
				reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

			return f(invoker_storage_.Ptr(), a1);
		}
	};

	template<typename R, typename A1, typename A2>
	class Callback<R(A1, A2)> : public CallbackBase
	{
	public:
		typedef R(*PolymorphicInvoke)(InvokerStorageBase*,
			typename CallbackParamTraits<A1>::ForwardType,
			typename CallbackParamTraits<A2>::ForwardType);

		Callback() : CallbackBase(NULL, NULL) {}

		template <typename T>
		Callback(const InvokerStorageHolder<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{

		}

		bool Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(typename CallbackParamTraits<A1>::ForwardType a1,
			typename CallbackParamTraits<A2>::ForwardType a2) const
		{
			PolymorphicInvoke f =
				reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

			return f(invoker_storage_.Ptr(), a1, a2);
		}
	};

	template<typename R, typename A1, typename A2, typename A3>
	class Callback<R(A1, A2, A3)> : public CallbackBase
	{
	public:
		typedef R(*PolymorphicInvoke)(InvokerStorageBase*,
			typename CallbackParamTraits<A1>::ForwardType,
			typename CallbackParamTraits<A2>::ForwardType,
			typename CallbackParamTraits<A3>::ForwardType);

		Callback() : CallbackBase(NULL, NULL) {}

		template<typename T>
		Callback(const InvokerStorageHolder<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{

		}

		bool Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(typename CallbackParamTraits<A1>::ForwardType a1,
			typename CallbackParamTraits<A2>::ForwardType a2,
			typename CallbackParamTraits<A3>::ForwardType a3) const
		{
			PolymorphicInvoke f =
				reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

			return f(invoker_storage_.Ptr(), a1, a2, a3);
		}
	};

	template<typename R, typename A1, typename A2, typename A3, typename A4>
	class Callback<R(A1, A2, A3, A4)> : public CallbackBase
	{
	public:
		typedef R(*PolymorphicInvoke)(
			InvokerStorageBase*,
			typename CallbackParamTraits<A1>::ForwardType,
			typename CallbackParamTraits<A2>::ForwardType,
			typename CallbackParamTraits<A3>::ForwardType,
			typename CallbackParamTraits<A4>::ForwardType);

		Callback() : CallbackBase(NULL, NULL) {}

		template<typename T>
		Callback(const InvokerStorageHolder<T>& invoker_holder)
			: CallbackBase(
			reinterpret_cast<InvokeFuncStorage>(&T::Invoker::DoInvoke),
			&invoker_holder.invoker_storage_)
		{

		}

		bool Equals(const Callback& other) const
		{
			return CallbackBase::Equals(other);
		}

		R Run(typename CallbackParamTraits<A1>::ForwardType a1,
			typename CallbackParamTraits<A2>::ForwardType a2,
			typename CallbackParamTraits<A3>::ForwardType a3,
			typename CallbackParamTraits<A4>::ForwardType a4) const
		{
			PolymorphicInvoke f =
				reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

			return f(invoker_storage_.get(), a1, a2, a3, a4);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename Sig>
	InvokerStorageHolder<InvokerStorage0<Sig>>
		Bind(Sig f)
	{
			return MakeInvokerStorageHolder(
				new InvokerStorage0<Sig>(f));
		}

	template<typename Sig, typename P1>
	InvokerStorageHolder<InvokerStorage1<Sig, P1> >
		Bind(Sig f, const P1& p1)
	{
			return MakeInvokerStorageHolder(
				new InvokerStorage1<Sig, P1>(f, p1));
		}

	template<typename Sig, typename P1, typename P2>
	InvokerStorageHolder<InvokerStorage2<Sig, P1, P2> >
		Bind(Sig f, const P1& p1, const P2& p2)
	{
			return MakeInvokerStorageHolder(
				new InvokerStorage2<Sig, P1, P2>(
				f, p1, p2));
		}

	template<typename Sig, typename P1, typename P2, typename P3>
	InvokerStorageHolder<InvokerStorage3<Sig, P1, P2, P3> >
		Bind(Sig f, const P1& p1, const P2& p2, const P3& p3)
	{
			return MakeInvokerStorageHolder(
				new InvokerStorage3<Sig, P1, P2, P3>(
				f, p1, p2, p3));
		}

	template<typename Sig, typename P1, typename P2, typename P3, typename P4>
	InvokerStorageHolder<InvokerStorage4<Sig, P1, P2, P3, P4> >
		Bind(Sig f, const P1& p1, const P2& p2, const P3& p3, const P4& p4)
	{
			return MakeInvokerStorageHolder(
				new InvokerStorage4<Sig, P1, P2, P3, P4>(
				f, p1, p2, p3, p4));
		}
};

