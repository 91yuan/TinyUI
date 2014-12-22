#pragma once
#include <time.h>
#include "TinyObject.h"
#ifndef __oledb_h__
struct tagDBTIMESTAMP;
typedef tagDBTIMESTAMP DBTIMESTAMP;
#endif

namespace TinyUI
{
	const int maxTimeBufferSize = 128;
	const long maxDaysInSpan = 3615897L;
	inline BOOL ConvertSystemTimeToVariantTime(const SYSTEMTIME& systimeSrc, double* pVarDtTm);
	extern __declspec(selectany) const TCHAR * const szInvalidDateTime = _T("Invalid DateTime");

	/// <summary>
	/// 时间间隔类
	/// </summary>
	class TinyTimeSpan : public TinyObject
	{
		DECLARE_DYNAMIC(TinyTimeSpan);
	public:
		TinyTimeSpan() throw();
		TinyTimeSpan(__time64_t time) throw();
		TinyTimeSpan(LONG lDays, int nHours, int nMins, int nSecs) throw();
		__time64_t GetTimeSpan() const throw();
		LONGLONG GetDays() const throw();
		LONGLONG GetTotalHours() const throw();
		LONG GetHours() const throw();
		LONGLONG GetTotalMinutes() const throw();
		LONG GetMinutes() const throw();
		LONGLONG GetTotalSeconds() const throw();
		LONG GetSeconds() const throw();
		TinyTimeSpan operator+(TinyTimeSpan span) const throw();
		TinyTimeSpan operator-(TinyTimeSpan span) const throw();
		TinyTimeSpan& operator+=(TinyTimeSpan span) throw();
		TinyTimeSpan& operator-=(TinyTimeSpan span) throw();
		BOOL operator==(TinyTimeSpan span) const throw();
		BOOL operator!=(TinyTimeSpan span) const throw();
		BOOL operator<(TinyTimeSpan span) const throw();
		BOOL operator>(TinyTimeSpan span) const throw();
		BOOL operator<=(TinyTimeSpan span) const throw();
		BOOL operator>=(TinyTimeSpan span) const throw();
	private:
		__time64_t m_timeSpan;
	};
	/// <summary>
	/// 时间类
	/// </summary>
	class TinyTime : public TinyObject
	{
		DECLARE_DYNAMIC(TinyTime);
	public:
		static TinyTime WINAPI GetCurrentTime() throw();
		static BOOL WINAPI IsValidFILETIME(const FILETIME& ft) throw();

		TinyTime() throw();
		TinyTime(__time64_t time) throw();

		__time64_t GetTime() const throw();

		TinyTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec, INT nDST = -1);
		TinyTime(WORD wDosDate, WORD wDosTime, INT nDST = -1);
		TinyTime(const SYSTEMTIME& st, INT nDST = -1);
		TinyTime(const FILETIME& ft, INT nDST = -1);
#ifdef __oledb_h__
		TinyTime(const DBTIMESTAMP& dbts, int nDST = -1) throw();
#endif

		TinyTime& operator=(__time64_t time) throw();

		TinyTime& operator+=(TinyTimeSpan span) throw();
		TinyTime& operator-=(TinyTimeSpan span) throw();

		TinyTimeSpan operator-(TinyTime time) const throw();
		TinyTime operator-(TinyTimeSpan span) const throw();
		TinyTime operator+(TinyTimeSpan span) const throw();

		BOOL operator==(TinyTime time) const throw();
		BOOL operator!=(TinyTime time) const throw();
		BOOL operator<(TinyTime time) const throw();
		BOOL operator>(TinyTime time) const throw();
		BOOL operator<=(TinyTime time) const throw();
		BOOL operator>=(TinyTime time) const throw();
		struct tm* GetGmtTm(struct tm* ptm) const;
		struct tm* GetLocalTm(struct tm* ptm) const;
		BOOL GetAsSystemTime(SYSTEMTIME& st) const throw();
		BOOL GetAsDBTIMESTAMP(DBTIMESTAMP& dbts) const throw();
		INT GetYear() const throw();
		INT GetMonth() const throw();
		INT GetDay() const throw();
		INT GetHour() const throw();
		INT GetMinute() const throw();
		INT GetSecond() const throw();
		INT GetDayOfWeek() const throw();
	private:
		__time64_t m_time;
	};
}
