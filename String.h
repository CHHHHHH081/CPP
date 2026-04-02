#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
namespace tzz
{
	class string
	{
		friend ostream& operator<<(ostream& out, string& ch);
	public:
		string()
			:_str(new char[1]{'\0'})
			,_size(0)
			,_capacity(0)
		{ }
		string(const char* str)
		{
			_size = strlen(str);
			//_capacity²»°üº¬\0
			_capacity = _size;
			_str = new char[_capacity+1];
			strcpy(_str, str);
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
		char& operator[](size_t pos);
		string& operator+=(string& str);
		/*string& operator+=(const char* s);
		string& operator+=(char ch);*/
		void resize(size_t n);
		void resize(size_t n, char c);
		size_t size() const;
		size_t capacity()const;
		void reserve(size_t n = 0);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	ostream& operator<<(ostream& out, string& ch);
}
