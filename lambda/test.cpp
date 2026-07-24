#include <iostream>
#include <functional>

using namespace std;
//int main()
//{
//	auto add = [](int x, int y)->int {return x + y; };
//	cout << "add: " << add(1, 2) << endl;
//
//	auto func1 = [] {cout << "hello" << endl; };
//	cout << "func1: ";
//	func1();
//
//	int a = 1, b = 2;
//	cout << a << ':' << b<<endl;
//	auto swap = [](int& x, int& y)
//	{
//		int tmp = x;
//		x = y;
//		y = tmp;
//	};
//	swap(a, b);
//	cout << a << ':' << b << endl;
//	return 0;
//}

//int main()
//{
//	int a = 1, b = 2, c = 3;
//	auto func1 = [a, b, &c]()->int
//		{
//			c++;
//			return a + b + c;
//		};
//	cout << "func1: " << func1() << endl;
//
//	int x = 2, y = 3;
//	auto func2 = [=]()->int
//		{
//			return x + y + a;
//		};
//	cout << "func2: " << func2() << endl;
//
//	auto func3 = [&]()->int
//		{
//			x++;
//			y++;
//			return x + y;
//		};
//	cout << "func3: " << func3() << endl;
//
//	return 0;
//}

//class func
//{
//public:
//	func() = default;
//	void operator()()
//	{
//		cout << a << endl;
//	}
//private:
//	int a = 1;
//};
//
//int main()
//{
//	int a = 1;
//	auto f1 = [a] {cout << a << endl; };
//	func f2 = func();
//	f1();
//	f2();
//	return 0;
//}

//int Add(int a, int b)
//{
//    return a + b;
//}
//
//class Func
//{
//public:
//    int operator()(int a, int b)
//    {
//        return a + b;
//    }
//};
//
//int main()
//{
//    auto func = [](int a, int b) {return a + b; };
//    
//    function<int(int, int)> f1 = Add;
//    function<int(int, int)> f2 = Func();
//    function<int(int, int)> f3 = [](int a, int b) {return a + b; };
//
//    cout << f1(1, 1) << endl;
//    cout << f2(1, 1) << endl;
//    cout << f3(1, 1) << endl;
//
//
//	return 0;
//}

//class Plus
//{
//public:
//	Plus(int n = 1)
//		: _n(n)
//	{}
//	static int plusi(int a, int b)
//	{
//		return a + b;
//	} 
//	double plusd(double a, double b)
//	{
//		return (a + b) * _n;
//	}
//private:
//	int _n;
//};
//
//int main()
//{
//	function<int(int, int)> f4 = &Plus::plusi;
//	function<double(Plus*,double, double)> f5 = &Plus::plusd;
//	function<double(Plus,double, double)> f6 = &Plus::plusd;
//	function<double(Plus&&,double, double)> f7 = &Plus::plusd;
//
//	Plus pd;
//	cout << f4(1, 1) << endl;
//	cout << f5(&pd, 1.1, 1.1) << endl;
//	cout << f6(pd, 1.1, 1.1) << endl;
//	cout << f7(move(pd), 1.1, 1.1) << endl;
//	cout << f7(Plus(), 1.1, 1.1) << endl;
//
//	return 0;
//}

using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

//int sub(int a, int b)
//{
//	return a - b;
//}
//
//int subX(int a, int b, int c)
//{
//	return a - b - c;
//}
//
//int main()
//{
//	/*auto sub1 = bind(sub, _1, _2);
//	auto sub2 = bind(sub, _2, _1);
//
//	cout << sub1(5, 3) << endl;
//	cout << sub2(5, 3) << endl;*/
//	
//	/*auto sub3 = bind(sub, 100, _1);
//	auto sub4 = bind(sub, _1, 100);
//
//	cout << sub3(5) << endl;
//	cout << sub4(5) << endl;*/
//
//	auto sub5 = bind(subX, 100, _1, _2);
//	auto sub6 = bind(subX, _1, 100, _2);
//	auto sub7 = bind(subX, _1, _2, 100);
//
//	cout << sub5(5, 1) << endl;
//	cout << sub6(5, 1) << endl;
//	cout << sub7(5, 1) << endl;
//
//	return 0;
//}

//class Plus
//{
//public:
//	static int plusi(int a, int b)
//	{
//		return a + b;
//	}
//	double plusd(double a, double b)
//	{
//		return a + b;
//	}
//};
//
//int main()
//{
//	function<double(double, double)> f6 = bind(&Plus::plusd, Plus(), _1, _2);
//	cout << f6(1.1, 1.1);
//	return 0;
//}

int main()
{
	// 计算复利的lambda
	auto func1 = [](double rate, double money, int year)->double {
		double ret = money;
		for (int i = 0; i < year; i++)
		{
			ret += ret * rate;
		} 
		return ret - money;
		};
	// 绑死⼀些参数，实现出⽀持不同年华利率，不同⾦额和不同年份计算出复利的结算利息
	function<double(double)> func3_1_5 = bind(func1, 0.015, _1, 3);
	function<double(double)> func5_1_5 = bind(func1, 0.015, _1, 5);
	function<double(double)> func10_2_5 = bind(func1, 0.025, _1, 10);
	function<double(double)> func20_3_5 = bind(func1, 0.035, _1, 30);
	return 0;
}
