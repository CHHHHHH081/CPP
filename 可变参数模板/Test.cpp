#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <list>

using namespace std;
//void ShowList()
//{
//    // 编译器时递归的终⽌条件，参数包是0个时，直接匹配这个函数
//    cout << endl;
//}
//template <class T, class ...Args>
//void ShowList(T x, Args... args)
//{
//    cout << x << " ";
//    // args是N个参数的参数包
//    // 调⽤ShowList，参数包的第⼀个传给x，剩下N-1传给第⼆个参数包
//    ShowList(args...);
//}
//// 编译时递归推导解析参数
//template <class ...Args>
//void Print(Args... args)
//{
//    ShowList(args...);
//}

//template <class T>
//const T& GetArg(const T& x)
//{
//	cout << x << " ";
//	return x;
//} 
//template <class ...Args>
//void Arguments(Args... args)
//{}
//template <class ...Args>
//void Print(Args... args)
//{
//	// 注意GetArg必须返回或者到的对象，这样才能组成参数包给Arguments
//	Arguments(GetArg(args)...);
//}

//template<class... Args>
//void Print(Args... args)
//{
//    int arr[] = { (cout << args << ' ',0)... };
//    cout << endl;
//}
//
//int main()
//{
//    Print(1, 2.2, string("hello"));
//	return 0;
//}

namespace zzt
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str) -- 构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造" << endl;
			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}

		void swap(string& ss)
		{
			::swap(_str, ss._str);
			::swap(_size, ss._size);
			::swap(_capacity, ss._capacity);
		}

		// 移动构造
		string(string&& s)
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			// 转移掠夺你的资源
			swap(s);
		}

		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷贝赋值" <<
				endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}

		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;
			swap(s);
			return *this;
		}

		~string()
		{
			//cout << "~string() -- 析构" << endl;
			delete[] _str;
			_str = nullptr;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		const char* c_str() const
		{
			return _str;
		}

		size_t size() const
		{
			return _size;
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	};
}

//int main()
//{
//	list<zzt::string> lt;
//	zzt::string s1 = "1111111111";
//	/*cout << "********************************" << endl;
//	lt.push_back(s1);
//	cout << "********************************" << endl;
//	lt.emplace_back(s1);*/
//	zzt::string s2 = "1111111111";
//	cout << "********************************" << endl;
//	lt.push_back(move(s1));
//	cout << "********************************" << endl;
//	lt.emplace_back(move(s2));
//
//	return 0;
//}

//int main()
//{
//	list<zzt::string> lt;
//	lt.push_back("1111111111");
//	cout << "********************************" << endl;
//	lt.emplace_back("1111111111");
//}

int main()
{
	list<pair<zzt::string, int>> lt;
	lt.push_back({ "苹果",1 });
	cout<< "********************************" <<endl;
	lt.emplace_back("苹果", 1);
	return 0;
}
