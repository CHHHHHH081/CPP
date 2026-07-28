# 一、C++的发展史
C++11 是 C++ 的第二个主要版本，并且是从 C++98 起的**最重要更新**。它引入了大量更改，标准化了既有实践，并改进了对C++程序员可用的抽象。在它最终由 ISO 在 2011 年 8月12日采纳前，人们曾使⽤名称“C++0x”，因为它曾被期待在 2010 年之前发布。C++03 与 C++11 期间花了 8 年时间，故而这是**迄今为止最长的版本间隔**。**从那时起，C++ 有规律地每 3 年更新一次**。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8bfad922feb3465086f5d62dc3f00cab.png)

# 二、列表初始化
## 1. 出现的问题
在C++98中，我们可以用{}初始化**数组和结构体**。
```cpp
int arr[] = {1,2,3};

struct Point
{
    int x;
    int y;
};

Point p = {1,2};
```
但是我们不能这样初始化类对象：
```cpp
string s = {"hello"}; // C++98不支持
```
##  2. C++11的列表初始化
> **为了解决C++98中列表初始化的问题，C++11的列表初始化应运而生**，它可以应用于**任何数据类型的初始化**，实现了初始化方式的统一。

- 这个初始化**内置类型支持，自定义类型也支持**，自定义类型本质是**类型转换，中间会产生临时对象，最后优化了以后变成直接构造**。
- {}初始化的过程中，可以省略掉= 
- C++11列表初始化的本意是想实现一个大统一的初始化方式，其次他在有些场景下带来的不少便利，如容器push/insert多参数构造的对象时，{}初始化会很方便 
### 2.1 内置类型的初始化

```cpp
int a=2;
int b{2};
```

列表初始化与普通的初始化完全一样，我们可以看看它们底层的汇编语言：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/f056cff009f04082909ed42daad05566.png)
可见它们没的汇编语言一模一样，没有任何区别。
### 2.2 自定义类型的初始化

```cpp
class Date
{
public:
	Date(const int year,const int month,const int day)
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
int main()
{
	Date d1(2026, 6, 22);
	Date d2 = { 2026,6,22 };
	return 0;
}
```

自定义类型也是一样的，列表初始化与普通初始化没有区别：![](https://i-blog.csdnimg.cn/direct/f2e995e0d1c949f8b064d8a8a75a0b1c.png)
如果在编译器不优化的情况下，对于：
```cpp
Date d2 = { 2026,6,22 };
```
编译器会先先生成一个{2026,6,22}的临时变量，再拷贝给d2。编译器采取了优化，它会直接构造{2026,6,22}的对象d1。
我们可以运行以上代码验证：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c9ab859404374878b1843f062ad50996.png)
只有两个构造，没有拷贝，印证了之前的结论。

```cpp
const Date& d2 = { 2026, 6, 22 };
```
对于d2，它引用的是{2026,6,22}产生的**临时对象**，**临时对象具有常性，是一个右值，必须要加const**，至于右值的概念，下一节会详细讲述。
对于类型转换，C++98支持单参数类型转换，可以省去{}
```cpp
//在构造函数后两个参数为缺省值的情况下
Date d3 = { 2026 };	//C++11列表初始化
Date d4 = 2026;		//C++98单参数
```
对于列表初始化来讲，可以省略“=”，但是C++98的单参数类型转换不能省略“=”。
```cpp
Date d3{ 2026 };	//C++11可行
Date d4 2026;		//C++98不支持
```
### 2.3 STL中的应用
我们就以vector的push_back为例：
```cpp
vector<Date> v;
v.push_back(Date{ 2026,6,22 });
v.push_back({ 2026,6,22 });
```
我们在一个vector< Date >中插入数据，如果不使用初始化列表的话我们是创建一个匿名对象再进行插入；那么现在我们可以直接省略Date，直接插入{}。
# 三、std::initializer_list
## 1. 什么是initializer_list
我们先看一行代码：
```cpp
Date d2 = { 2026,6,22 };
vector<int> v1{ 1,2,3,4,5 };
```
这两个看上去好像是同一种语法，但是它们在底层调用上有所区别。
对于Date来讲，编译器看到 `{ 2026,6,22 }` ，它会匹配到`Date(int,int,int)`的构造函数，直接构造。
对于vector来讲，编译器看到`{1,2,3,4,5}`，它会匹配到`vector(initializer_list)`
引入正题，**initializer_list就是C++11 提供的一个轻量级容器**，之前我们也有提到过。我们先来看看它的声明：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/459ab7053156460e974d77dae0186f98.png)
它的接口也是非常的精简：![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dd9a589e39a847e081c3eb6befdf4011.png)

## 2. 底层与迭代器
它的底层结构大概是这样：

```cpp
template<class T>
class initializer_list
{
public:
    typedef const T* iterator;
    typedef const T* const_iterator;

    iterator begin() const
    {
        return _first;
    }

    iterator end() const
    {
        return _last;
    }

    size_t size() const
    {
        return _last - _first;
    }

private:
    const T* _First;
    const T* _Last;
};
```
它实际上就是_First和_Last两个指针，两指针分别指向数据头和尾的下一个，**它的本质就是一个只读区间**。它里面有begin和end两个迭代器，因此它支持范围for。**它的内层是开辟在栈区的**。
## 3. vector的情形
当我们调用：
```cpp
vector<int> v1{ 1,2,3,4,5 };
```
编译器匹配`vector(initializer_list)`，在编译器不优化的情况下，它会生成一个initializer_list来拷贝。但是实际情况下，编译器就**直接将列表里的数给v1，而不产生额外的开销**。
## 4. 总结
| 项目        | 底层实现     |
| ----------- | ------------ |
| 存储结构    | 两个指针     |
| begin()     | const T*     |
| end()       | const T*     |
| iterator    | const T*     |
| 支持范围for | 支持         |
| 元素可修改  | 不支持       |
| 本质        | 一个只读区间 |

==**要注意：initializer_list本身不存储数据，只是对编译器生成的临时数组进行包装。它内部仅维护[first,last)两个指针，其迭代器本质就是const T*。**==

