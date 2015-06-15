#pragma once
#include <time.h>
#include <ctime>
#include "TinyString.h"
#ifndef __oledb_h__
struct tagDBTIMESTAMP;
typedef tagDBTIMESTAMP DBTIMESTAMP;
#endif

namespace TinyUI
{
	const INT maxTimeBufferSize = 128;
	const LONG maxDaysInSpan = 3615897L;
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
		TinyTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw();
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
	class TinyTime
	{
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
		TinyTime(const DBTIMESTAMP& dbts, INT nDST = -1) throw();
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
	/// <summary>
	/// OLE时间间隔类
	/// </summary>
	class TinyOleDateTimeSpan
	{
	public:
		TinyOleDateTimeSpan() throw();
		TinyOleDateTimeSpan(double dblSpanSrc) throw();
		TinyOleDateTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw();
		enum DateTimeSpanStatus
		{
			valid = 0,
			invalid = 1,
			null = 2,
		};

		double m_span;
		DateTimeSpanStatus m_status;

		void SetStatus(DateTimeSpanStatus status) throw();
		DateTimeSpanStatus GetStatus() const throw();

		double GetTotalDays() const throw();
		double GetTotalHours() const throw();
		double GetTotalMinutes() const throw();
		double GetTotalSeconds() const throw();

		LONG GetDays() const throw();
		LONG GetHours() const throw();
		LONG GetMinutes() const throw();
		LONG GetSeconds() const throw();
		TinyOleDateTimeSpan& operator=(double dblSpanSrc) throw();

		bool operator==(const TinyOleDateTimeSpan& dateSpan) const throw();
		bool operator!=(const TinyOleDateTimeSpan& dateSpan) const throw();
		bool operator<(const TinyOleDateTimeSpan& dateSpan) const throw();
		bool operator>(const TinyOleDateTimeSpan& dateSpan) const throw();
		bool operator<=(const TinyOleDateTimeSpan& dateSpan) const throw();
		bool operator>=(const TinyOleDateTimeSpan& dateSpan) const throw();
		TinyOleDateTimeSpan operator+(const TinyOleDateTimeSpan& dateSpan) const throw();
		TinyOleDateTimeSpan operator-(const TinyOleDateTimeSpan& dateSpan) const throw();
		TinyOleDateTimeSpan& operator+=(const TinyOleDateTimeSpan dateSpan) throw();
		TinyOleDateTimeSpan& operator-=(const TinyOleDateTimeSpan dateSpan) throw();
		TinyOleDateTimeSpan operator-() const throw();
		operator double() const throw();
		void SetDateTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw();
		void CheckRange();
	private:
		static const double OLE_DATETIME_HALFSECOND;
	};
	/// <summary>
	/// OLE时间类
	/// </summary>
	class TinyOleDateTime
	{
	public:
		static TinyOleDateTime WINAPI GetCurrentTime() throw();
		TinyOleDateTime() throw();
		TinyOleDateTime(const VARIANT& varSrc) throw();
		TinyOleDateTime(DATE dtSrc) throw();
		TinyOleDateTime(__time32_t timeSrc) throw();
		TinyOleDateTime(__time64_t timeSrc) throw();
		TinyOleDateTime(const SYSTEMTIME& systimeSrc) throw();
		TinyOleDateTime(const FILETIME& filetimeSrc) throw();
		TinyOleDateTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec) throw();
		TinyOleDateTime(WORD wDosDate, WORD wDosTime) throw();

#ifdef __oledb_h__
		TinyOleDateTime(const DBTIMESTAMP& dbts) throw();
		bool GetAsDBTIMESTAMP(DBTIMESTAMP& dbts) const throw();
#endif

		enum DateTimeStatus
		{
			error = -1,
			valid = 0,
			invalid = 1,
			null = 2,
		};

		DATE m_dt;
		DateTimeStatus m_status;

		void SetStatus(DateTimeStatus status) throw();
		DateTimeStatus GetStatus() const throw();

		bool GetAsSystemTime(SYSTEMTIME& sysTime) const throw();
		bool GetAsUDATE(UDATE& udate) const throw();

		INT GetYear() const throw();
		INT GetMonth() const throw();
		INT GetDay() const throw();
		INT GetHour() const throw();
		INT GetMinute() const throw();
		INT GetSecond() const throw();
		INT GetDayOfWeek() const throw();
		INT GetDayOfYear() const throw();

		TinyOleDateTime& operator=(const VARIANT& varSrc) throw();
		TinyOleDateTime& operator=(DATE dtSrc) throw();

		TinyOleDateTime& operator=(const __time32_t& timeSrc) throw();
		TinyOleDateTime& operator=(const __time64_t& timeSrc) throw();

		TinyOleDateTime& operator=(const SYSTEMTIME& systimeSrc) throw();
		TinyOleDateTime& operator=(const FILETIME& filetimeSrc) throw();
		TinyOleDateTime& operator=(const UDATE& udate) throw();

		bool operator==(const TinyOleDateTime& date) const throw();
		bool operator!=(const TinyOleDateTime& date) const throw();
		bool operator<(const TinyOleDateTime& date) const throw();
		bool operator>(const TinyOleDateTime& date) const throw();
		bool operator<=(const TinyOleDateTime& date) const throw();
		bool operator>=(const TinyOleDateTime& date) const throw();

