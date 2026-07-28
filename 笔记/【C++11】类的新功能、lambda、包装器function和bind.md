# 一、类的新功能
## 1. 默认的移动构造与移动赋值
- 在我们之前学习类和对象时，我们知道有**四个最重要的默认成员函数：构造函数、析构函数、拷贝构造函数、拷贝赋值重载**。
- 我们之前也学过了**C++11的移动构造与移动赋值**，那么C++11新增了它们的**默认形式**。但是生成它们的条件比较苛刻：如果没有自己实现**移动构造/移动赋值**，且**没有实现析构函数、拷贝构造、拷贝赋值重载中的任意一个**。那么编译器会自动生成一个**默认移动构造/移动赋值**。默认生成的**移动构造/移动赋值**，对于内置类型成员会执行逐成员按字节拷贝，自定义类型成员，则需要看这个成员是否实现**移动构造/移动赋值**，如果实现了就调用**移动构造/移动赋值**，没有实现就调用**拷贝构造/拷贝赋值**。
- 如果你提供了**移动构造或者移动赋值**，编译器不会自动提供拷贝构造和拷贝赋值。
## 2. 成员变量声明时给缺省值
成员变量声明时可以给缺省值，这个缺省值是给初始化列表的时候用的，在前面的类和对象已经提及。
## 3. defult与delete
### 3.1 defult
对于defult，假设你要使某个类有自己的默认构造，但是它没有生成，你可以使用`=defult`强制生成。
```cpp
class A
{
public:
    A(int x)
    {}
};
```
像上面，已经写了`A(int)`的构造函数，因此编译器不会在生成默认构造，如果直接直接实例化A对象而不初始化：`A a;`，就会报错。
```cpp
class A
{
public:
    A() = default;

    A(int x)
    {
    }
};
```
像这样，就能解决以上的问题。
defult不仅只局限于**构造函数**，对于析构函数、拷贝构造、移动构造等等也同样适用。
### 3.2 delete
`=delete`刚好与`=defult`相反，它可以使某个函数直接被禁止调用。
在C++98中，我们可以将函数放在private区中以实现类似的效果，两者在调用函数时编译器都会报错。
但是，对于`=delete`，如果调用函数，编译器会在编译期就报错，而且即使在类的内部也无法使用该函数。
对于`private`限定，如果调用函数，编译器会在编译期或链接期报错，而且函数在类的内部可以被调用。
因此，`=delete`限定的函数要求更严格，在任何地方都无法被调用。
## 4. final与override
这个在继承与多态中已经详细提及，这里就不做介绍了。
# 二、STL的变化
- 对于容器，最显著实用的变化就是多了`unordered_map`与`unordered_set`两个容器，其余并不是特别重要。
- STL同时也增加了许多新接口，最重要的就是右值引用和移动语义相关的push/insert/emplace系列接口和移动构造和移动赋值，还有initializer_list版本的构造等。
# 三、lambda
## 1. lambda表达式
Lambda 表达式是 **C++11 最重要的新特性之一**，它本质上就是**匿名函数对象（匿名仿函数）**。
在C++中，如果要对一个数组进行排序，同时我们可以调整其升序或者降序，我们很容易想到可以采用**sort( )+仿函数**来实现：

```cpp
class Compare
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

int v[10]={2,7,3,1,5,4,9,0,8,6};
sort(v.begin(), v.end(), Compare());
```
但是，这种方法存在缺陷，在排序前，还必须写一个仿函数类。因此，在C++11中就引入了lambda：
```cpp
sort(v.begin(), v.end(),
    [](int a,int b)
    {
        return a>b;
    });
```
**在使用上，Lambda就是为了代替那些只使用一次的小函数。**
## 2. 语法
**完整语法：**

```cpp
[capture](parameters) mutable -> return_type
{
    function_body;
};
```

| 组成部分         | 名称                                     | 是否必写 | 作用                                                         | 示例                              |
| ---------------- | ---------------------------------------- | -------- | ------------------------------------------------------------ | --------------------------------- |
| `[]`             | **捕获列表（Capture List）**             | **是**   | 指定是否以及如何捕获外部局部变量                             | `[]`、`[=]`、`[&]`、`[a]`、`[&a]` |
| `()`             | **参数列表（Parameter List）**           | **否**   | 指定 Lambda 接收的参数，与普通函数参数一致，从 C++23 开始，Lambda 允许在没有参数、没有 mutable、没有返回类型、没有其他说明符时省略 ()。 | `(int a, int b)`                  |
| `mutable`        | **可变说明符（Mutable Specifier）**      | **否**   | 允许修改**值捕获**得到的变量副本                             | `[a]() mutable { a++; }`          |
| `-> return_type` | **尾置返回类型（Trailing Return Type）** | **否**   | 显式指定返回值类型，通常由编译器自动推导                     | `-> int`、`-> double`             |
| `{}`             | **函数体（Function Body）**              | **是**   | Lambda 的具体执行代码                                        | `{ return a + b; }`               |

