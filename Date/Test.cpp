#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
void Test1()
{
	Date d1(2025, 2, 8);
	Date d2(2024, 8, 11);
	/*cout << (d1 == d2)<<endl;
	cout << (d1 < d2) << endl;
	d1 += 4;
	cout << d1;
	Date d3;
	cin >> d3;
	cout << d3;*/
	/*int day = d1 - d2;
	cout << day << endl;*/
	/*d2 += 3000;
	cout << d2 << endl;*/
}
void Test2()
{
	Date d1(2026, 2, 8);
	Date d2;
	d2 = d1 - 209;
	cout << d2 << endl;
}
int main()
{
	/*Test1();*/
	Test2();
}