#include "../stdafx.h"
#include "TinyIO.h"

namespace TinyUI
{
	const HANDLE TinyFile::hFileNull = INVALID_HANDLE_VALUE;

	TinyFile::TinyFile()
	{
		this->m_hFile = NULL;
		this->m_pzFileName = NULL;
		memset(m_pzPath, 0, sizeof(TCHAR)*MAX_PATH);
		memset(m_pzFileTitle, 0, sizeof(TCHAR)*MAX_PATH);
	}
	TinyFile::TinyFile(HANDLE hFile)
	{
		this->m_hFile = hFile;
		this->m_pzFileName = NULL;
		memset(m_pzPath, 0, sizeof(TCHAR)*MAX_PATH);
		memset(m_pzFileTitle, 0, sizeof(TCHAR)*MAX_PATH);
	}
	TinyFile::~TinyFile()
	{
		Close();
	}
	HANDLE TinyFile::Handle() const
	{
		return m_hFile;
	};
	BOOL TinyFile::Create(LPCTSTR lpszFileName, DWORD dwFlagsAndAttributes)
	{
		m_hFile = INVALID_HANDLE_VALUE;
		m_pzFileName = lpszFileName;
		dwFlagsAndAttributes |= FILE_ATTRIBUTE_NORMAL;
		HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, dwFlagsAndAttributes, NULL);
		if (hFile && hFile != INVALID_HANDLE_VALUE)
		{
			m_hFile = hFile;
			return TRUE;
		}
		return FALSE;
	}
	BOOL TinyFile::Open(LPCTSTR lpszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwFlagsAndAttributes)
	{
		m_hFile = INVALID_HANDLE_VALUE;
		m_pzFileName = lpszFileName;
		dwFlagsAndAttributes |= FILE_ATTRIBUTE_NORMAL;
		HANDLE hFile = CreateFile(lpszFileName, dwDesiredAccess, dwShareMode, NULL, OPEN_EXISTING, dwFlagsAndAttributes, NULL);
		if (hFile && hFile != INVALID_HANDLE_VALUE)
		{
			m_hFile = hFile;
			return TRUE;
		}
		return FALSE;
	}
	LPTSTR TinyFile::GetPath() const
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		ASSERT(m_pzFileName != NULL);
		DWORD dwRes = ::GetFullPathName(m_pzFileName, MAX_PATH, (LPTSTR)m_pzPath, NULL);
		return (LPTSTR)m_pzPath;
	}
	DWORD TinyFile::GetType() const
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		return ::GetFileType(m_hFile);
	}
	LPTSTR TinyFile::GetTitle() const
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		ASSERT(m_pzFileName != NULL);
		::GetFileTitle(m_pzFileName, (LPTSTR)m_pzFileTitle, MAX_PATH);
		return (LPTSTR)m_pzFileTitle;
	}
	BOOL TinyFile::SetSize(ULARGE_INTEGER newSize)
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		DWORD   newPos;
		if (newSize.HighPart != 0) return FALSE;
		newPos = SetFilePointer(m_hFile, (LONG)newSize.LowPart, NULL, FILE_BEGIN);
		if (newPos == -1) return FALSE;
		return ::SetEndOfFile(m_hFile);
	}
	DWORD TinyFile::GetSize() const
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		return ::GetFileSize(m_hFile, NULL);
	}

	BOOL TinyFile::LockRange(ULONGLONG dwPos, ULONGLONG dwCount)
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		ULARGE_INTEGER intPos;
		ULARGE_INTEGER intCount;
		intPos.QuadPart = dwPos;
		intCount.QuadPart = dwCount;
		return ::LockFile(m_hFile, intPos.LowPart, intPos.HighPart, intCount.LowPart, intCount.HighPart);
	}

	BOOL TinyFile::UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount)
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		ULARGE_INTEGER intPos;
		ULARGE_INTEGER intCount;
		intPos.QuadPart = dwPos;
		intCount.QuadPart = dwCount;
		return ::UnlockFile(m_hFile, intPos.LowPart, intPos.HighPart, intCount.LowPart, intCount.HighPart);
	}

	DWORD TinyFile::Read(void* pData, DWORD cbData)
	{
		ASSERT(pData != NULL);
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		if (cbData == 0) return 0;
		DWORD dw = 0;
		::ReadFile(m_hFile, pData, cbData, &dw, NULL);
		return dw;
	}
	DWORD TinyFile::Write(const void* pData, DWORD cbData)
	{
		ASSERT(pData != NULL);
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		if (cbData == 0) return 0;
		DWORD dw = 0;
		::WriteFile(m_hFile, pData, cbData, &dw, NULL);
		return dw;
	}
	//ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.chs/fileio/fs/setfilepointer.htm
	LONGLONG TinyFile::Seek(LONGLONG distance, DWORD dwMoveMethod)
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		LARGE_INTEGER pos;
		pos.QuadPart = distance;
		pos.LowPart = SetFilePointer(m_hFile, pos.LowPart, &pos.HighPart, dwMoveMethod);
		if (pos.LowPart == INVALID_SET_FILE_POINTER
			&& GetLastError() != NO_ERROR) return -1;
		return pos.QuadPart;
	}
	//ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.chs/fileio/fs/setfilepointer.htm
	LONGLONG TinyFile::GetPosition() const
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		LARGE_INTEGER pos;
		pos.QuadPart = 0;
		pos.LowPart = ::SetFilePointer(m_hFile, pos.LowPart, &pos.HighPart, FILE_CURRENT);
		if (pos.LowPart == INVALID_SET_FILE_POINTER
			&& GetLastError() != NO_ERROR) return -1;
		return pos.QuadPart;
	}
	ULONGLONG TinyFile::SeekToEnd()
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		LARGE_INTEGER pos;
		pos.QuadPart = 0;
		pos.LowPart = ::SetFilePointer(m_hFile, pos.LowPart, &pos.HighPart, FILE_END);
		if (pos.LowPart == INVALID_SET_FILE_POINTER
			&& GetLastError() != NO_ERROR) return -1;
		return pos.QuadPart;
	}
	ULONGLONG TinyFile::SeekToBegin()
	{
		ASSERT(m_hFile != INVALID_HANDLE_VALUE);
		LARGE_INTEGER pos;
		pos.QuadPart = 0;
		pos.LowPart = ::SetFilePointer(m_hFile, pos.LowPart, &pos.HighPart, FILE_BEGIN);
		if (pos.LowPart == INVALID_SET_FILE_POINTER
			&& GetLastError() != NO_ERROR) return -1;
		return pos.QuadPart;
	}
	BOOL TinyFile::Flush()
	{
		if (m_hFile == INVALID_HANDLE_VALUE) return FALSE;
		return ::FlushFileBuffers(m_hFile);
	}
	BOOL TinyFile::Close()
	{
		if (m_hFile == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}
		BOOL hRes = CloseHandle(m_hFile);
		if (hRes)
		{
			m_hFile = INVALID_HANDLE_VALUE;
			m_pzFileName = NULL;
		}
		return hRes;
	}
	BOOL TinyFile::Remove(LPCSTR pzFileName)
	{
		return DeleteFile(pzFileName);
	}
	BOOL TinyFile::Rename(LPCSTR lpszOldName, LPCTSTR lpszNewName)
	{
		return MoveFile(lpszOldName, lpszNewName);
	}
	BOOL TinyFile::Exists(LPCSTR pszPath)
	{
		BOOL bResult = FALSE;
		if (pszPath && IS_VALID_STRING_PTR(pszPath, -1))
		{
			DWORD errorMode;
			errorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
			bResult = (BOOL)(GetFileAttributes(pszPath) != (DWORD)-1);
			SetErrorMode(errorMode);
		}
		return bResult;
	};
	BOOL TinyFile::GetStatus(FileStatus& rStatus) const
	{
		memset(&rStatus, 0, sizeof(FileStatus));
		_tcsncpy_s(rStatus.m_szFullName, _countof(rStatus.m_szFullName), m_pzFileName, _TRUNCATE);
		if (m_hFile != hFileNull)
		{
			FILETIME ftCreate, ftAccess, ftModify;
			if (!::GetFileTime(m_hFile, &ftCreate, &ftAccess, &ftModify))
				return FALSE;

			LARGE_INTEGER li;

			if (::GetFileSizeEx(m_hFile, &li) == 0)
				return FALSE;

			rStatus.m_size = li.QuadPart;


			if (m_pzFileName == NULL)
				rStatus.m_attribute = 0;
			else
			{
				DWORD dwAttribute = ::GetFileAttributes(m_pzFileName);
				if (dwAttribute == 0xFFFFFFFF)
					rStatus.m_attribute = 0;
				else
				{
					rStatus.m_attribute = (BYTE)dwAttribute;
				}
			}
			if (TinyTime::IsValidFILETIME(ftCreate))
			{
				rStatus.m_ctime = TinyTime(ftCreate);
			}
			else
			{
				rStatus.m_ctime = TinyTime();
			}

			if (TinyTime::IsValidFILETIME(ftAccess))
			{
				rStatus.m_atime = TinyTime(ftAccess);
			}
			else
			{
				rStatus.m_atime = TinyTime();
			}

			if (TinyTime::IsValidFILETIME(ftModify))
			{
				rStatus.m_mtime = TinyTime(ftModify);
			}
			else
			{
				rStatus.m_mtime = TinyTime();
			}

			if (rStatus.m_ctime.GetTime() == 0)
				rStatus.m_ctime = rStatus.m_mtime;

			if (rStatus.m_atime.GetTime() == 0)
				rStatus.m_atime = rStatus.m_mtime;
		}
		return TRUE;
	}
	BOOL PASCAL TinyFile::GetStatus(LPCTSTR lpszFileName, FileStatus& rStatus)
	{
		ASSERT(lpszFileName != NULL);
		if (lpszFileName == NULL)
		{
			return FALSE;
		}
		if (lstrlen(lpszFileName) >= _MAX_PATH)
		{
			ASSERT(FALSE);
			return FALSE;
		}

		WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
		if (!GetFileAttributesEx(lpszFileName, GetFileExInfoStandard, &fileAttributeData))
			return FALSE;

		rStatus.m_attribute = (BYTE)
			(fileAttributeData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

		rStatus.m_size = fileAttributeData.nFileSizeHigh;
		rStatus.m_size <<= 32;
		rStatus.m_size |= fileAttributeData.nFileSizeLow;

		if (TinyTime::IsValidFILETIME(fileAttributeData.ftCreationTime))
		{
			rStatus.m_ctime = TinyTime(fileAttributeData.ftCreationTime);
		}
		else
		{
			rStatus.m_ctime = TinyTime();
		}

		if (TinyTime::IsValidFILETIME(fileAttributeData.ftLastAccessTime))
		{
			rStatus.m_atime = TinyTime(fileAttributeData.ftLastAccessTime);
		}
		else
		{
			rStatus.m_atime = TinyTime();
		}

		if (TinyTime::IsValidFILETIME(fileAttributeData.ftLastWriteTime))
		{
			rStatus.m_mtime = TinyTime(fileAttributeData.ftLastWriteTime);
		}
		else
		{
			rStatus.m_mtime = TinyTime();
		}

		if (rStatus.m_ctime.GetTime() == 0)
			rStatus.m_ctime = rStatus.m_mtime;

		if (rStatus.m_atime.GetTime() == 0)
			rStatus.m_atime = rStatus.m_mtime;

		return TRUE;
	}
	//ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.chs/memory/base/obtaining_a_file_name_from_a_file_handle.htm
	BOOL TinyFile::GetFileNameFromHandle(HANDLE hFile, LPTSTR pszFilename)
	{
		BOOL bSuccess = FALSE;
		HANDLE hFileMap;
		DWORD dwFileSizeHi = 0;
		DWORD dwFileSizeLo = ::GetFileSize(hFile, &dwFileSizeHi);
		if (dwFileSizeLo == 0 && dwFileSizeHi == 0) return FALSE;
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, MAX_PATH, NULL);
		if (hFileMap)
		{
			void* pMapView = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);
			if (pMapView)
			{
				if (GetMappedFileName(GetCurrentProcess(), pMapView, pszFilename, MAX_PATH))
				{
					TCHAR szTemp[1024];
					szTemp[0] = '\0';
					if (GetLogicalDriveStrings(1024 - 1, szTemp))
					{
						TCHAR szName[MAX_PATH];
						TCHAR szDrive[3] = TEXT(" :");
						BOOL bFound = FALSE;
						TCHAR* p = szTemp;
						do
						{
							*szDrive = *p;
							if (QueryDosDevice(szDrive, szName, 1024))
							{
								UINT iNameSize = _tcslen(szName);
								if (iNameSize < MAX_PATH)
								{
									bFound = _tcsnicmp(pszFilename, szName, iNameSize) == 0;
									if (bFound)
									{
										TCHAR szTempFile[MAX_PATH];
										StringCchPrintf(szTempFile,
											MAX_PATH,
											TEXT("%s%s"),
											szDrive,
											pszFilename + iNameSize);
										StringCchCopyN(pszFilename, MAX_PATH + 1, szTempFile, _tcslen(szTempFile));
									}
								}
							}
							while (*p++);
						} while (!bFound && *p);
					}
				}
				bSuccess = TRUE;
				UnmapViewOfFile(pMapView);
			}
			CloseHandle(hFileMap);
		}
		return(bSuccess);
	}
	//////////////////////////////////////////////////////////////////////////
	TinyFileStream::TinyFileStream(HANDLE hf, DWORD grfMode)
		:m_cRef(1),
		m_hFile(hf)
	{
	}

	TinyFileStream::~TinyFileStream()
	{
		ASSERT(this->m_hFile != INVALID_HANDLE_VALUE);
		CloseHandle(m_hFile);
	}

	STDMETHODIMP TinyFileStream::QueryInterface(REFIID riid, void **ppvObj)
	{
		if (IsEqualIID(riid, IID_IStream) || IsEqualIID(riid, IID_IUnknown))
		{
			*ppvObj = this;
		}
		else
		{
			*ppvObj = NULL;
			return E_NOINTERFACE;
		}
		AddRef();
		return NOERROR;
	}

	STDMETHODIMP_(ULONG) TinyFileStream::AddRef()
	{
		return InterlockedIncrement(&this->m_cRef);
	}

	STDMETHODIMP_(ULONG) TinyFileStream::Release()
	{
		if (InterlockedDecrement(&this->m_cRef))
		{
			return this->m_cRef;
		}
		delete this;
		return NOERROR;
	}

	STDMETHODIMP TinyFileStream::Read(VOID *pv, ULONG cb, ULONG *pcbRead)
	{
		ULONG   cbRead;
		HRESULT hRes = S_OK;
		if (!pv) return E_INVALIDARG;
		if (!pcbRead)
		{
			pcbRead = &cbRead;
		}
		hRes = (::ReadFile(m_hFile, pv, cb, pcbRead, NULL) ? S_OK : S_FALSE);
		return hRes;
	}

	STDMETHODIMP TinyFileStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
	{
		ULONG   cbWritten;
		HRESULT hRes;
		if (!pv) return E_INVALIDARG;
		if (!pcbWritten)
		{
			pcbWritten = &cbWritten;
		}
		hRes = (::WriteFile(m_hFile, pv, cb, pcbWritten, NULL) ? S_OK : S_FALSE);
		return hRes;
	}

	STDMETHODIMP TinyFileStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
	{
		DWORD           dwMoveMethod;
		switch (dwOrigin)
		{
		case STREAM_SEEK_SET: dwMoveMethod = FILE_BEGIN; break;
		case STREAM_SEEK_CUR: dwMoveMethod = FILE_CURRENT; break;
		case STREAM_SEEK_END: dwMoveMethod = FILE_END; break;
		default:
			return E_INVALIDARG;
		}
		DWORD dwCurrent = ::SetFilePointer(m_hFile, dlibMove.LowPart, NULL, dwMoveMethod);
		if (plibNewPosition)
		{
			plibNewPosition->LowPart = dwCurrent;
			plibNewPosition->HighPart = 0;
		}
		return NOERROR;
	}

	STDMETHODIMP TinyFileStream::SetSize(ULARGE_INTEGER libNewSize)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyFileStream::CopyTo(IStream *pstmTo, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
	{
		BYTE data[512];
		ULONG cbRead;
		HRESULT hRes = NOERROR;
		if (pcbRead)
		{
			pcbRead->LowPart = 0;
			pcbRead->HighPart = 0;
		}
		if (pcbWritten)
		{
			pcbWritten->LowPart = 0;
			pcbWritten->HighPart = 0;
		}
		ASSERT(cb.HighPart == 0);
		while (cb.LowPart)
		{
			hRes = this->Read(data, min(cb.LowPart, sizeof(data)), &cbRead);
			if (pcbRead) pcbRead->LowPart += cbRead;
			if (FAILED(hRes) || (cbRead == 0)) break;
			cb.LowPart -= cbRead;
			hRes = pstmTo->Write(data, cbRead, &cbRead);
			if (pcbWritten)	pcbWritten->LowPart += cbRead;
			if (FAILED(hRes) || (cbRead == 0))	break;
		}
		return hRes;
	}

	STDMETHODIMP TinyFileStream::Commit(DWORD grfCommitFlags)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyFileStream::Revert()
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyFileStream::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyFileStream::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyFileStream::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyFileStream::Clone(IStream * *ppstm)
	{
		return E_NOTIMPL;
	}
	//////////////////////////////////////////////////////////////////////////
	TinyMemoryFile::TinyMemoryFile(BYTE* pBuffer, LONGLONG dwBufferSize)
		:m_pBuffer(pBuffer),
		m_dwBufferSize(dwBufferSize),
		m_dwPosition(0)
	{
	}
	TinyMemoryFile::~TinyMemoryFile()
	{
		Close();
	}
	LONGLONG TinyMemoryFile::GetPosition() const
	{
		if (m_pBuffer == NULL) return -1;
		return m_dwPosition;
	}
	BOOL TinyMemoryFile::SetSize(LONGLONG dwNewLen)
	{
		if (dwNewLen > ULONG_MAX)
			return FALSE;

		if (dwNewLen > m_dwBufferSize)
		{
			if (!Realloc(dwNewLen))
				return FALSE;
		}
		if (dwNewLen < m_dwPosition)
			m_dwPosition = dwNewLen;
		m_dwBufferSize = dwNewLen;
		return TRUE;
	}
	LONGLONG TinyMemoryFile::GetSize() const
	{
		return m_dwBufferSize;
	}
	BOOL TinyMemoryFile::Realloc(LONGLONG dwNewLen)
	{
		if (dwNewLen > m_dwBufferSize)
		{
			LONGLONG dwNewBufferSize = m_dwBufferSize;
			while (dwNewBufferSize < dwNewLen)
				dwNewBufferSize += 1024;

			BYTE* lpNew = NULL;
			if (m_pBuffer == NULL)
				lpNew = (BYTE*)malloc(static_cast<size_t>(dwNewBufferSize));
			else
				lpNew = (BYTE*)realloc(m_pBuffer, static_cast<size_t>(dwNewBufferSize));

			if (lpNew == NULL)
				return FALSE;

			m_pBuffer = lpNew;
			m_dwBufferSize = dwNewBufferSize;
			return TRUE;
		}
		return FALSE;
	}
	/************************************************************************/
	/* dwMoveMethod only can have SEEK_SET, SEEK_CUR ,SEEK_END              */
	/************************************************************************/
	LONGLONG TinyMemoryFile::Seek(LONGLONG lOff, DWORD dwMoveMethod)
	{
		LONGLONG lNewPos = m_dwPosition;
		if (dwMoveMethod == SEEK_SET)
			lNewPos = lOff;
		else if (dwMoveMethod == SEEK_CUR)
			lNewPos += lOff;
		else if (dwMoveMethod == SEEK_END)
			lNewPos = m_dwBufferSize + lOff;
		if (lNewPos < 0) lNewPos = 0;
		if (lNewPos > m_dwBufferSize)
		{
			if (!Realloc((m_dwPosition + lNewPos)))
				return FALSE;
		}
		m_dwPosition = lNewPos;
		return m_dwPosition;
	}

	DWORD TinyMemoryFile::Read(void* pData, DWORD cbData)
	{
		if (pData == NULL || cbData == 0)
			return FALSE;
		if (m_dwPosition > m_dwBufferSize)
			return FALSE;
		UINT readSize = 0;
		if ((m_dwPosition + cbData) > m_dwBufferSize || (m_dwPosition + cbData) < m_dwPosition)
			readSize = (UINT)(m_dwBufferSize - m_dwPosition);
		else
			readSize = cbData;
		memcpy_s((BYTE*)pData, readSize, (BYTE*)m_pBuffer + m_dwPosition, readSize);
		m_dwPosition += readSize;
		return readSize;
	}

	DWORD TinyMemoryFile::Write(const void* pData, DWORD cbData)
	{
		if (pData == NULL || cbData == 0)
			return FALSE;

		if ((m_dwPosition + cbData) < m_dwPosition)
			return FALSE;

		//超出当前缓冲区大小重新分配大小
		if ((m_dwPosition + cbData) > m_dwBufferSize)
		{
			if (!Realloc((m_dwPosition + cbData)))
				return FALSE;
		}
		memcpy_s((BYTE*)pData + m_dwPosition, cbData, (BYTE*)pData, cbData);
		m_dwPosition += cbData;
		if (m_dwPosition > m_dwBufferSize)
			m_dwBufferSize = m_dwPosition;
		return cbData;
	}

	BOOL TinyMemoryFile::LockRange(ULONGLONG dwPos, ULONGLONG dwCount)
	{
		return TRUE;
	}

	BOOL TinyMemoryFile::UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount)
	{
		return TRUE;
	}

	BOOL TinyMemoryFile::Flush()
	{
		return TRUE;
	}

	BOOL TinyMemoryFile::Close()
	{
		if (m_pBuffer != NULL)
		{
			free(m_pBuffer);
			m_pBuffer = NULL;
		}
		m_dwPosition = 0;
		m_dwBufferSize = 0;
		return TRUE;
	}
	//////////////////////////////////////////////////////////////////////////
	STDAPI CreateStreamOnFile(LPCTSTR pszFile, DWORD grfMode, IStream **ppstm)
	{
		HANDLE hFile;
		*ppstm = NULL;
		if (grfMode &
			~(STGM_READ |
			STGM_WRITE |
			STGM_SHARE_DENY_NONE |
			STGM_SHARE_DENY_READ |
			STGM_SHARE_DENY_WRITE |
			STGM_SHARE_EXCLUSIVE |
			STGM_READWRITE |
			STGM_CREATE))
		{
			TRACE(TEXT("CreateSreamOnFile: Invalid STGM_ mode"));
			return E_INVALIDARG;
		}

		if (grfMode & STGM_CREATE)
		{
			DWORD dwAttrib = GetFileAttributes(pszFile);
			if ((DWORD)-1 == dwAttrib)
			{
				dwAttrib = 0;
			}
			hFile = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
				dwAttrib, NULL);
		}
		else
		{
			DWORD dwDesiredAccess, dwShareMode, dwShareBits;
			if (grfMode & STGM_WRITE)
			{
				dwDesiredAccess = GENERIC_WRITE;
			}
			else
			{
				dwDesiredAccess = GENERIC_READ;
			}
			if (grfMode & STGM_READWRITE)
			{
				dwDesiredAccess |= (GENERIC_READ | GENERIC_WRITE);
			}
			dwShareBits = grfMode & (STGM_SHARE_EXCLUSIVE |
				STGM_SHARE_DENY_WRITE |
				STGM_SHARE_DENY_READ |
				STGM_SHARE_DENY_NONE);
			switch (dwShareBits) {
			case STGM_SHARE_DENY_WRITE:
				dwShareMode = FILE_SHARE_READ;
				break;
			case STGM_SHARE_DENY_READ:
				dwShareMode = FILE_SHARE_WRITE;
				break;
			case STGM_SHARE_EXCLUSIVE:
				dwShareMode = 0;
				break;
			default:
				dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
				break;
			}


			hFile = CreateFile(pszFile, dwDesiredAccess, dwShareMode, NULL,
				OPEN_EXISTING, 0, NULL);
		}

		if (hFile == INVALID_HANDLE_VALUE)
		{
			TRACE(TEXT("CreateSreamOnFile: CreateFileW() failed %s"), pszFile);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		*ppstm = (IStream *)new TinyFileStream(hFile, grfMode);
		if (*ppstm)
		{
			return S_OK;
		}
		else
		{
			CloseHandle(hFile);
			return E_OUTOFMEMORY;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	TinyMemoryStream::TinyMemoryStream()
		:m_cRef(1),
		m_pData(NULL),
		m_cbAlloc(0),
		m_cbData(0),
		m_iSeek(0)
	{

	}
	TinyMemoryStream::~TinyMemoryStream()
	{

	}
	STDMETHODIMP TinyMemoryStream::QueryInterface(REFIID riid, void **ppvObj)
	{
		if (IsEqualIID(riid, IID_IStream) || IsEqualIID(riid, IID_IUnknown))
		{
			*ppvObj = this;
		}
		else
		{
			*ppvObj = NULL;
			return E_NOINTERFACE;
		}
		AddRef();
		return NOERROR;
	}
	STDMETHODIMP_(ULONG) TinyMemoryStream::AddRef()
	{
		return InterlockedIncrement(&this->m_cRef);
	}
	STDMETHODIMP_(ULONG) TinyMemoryStream::Release()
	{
		if (InterlockedDecrement(&this->m_cRef))
		{
			return this->m_cRef;
		}
		if (this->m_pData)
		{
			LocalFree(this->m_pData);
			this->m_pData = NULL;
		}
		delete this;
		return NOERROR;
	}
	STDMETHODIMP TinyMemoryStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
	{
		ASSERT(pv);
		if (!cb)
		{
			if (pcbRead != NULL)
			{
				*pcbRead = 0;
			}
			return NOERROR;
		}
		if (this->m_iSeek >= this->m_cbData)
		{
			if (pcbRead != NULL)
			{
				*pcbRead = 0;
			}
		}
		else
		{
			if ((this->m_iSeek + cb) > this->m_cbData)
			{
				cb = this->m_cbData - this->m_iSeek;
			}
			ASSERT(this->m_pData);
			CopyMemory(pv, this->m_pData + this->m_iSeek, cb);
			this->m_iSeek += (UINT)cb;
			if (pcbRead != NULL)
			{
				*pcbRead = cb;
			}
		}
		return NOERROR;
	}
	STDMETHODIMP TinyMemoryStream::Write(void const *pv, ULONG cb, ULONG *pcbWritten)
	{
		if (!cb)
		{
			if (pcbWritten != NULL)	*pcbWritten = 0;
			return NOERROR;
		}
		if ((this->m_iSeek + cb) > this->m_cbAlloc)
		{
			if (ReAlloc(this->m_iSeek + (UINT)cb + SIZEINCR) == NULL)
				return STG_E_INSUFFICIENTMEMORY;
		}
		ASSERT(this->m_pData);
		if (this->m_iSeek > this->m_cbData)
		{
			ZeroMemory(this->m_pData + this->m_cbData, this->m_iSeek - this->m_cbData);
		}
		CopyMemory(this->m_pData + this->m_iSeek, pv, cb);
		this->m_iSeek += (UINT)cb;
		if (this->m_iSeek > this->m_cbData) this->m_cbData = this->m_iSeek;
		if (pcbWritten != NULL)	*pcbWritten = cb;
		return NOERROR;
	}
	STDMETHODIMP TinyMemoryStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
	{
		LONG lNewSeek;
		switch (dwOrigin)
		{
		case STREAM_SEEK_SET:
			lNewSeek = (LONG)dlibMove.LowPart;
			break;
		case STREAM_SEEK_CUR:
			lNewSeek = (LONG)this->m_iSeek + (LONG)dlibMove.LowPart;
			break;
		case STREAM_SEEK_END:
			lNewSeek = (LONG)this->m_cbData + (LONG)dlibMove.LowPart;
			break;
		default:
			return STG_E_INVALIDPARAMETER;
		}
		if (lNewSeek < 0)	return STG_E_INVALIDFUNCTION;
		this->m_iSeek = (UINT)lNewSeek;
		if (plibNewPosition != NULL)
		{
			plibNewPosition->LowPart = (DWORD)lNewSeek;
			plibNewPosition->HighPart = 0;
		}
		return NOERROR;
	}
	STDMETHODIMP TinyMemoryStream::SetSize(ULARGE_INTEGER libNewSize)
	{
		UINT cbNew = (UINT)libNewSize.LowPart;
		if (cbNew > this->m_cbData)
		{
			if (cbNew > this->m_cbAlloc)
			{
				if (ReAlloc(cbNew) == NULL)	return STG_E_INSUFFICIENTMEMORY;
			}
			ZeroMemory(this->m_pData + this->m_cbData, cbNew - this->m_cbData);
		}
		this->m_cbData = cbNew;
		return NOERROR;
	}

	STDMETHODIMP TinyMemoryStream::CopyTo(IStream *pstmTo, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
	{
		HRESULT hRes = NOERROR;
		UINT cbRead = this->m_cbData - this->m_iSeek;
		ULONG cbWritten = 0;
		if (cb.HighPart == 0 && cb.LowPart < cbRead)
		{
			cbRead = cb.LowPart;
		}
		if (cbRead > 0)
		{
			hRes = pstmTo->Write(this->m_pData + this->m_iSeek, cbRead, &cbWritten);
			this->m_iSeek += cbRead;
		}
		if (pcbRead)
		{
			pcbRead->LowPart = cbRead;
			pcbRead->HighPart = 0;
		}
		if (pcbWritten)
		{
			pcbWritten->LowPart = cbWritten;
			pcbWritten->HighPart = 0;
		}
		return hRes;
	}
	STDMETHODIMP TinyMemoryStream::Commit(DWORD grfCommitFlags)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyMemoryStream::Revert()
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyMemoryStream::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyMemoryStream::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP TinyMemoryStream::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
	{
		ZeroMemory(pstatstg, sizeof(*pstatstg));
		pstatstg->type = STGTY_STREAM;
		pstatstg->cbSize.LowPart = this->m_cbData;
		pstatstg->grfMode = STGM_READWRITE;
		return S_OK;
	}

	STDMETHODIMP TinyMemoryStream::Clone(IStream **ppstm)
	{
		*ppstm = NULL;
		return E_NOTIMPL;
	}
	LPBYTE TinyMemoryStream::ReAlloc(ULONG cbNew)
	{
		if (this->m_pData == NULL)
		{
			this->m_pData = (LPBYTE)LocalAlloc(LPTR, cbNew);
		}
		else
		{
			LPBYTE ps = (LPBYTE)LocalReAlloc(this->m_pData, cbNew, LMEM_MOVEABLE | LMEM_ZEROINIT);
			if (ps)
			{
				this->m_pData = ps;
			}
			else
			{
				TRACE("Stream Realloc Failed!");
				return NULL;
			}
		}
		if (this->m_pData)
		{
			this->m_cbAlloc = cbNew;
		}
		return this->m_pData;
	}
	//////////////////////////////////////////////////////////////////////////
	STDAPI CreateStreamOnMemory(LPBYTE pInit, UINT cbInit, IStream **ppstm)
	{
		UINT l_cbAlloc = sizeof(TinyMemoryStream);
		TinyMemoryStream *localthis = (TinyMemoryStream *)LocalAlloc(LPTR, l_cbAlloc);
		if (localthis)
		{
			new (localthis)TinyMemoryStream;//Place New
			localthis->m_cRef = 1;
			if ((pInit != NULL) && (cbInit > 0))
			{
				if (localthis->ReAlloc(cbInit) == NULL)
				{
					LocalFree((HLOCAL)localthis);
					return NULL;
				}
				localthis->m_cbData = cbInit;
				CopyMemory(localthis->m_pData, pInit, cbInit);
			}
			*ppstm = (IStream *)localthis;
			return S_OK;
		}
		return E_OUTOFMEMORY;
	}

}
