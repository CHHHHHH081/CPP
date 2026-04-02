#include "String.h"
using namespace std;
namespace tzz
{
	void string::resize(size_t n)
	{
		if (n == _size) return;
		char* tmp = new char[n+1] {'\0'};
		if (n >= _size) strcpy(tmp, _str);
		else
		{
			strncpy(tmp, _str, n);
			tmp[n] = '\0';
		}
		delete[] _str;
		_str = tmp;
		_size = n;
		_capacity = n;
	}
	void string::resize(size_t n, char c)
	{
		if (n == _size) return;
		char* tmp = new char[n + 1];
		fill(tmp, tmp + n + 1, c);
		if (n > _size) strncpy(tmp, _str,_size);
		else
		{
			strncpy(tmp, _str, n);
			tmp[n] = '\0';
		}
		delete[] _str;
		_str = tmp;
		_size = n;
		_capacity = n;
	}
	ostream& operator<<(ostream& out, string& ch)
	{
		for (int i = 0; i < ch._size; i++)
			out << ch._str[i];
		return out;
	}
	char& tzz::string::operator[](size_t pos)
	{
		assert(pos<_size);
		return _str[pos];
	}
	string& tzz::string::operator+=(string& str)
	{
		_capacity += str._capacity;
		char* tmp = new char[_capacity + 1];
		strcpy(tmp, str._str);
		delete[] str._str;
		str._str = tmp;
		for (int i = 0; i < str._size; i++)
		{
			_str[i + _size] = str._str[i];
		}
		_size += str._size;
		return *this;
	}
	/*string& tzz::string::operator+=(const char* s)
	{

	}
	string& tzz::string::operator+=(char ch)
	{

	}*/
	size_t string::size() const
	{
		return _size;
	}
	size_t string::capacity() const
	{
		return _capacity;
	}
	void string::reserve(size_t n)
	{
		if (n <= _capacity) return;
		_capacity = n;
		char* tmp = new char[n+1];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
}