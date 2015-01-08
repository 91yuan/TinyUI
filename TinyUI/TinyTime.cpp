#include "stdafx.h"
#include "TinyTime.h"
#pragma comment(lib, "comsupp.lib") 

namespace TinyUI
{
	inline BOOL _ConvertSystemTimeToVariantTime(const SYSTEMTIME& systimeSrc, double* pVarDtTm)
	{
		BOOL ok = ::SystemTimeToVariantTime(const_cast<SYSTEMTIME*>(&systimeSrc), pVarDtTm);
		SYSTEMTIME sysTime;
		::ZeroMemory(&sysTime, sizeof(SYSTEMTIME));

		ok = ok && ::VariantTimeToSystemTime(*pVarDtTm, &sysTime);
		ok = ok && (systimeSrc.wYear == sysTime.wYear &&
			systimeSrc.wMonth == sysTime.wMonth &&
			systimeSrc.wDay == sysTime.wDay &&
			systimeSrc.wHour == sysTime.wHour &&
			systimeSrc.wMinute == sysTime.wMinute &&
			systimeSrc.wSecond == sysTime.wSecond);

		return ok;
	}
	/************************************************************************/
	/* TinyTimeSpan                                                         */
	/************************************************************************/
	TinyTimeSpan::TinyTimeSpan() throw() :m_timeSpan(0)
	{
	}
	TinyTimeSpan::TinyTimeSpan(__time64_t time) throw() :m_timeSpan(time)
	{
	}
	TinyTimeSpan::TinyTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw()
	{
		m_timeSpan = nSecs + 60 * (nMins + 60 * (nHours + __int64(24) * lDays));
	}
	__time64_t TinyTimeSpan::GetTimeSpan() const throw()
	{
		return(m_timeSpan);
	}
	LONGLONG TinyTimeSpan::GetDays() const throw()
	{
		return(m_timeSpan / (24 * 3600));
	}
	LONGLONG TinyTimeSpan::GetTotalHours() const throw()
	{
		return(m_timeSpan / 3600);
	}
	LONG TinyTimeSpan::GetHours() const throw()
	{
		return(LONG(GetTotalHours() - (GetDays() * 24)));
	}
	LONGLONG TinyTimeSpan::GetTotalMinutes() const throw()
	{
		return(m_timeSpan / 60);
	}
	LONG TinyTimeSpan::GetMinutes() const throw()
	{
		return(LONG(GetTotalMinutes() - (GetTotalHours() * 60)));
	}
	LONGLONG TinyTimeSpan::GetTotalSeconds() const throw()
	{
		return(m_timeSpan);
	}
	LONG TinyTimeSpan::GetSeconds() const throw()
	{
		return(LONG(GetTotalSeconds() - (GetTotalMinutes() * 60)));
	}
	TinyTimeSpan TinyTimeSpan::operator+(TinyTimeSpan span) const throw()
	{
		return(TinyTimeSpan(m_timeSpan + span.m_timeSpan));
	}
	TinyTimeSpan TinyTimeSpan::operator-(TinyTimeSpan span) const throw()
	{
		return(TinyTimeSpan(m_timeSpan - span.m_timeSpan));
	}
	TinyTimeSpan& TinyTimeSpan::operator+=(TinyTimeSpan span) throw()
	{
		m_timeSpan += span.m_timeSpan;
		return(*this);
	}
	TinyTimeSpan& TinyTimeSpan::operator-=(TinyTimeSpan span) throw()
	{
		m_timeSpan -= span.m_timeSpan;
		return(*this);
	}
	BOOL TinyTimeSpan::operator==(TinyTimeSpan span) const throw()
	{
		return(m_timeSpan == span.m_timeSpan);
	}
	BOOL TinyTimeSpan::operator!=(TinyTimeSpan span) const throw()
	{
		return(m_timeSpan != span.m_timeSpan);
	}
	BOOL TinyTimeSpan::operator<(TinyTimeSpan span) const throw()
	{
		return(m_timeSpan < span.m_timeSpan);
	}
	BOOL TinyTimeSpan::operator>(TinyTimeSpan span) const throw()
	{
		return(m_timeSpan > span.m_timeSpan);
	}
	BOOL TinyTimeSpan::operator<=(TinyTimeSpan span) const throw()
	{
		return(m_timeSpan <= span.m_timeSpan);
	}
	BOOL TinyTimeSpan::operator>=(TinyTimeSpan span) const throw()
	{
		return(m_timeSpan >= span.m_timeSpan);
	}
	/************************************************************************/
	/* TinyTime																*/
	/************************************************************************/
	TinyTime WINAPI TinyTime::GetCurrentTime() throw()
	{
		return(TinyTime(::_time64(NULL)));
	}
	BOOL WINAPI TinyTime::IsValidFILETIME(const FILETIME& fileTime) throw()
	{
		FILETIME localTime;
		if (!FileTimeToLocalFileTime(&fileTime, &localTime))
		{
			return FALSE;
		}
		SYSTEMTIME sysTime;
		if (!FileTimeToSystemTime(&localTime, &sysTime))
		{
			return FALSE;
		}

		return TRUE;
	}
	TinyTime::TinyTime() throw()
		:m_time(0)
	{
	}
	TinyTime::TinyTime(__time64_t time)  throw() :
		m_time(time)
	{
	}
	TinyTime::TinyTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec, INT nDST)
	{
		struct tm atm;
		atm.tm_sec = nSec;
		atm.tm_min = nMin;
		atm.tm_hour = nHour;
		atm.tm_mday = nDay;
		atm.tm_mon = nMonth - 1;
		atm.tm_year = nYear - 1900;
		atm.tm_isdst = nDST;
		m_time = _mktime64(&atm);
		ASSUME(m_time != -1);
		if (m_time == -1)
		{
			throw(_T("无效的参数"));
		}
	}
	TinyTime::TinyTime(WORD wDosDate, WORD wDosTime, INT nDST)
	{
		struct tm atm;
		atm.tm_sec = (wDosTime & ~0xFFE0) << 1;
		atm.tm_min = (wDosTime & ~0xF800) >> 5;
		atm.tm_hour = wDosTime >> 11;
		atm.tm_mday = wDosDate & ~0xFFE0;
		atm.tm_mon = ((wDosDate & ~0xFE00) >> 5) - 1;
		atm.tm_year = (wDosDate >> 9) + 80;
		atm.tm_isdst = nDST;
		m_time = _mktime64(&atm);
		ASSUME(m_time != -1);
		if (m_time == -1)
		{
			throw(_T("无效的参数"));
		}
	}
	TinyTime::TinyTime(const SYSTEMTIME& sysTime, INT nDST)
	{
		if (sysTime.wYear < 1900)
		{
			__time64_t time0 = 0L;
			TinyTime timeT(time0);
			*this = timeT;
		}
		else
		{
			TinyTime timeT(
				(INT)sysTime.wYear,
				(INT)sysTime.wMonth,
				(INT)sysTime.wDay,
				(INT)sysTime.wHour,
				(INT)sysTime.wMinute,
				(INT)sysTime.wSecond,
				nDST);
			*this = timeT;
		}
	}
	TinyTime::TinyTime(const FILETIME& fileTime, INT nDST)
	{
		FILETIME localTime;
		if (!FileTimeToLocalFileTime(&fileTime, &localTime))
		{
			m_time = 0;
			return;
		}
		SYSTEMTIME sysTime;
		if (!FileTimeToSystemTime(&localTime, &sysTime))
		{
			m_time = 0;
			return;
		}
		TinyTime timeT(sysTime, nDST);
		*this = timeT;
	}
	TinyTime& TinyTime::operator=(__time64_t time) throw()
	{
		m_time = time;
		return(*this);
	}

	TinyTime& TinyTime::operator+=(TinyTimeSpan span) throw()
	{
		m_time += span.GetTimeSpan();
		return(*this);
	}

	TinyTime& TinyTime::operator-=(TinyTimeSpan span) throw()
	{
		m_time -= span.GetTimeSpan();
		return(*this);
	}

	TinyTimeSpan TinyTime::operator-(TinyTime time) const throw()
	{
		return(TinyTimeSpan(m_time - time.m_time));
	}

	TinyTime TinyTime::operator-(TinyTimeSpan span) const throw()
	{
		return(TinyTime(m_time - span.GetTimeSpan()));
	}

	TinyTime TinyTime::operator+(TinyTimeSpan span) const throw()
	{
		return(TinyTime(m_time + span.GetTimeSpan()));
	}

	BOOL TinyTime::operator==(TinyTime time) const throw()
	{
		return(m_time == time.m_time);
	}

	BOOL TinyTime::operator!=(TinyTime time) const throw()
	{
		return(m_time != time.m_time);
	}

	BOOL TinyTime::operator<(TinyTime time) const throw()
	{
		return(m_time < time.m_time);
	}

	BOOL TinyTime::operator>(TinyTime time) const throw()
	{
		return(m_time > time.m_time);
	}

	BOOL TinyTime::operator<=(TinyTime time) const throw()
	{
		return(m_time <= time.m_time);
	}

	BOOL TinyTime::operator>=(TinyTime time) const throw()
	{
		return(m_time >= time.m_time);
	}

	struct tm* TinyTime::GetGmtTm(struct tm* ptm) const
	{
		if (ptm != NULL)
		{
			struct tm ptmTemp;
			errno_t err = _gmtime64_s(&ptmTemp, &m_time);
			if (err != 0) { return NULL; }

			*ptm = ptmTemp;
			return ptm;
		}
		return NULL;
	}

	struct tm* TinyTime::GetLocalTm(struct tm* ptm) const
	{
		if (ptm != NULL)
		{
			struct tm ptmTemp;
			errno_t err = _localtime64_s(&ptmTemp, &m_time);
			if (err != 0)
			{
				return NULL;
			}
			*ptm = ptmTemp;
			return ptm;
		}
		return NULL;
	}

	BOOL TinyTime::GetAsSystemTime(SYSTEMTIME& timeDest) const throw()
	{
		struct tm ttm;
		struct tm* ptm;
		ptm = GetLocalTm(&ttm);
		if (!ptm) { return false; }
		timeDest.wYear = (WORD)(1900 + ptm->tm_year);
		timeDest.wMonth = (WORD)(1 + ptm->tm_mon);
		timeDest.wDayOfWeek = (WORD)ptm->tm_wday;
		timeDest.wDay = (WORD)ptm->tm_mday;
		timeDest.wHour = (WORD)ptm->tm_hour;
		timeDest.wMinute = (WORD)ptm->tm_min;
		timeDest.wSecond = (WORD)ptm->tm_sec;
		timeDest.wMilliseconds = 0;
		return true;
	}

	__time64_t TinyTime::GetTime() const throw()
	{
		return(m_time);
	}

	INT TinyTime::GetYear() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? (ptm->tm_year) + 1900 : 0;
	}

	INT TinyTime::GetMonth() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? ptm->tm_mon + 1 : 0;
	}

	INT TinyTime::GetDay() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? ptm->tm_mday : 0;
	}

	INT TinyTime::GetHour() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? ptm->tm_hour : -1;
	}

	INT TinyTime::GetMinute() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? ptm->tm_min : -1;
	}

	INT TinyTime::GetSecond() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? ptm->tm_sec : -1;
	}

	INT TinyTime::GetDayOfWeek() const
	{
		struct tm ttm;
		struct tm * ptm;

		ptm = GetLocalTm(&ttm);
		return ptm ? ptm->tm_wday + 1 : 0;
	}

	/************************************************************************/
	/* TinyOleDateTimeSpan													*/
	/************************************************************************/
	TinyOleDateTimeSpan::TinyOleDateTimeSpan() throw() : m_span(0), m_status(valid)
	{
	}

	TinyOleDateTimeSpan::TinyOleDateTimeSpan(double dblSpanSrc) throw() : m_span(dblSpanSrc), m_status(valid)
	{
		CheckRange();
	}

	TinyOleDateTimeSpan::TinyOleDateTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw()
	{
		SetDateTimeSpan(lDays, nHours, nMins, nSecs);
	}

	void TinyOleDateTimeSpan::SetStatus(DateTimeSpanStatus status) throw()
	{
		m_status = status;
	}

	TinyOleDateTimeSpan::DateTimeSpanStatus TinyOleDateTimeSpan::GetStatus() const throw()
	{
		return m_status;
	}

	__declspec(selectany) const double
		TinyOleDateTimeSpan::OLE_DATETIME_HALFSECOND =
		1.0 / (2.0 * (60.0 * 60.0 * 24.0));

	double TinyOleDateTimeSpan::GetTotalDays() const throw()
	{
		ASSERT(GetStatus() == valid);
		return (double)LONGLONG(m_span + (m_span < 0 ?
			-OLE_DATETIME_HALFSECOND : OLE_DATETIME_HALFSECOND));
	}

	double TinyOleDateTimeSpan::GetTotalHours() const throw()
	{
		ASSERT(GetStatus() == valid);
		return (double)LONGLONG((m_span + (m_span < 0 ?
			-OLE_DATETIME_HALFSECOND : OLE_DATETIME_HALFSECOND)) * 24);
	}

	double TinyOleDateTimeSpan::GetTotalMinutes() const throw()
	{
		ASSERT(GetStatus() == valid);
		return (double)LONGLONG((m_span + (m_span < 0 ?
			-OLE_DATETIME_HALFSECOND : OLE_DATETIME_HALFSECOND)) * (24 * 60));
	}

	double TinyOleDateTimeSpan::GetTotalSeconds() const throw()
	{
		ASSERT(GetStatus() == valid);
		return (double)LONGLONG((m_span + (m_span < 0 ?
			-OLE_DATETIME_HALFSECOND : OLE_DATETIME_HALFSECOND)) * (24 * 60 * 60));
	}

	LONG TinyOleDateTimeSpan::GetDays() const throw()
	{
		ASSERT(GetStatus() == valid);
		return LONG(GetTotalDays());
	}

	LONG TinyOleDateTimeSpan::GetHours() const throw()
	{
		return LONG(GetTotalHours()) % 24;
	}

	LONG TinyOleDateTimeSpan::GetMinutes() const throw()
	{
		return LONG(GetTotalMinutes()) % 60;
	}

	LONG TinyOleDateTimeSpan::GetSeconds() const throw()
	{
		return LONG(GetTotalSeconds()) % 60;
	}

	TinyOleDateTimeSpan& TinyOleDateTimeSpan::operator=(double dblSpanSrc) throw()
	{
		m_span = dblSpanSrc;
		m_status = valid;
		CheckRange();
		return *this;
	}

	bool TinyOleDateTimeSpan::operator==(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		if (GetStatus() == dateSpan.GetStatus())
		{
			if (GetStatus() == valid)
				return (m_span == dateSpan.m_span);

			return (GetStatus() == null);
		}

		return false;
	}

	bool TinyOleDateTimeSpan::operator!=(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		return !operator==(dateSpan);
	}

	bool TinyOleDateTimeSpan::operator<(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		if ((GetStatus() == valid) && (GetStatus() == dateSpan.GetStatus()))
			return m_span < dateSpan.m_span;

		return false;
	}

	bool TinyOleDateTimeSpan::operator>(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		if ((GetStatus() == valid) && (GetStatus() == dateSpan.GetStatus()))
			return m_span > dateSpan.m_span;

		return false;
	}

	bool TinyOleDateTimeSpan::operator<=(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		return operator<(dateSpan) || operator==(dateSpan);
	}

	bool TinyOleDateTimeSpan::operator>=(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		return operator>(dateSpan) || operator==(dateSpan);
	}

	TinyOleDateTimeSpan TinyOleDateTimeSpan::operator+(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		TinyOleDateTimeSpan dateSpanTemp;
		if (GetStatus() == null || dateSpan.GetStatus() == null)
		{
			dateSpanTemp.SetStatus(null);
			return dateSpanTemp;
		}
		if (GetStatus() == invalid || dateSpan.GetStatus() == invalid)
		{
			dateSpanTemp.SetStatus(invalid);
			return dateSpanTemp;
		}
		dateSpanTemp.m_span = m_span + dateSpan.m_span;
		dateSpanTemp.CheckRange();

		return dateSpanTemp;
	}

	TinyOleDateTimeSpan TinyOleDateTimeSpan::operator-(const TinyOleDateTimeSpan& dateSpan) const throw()
	{
		TinyOleDateTimeSpan dateSpanTemp;
		if (GetStatus() == null || dateSpan.GetStatus() == null)
		{
			dateSpanTemp.SetStatus(null);
			return dateSpanTemp;
		}
		if (GetStatus() == invalid || dateSpan.GetStatus() == invalid)
		{
			dateSpanTemp.SetStatus(invalid);
			return dateSpanTemp;
		}
		dateSpanTemp.m_span = m_span - dateSpan.m_span;
		dateSpanTemp.CheckRange();

		return dateSpanTemp;
	}

	TinyOleDateTimeSpan& TinyOleDateTimeSpan::operator+=(const TinyOleDateTimeSpan dateSpan) throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		*this = *this + dateSpan;
		CheckRange();
		return *this;
	}

	TinyOleDateTimeSpan& TinyOleDateTimeSpan::operator-=(const TinyOleDateTimeSpan dateSpan) throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		*this = *this - dateSpan;
		CheckRange();
		return *this;
	}

	TinyOleDateTimeSpan TinyOleDateTimeSpan::operator-() const throw()
	{
		return -this->m_span;
	}

	TinyOleDateTimeSpan::operator double() const throw()
	{
		return m_span;
	}

	void TinyOleDateTimeSpan::SetDateTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw()
	{
		m_span = lDays + ((double)nHours) / 24 + ((double)nMins) / (24 * 60) + ((double)nSecs) / (24 * 60 * 60);
		m_status = valid;
		CheckRange();
	}

	void TinyOleDateTimeSpan::CheckRange()
	{
		if (m_span < -maxDaysInSpan || m_span > maxDaysInSpan)
			m_status = invalid;
	}

	/************************************************************************/
	/* TinyOleDateTime														*/
	/************************************************************************/
	TinyOleDateTime WINAPI TinyOleDateTime::GetCurrentTime() throw()
	{
		return TinyOleDateTime(::_time64(NULL));
	}

	TinyOleDateTime::TinyOleDateTime() throw() :
		m_dt(0), m_status(valid)
	{
	}

	TinyOleDateTime::TinyOleDateTime(const VARIANT& varSrc) throw() :
		m_dt(0), m_status(valid)
	{
		*this = varSrc;
	}

	TinyOleDateTime::TinyOleDateTime(DATE dtSrc) throw() :
		m_dt(dtSrc), m_status(valid)
	{
	}

	TinyOleDateTime::TinyOleDateTime(__time32_t timeSrc) throw() :
		m_dt(0), m_status(valid)
	{
		*this = timeSrc;
	}

	TinyOleDateTime::TinyOleDateTime(__time64_t timeSrc) throw() :
		m_dt(0), m_status(valid)
	{
		*this = timeSrc;
	}

	TinyOleDateTime::TinyOleDateTime(const SYSTEMTIME& systimeSrc) throw() :
		m_dt(0), m_status(valid)
	{
		*this = systimeSrc;
	}

	TinyOleDateTime::TinyOleDateTime(const FILETIME& filetimeSrc) throw() :
		m_dt(0), m_status(valid)
	{
		*this = filetimeSrc;
	}

	TinyOleDateTime::TinyOleDateTime(INT nYear, INT nMonth, INT nDay,
		INT nHour, INT nMin, INT nSec) throw()
	{
		SetDateTime(nYear, nMonth, nDay, nHour, nMin, nSec);
	}

	TinyOleDateTime::TinyOleDateTime(WORD wDosDate, WORD wDosTime) throw()
	{
		m_status = ::DosDateTimeToVariantTime(wDosDate, wDosTime, &m_dt) ?
		valid : invalid;
	}

	void TinyOleDateTime::SetStatus(DateTimeStatus status) throw()
	{
		m_status = status;
	}

	TinyOleDateTime::DateTimeStatus TinyOleDateTime::GetStatus() const throw()
	{
		return m_status;
	}

	bool TinyOleDateTime::GetAsSystemTime(SYSTEMTIME& sysTime) const throw()
	{
		return GetStatus() == valid && ::VariantTimeToSystemTime(m_dt, &sysTime);
	}

	bool TinyOleDateTime::GetAsUDATE(UDATE &udate) const throw()
	{
		return SUCCEEDED(::VarUdateFromDate(m_dt, 0, &udate));
	}

	INT TinyOleDateTime::GetYear() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wYear : error;
	}

	INT TinyOleDateTime::GetMonth() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wMonth : error;
	}

	INT TinyOleDateTime::GetDay() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wDay : error;
	}

	INT TinyOleDateTime::GetHour() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wHour : error;
	}

	INT TinyOleDateTime::GetMinute() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wMinute : error;
	}

	INT TinyOleDateTime::GetSecond() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wSecond : error;
	}

	INT TinyOleDateTime::GetDayOfWeek() const throw()
	{
		SYSTEMTIME st;
		return GetAsSystemTime(st) ? st.wDayOfWeek + 1 : error;
	}

	INT TinyOleDateTime::GetDayOfYear() const throw()
	{
		UDATE udate;
		return GetAsUDATE(udate) ? udate.wDayOfYear : error;
	}

	TinyOleDateTime& TinyOleDateTime::operator=(const VARIANT& varSrc) throw()
	{
		if (varSrc.vt != VT_DATE)
		{
			VARIANT varDest;
			varDest.vt = VT_EMPTY;
			if (SUCCEEDED(::VariantChangeType(&varDest, const_cast<VARIANT *>(&varSrc), 0, VT_DATE)))
			{
				m_dt = varDest.date;
				m_status = valid;
			}
			else
				m_status = invalid;
		}
		else
		{
			m_dt = varSrc.date;
			m_status = valid;
		}

		return *this;
	}

	TinyOleDateTime& TinyOleDateTime::operator=(DATE dtSrc) throw()
	{
		m_dt = dtSrc;
		m_status = valid;
		return *this;
	}

	TinyOleDateTime& TinyOleDateTime::operator=(const __time32_t& timeSrc) throw()
	{
		return operator=(static_cast<__time64_t>(timeSrc));
	}

	TinyOleDateTime& TinyOleDateTime::operator=(const __time64_t& timeSrc) throw()
	{
		SYSTEMTIME st;
		TinyTime tmp(timeSrc);
		m_status = tmp.GetAsSystemTime(st) && ConvertSystemTimeToVariantTime(st) ? valid : invalid;
		return *this;
	}

	TinyOleDateTime &TinyOleDateTime::operator=(const SYSTEMTIME &systimeSrc) throw()
	{
		m_status = ConvertSystemTimeToVariantTime(systimeSrc) ? valid : invalid;
		return *this;
	}

	TinyOleDateTime &TinyOleDateTime::operator=(const FILETIME &filetimeSrc) throw()
	{
		FILETIME ftl;
		SYSTEMTIME st;

		m_status = ::FileTimeToLocalFileTime(&filetimeSrc, &ftl) &&
			::FileTimeToSystemTime(&ftl, &st) &&
			ConvertSystemTimeToVariantTime(st) ? valid : invalid;

		return *this;
	}

	BOOL TinyOleDateTime::ConvertSystemTimeToVariantTime(const SYSTEMTIME& systimeSrc)
	{
		return _ConvertSystemTimeToVariantTime(systimeSrc, &m_dt);
	}
	TinyOleDateTime &TinyOleDateTime::operator=(const UDATE &udate) throw()
	{
		m_status = (S_OK == VarDateFromUdate((UDATE*)&udate, 0, &m_dt)) ? valid : invalid;

		return *this;
	}

	bool TinyOleDateTime::operator==(const TinyOleDateTime& date) const throw()
	{
		if (GetStatus() == date.GetStatus())
		{
			if (GetStatus() == valid)
				return(m_dt == date.m_dt);

			return (GetStatus() == null);
		}
		return false;

	}

	bool TinyOleDateTime::operator!=(const TinyOleDateTime& date) const throw()
	{
		return !operator==(date);
	}

	bool TinyOleDateTime::operator<(const TinyOleDateTime& date) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(date.GetStatus() == valid);
		if ((GetStatus() == valid) && (GetStatus() == date.GetStatus()))
			return(DoubleFromDate(m_dt) < DoubleFromDate(date.m_dt));
		return false;
	}

	bool TinyOleDateTime::operator>(const TinyOleDateTime& date) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(date.GetStatus() == valid);
		if ((GetStatus() == valid) && (GetStatus() == date.GetStatus()))
			return(DoubleFromDate(m_dt) > DoubleFromDate(date.m_dt));

		return false;
	}

	bool TinyOleDateTime::operator<=(const TinyOleDateTime& date) const throw()
	{
		return operator<(date) || operator==(date);
	}

	bool TinyOleDateTime::operator>=(const TinyOleDateTime& date) const throw()
	{
		return operator>(date) || operator==(date);
	}

	TinyOleDateTime TinyOleDateTime::operator+(TinyOleDateTimeSpan dateSpan) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		return(TinyOleDateTime(DateFromDouble(DoubleFromDate(m_dt) + (double)dateSpan)));
	}

	TinyOleDateTime TinyOleDateTime::operator-(TinyOleDateTimeSpan dateSpan) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		return(TinyOleDateTime(DateFromDouble(DoubleFromDate(m_dt) - (double)dateSpan)));
	}

	TinyOleDateTime& TinyOleDateTime::operator+=(TinyOleDateTimeSpan dateSpan) throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		m_dt = DateFromDouble(DoubleFromDate(m_dt) + (double)dateSpan);
		return(*this);
	}

	TinyOleDateTime& TinyOleDateTime::operator-=(TinyOleDateTimeSpan dateSpan) throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(dateSpan.GetStatus() == valid);
		m_dt = DateFromDouble(DoubleFromDate(m_dt) - (double)dateSpan);
		return(*this);
	}

	TinyOleDateTimeSpan TinyOleDateTime::operator-(const TinyOleDateTime& date) const throw()
	{
		ASSERT(GetStatus() == valid);
		ASSERT(date.GetStatus() == valid);
		return DoubleFromDate(m_dt) - DoubleFromDate(date.m_dt);
	}

	TinyOleDateTime::operator DATE() const throw()
	{
		ASSERT(GetStatus() == valid);
		return(m_dt);
	}

	INT TinyOleDateTime::SetDateTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec) throw()
	{
		SYSTEMTIME st;
		::ZeroMemory(&st, sizeof(SYSTEMTIME));

		st.wYear = WORD(nYear);
		st.wMonth = WORD(nMonth);
		st.wDay = WORD(nDay);
		st.wHour = WORD(nHour);
		st.wMinute = WORD(nMin);
		st.wSecond = WORD(nSec);

		m_status = ConvertSystemTimeToVariantTime(st) ? valid : invalid;
		return m_status;
	}

	INT TinyOleDateTime::SetDate(INT nYear, INT nMonth, INT nDay) throw()
	{
		return SetDateTime(nYear, nMonth, nDay, 0, 0, 0);
	}

	INT TinyOleDateTime::SetTime(INT nHour, INT nMin, INT nSec) throw()
	{
		return SetDateTime(1899, 12, 30, nHour, nMin, nSec);
	}

	double WINAPI TinyOleDateTime::DoubleFromDate(DATE date) throw()
	{
		double fTemp;
		if (date >= 0)
		{
			return(date);
		}
		fTemp = ceil(date);

		return(fTemp - (date - fTemp));
	}

	DATE WINAPI TinyOleDateTime::DateFromDouble(double f) throw()
	{
		double fTemp;
		if (f >= 0)
		{
			return(f);
		}
		fTemp = floor(f);

		return(fTemp + (fTemp - f));
	}

	void TinyOleDateTime::CheckRange()
	{
		if (m_dt > VTDATEGRE_MAX || m_dt < VTDATEGRE_MIN)
		{
			SetStatus(invalid);
		}
	}
	TinyString TinyOleDateTime::Format(LPCTSTR pFormat) const
	{
		if (GetStatus() == null)
			return _T("");

		if (GetStatus() == invalid)
		{
			return szInvalidDateTime;
		}

		UDATE ud;
		if (S_OK != VarUdateFromDate(m_dt, 0, &ud))
		{
			return szInvalidDateTime;
		}

		struct tm tmTemp;
		tmTemp.tm_sec = ud.st.wSecond;
		tmTemp.tm_min = ud.st.wMinute;
		tmTemp.tm_hour = ud.st.wHour;
		tmTemp.tm_mday = ud.st.wDay;
		tmTemp.tm_mon = ud.st.wMonth - 1;
		tmTemp.tm_year = ud.st.wYear - 1900;
		tmTemp.tm_wday = ud.st.wDayOfWeek;
		tmTemp.tm_yday = ud.wDayOfYear - 1;
		tmTemp.tm_isdst = 0;

		CHAR* lpszTemp = new CHAR[256];
		_tcsftime(lpszTemp, 256, pFormat, &tmTemp);
		TinyString str(lpszTemp);
		SAFE_DELETE_ARRAY(lpszTemp);
		return str;//一个构造和拷贝的代价
	}
}