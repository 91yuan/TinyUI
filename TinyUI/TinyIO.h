#pragma once
#include "TinyCommon.h"
#include "TinyTime.h"

namespace TinyUI
{
	struct FileStatus
	{
		TinyTime m_ctime;
		TinyTime m_mtime;
		TinyTime m_atime;
		ULONGLONG m_size;
		BYTE m_attribute;
		BYTE _m_padding;
		TCHAR m_szFullName[_MAX_PATH];
	};
	//虚基类
	class TinyIO : public TinyObject
	{
		DECLARE_DYNAMIC(TinyIO)
	public:
		virtual LONGLONG Seek(LONGLONG lOff, DWORD dwMoveMethod) = 0;
		virtual DWORD Read(void* pData, DWORD cbData) = 0;
		virtual DWORD Write(const void* pData, DWORD cbData) = 0;
		virtual BOOL LockRange(ULONGLONG dwPos, ULONGLONG dwCount) = 0;
		virtual BOOL UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount) = 0;
		virtual BOOL Flush() = 0;
		virtual BOOL Close() = 0;
	};
	//////////////////////////////////////////////////////////////////////////
	class TinyFile : public TinyIO
	{
		DECLARE_DYNAMIC(TinyFile)
	public:
		enum OpenFlags
		{
			modeRead = (int)0x00000,
			modeWrite = (int)0x00001,
			modeReadWrite = (int)0x00002,
			shareCompat = (int)0x00000,
			shareExclusive = (int)0x00010,
			shareDenyWrite = (int)0x00020,
			shareDenyRead = (int)0x00030,
			shareDenyNone = (int)0x00040,
			modeNoInherit = (int)0x00080,
			modeCreate = (int)0x01000,
			modeNoTruncate = (int)0x02000,
			typeText = (int)0x04000, // typeText and typeBinary are
			typeBinary = (int)0x08000, // used in derived classes only
			osNoBuffer = (int)0x10000,
			osWriteThrough = (int)0x20000,
			osRandomAccess = (int)0x40000,
			osSequentialScan = (int)0x80000,
		};

		enum Attribute
		{
			normal = 0x00,
			readOnly = 0x01,
			hidden = 0x02,
			system = 0x04,
			volume = 0x08,
			directory = 0x10,
			archive = 0x20
		};
	public:
		static const HANDLE hFileNull;
		TinyFile();
		TinyFile(HANDLE hFile);
		virtual ~TinyFile();
		HANDLE Handle() const;
		BOOL GetStatus(FileStatus& rStatus) const;
		virtual BOOL Create(LPCTSTR lpszFileName, DWORD dwFlagsAndAttributes);
		virtual BOOL Open(LPCTSTR lpszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwFlagsAndAttributes);
		virtual LONGLONG GetPosition() const;
		virtual LPTSTR GetTitle() const;
		virtual LPTSTR GetPath() const;
		virtual BOOL SetSize(ULARGE_INTEGER dwNewLen);
		virtual DWORD GetSize() const;
		virtual DWORD GetType() const;
		//////////////////////////////////////////////////////////////////////////
		ULONGLONG SeekToEnd();
		ULONGLONG SeekToBegin();
		virtual LONGLONG Seek(LONGLONG lOff, DWORD dwMoveMethod);
		virtual DWORD Read(void* pData, DWORD cbData);
		virtual DWORD Write(const void* pData, DWORD cbData);
		virtual BOOL LockRange(ULONGLONG dwPos, ULONGLONG dwCount);
		virtual BOOL UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount);
		virtual BOOL Flush();
		virtual BOOL Close();
		//////////////////////////////////////////////////////////////////////////
		static BOOL PASCAL GetStatus(LPCTSTR lpszFileName, FileStatus& rStatus);
		static void PASCAL SetStatus(LPCTSTR lpszFileName, const FileStatus& status);
		static BOOL Exists(LPCSTR pszPath);
		static BOOL Rename(LPCSTR lpszOldName, LPCTSTR lpszNewName);
		static BOOL Remove(LPCSTR lpszFileName);
		static BOOL GetFileNameFromHandle(HANDLE hFile, LPTSTR pszFileName);//获得文件的绝对路径
	private:
		HANDLE	m_hFile;
		LPCTSTR m_pzFileName;
		TCHAR	m_pzFileTitle[MAX_PATH];
		TCHAR	m_pzPath[MAX_PATH];
	};
	//////////////////////////////////////////////////////////////////////////
	class TinyMemoryFile : public TinyIO
	{
		DECLARE_DYNAMIC(TinyMemoryFile)
	public:
		virtual LONGLONG Seek(LONGLONG lOff, DWORD dwMoveMethod);
		virtual DWORD Read(void* pData, DWORD cbData);
		virtual DWORD Write(const void* pData, DWORD cbData);
		virtual BOOL LockRange(ULONGLONG dwPos, ULONGLONG dwCount);
		virtual BOOL UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount);
		virtual BOOL Flush();
		virtual BOOL Close();
	public:
		TinyMemoryFile(BYTE* pBuffer = NULL, LONGLONG dwBufferSize = 0);
		virtual ~TinyMemoryFile();
		virtual LONGLONG GetPosition() const;
		virtual BOOL SetSize(LONGLONG dwNewLen);
		virtual LONGLONG GetSize() const;
	private:
		BOOL Realloc(LONGLONG dwNewLen);
	private:
		BYTE*		m_pBuffer;
		LONGLONG	m_dwBufferSize;
		LONGLONG	m_dwPosition;
	};
	//////////////////////////////////////////////////////////////////////////
	class TinyFileStream : public IStream
	{
	public:
		// *** IUnknown methods ***
		STDMETHOD(QueryInterface) (REFIID riid, void **ppvObj);
		STDMETHOD_(ULONG, AddRef) ();
		STDMETHOD_(ULONG, Release) ();

		// *** IStream methods ***
		STDMETHOD(Read) (VOID *pv, ULONG cb, ULONG *pcbRead);
		STDMETHOD(Write) (VOID const *pv, ULONG cb, ULONG *pcbWritten);
		STDMETHOD(Seek) (LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
		STDMETHOD(SetSize) (ULARGE_INTEGER libNewSize);
		STDMETHOD(CopyTo) (IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
		STDMETHOD(Commit) (DWORD grfCommitFlags);
		STDMETHOD(Revert) ();
		STDMETHOD(LockRegion) (ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
		STDMETHOD(UnlockRegion) (ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
		STDMETHOD(Stat) (STATSTG *pstatstg, DWORD grfStatFlag);
		STDMETHOD(Clone)(IStream **ppstm);

	public:
		TinyFileStream(HANDLE hf, DWORD grfMode);
		~TinyFileStream();

	private:
		LONG        cRef;
		HANDLE      hFile;
	};
#define SIZEINCR    0x1000
	class TinyMemoryStream : public IStream
	{
	public:
		STDMETHOD(QueryInterface)(REFIID riid, void **ppvObj);
		STDMETHOD_(ULONG, AddRef)();
		STDMETHOD_(ULONG, Release)();
		//////////////////////////////////////////////////////////////////////////
		STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead);
		STDMETHOD(Write)(void const *pv, ULONG cb, ULONG *pcbWritten);
		STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
		STDMETHOD(SetSize)(ULARGE_INTEGER libNewSize);
		STDMETHOD(CopyTo)(IStream *, ULARGE_INTEGER, ULARGE_INTEGER *, ULARGE_INTEGER *);
		STDMETHOD(Commit)(DWORD);
		STDMETHOD(Revert)();
		STDMETHOD(LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
		STDMETHOD(UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
		STDMETHOD(Stat)(STATSTG *, DWORD);
		STDMETHOD(Clone)(IStream **);
		//////////////////////////////////////////////////////////////////////////
		LPBYTE ReAlloc(ULONG cbNew);
	public:
		LONG        cRef;
		LPBYTE      pData;
		UINT        cbAlloc;
		UINT        cbData;
		UINT        iSeek;
	};
}


