#pragma once
#include <stdint.h>
#include <time.h>
#include <string>



class Time
{
public:
	Time();

	static Time Day(const time_t val);

	static void TimeBeginPeriod(const time_t u_period);

	Time& today();
	Time& now();
	Time& year(const int32_t val);
	Time& mon(const int32_t val);
	Time& day(const int32_t val);
	Time& hour(const int32_t val);
	Time& minute(const int32_t val);
	Time& sec(const int32_t val);

	int32_t to_year()const;
	int32_t to_mon()const;
	int32_t to_day()const;
	int32_t to_hour()const;
	int32_t to_minute()const;
	int32_t to_sec()const;

	bool operator > (Time& time);
	bool operator >= (Time& time);
	bool operator < (Time& time);
	bool operator <= (Time& time);
	bool operator == (Time& time);
	bool operator != (Time& time);

	Time& operator - (const Time& time) const;
	Time& operator + (const Time& time) const;
	void operator += (const Time& time);
	void operator -= (const Time& time);

	Time& operator - (const time_t time) const;
	Time& operator + (const time_t time) const;
	void operator += (const time_t time);
	void operator -= (const time_t time);
public:
	time_t to_milliseconds_count() const;
	time_t to_seconds_count() const;
	// 输出日期格式 
	std::string to_date_format() const;
private:
	tm	m_time;
};