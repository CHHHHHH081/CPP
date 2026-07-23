#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;
class Date
{
public:
	Date(const int year,const int month=6,const int day=22)
		:_year(year),_month(month),_day(day)
	{
		cout << "Date(const int year,const int month,const int day)"<<endl;
	}

	Date(const Date& d)
		:_year(d._year), _month(d._month), _day(d._day)
	{
		cout << "Date(const Date& d)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
//int main()
//{
//	Date d1(2026, 6, 22);
//	Date d2 = { 2026,6,22 };
//	Date d3 = { 2026 };
//	Date d4 = 2026;
//	Date d5{ 2026 };
//	vector<Date> v;
//	v.push_back(Date{ 2026,6,22 });
//	v.push_back({ 2026,6,22 });
//	vector<int> v1{{ 1,2,3,4,5 }};
//	return 0;
//}

int main()
{
	initializer_list<int> il = { 1,2,3,4,5 };
	vector<int> v1(il)
	return 0;
}