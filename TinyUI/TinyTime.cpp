#include "stdafx.h"
#include "TinyTime.h"

namespace TinyUI
{
	TinyTimeSpan::TinyTimeSpan() throw() :m_timeSpan(0)
	{
	}
	TinyTimeSpan::TinyTimeSpan(__time64_t time) throw() :m_timeSpan(time)
	{
	}
	TinyTimeSpan::TinyTimeSpan(LONG lDays, int nHours, int nMins, int nSecs) throw()
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
	//////////////////////////////////////////////////////////////////////////
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
				(int)sysTime.wYear,
				(int)sysTime.wMonth,
				(int)sysTime.wDay,
				(int)sysTime.wHour,
				(int)sysTime.wMinute,
				(int)sysTime.wSecond,
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
}