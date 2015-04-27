#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run()
		{
			return m_runType();
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(T* runnable)
		{
			return (runnable->*m_runType)();
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(const T* runnable)
		{
			return (runnable->*m_runType)();
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(A1Type a1)
		{
			return m_runType(a1);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(T* runnable, A1Type a1)
		{
			return (runnable->*m_runType)(a1);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(const T* runnable, A1Type a1)
		{
			return (runnable->*m_runType)(a1);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}

		R Run(A1Type a1, A2Type a2)
		{
			return m_runType(a1, a2);
		}

	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{

		}
		R Run(T* runnable, A1Type a1, A2Type a2)
		{
			return (runnable->*m_runType)(a1, a2);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(const T* runnable, A1Type a1, A2Type a2)
		{
			return (runnable->*m_runType)(a1, a2);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(A1Type a1, A2Type a2, A3Type a3)
		{
			return m_runType(a1, a2, a3);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(T* runnable, A1Type a1, A2Type a2, A3Type a3)
		{
			return (runnable->*m_runType)(a1, a2, a3);
		}
	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}

		R Run(const T* runnable, A1Type a1, A2Type a2, A3Type a3)
		{
			return (runnable->*m_runType)(a1, a2, a3);
		}

	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}

		R Run(A1Type a1, A2Type a2, A3Type a3, A4Type a4)
		{
			return m_runType(a1, a2, a3, a4);
		}

	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}

		R Run(T* runnable, A1Type a1, A2Type a2, A2Type a3, A4Type a4)
		{
			return (runnable->*m_runType)(a1, a2, a3, a4);
		}

	private:
		RunType m_runType;
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

		explicit RunnableAdapter(RunType runType)
			: m_runType(runType)
		{
		}
		R Run(const T* runnable, A1Type a1, A2Type a2, A3Type a3, A4Type a4)
		{
			return (runnable->*m_runType)(a1, a2, a3, a4);
		}
	private:
		RunType m_runType;
	};
	/// <summary>
	/// 回调函数类型萃取
	/// </summary>
	template<typename T>
	class CallbackTypeTraits
	{
	private:
		template<typename P>
		struct PointerTraits
		{
			enum { Result = FALSE };
			typedef NullType PointerType;
		};
		template<typename P>
		struct PointerTraits < P* >
		{
			enum { Result = TRUE };
			typedef P* PointerType;
		};
		template<typename P>
		struct PointerTraits < P*& >
		{
			enum { Result = TRUE };
			typedef P*& PointerType;
		};
		template<typename P>
		struct PointerTraits < const P* >
		{
			enum { Result = TRUE };
			typedef const P* PointerType;
		};
		template<typename P>
		struct PointerTraits < const P*& >
		{
			enum { Result = TRUE };
			typedef const P*& PointerType;
		};
		template<typename P, typename S>
		struct PointerTraits < P S::* >
		{
			enum { Result = TRUE };
			typedef P S::* PointerType;
		};
		template<typename P, typename S>
		struct PointerTraits < P S::*& >
		{
			enum { Result = TRUE };
			typedef P S::*& PointerType;
		};
		template<typename P, typename S>
		struct PointerTraits < const P S::* >
		{
			enum { Result = TRUE };
			typedef const P S::* PointerType;
		};
		template<typename P, typename S>
		struct PointerTraits < const P S::*& >
		{
			enum { Result = TRUE };
			typedef const P S::*& PointerType;
		};

		template<typename U>
		struct ReferenceTraits
		{
			enum { Result = FALSE };
			typedef U ReferenceType;
		};
		template<typename U>
		struct ReferenceTraits < U& >
		{
			enum { Result = TRUE };
			typedef U& ReferenceType;
		};
		template<typename U>
		struct ReferenceTraits < const U& >
		{
			enum { Result = TRUE };
			typedef const U& ReferenceType;
		};

	public:
		enum { IsPointer = PointerTraits < T >::Result };
		typedef typename PointerTraits < T >::PointerType PointerType;
		enum { IsReference = ReferenceTraits < T >::Result };
		typedef typename ReferenceTraits < T >::ReferenceType ReferenceType;
	};
};