**写几个简单的lambda：**

```cpp
int main()
{
	auto add = [](int x, int y)->int {return x + y; };
	cout << "add: " << add(1, 2) << endl;

	auto func1 = [] {cout << "hello" << endl; };
	cout << "func1: ";
	func1();

	int a = 1, b = 2;
	cout << a << ':' << b<<endl;
	auto swap = [](int& x, int& y)
		{
			int tmp = x;
			x = y;
			y = tmp;
		};
	swap(a, b);
	cout << a << ':' << b << endl;
	return 0;
}
```
**结果：**
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7797fc84907e419790c762958d5dfca4.png)
## 3. 捕获列表
- lambda默认只能使用lambda函数体和参数中的变量，如果想要使用外层作用域中的变量就要进行捕获。捕获方式有**值捕获、引用捕获、隐式捕获以及混合捕获**。
- 第一种捕获方式就是显式的传值或传引用捕获，捕获的变量用逗号分开。如：`[x, y, &z]`，其中，x,y是传值捕获，z是传引用捕获。
- 要注意，传值捕获的变量在lambda中是不能被修改的，但是像上面一样加上**mutable**就可以被修改。修改x,y不会影响原作用域中x,y的值，修改z会影响。
- 第二种捕获方式是隐式捕获，我们在捕获列表中写一个 **=** 表示隐式值捕获，写一个 **&** 表示隐式引用捕获，**这样编译器就会根据我们在函数体中对变量的使用情况来进行捕获（注意：底层不是全部捕获进来）**。
- 第三种捕捉方式是在捕捉列表中混合使用隐式捕捉和显示捕捉。`[=,&x]`表示其他变量隐式值捕捉，x引用捕捉；`[&, x, y]`表示其他变量引用捕捉，x和y值捕捉。当使用混合捕捉时，第一个元素必须是&或=，**并且&混合捕捉时，后面的捕捉变量必须是值捕捉，同理=混合捕捉时，后面的捕捉变量必须是引用捕捉**。
- lambda 表达式如果在函数局部域中，他可以捕捉 lambda 位置之前定义的变量，不能捕捉静态局部变量和全局变量，静态局部变量和全局变量也不需要捕捉， lambda 表达式中可以直接使用。**这也意味着 lambda 表达式如果定义在全局位置，捕捉列表必须为空**。

```cpp
int main()
{
	int a = 1, b = 2, c = 3;
	auto func1 = [a, b, &c]()->int
		{
			c++;
			return a + b + c;
		};
	cout << "func1: " << func1() << endl;

	int x = 2, y = 3;
	auto func2 = [=]()->int
		{
			return x + y + a;
		};
	cout << "func2: " << func2() << endl;

	auto func3 = [&]()->int
		{
			x++;
			y++;
			return x + y;
		};
	cout << "func3: " << func3() << endl;

	return 0;
}
```
## 4. lambda的原理
- **lambda底层就是一个仿函数类**。
- 仿函数类名是随机生成的，为了保证不同的lambda生成的类名不同。**lambda的参数/返回类型/函数体就是operator()的参数/返回类型/函数体，lambda的捕获列表就是仿函数类的成员变量。**

对于一个lambda：

```cpp
auto f = [a, &b](int x){};
```
编译器生成（实际并非如此，仅供理解）：

```cpp
class __Lambda_1
{
public:
    int operator()(int x) const{}
private:
	int a;
	int& b;
};
```
我们可以从汇编层来看：
对于：
```cpp
class func
{
public:
	func() = default;
	void operator()()
	{
		cout << a << endl;
	}
private:
	int a = 1;
};

int main()
{
	int a = 1;
	auto f1 = [a] {cout << a << endl; };
	func f2 = func();
	f1();
	f2();
	return 0;
}
```
看看汇编：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/77ae4cb2559148adab933069947145cc.png)
# 四、包装器
## 1. function

