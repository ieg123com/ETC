#include "Time.h"
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"Winmm.lib")
#endif

Time::Time()
{
	memset(&m_time, 0, sizeof(m_time));
}

Time Time::Day(const time_t val)
{
	Time time;
	time_t now_time = (val * (60 * 60 * 24));
	time.m_time = *localtime(&now_time);
	return time;
}

void Time::TimeBeginPeriod(const time_t u_period)
{
#ifdef _WIN32
	::timeBeginPeriod(u_period);
#endif
}


Time& Time::today()
{
	now();
	m_time.tm_min = 0;
	m_time.tm_sec = 0;
	m_time.tm_hour = 0;
	return *this;
}

Time& Time::now()
{
	time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	m_time = *localtime(&now_time);
	return *this;
}


Time& Time::year(const int32_t val)
{
	m_time.tm_year = val;
	return *this;
}

Time& Time::mon(const int32_t val)
{
	m_time.tm_mon = val;
	return *this;
}

Time& Time::day(const int32_t val)
{
	m_time.tm_mday = val;
	return *this;
}

Time& Time::hour(const int32_t val)
{
	m_time.tm_hour = val;
	return *this;
}

Time& Time::minute(const int32_t val)
{
	m_time.tm_min = val;
	return *this;
}

Time& Time::sec(const int32_t val)
{
	m_time.tm_sec = val;
	return *this;
}

int32_t Time::to_year()const
{
	return m_time.tm_year;
}

int32_t Time::to_mon()const
{
	return m_time.tm_mon;
}

int32_t Time::to_day()const
{
	return m_time.tm_mday;
}

int32_t Time::to_hour()const
{
	return m_time.tm_hour;
}

int32_t Time::to_minute()const
{
	return m_time.tm_min;
}

int32_t Time::to_sec()const
{
	return m_time.tm_sec;
}



bool Time::operator > (Time& time)
{
	return to_milliseconds_count() > time.to_milliseconds_count();
}

bool Time::operator >= (Time& time)
{
	return to_milliseconds_count() >= time.to_milliseconds_count();
}

bool Time::operator < (Time& time)
{
	return to_milliseconds_count() < time.to_milliseconds_count();
}

bool Time::operator <= (Time& time)
{
	return to_milliseconds_count() <= time.to_milliseconds_count();
}

bool Time::operator == (Time& time)
{
	return to_milliseconds_count() == time.to_milliseconds_count();
}

bool Time::operator != (Time& time)
{
	return to_milliseconds_count() != time.to_milliseconds_count();
}

Time& Time::operator - (const Time& time) const
{
	Time new_time;
	time_t self = mktime((tm* const)&m_time) - mktime((tm* const)&time.m_time);
	new_time.m_time = *localtime(&self);
	return new_time;
}

Time& Time::operator + (const Time& time) const
{
	Time new_time;
	time_t self = mktime((tm* const)&m_time) + mktime((tm* const)&time.m_time);
	new_time.m_time = *localtime(&self);
	return new_time;
}

void Time::operator += (const Time& time)
{
	time_t self = mktime((tm* const)&m_time) + mktime((tm* const)&time.m_time);
	m_time = *localtime(&self);
}

void Time::operator -= (const Time& time)
{
	time_t self = mktime((tm* const)&m_time) - mktime((tm* const)&time.m_time);
	m_time = *localtime(&self);
}

Time& Time::operator - (const time_t time) const
{
	Time new_time;
	time_t self = mktime((tm* const)&m_time) - time;
	new_time.m_time = *localtime(&self);
	return new_time;
}

Time& Time::operator + (const time_t time) const
{
	Time new_time;
	time_t self = mktime((tm* const)&m_time) + time;
	new_time.m_time = *localtime(&self);
	return new_time;
}

void Time::operator += (const time_t time)
{
	time_t self = mktime((tm* const)&m_time) + time;
	m_time = *localtime(&self);
}

void Time::operator -= (const time_t time)
{
	time_t self = mktime((tm* const)&m_time) - time;
	m_time = *localtime(&self);
}

time_t Time::to_milliseconds_count() const
{
	time_t now_time = mktime((tm *const)&m_time);
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(now_time).time_since_epoch()).count();
}

time_t Time::to_seconds_count() const
{
	time_t now_time = mktime((tm* const)&m_time);
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::from_time_t(now_time).time_since_epoch()).count();
}

std::string Time::to_date_format() const
{
	return std::to_string(m_time.tm_year+1900) + \
		((m_time.tm_mon < 9) ? "0" + std::to_string(m_time.tm_mon+1) : std::to_string(m_time.tm_mon+1)) + \
		((m_time.tm_mday < 10) ? "0" + std::to_string(m_time.tm_mday) : std::to_string(m_time.tm_mday));
}