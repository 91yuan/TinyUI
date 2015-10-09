#pragma once
#include "../Common/TinyCommon.h"
#include "../Common/TinyTime.h"

namespace TinyUI
{
	namespace IO
	{
#define SIZEINCR    0x1000
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
		/// <summary>
		/// 文件操作类
		/// </summary>
		class TinyFile : public TinyIO
		{
			DECLARE_DYNAMIC(TinyFile)
		public:
			enum OpenFlags
			{
				modeRead = (INT)0x00000,
				modeWrite = (INT)0x00001,
				modeReadWrite = (INT)0x00002,
				shareCompat = (INT)0x00000,
				shareExclusive = (INT)0x00010,
				shareDenyWrite = (INT)0x00020,
				shareDenyRead = (INT)0x00030,
				shareDenyNone = (INT)0x00040,
				modeNoInherit = (INT)0x00080,
				modeCreate = (INT)0x01000,
				modeNoTruncate = (INT)0x02000,
				typeText = (INT)0x04000, // typeText and typeBinary are
				typeBinary = (INT)0x08000, // used in derived classes only
				osNoBuffer = (INT)0x10000,
				osWriteThrough = (INT)0x20000,
				osRandomAccess = (INT)0x40000,
				osSequentialScan = (INT)0x80000,
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
		/// <summary>
		/// 内存文件
		/// </summary>
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
		/// <summary>
		/// 文件流
		/// </summary>
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
			virtual~TinyFileStream();
		private:
			LONG        m_cRef;
			HANDLE      m_hFile;
		};
		/// <summary>
		/// 内存流
		/// </summary>
		class TinyMemoryStream : public IStream
		{
		public:
			// *** IUnknown methods ***
			STDMETHOD(QueryInterface)(REFIID riid, void **ppvObj);
			STDMETHOD_(ULONG, AddRef)();
			STDMETHOD_(ULONG, Release)();
			// *** IStream methods ***
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
			LPBYTE ReAlloc(ULONG cbNew);
		public:
			TinyMemoryStream();
			virtual~TinyMemoryStream();
		public:
			LONG        m_cRef;
			LPBYTE      m_pData;
			UINT        m_cbAlloc;
			UINT        m_cbData;
			UINT        m_iSeek;
		};
	};
}


