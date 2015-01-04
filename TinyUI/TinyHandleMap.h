#pragma once
#include <map>
#include "TinyObject.h"
using namespace std;

namespace TinyUI
{
	/// <summary>
	/// 句柄对象映射类,std::map效率高点
	/// </summary>
	template<class T = HANDLE>
	class TinyHandleMap
	{
	public:
		TinyHandleMap();
		~TinyHandleMap();
		TinyObject* FromHandle(T& _value);
		TinyObject* operator[](T& _value);
		void AddHandle(T& _value, TinyObject* ps);
		void RemoveHandle(T& _value);
		INT GetSize() const;
	private:
		map<T, TinyObject*> m_handleMap;
	};
	template<class T>
	TinyHandleMap<T>::TinyHandleMap()
	{

	}
	template<class T>
	TinyHandleMap<T>::~TinyHandleMap()
	{
	}
	template<class T>
	TinyObject* TinyHandleMap<T>::FromHandle(T& _value)
	{
		map<T, TinyObject*>::iterator pos = m_handleMap.find(_value);
		if (pos != m_handleMap.end())
		{
			return pos->second;
		}
		return NULL;
	}
	template<class T>
	TinyObject* TinyHandleMap<T>::operator[](T& _value)
	{
		map<T, TinyObject*>::iterator pos = m_handleMap.find(_value);
		if (pos != m_handleMap.end())
		{
			return pos->second;
		}
		return NULL;
	}
	template<class T>
	void TinyHandleMap<T>::AddHandle(T& _value, TinyObject* ps)
	{
		m_handleMap.insert(map<T, TinyObject*>::value_type(_value, ps));
	}
	template<class T>
	void TinyHandleMap<T>::RemoveHandle(T& _value)
	{
		map<T, TinyObject*>::iterator pos = m_handleMap.find(_value);
		if (pos != m_handleMap.end())
		{
			m_handleMap.erase(pos);
		}
	}
	template<class T>
	INT TinyHandleMap<T>::GetSize() const
	{
		return m_handleMap.size();
	}
}

