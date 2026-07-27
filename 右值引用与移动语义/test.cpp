#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <assert.h>

using namespace std;

//int main()
//{
//	int x = 1;
//	int& r1 = x;
//	int&& rr1 = 2;
//	return 0;
//}

//string&& addstring(string s1,string s2)
//{
//	string s = s1 + s2;
//	return move(s);
//}
//
//int main()
//{
//	string s = addstring("111111111", "22222222");
//	cout << s;
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

		//// 移动构造
		//string(string&& s)
		//{
		//	cout << "string(string&& s) -- 移动构造" << endl;
		//	// 转移掠夺你的资源
		//	swap(s);
		//}

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

		//// 移动赋值
		//string& operator=(string&& s)
		//{
		//	cout << "string& operator=(string&& s) -- 移动赋值" << endl;
		//	swap(s);
		//	return *this;
		//}

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
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *2;
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
	// 传值返回需要拷⻉
	string addStrings(string num1, string num2) {
		string str;
		int end1 = num1.size() - 1, end2 = num2.size() - 1;
		// 进位
		int next = 0;
		while (end1 >= 0 || end2 >= 0)
		{
			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
			int ret = val1 + val2 + next;
			next = ret / 10;
			ret = ret % 10;
			str += ('0' + ret);
		}
		if (next == 1)
			str += '1';
		reverse(str.begin(), str.end());
		return str;
	}

	// 这⾥的传值返回拷⻉代价就太⼤了
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> vv(numRows);
		for (int i = 0; i < numRows; ++i)
		{
			vv[i].resize(i + 1, 1);
		}
		for (int i = 2; i < numRows; ++i)
		{
			for (int j = 1; j < i; ++j)
			{
				vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
			}
		}
		return vv;
	}
}

//int main()
//{
//	zzt::string s1("xxxxxx");
//	//拷贝构造
//	zzt::string s2 = s1;
//	//构造+移动构造，优化为直接构造
//	zzt::string s3 = zzt::string("114514");
//	//移动构造
//	zzt::string s4 = move(s1);
//	cout << "***********************************" << endl;
//	cout << s1.c_str() << endl;
//
//	return 0;
//}


//int main()
//{
//	zzt::string ret = zzt::addStrings("22222222", "333333333333333333333");
//	return 0;
//}

void Fun(int& x) { cout << "左值引用" << endl; }
void Fun(const int& x) { cout << "const 左值引用" << endl; }
void Fun(int&& x) { cout << "右值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }
template<class T>
void Function(T&& t)
{
	//Fun(t);
	Fun(forward<T>(t));
} 
int main()
{
	//10是右值-->T为int-->t是int&&
	Function(10);
	//a是左值-->T为int-->t是int&
	int a;
	Function(a);
	//move(a)是右值-->T为int-->t是int&&
	Function(move(a));

	const int b = 8;
	// b是左值-->T为const int&-->t为const int&
	Function(b);
	//move(b)是右值-->T为const int-->t为const int&&
	Function(move(b));
	return 0;
}
