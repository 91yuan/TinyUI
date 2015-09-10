#pragma once
#include "TinyWindowMsg.h"
#include "TinyCollection.h"

namespace TinyUI
{
	/// <summary>
	/// ¾ä±úÓ³ÉäÀà
	/// </summary>
	template<class T = HANDLE, class V = void*>
	class TinyHandleMap
	{
		DISALLOW_COPY_AND_ASSIGN(TinyHandleMap)
	public:
		TinyHandleMap();
		~TinyHandleMap();
		V* Lookup(const T& _key);
		const V* Lookup(const T& _key) const;
		V* operator[](const T& _key);
		const V* operator[](const T& _key) const;
		void Add(const T& _key, V& _value);
		void Remove(const T& _key);
		void RemoveAll();
		INT GetSize() const;
	private:
		TinyMap<T, V> m_handleMap;
	};
	template<class T, class V>
	TinyHandleMap<T, V>::TinyHandleMap()
	{

	}
	template<class T, class V>
	TinyHandleMap<T, V>::~TinyHandleMap()
	{

	}
	template<class T, class V>
	V* TinyHandleMap<T, V>::Lookup(const T& _key)
	{
		return m_handleMap.GetValue(_key);
	}
	template<class T, class V>
	const V* TinyHandleMap<T, V>::Lookup(const T& _key) const
	{
		return m_handleMap.GetValue(_key);
	}
	template<class T, class V>
	V* TinyHandleMap<T, V>::operator[](const T& _key)
	{
		return m_handleMap.GetValue(_key);
	}
	template<class T, class V>
	const V* TinyHandleMap<T, V>::operator[](const T& _key) const
	{
		return m_handleMap.GetValue(_key);
	}
	template<class T, class V>
	void TinyHandleMap<T, V>::Add(const T& _key, V& _value)
	{
		m_handleMap.Add(_key, _value);
	}
	template<class T, class V>
	void TinyHandleMap<T, V>::Remove(const T& _key)
	{
		m_handleMap.Remove(_key);
	}
	template<class T, class V>
	void TinyHandleMap<T, V>::RemoveAll()
	{
		m_handleMap.RemoveAll();
	}
	template<class T, class V>
	INT TinyHandleMap<T, V>::GetSize() const
	{
		return m_handleMap.GetSize();
	}
	/// <summary>
	/// ´°¿Ú¾ä±úÀà
	/// </summary>
	class TinyHandleHWND :public TinyWindowMsg, public TinyMessageFilter
	{
	public:
		TinyHandleHWND();
		~TinyHandleHWND();
		operator HWND() const;
		HWND Handle() const;
		BOOL operator==(const TinyHandleHWND& obj) const;
		BOOL operator!=(const TinyHandleHWND& obj) const;
		BOOL Attach(HWND hWND);
		HWND Detach();
		static TinyHandleHWND* Lookup(HWND hWND);
	public:
		HWND m_hWND;
	};
	/// <summary>
	/// ²Ëµ¥¾ä±úÀà
	/// </summary>
	class TinyHandleHMENU
	{
	public:
		TinyHandleHMENU();
		~TinyHandleHMENU();
		operator HMENU() const;
		HMENU Handle() const;
		BOOL operator==(const TinyHandleHMENU& obj) const;
		BOOL operator!=(const TinyHandleHMENU& obj) const;
		BOOL Attach(HMENU hMENU);
		HMENU Detach();
		static TinyHandleHMENU* Lookup(HMENU hMENU);
	public:
		HMENU m_hMENU;
	};
	/// <summary>
	/// DC¾ä±úÀà
	/// </summary>
	class TinyHandleHDC
	{
	public:
		TinyHandleHDC();
		~TinyHandleHDC();
		operator HDC() const;
		HDC Handle() const;
		BOOL operator==(const TinyHandleHDC& obj) const;
		BOOL operator!=(const TinyHandleHDC& obj) const;
		BOOL Attach(HDC hDC);
		HDC Detach();
		static TinyHandleHDC* Lookup(HDC hDC);
	public:
		HDC m_hDC;
	};
	/// <summary>
	/// BITMAP¾ä±úÀà
	/// </summary>
	class TinyHandleHBITMAP
	{
	public:
		TinyHandleHBITMAP();
		~TinyHandleHBITMAP();
		operator HBITMAP() const;
		HBITMAP Handle() const;
		BOOL operator==(const TinyHandleHBITMAP& obj) const;
		BOOL operator!=(const TinyHandleHBITMAP& obj) const;
		BOOL Attach(HBITMAP hBITMAP);
		HBITMAP Detach();
		static TinyHandleHBITMAP* Lookup(HBITMAP hBITMAP);
	public:
		HBITMAP m_hBITMAP;
	};
	/// <summary>
	/// FONT¾ä±úÀà
	/// </summary>
	class TinyHandleHFONT
	{
	public:
		TinyHandleHFONT();
		~TinyHandleHFONT();
		operator HFONT() const;
		HFONT Handle() const;
		BOOL operator==(const TinyHandleHFONT& obj) const;
		BOOL operator!=(const TinyHandleHFONT& obj) const;
		BOOL Attach(HFONT hFONT);
		HFONT Detach();
		static TinyHandleHFONT* Lookup(HFONT hFONT);
	public:
		HFONT m_hFONT;
	};
	/// <summary>
	/// PEN¾ä±úÀà
	/// </summary>
	class TinyHandleHPEN
	{
	public:
		TinyHandleHPEN();
		~TinyHandleHPEN();
		operator HPEN() const;
		HPEN Handle() const;
		BOOL operator==(const TinyHandleHPEN& obj) const;
		BOOL operator!=(const TinyHandleHPEN& obj) const;
		BOOL Attach(HPEN hPEN);
		HPEN Detach();
		static TinyHandleHPEN* Lookup(HPEN hPEN);
	public:
		HPEN m_hPEN;
	};
	/// <summary>
	/// BRUSH¾ä±úÀà
	/// </summary>
	class TinyHandleHBRUSH
	{
	public:
		TinyHandleHBRUSH();
		~TinyHandleHBRUSH();
		operator HBRUSH() const;
		HBRUSH Handle() const;
		BOOL operator==(const TinyHandleHBRUSH& obj) const;
		BOOL operator!=(const TinyHandleHBRUSH& obj) const;
		BOOL Attach(HBRUSH hBRUSH);
		HBRUSH Detach();
		static TinyHandleHBRUSH* Lookup(HBRUSH hBRUSH);
	public:
		HBRUSH m_hBRUSH;
	};
	/// <summary>
	/// PALETTE¾ä±úÀà
	/// </summary>
	class TinyHandleHPALETTE
	{
	public:
		TinyHandleHPALETTE();
		~TinyHandleHPALETTE();
		operator HPALETTE() const;
		HPALETTE Handle() const;
		BOOL operator==(const TinyHandleHPALETTE& obj) const;
		BOOL operator!=(const TinyHandleHPALETTE& obj) const;
		BOOL Attach(HPALETTE hPALETTE);
		HPALETTE Detach();
		static TinyHandleHPALETTE* Lookup(HPALETTE hPALETTE);
	public:
		HPALETTE m_hPALETTE;
	};
	/// <summary>
	/// RGN¾ä±úÀà
	/// </summary>
	class TinyHandleHRGN
	{
	public:
		TinyHandleHRGN();
		~TinyHandleHRGN();
		operator HRGN() const;
		HRGN Handle() const;
		BOOL operator==(const TinyHandleHRGN& obj) const;
		BOOL operator!=(const TinyHandleHRGN& obj) const;
		BOOL Attach(HRGN hHRGN);
		HRGN Detach();
		static TinyHandleHRGN* Lookup(HRGN hHRGN);
	public:
		HRGN m_hHRGN;
	};
	/// <summary>
	/// IMAGELIST¾ä±úÀà
	/// </summary>
	class TinyHandleHIMAGELIST
	{
	public:
		TinyHandleHIMAGELIST();
		~TinyHandleHIMAGELIST();
		operator HIMAGELIST() const;
		HIMAGELIST Handle() const;
		BOOL operator==(const TinyHandleHIMAGELIST& obj) const;
		BOOL operator!=(const TinyHandleHIMAGELIST& obj) const;
		BOOL Attach(HIMAGELIST hIMAGELIST);
		HIMAGELIST Detach();
		static TinyHandleHIMAGELIST* Lookup(HIMAGELIST hIMAGELIST);
	public:
		HIMAGELIST m_hIMAGELIST;
	};
}

