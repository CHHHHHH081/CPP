#include "SeqList.h"
template<class T>
void InterSection( SeqList<T>& cur,const SeqList<T>& other)
{
	std::unordered_map<T, int> hash;
	int n = cur.getSize();
	for (int i = 0; i < other.getSize(); i++) hash[other[i]]++;
	for (int i = 0; i < cur.getSize(); )
	{
		if (hash.count(cur[i]) == 0) cur.erase(i);
		else i++;
	}
}
template<class T>
void Union( SeqList<T>& cur,const SeqList<T>& other)
{
	std::unordered_map<T, int> hash;
	int n = cur.getSize();
	for (int i = 0; i < n; i++) hash[cur[i]]++;
	for (int i = 0; i < other.getSize(); i++)
	{
		if (hash.count(other[i]) == 0) cur.push_back(other[i]);
	}
}
int main()
{	
	SeqList<int> a, b;
	int x1 = 004,x2=10,x3=20,y1=004,y2=-10,y3=-20;
	a.push_back(x1);
	a.push_back(x2);
	a.push_back(x3);
	a.print();
	b.push_back(y1);
	b.push_back(y2);
	b.push_back(y3);
	b.print();
	Union(a,b);
	a.print();
	InterSection(a,b);
	a.print();
	std::cout << a.IsEmpty()<<std::endl;
	std::cout << a.IsFull() << std::endl;
	return 0;
}