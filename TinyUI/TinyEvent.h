#pragma once
#include "TinyDelegate.h"

namespace TinyUI
{
	/// <summary>
	/// �¼���
	/// </summary>
	template<typename R = void()>
	class Event;
	template<typename R>
	class Event<R()>
	{
	public:
		/// <summary>
		/// ���߱��������Ǹ����Ͱ������͵ķ�ʽ����
		/// </summary>
		typedef typename Delegate<R()> DelegateType;
		/// <summary>
		/// ����ί�з������Ϳ���ʹ�������� �ಥί�з�������ֻ��Ϊvoid
		/// </summary>
		void operator+= (DelegateType* ps)
		{
			if (m_array.GetSize() >= 1 && IsVoidType<R>::Result == 0)
			{
				throw("�ಥί�з�������ֻ��Ϊvoid");
			}
			if (m_array.Lookup(ps) < 0)
			{
				m_array.Add(ps);
			}
		}
		void operator-= (DelegateType* ps)
		{
			INT index = m_array.Lookup(ps);
			if (index >= 0)
			{
				m_array.RemoveAt(index);
			}
		};
		/// <summary>
		/// ����ί�з���R,�ಥί�з���void
		/// </summary>
		R operator()()
		{
			INT size = m_array.GetSize();
			if (size == 1)//����ί��
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[0]);
				if (fType)
				{
					return (*fType)();
				};
			}
			for (INT i = 0; i < size; i++)
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[i]);
				if (fType)
				{
					(*fType)();
				};
			};
		};
		INT GetSize() const
		{
			return m_array.GetSize();
		};
	private:
		TinyArray<DelegateType*> m_array;
	};
	template<typename R, typename P1>
	class Event<R(P1)>
	{
	public:
		/// <summary>
		/// ���߱��������Ǹ����Ͱ������͵ķ�ʽ����
		/// </summary>
		typedef typename Delegate<R(P1)> DelegateType;
		void operator+= (DelegateType* ps)
		{
			if (m_array.GetSize() >= 1 && IsVoidType<R>::Result == 0)
			{
				throw("�ಥί�з�������ֻ��Ϊvoid");
			}
			if (m_array.Lookup(ps) < 0)
			{
				m_array.Add(ps);
			}
		}
		void operator-= (DelegateType* ps)
		{
			INT index = m_array.Lookup(ps);
			if (index >= 0)
			{
				m_array.RemoveAt(index);
			}
		};
		/// <summary>
		/// ����ί�з���R,�ಥί�з���void
		/// </summary>
		R operator()(P1 p1)
		{
			INT size = m_array.GetSize();
			if (size == 1)//����ί��
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[0]);
				if (fType)
				{
					return (*fType)(p1);
				};
			}
			for (INT i = 0; i < size; i++)
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[i]);
				if (fType)
				{
					(*fType)(p1);
				};
			};
		};
		INT GetSize() const
		{
			return m_array.GetSize();
		};
	private:
		TinyArray<DelegateType*> m_array;
	};
	template<typename R, typename P1, typename P2>
	class Event<R(P1, P2)>
	{
	public:
		/// <summary>
		/// ���߱��������Ǹ����Ͱ������͵ķ�ʽ����
		/// </summary>
		typedef typename Delegate<R(P1, P2)> DelegateType;
		void operator+= (DelegateType* ps)
		{
			if (m_array.GetSize() >= 1 && IsVoidType<R>::Result == 0)
			{
				throw("�ಥί�з�������ֻ��Ϊvoid");
			}
			if (m_array.Lookup(ps) < 0)
			{
				m_array.Add(ps);
			}
		}
		void operator-= (DelegateType* ps)
		{
			INT index = m_array.Lookup(ps);
			if (index >= 0)
			{
				m_array.RemoveAt(index);
			}
		};
		/// <summary>
		/// ����ί�з���R,�ಥί�з���void
		/// </summary>
		R operator()(P1 p1, P2 p2)
		{
			INT size = m_array.GetSize();
			if (size == 1)//����ί��
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[0]);
				if (fType)
				{
					return (*fType)(p1, p2);
				};
			}
			for (INT i = 0; i < size; i++)
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[i]);
				if (fType)
				{
					(*fType)(p1, p2);
				};
			};
		};
		INT GetSize() const
		{
			return m_array.GetSize();
		};
	private:
		TinyArray<DelegateType*> m_array;
	};
	template<typename R, typename P1, typename P2, typename P3>
	class Event<R(P1, P2, P3)>
	{
	public:
		/// <summary>
		/// ���߱��������Ǹ����Ͱ������͵ķ�ʽ����
		/// </summary>
		typedef typename Delegate<R(P1, P2, P3)> DelegateType;
		void operator+= (DelegateType* ps)
		{
			if (m_array.GetSize() >= 1 && IsVoidType<R>::Result == 0)
			{
				throw("�ಥί�з�������ֻ��Ϊvoid");
			}
			if (m_array.Lookup(ps) < 0)
			{
				m_array.Add(ps);
			}
		}
		void operator-= (DelegateType* ps)
		{
			INT index = m_array.Lookup(ps);
			if (index >= 0)
			{
				m_array.RemoveAt(index);
			}
		};
		/// <summary>
		/// ����ί�з���R,�ಥί�з���void
		/// </summary>
		R operator()(P1 p1, P2 p2, P3 p3)
		{
			INT size = m_array.GetSize();
			if (size == 1)//����ί��
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[0]);
				if (fType)
				{
					return (*fType)(p1, p2, p3);
				};
			}
			for (INT i = 0; i < size; i++)
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[i]);
				if (fType)
				{
					(*fType)(p1, p2, p3);
				};
			};
		};
		INT GetSize() const
		{
			return m_array.GetSize();
		};
	private:
		TinyArray<DelegateType*> m_array;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class Event<R(P1, P2, P3, P4)>
	{
	public:
		/// <summary>
		/// ���߱��������Ǹ����Ͱ������͵ķ�ʽ����
		/// </summary>
		typedef typename Delegate<R(P1, P2, P3, P4)> DelegateType;
		void operator+= (DelegateType* ps)
		{
			if (m_array.GetSize() >= 1 && IsVoidType<R>::Result == 0)
			{
				throw("�ಥί�з�������ֻ��Ϊvoid");
			}
			if (m_array.Lookup(ps) < 0)
			{
				m_array.Add(ps);
			}
		}
		void operator-= (DelegateType* ps)
		{
			INT index = m_array.Lookup(ps);
			if (index >= 0)
			{
				m_array.RemoveAt(index);
			}
		};
		/// <summary>
		/// ����ί�з���R,�ಥί�з���void
		/// </summary>
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4)
		{
			INT size = m_array.GetSize();
			if (size == 1)//����ί��
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[0]);
				if (fType)
				{
					return (*fType)(p1, p2, p3, p4);
				};
			}
			for (INT i = 0; i < size; i++)
			{
				DelegateType* fType = static_cast<DelegateType*>(m_array[i]);
				if (fType)
				{
					(*fType)(p1, p2, p3, p4);
				};
			};
		};
		INT GetSize() const
		{
			return m_array.GetSize();
		};
	private:
		TinyArray<DelegateType*> m_array;
	};
};

