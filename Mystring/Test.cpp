#include "String.h"
using namespace std;
namespace tzz
{
	void Test1()
	{
		string ch1;
		string ch2("hello world");
		ch2.resize(20,'m');
		cout << ch2;
	}
	void Test2()
	{
		string ch3("opopopop");
		cout << ch3<<endl;
		ch3.reserve(13);
		cout << ch3<<endl;
		cout << ch3.capacity() << endl;
	}
}
int main()
{
	//tzz::Test1();
	tzz::Test2();
	return 0;
}