```cpp
template <class T> function;     // undefined
template <class Ret, class... Args> class function<Ret(Args...)>;
```
有三个可调用对象，普通函数、仿函数和lambda：
```cpp
int Add(int a, int b)
{
    return a + b;
}

class Func
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};

auto func = [](int a, int b)
{
    return a + b;
};
```
如果我们想要统一存放它们，就可以用到**包装器function**。
- **std::function 是一个类模板，也是一个包装器。** std::function的实例对象可以包装存储其他的可以调用对象，包括**函数指针、仿函数、lambda 、bind表达式等**，存储的可调用对象被称为std::function 的目标。若std::function 不含目标，则称它为空。调用空std::function 的目标导致抛出std::bad_function_call异常。
**语法：**
```cpp
function<返回值(参数...)> 名字;
```
对上面的可调用对象进行包装：
```cpp
function<int(int, int)> f1 = Add;
function<int(int, int)> f2 = Func();
function<int(int, int)> f3 = [](int a, int b) {return a + b; };
```
对于成员函数，静态成员函数要指定类域并且前面加&才能获取地址；对于普通成员函数，还需要再传一个隐含的this指针参数，因此在绑定时还需传一个对象或对象的指针过去。
```cpp
class Plus
{
public:
	Plus(int n = 1)
		: _n(n)
	{}
	static int plusi(int a, int b)
	{
		return a + b;
	} 
	double plusd(double a, double b)
	{
		return (a + b) * _n;
	}
private:
	int _n;
};

int main()
{
	function<int(int, int)> f4 = &Plus::plusi;
	function<double(Plus*,double, double)> f5 = &Plus::plusd;
	function<double(Plus,double, double)> f6 = &Plus::plusd;
	function<double(Plus&&,double, double)> f7 = &Plus::plusd;
	
	Plus pd;
	cout << f4(1, 1) << endl;
	cout << f5(&pd, 1.1, 1.1) << endl;
	cout << f6(pd, 1.1, 1.1) << endl;
	cout << f7(move(pd), 1.1, 1.1) << endl;
	cout << f7(Plus(), 1.1, 1.1) << endl;

	return 0;
}
```
## 2. bind
```cpp
simple(1)	
template <class Fn, class... Args>
  /* unspecified */ bind (Fn&& fn, Args&&... args);
with return type (2)	
template <class Ret, class Fn, class... Args>
  /* unspecified */ bind (Fn&& fn, Args&&... args);
```
- bind 是一个**函数模板**，它也是一个**可调用对象的包装器**，可以把他看做一个**函数适配器**，对接收的fn可调用对象进行处理后返回一个可调用对象。 bind 可以用来调整参数个数和参数顺序。**bind也在 < functional > 这个头文件中**。
- 调用bind的一般形式：**auto newCallable = bind(callable,arg_list);** 其中**newCallable和callable本身是一个可调用对象，arg_list是一个逗号分隔的参数列表**，对应给定的callable的参数。当我们调用newCallable时，newCallable会调用callable，并传给它arg_list中的参数。
- arg_list中的参数可能包含形如_n的名字，其中n是一个整数，这些参数是占位符，表示newCallable的参数，它们占据了传递给newCallable的参数的位置，**实际上就是表示实参的位置**。数值n表示生成的可调用对象中参数的位置，**这些占位符放到placeholders的一个命名空间中**。
### 2.1 调整参数位置

```cpp
#include <functional>
using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

int sub(int a, int b)
{
	return a - b;
}

int main()
{
	auto sub1 = bind(sub, _1, _2);
	auto sub2 = bind(sub, _2, _1);

	cout << sub1(5, 3) << endl;
	cout << sub2(5, 3) << endl;
	
	return 0;
}
```
结果分别是2  -2。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3d3dd5d4d779419f80e0dedaa835cc4f.png)
### 2.2 调整参数个数

```cpp
int main()
{
	auto sub3 = bind(sub, 100, _1);
	auto sub4 = bind(sub, _1, 100);
	
	cout << sub3(5) << endl;
	cout << sub4(5) << endl;
	return 0;
}
```
结果是95  -95。

```cpp
int subX(int a, int b, int c)
{
	return a - b - c;
}
int main()
{
	//分别绑定1,2,3的参数
	auto sub5 = bind(subX, 100, _1, _2);
	auto sub6 = bind(subX, _1, 100, _2);
	auto sub7 = bind(subX, _1, _2, 100);
	
	cout << sub5(5, 1) << endl;
	cout << sub6(5, 1) << endl;
	cout << sub7(5, 1) << endl;
	return 0;
}
```
结果是94  -96  -96。
我们在之前的function中提到，对于普通成员函数，要在包装器中传一个对象或对象的指针，**那么我们可以用bind将其绑定，这样就不用我们手动去传了**。

```cpp
class Plus
{
public:
	static int plusi(int a, int b)
	{
		return a + b;
	}
	double plusd(double a, double b)
	{
		return a + b;
	}
};

int main()
{
	function<double(double, double)> f6 = bind(&Plus::plusd, Plus(), _1, _2);
	cout << f6(1.1, 1.1);
	return 0;
}
```
在实际场景中，比如计算复利，我们可以绑定一些一般不变的常量。
```cpp
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
```