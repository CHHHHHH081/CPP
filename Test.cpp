#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include <unordered_map>
using namespace std;
void Test01()
{
	string s1;
	string s2("Hello World");
	string s3(s2);
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
}
void Test02()
{
	string s1;
	cout << "Initial Capacity: " << s1.capacity() << endl;
	for (int i = 0; i < 200; i++)
	{
		size_t cap = s1.capacity();
		s1 += 'm';
		if (s1.capacity() != cap)
			cout << "Capacity Change: " << s1.capacity()<<endl;
	}
}
void Test03()
{
	int a = 10;
	double b = 1.5;
	string s = "jjjjjj";
	int& _a = a;
	auto c = a;
	auto d = b;
	auto e = s;
	auto& f = _a;
	cout << "c: " << typeid(c).name() << endl;
	cout << "d: " << typeid(d).name() << endl;
	cout << "e: " << typeid(e).name() << endl;
	cout << "f: " << typeid(f).name() << endl;
}
void Test04()
{
	unordered_map<string, string> dict;
	//unordered_map<string, string>::iterator it=dict.begin();
	auto it = dict.begin();
	cout << typeid(it).name() << endl;
}
void Test05()
{
	int arr[] = { 1,1,4,5,1,4 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	for (auto i : arr)
	{
		cout << i << ' ';
	}
	cout << endl;
	string s = "hello world";
	for (auto i : s)
	{
		cout << i;
	}
	cout << endl;
}
void Test06()
{
	string s("hello world");
	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i] << ' ';
	}
	cout << endl;
}
void Test08()
{
	string s("hello world");
	for (auto it = s.rbegin(); it != s.rend(); it++)
	{
		cout << *it << ' ';
	}
	cout << endl;
}
void Test09()
{
	string s("hello world");
	cout << s.c_str();
}
void Test10()
{
	string s1("abc");
	string s2("def");
	s1.append("defg", 2);
	cout << s1 << endl;
}
void Test11()
{
	cout << "非迭代器版本插入：" << endl;
	string s1("abc");
	string s2("defgh");
	cout << s1 << ' ' << s2 << endl;
	s2.insert(0, s1);
	cout << s2 << endl;
	s2.insert(s2.size(),"ijk");
	cout << s2 << endl;
	cout << "迭代器版本插入：" << endl;
	auto it1 = s1.begin();
	s1.insert(it1 + 1, 10, 'x');
	cout << s1 << endl;
}
void Test12()
{
	string s1("abcdefg");
	string s2("qwerty");
	cout << "s1: " << s1 << endl << "s2: " << s2 << endl;
	s1.assign(s2);
	cout << s1 << endl;
	s1.assign("plmokn");
	cout << s1 << endl;
	s1.assign("zxcvbn", 4);
	cout << s1 << endl;
}
void Test13()
{
	string s1("abcdefg");
	cout << s1 << endl;
	s1.erase(0, 2);
	cout << s1 << endl;
	auto it = s1.begin();
	s1.erase(it,it+2);
	cout << s1 << endl;
}
void Test14()
{
	string s1("0123456789");
	string s2("123456");
	size_t index = s1.find(s2);
	cout << index << endl;
	index = s1.find("56789");
	cout << index << endl;
	index = s1.find('x');
	cout << index << endl;
}
void Test15()
{
	string s1("abcdef");
	string s2("aaafgh");
	int a = s1.compare(1, 1, s2, 3, 1);
	cout << a;
}
int main()
{
	Test15();
	return 0;

}