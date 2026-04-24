#include "Date.h"
bool Date::CheckDate()
{
	if (_month <= 0 || _month >= 13) return false;
	if (_day <= 0 || _day > GetMonthDay(_year, _month)) return false;
	return true;
}
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	if (!CheckDate())
	{
		cout << "日期非法";
	}
}
bool Date::operator>(const Date& d) const
{
	if (_year > d._year) return true;
	else if (_year == d._year)
	{
		if (_month > d._month) return true;
		else if (_month == d._month) return _day > d._day;
	}
	return false;
}
bool Date::operator>=(const Date& d) const
{
	return (*this) > d || (*this) == d;
}
bool Date::operator<(const Date& d) const
{
	return !((*this) >= d);
}
bool Date::operator<=(const Date& d) const
{
	return !((*this) > d);
}
bool Date::operator==(const Date& d) const
{
	return _year == d._year && _month == d._month && _day == d._month;
}
bool Date::operator!=(const Date& d) const
{
	return !((*this) == d);
}

Date& Date::operator+=(int day)
{
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month >= 13)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}
Date Date::operator+(int day)
{
	Date tmp = *this;
	tmp += day;
	return tmp;
}
Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		if (_month == 1)
		{
			_year--;
			_month = 12;
			_day += GetMonthDay(_year,_month);
		}
		else
		{
			_month--;
			_day += GetMonthDay(_year,_month);
		}
	}
	return *this;
}
int Date::operator-(const Date& d)
{
	Date max = *this;
	Date min = d;
	int cnt = 0;
	int flag = 1;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	while (min != max)
	{
		min+=1;
		cnt++;
	}
	return cnt * flag;
}
Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}
Date& Date::operator++()
{
	*this += 1;
	return *this;
}
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}
ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日"<<endl;
	return out;
}
istream& operator>>(istream& in, Date& d)
{
	cout << "请依次输入年月日"<<endl;
	in >> d._year >> d._month >> d._day;
	return in;
}