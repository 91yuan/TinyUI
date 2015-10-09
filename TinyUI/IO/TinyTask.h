#pragma once
#include "../Common/TinyCollection.h"
#include "../Common/TinySingle.h"
#include "../Common/TinyCallback.h"
#include "../Common/TinyEvent.h"
#include <string>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

namespace TinyUI
{
	namespace IO
	{
		class TinyTaskAccess;
		template <typename Task>
		class TinyTaskQueue;
		/// <summary>
		/// 任务队列
		/// </summary>
		template <typename Task>
		class TinyTaskQueue : public TinyReference < TinyTaskQueue<Task> >
		{
			DISALLOW_COPY_AND_ASSIGN(TinyTaskQueue)
		public:
			TinyTaskQueue();
			~TinyTaskQueue();
			void Pop();
			void Push(Task* task);
			template <typename OtherTask>
			void Push(TinyTaskQueue<OtherTask>& q)
			{
				if (OtherTask* otherFront = TinyTaskAccess::Front(q))
				{
					if (m_nextTask)
						TinyTaskAccess::Next(m_nextTask, otherFront);
					else
						m_prevTask = otherFront;
					m_nextTask = TinyTaskAccess::Back(q);
					TinyTaskAccess::Front(q) = 0;
					TinyTaskAccess::Back(q) = 0;
				}
			}
			class TinyTaskAccess
			{
			public:
				template <typename Task>
				static Task* Next(Task* o)
				{
					return static_cast<Task*>(o->m_nextTask);
				}

				template <typename Task1, typename Task2>
				static void Next(Task1*& o1, Task2* o2)
				{
					o1->m_nextTask = o2;
				}

				template <typename Task>
				static void Destroy(Task* o)
				{
					o->Destroy();
				}

				template <typename Task>
				static Task*& Front(TinyTaskQueue<Task>& queue)
				{
					return queue.m_prevTask;
				}

				template <typename Task>
				static Task*& Back(TinyTaskQueue<Task>& queue)
				{
					return queue.m_nextTask;
				}
			};
		private:
			Task*	m_prevTask;
			Task*	m_nextTask;
		};
		template <typename Task>
		TinyTaskQueue<Task>::TinyTaskQueue()
			:m_prevTask(NULL),
			m_nextTask(NULL)
		{

		}
		template <typename Task>
		TinyTaskQueue<Task>::~TinyTaskQueue()
		{
			while (Task* op = m_prevTask)
			{
				Pop();
				TinyTaskAccess::Destroy(op);
			}
		}
		template <typename Task>
		void TinyTaskQueue<Task>::Pop()
		{
			if (m_prevTask != NULL)
			{
				Task* tmp = m_prevTask;
				m_prevTask = TinyTaskAccess::Next(m_prevTask);
				if (m_prevTask == NULL)
					m_nextTask = NULL;
				TinyTaskAccess::Next(tmp, static_cast<Task*>(NULL));
			}
		}
		template <typename Task>
		void TinyTaskQueue<Task>::Push(Task* task)
		{
			TinyTaskAccess::Next(task, static_cast<Task*>(0));
			if (m_nextTask)
			{
				TinyTaskAccess::Next(m_nextTask, task);
				m_nextTask = task;
			}
			else
			{
				m_prevTask = m_prevTask = task;
			}
		}
		/// <summary>
		/// 任务基类，所有的操作都是Task
		/// </summary>
		class TinyBasicTask : public OVERLAPPED
		{
		protected:
			typedef void(*FunctionType)(void*, TinyBasicTask*, const error_code&, UINT);
		public:
			TinyBasicTask(FunctionType functionType);
			~TinyBasicTask();
			void Complete(void* owner, const error_code& ec, UINT bytes_transferred);
			void Reset();
			void Destory();
		private:
			FunctionType m_functionType;
		};
		/// <summary>
		/// Accept任务
		/// </summary>
		class AcceptTask : public TinyBasicTask
		{
		public:
			AcceptTask(SOCKET	socket);
			static void TaskComplete(void* owner, TinyBasicTask* op, const error_code& ec, UINT bytes_transferred);
			SOCKET	socket();
			CHAR*	data();
		private:
			SOCKET	m_socket;
			CHAR	m_data[1024];
		};
	};
}

