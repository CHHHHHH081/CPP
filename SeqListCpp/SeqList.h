#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <unordered_map>
template<class T>
class SeqList
{
public:
	SeqList(int capacity = 10)
	{
		assert(capacity > 0);
		this->capacity = capacity;
		this->size = 0;
		this->data = new T[capacity];
	}
	~SeqList()
	{
		assert(this->data != nullptr);
		delete[] this->data;
	}
	SeqList(const SeqList& other)
	{
		this->capacity = other.capacity;
		this->size = other.size;
		this->data = new T[this->capacity];
		for (int i = 0; i < this->size; ++i)
		{
			this->data[i] = other.data[i];
		}
	}
	void insert(int pos, const T& value)
	{
		assert(pos >= 0 && pos <= this->size);
		if (this->size == this->capacity)
		{
			reallocate();
		}
		for (int i = this->size - 1; i >= pos; i--)
		{
			this->data[i + 1] = this->data[i];
		}
		this->data[pos] = value;
		this->size++;
	}
	void erase(int pos)
	{
		assert(pos >= 0 && pos < this->size);
		for (int i = pos; i < this->size - 1; i++)
		{
			this->data[i] = this->data[i + 1];
		}
		this->size--;
	}
	void push_back(const T& value){ insert(this->size, value); }
	void pop_back()
	{
		assert(this->size > 0);
		this->size--;
	}
	void clear(){ this->size = 0; }
	void reverse()
	{
		for (int i = 0; i < this->size / 2; i++)
		{
			T temp = this->data[i];
			this->data[i] = this->data[this->size - 1 - i];
			this->data[this->size - 1 - i] = temp;
		}
	}
	void sort(){ std::sort(this->data, this->data + this->size); }
	void swap(SeqList& other)
	{
		std::swap(this->data, other.data);
		std::swap(this->size, other.size);
		std::swap(this->capacity, other.capacity);
	}
	int getSize() const{ return this->size; }
	int getCapacity() const{ return this->capacity; }
	void print() const
	{
		for (int i = 0; i < this->size; i++)
		{
			std::cout << this->data[i] << " ";
		}
		std::cout << std::endl;
	}
	int find(const T& value) const
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->data[i] == value) return i;
		}
		return -1;
	}
	bool IsEmpty(){ return !(size > 0); }
	bool IsFull() { return size > 0; }
	T operator[](int pos) const
	{
		assert(pos >= 0 && pos < this->size);
		return this->data[pos];
	}
private:
	void reallocate()
	{
		this->capacity *= 2;
		T* newData = new T[this->capacity];
		for (int i = 0; i < this->size; i++)
		{
			newData[i] = this->data[i];
		}
		delete[] this->data;
		this->data = newData;
	}
    T* data;
	int size;
	int capacity;
};