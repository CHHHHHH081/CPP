#pragma once
#include <iostream>
#define NN 10
using namespace std;
namespace zzt
{
	//¾²Ì¬Êý×é
	template<class T, size_t N = 10>
	class array
	{
	private:
		T _array[N];
		size_t _size;
	};
}

