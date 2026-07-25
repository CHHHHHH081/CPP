#include <iostream>
#include "inheritance.h"

//class A
//{
//public:
//	void fun()
//	{
//		cout << "func()" << endl;
//	}
//};
//class B : public A
//{
//public:
//	void fun(int i)
//	{
//		cout << "func(int i)" << i << endl;
//	}
//};
//int main()
//{
//	B b;
//	b.fun(10);
//	b.fun();
//	return 0;
//};

//class Person
//{
//public:
//    Person(const string& name)
//        :_name(name)
//    {
//        cout << "Person()" << endl;
//    }
//
//    ~Person()
//    {
//        cout << "~Person()" << endl;
//    }
//
//protected:
//    string _name;
//};
//
//class Student : public Person
//{
//public:
//    Student(const string& name, int id)
//        :Person(name)
//        , _id(id)
//    {
//        cout << "Student()" << endl;
//    }
//
//    ~Student()
//    {
//        Person::~Person();
//        cout << "~Student()" << endl;
//    }
//
//private:
//    int _id;
//};
//int main()
//{
//    Student s("张三", 1);
//    return 0;
//}

//前置声明
//class Student;
//
//class Person
//{
//public:
//	// 友元关系不能被继承
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // 姓名
//};
//
//class Student : public Person
//{
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // 学号
//};
//
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//
//int main()
//{
//	Person p;
//	Student s;
//	// 编译报错：error C2248: “Student::_stuNum”: 无法访问 protected 成员
//	// 解决方案：Display也变成Student 的友元即可
//	Display(p, s);
//
//	return 0;
//}

//class Person
//{
//public:
//	string _name;
//	static int _count;
//};
//int Person::_count = 0;
//
//class Student : public Person
//{
//protected:
//	int _stuNum;
//};
//
//int main()
//{
//	Person p;
//	Student s;
//
//	// 这里的运行结果可以看到非静态成员_name的地址是不一样的
//// 说明子类继承下来了，父子类对象各有一份
//	cout << "Pname：" << &p._name << endl;
//	cout << "Sname：" << &s._name << endl;
//
//	// 这里的运行结果可以看到静态成员_count的地址是一样的
//	// 说明子类和父类共用同一份静态成员
//	cout << "Pcount：" << &p._count << endl;
//	cout << "Scount：" << &s._count << endl;
//
//	// 公有的情况下，父子类指定类域都可以访问静态成员
//	cout << Person::_count << endl;
//	cout << Student::_count << endl;
//
//	Person::_count++;
//
//	cout << p._count << endl;
//	cout << s._count << endl;
//
//	return 0;
//}

//class Person
//{
//public :
//	string _name; // 姓名
//	string _Address;
//	string _Tel;
//	int _Age;
//	string _Gender;
//};
//
//class Student : public Person
//{
//protected :
//	int _num; //学号
//};
//
//class Teacher :  public Person
//{
//protected :
//	int _id; // 职⼯编号
//};
//// 教授助理
//class Assistant : public Student, public Teacher
//{
//protected :
//	string _majorCourse; // 主修课程
//};
//int main()
//{
//	Assistant a;
//	cout << sizeof(a) << endl;
//	return 0;
//}

class Person
{
public :
	Person(const char* name)
		: _name(name)
	{}
	string _name; // 姓名
};
class Student : virtual public Person
{
public :
	Student(const char* name, int num)
		: Person(name)
		, _num(num)
	{}
protected:
	int _num; //学号
};
class Teacher : virtual public Person
{
public :
	Teacher(const char* name, int id)
		: Person(name)
		, _id(id)
	{}
protected:
	int _id; // 职⼯编号
};

class Assistant : public Student, public Teacher
{
public :
	Assistant(const char* name1, const char* name2, const char* name3)
		: Person(name3)
		, Student(name1, 1)
		, Teacher(name2, 2)
	{}
protected:
	string _majorCourse; // 主修课程
};
int main()
{
	// 思考⼀下这⾥a对象中_name是"张三", "李四", "王五"中的哪⼀个？
	Assistant a("张三", "李四", "王五");
	return 0;
}
