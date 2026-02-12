#pragma once
#include <iostream>
using namespace std;
class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	Date(int year = 1900, int month = 1, int day = 1);
	//获取每月的天数
	int GetMonthDay(int year, int month)
	{
		static int MonthDayArray[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			return 29;
		}
		return MonthDayArray[month];
	}
	//检查日期是否正确
	bool CheckDate();
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;

	Date& operator+=(int day);
	Date operator+(int day);
	Date& operator-=(int day);
	int operator-(const Date& d);
	Date operator-(int day);
	Date& operator++();
	Date& operator--();
private:
	int _year;
	int _month;
	int _day;
};