		TinyOleDateTime operator+(TinyOleDateTimeSpan dateSpan) const throw();
		TinyOleDateTime operator-(TinyOleDateTimeSpan dateSpan) const throw();
		TinyOleDateTime& operator+=(TinyOleDateTimeSpan dateSpan) throw();
		TinyOleDateTime& operator-=(TinyOleDateTimeSpan dateSpan) throw();
		TinyOleDateTimeSpan operator-(const TinyOleDateTime& date) const throw();
		operator DATE() const throw();

		INT SetDateTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec) throw();
		INT SetDate(INT nYear, INT nMonth, INT nDay) throw();
		INT SetTime(INT nHour, INT nMin, INT nSec) throw();

		TinyString Format(LPCTSTR lpszFormat) const;

	protected:
		static double WINAPI DoubleFromDate(DATE date) throw();
		static DATE WINAPI DateFromDouble(double f) throw();
		void CheckRange();
		BOOL ConvertSystemTimeToVariantTime(const SYSTEMTIME& systimeSrc);
	};
	/// <summary>
	/// 时间间隔
	/// </summary>
	class Timespan
	{
	public:
		Timespan();
		Timespan(INT64 microseconds);
		Timespan(LONG seconds, LONG microseconds);
		Timespan(INT days, INT hours, INT minutes, INT seconds, INT microSeconds);
		Timespan(const Timespan& timespan);
		~Timespan();
		Timespan& operator = (const Timespan& timespan);
		Timespan& operator = (INT64 microseconds);
		Timespan& Assign(INT days, INT hours, INT minutes, INT seconds, INT microSeconds);
		Timespan& Assign(LONG seconds, LONG microseconds);
		void Swap(Timespan& timespan);
		BOOL operator == (const Timespan& ts) const;
		BOOL operator != (const Timespan& ts) const;
		BOOL operator >  (const Timespan& ts) const;
		BOOL operator >= (const Timespan& ts) const;
		BOOL operator <  (const Timespan& ts) const;
		BOOL operator <= (const Timespan& ts) const;
		BOOL operator == (INT64 microSeconds) const;
		BOOL operator != (INT64 microSeconds) const;
		BOOL operator >  (INT64 microSeconds) const;
		BOOL operator >= (INT64 microSeconds) const;
		BOOL operator <  (INT64 microSeconds) const;
		BOOL operator <= (INT64 microSeconds) const;
		Timespan operator + (const Timespan& d) const;
		Timespan operator - (const Timespan& d) const;
		Timespan& operator += (const Timespan& d);
		Timespan& operator -= (const Timespan& d);
		Timespan operator + (INT64 microSeconds) const;
		Timespan operator - (INT64 microSeconds) const;
		Timespan& operator += (INT64 microSeconds);
		Timespan& operator -= (INT64 microSeconds);
		INT Days() const;
		INT Hours() const;
		INT TotalHours() const;
		INT Minutes() const;
		INT TotalMinutes() const;
		INT Seconds() const;
		INT TotalSeconds() const;
		INT Milliseconds() const;
		INT64 TotalMilliseconds() const;
		INT Microseconds() const;
		INT64 TotalMicroseconds() const;
		static const INT64 MILLISECONDS;
		static const INT64 SECONDS;
		static const INT64 MINUTES;
		static const INT64 HOURS;
		static const INT64 DAYS;
	private:
		INT64 m_span;
	};
	/// <summary>
	/// 时间戮
	/// </summary>
	class Timestamp
	{
	public:
		static const INT64 TIMEVAL_MIN; 
		static const INT64 TIMEVAL_MAX; 
		Timestamp();
		Timestamp(INT64 tv);
		Timestamp(const Timestamp& other);
		~Timestamp();
		Timestamp& operator = (const Timestamp& other);
		Timestamp& operator = (INT64 tv);
		void Swap(Timestamp& timestamp);
		BOOL operator == (const Timestamp& ts) const;
		BOOL operator != (const Timestamp& ts) const;
		BOOL operator >  (const Timestamp& ts) const;
		BOOL operator >= (const Timestamp& ts) const;
		BOOL operator <  (const Timestamp& ts) const;
		BOOL operator <= (const Timestamp& ts) const;
		Timestamp  operator +  (INT64 d) const;
		Timestamp  operator +  (const Timespan& span) const;
		Timestamp  operator -  (INT64 d) const;
		Timestamp  operator -  (const Timespan& span) const;
		INT64   operator -  (const Timestamp& ts) const;
		Timestamp& operator += (INT64 d);
		Timestamp& operator += (const Timespan& span);
		Timestamp& operator -= (INT64 d);
		Timestamp& operator -= (const Timespan& span);
		std::time_t GetEpochTime() const;
		INT64 GetUTCTime() const;
		INT64 GetEpochMicroseconds() const;
		INT64 GetElapsed() const;
		BOOL IsElapsed(INT64 interval) const;
		INT64 raw() const;
		static Timestamp FromEpochTime(std::time_t t);
		static Timestamp FromUTCTime(INT64 val);
		static INT64 Resolution();
	private:
		void GetTime();
		INT64 _ts;
	};
}
