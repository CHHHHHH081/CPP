#pragma once
#include <string>
#include <vector>
using namespace std;
//class Person
//{
//public:
//	// 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
//	void identity()
//	{
//		cout << "void identity()" << _name << endl;
//	}
//protected:
//	string _name = "张三"; // 姓名
//	string _address; // 地址
//	string _tel; // 电话
//	int _age = 18; // 年龄
//};
//
//class Student : public Person
//{
//	public :
//	// 学习
//	void study()
//	{
//		// ...
//	}
//protected:
//	int _stuid; // 学号
//};
//
//class Teacher : public Person
//{
//public:
//	// 授课
//	void teaching()
//	{
//		//...
//	}
//protected:
//	string title; // 职称
//};

namespace zzt
{
	template<class T>
	class stack : public vector<T>
	{
	public:
		void push(const T& x)
		{
			vector<T>::push_back(x);
		}
	};
}