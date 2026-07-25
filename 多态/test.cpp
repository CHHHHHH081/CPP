//#define _CRT_SECURE_NO_WARNINGS
#include "Polymorphism.h"
//
//class Person {
//public:
//	 virtual void BuyTicket() { cout << "买票-全价" << endl; }
//	 virtual void func() { cout << "Perfunc()" << endl; }
//private:
//	string _name="张三";
//	int _age=18;
//};
//class Student : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//	virtual void func() { cout << "Stufunc()" << endl; }
//private:
//	int _id = 1;
//};
//
//void Func(Person* ptr){
//	ptr->BuyTicket();
//} 
//int main()
//{
//	int i = 0;
//	static int j = 1;
//	int* p1 = new int;
//	const char* p2 = "xxxxxxxx";
//	printf("栈:%p\n", &i);
//	printf("静态区:%p\n", &j);
//	printf("堆:%p\n", p1);
//	printf("常量区:%p\n", p2);
//
//	Person ps;
//	Student st;
//	Person* p3 = &ps;
//	Student* p4 = &st;
//	printf("Person虚表地址:%p\n", *(int*)p3);
//	printf("Student虚表地址:%p\n", *(int*)p4);
//	return 0;
//	return 0;
//}

//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); }
//};
//class B : public A
//{
//public:
//	void func(int val = 0) {
//		std::cout << "B->" << val << std::endl;
//	}
//};
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->test();
//	return 0;
//}

//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//protected:
//	int _b = 1;
//	char _ch = 'x';
//};
//int main()
//{
//	Base b;
//	cout << sizeof(b) << endl;
//	return 0;
//}

//class Car
//{
//public:
//	 纯虚函数
//	virtual void Drive() = 0;
//};
//
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-舒适" << endl;
//	}
//};
//
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-操控" << endl;
//	}
//};

class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
	void func5() { cout << "Base::func5" << endl; }
protected:
	int a = 1;
};

class Derive : public Base
{
public:
	// 重写基类的func1
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func1" << endl; }
	void func4() { cout << "Derive::func4" << endl; }

protected:
	int b = 2;
};

int main()
{
	int i = 0;
	static int j = 1;
	int* p1 = new int;
	const char* p2 = "xxxxxxxx";
	printf("栈:%p\n", &i);
	printf("静态区:%p\n", &j);
	printf("堆:%p\n", p1);
	printf("常量区:%p\n", p2);

	Base b;
	Derive d;
	Base* p3 = &b;
	Derive* p4 = &d;
	printf("Person虚表地址:%p\n", *(int*)p3);
	printf("Student虚表地址:%p\n", *(int*)p4);
	printf("虚函数地址:%p\n", &Base::func1);
	printf("普通函数地址:%p\n", &Base::func5);
	return 0;
}
