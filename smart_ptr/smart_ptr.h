#pragma once
#include <functional>
#include <iostream>
#include <memory>
using namespace std;

namespace zzt
{
	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr=nullptr)
			:_ptr(ptr),_pcount(new int(1))
		{}

		template<class D>
		shared_ptr(T* ptr,D del)
			:_ptr(ptr),_pcount(new int(1)),_del(del)
		{}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr), _pcount(sp._pcount), _del(sp._del)
		{
			(*_pcount)++;
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				release();
				this->_ptr = sp._ptr;
				this->_del = sp._del;
				this->_pcount = sp._pcount;
				_pcount++;
			}
			return *this;
		}

		void release()
		{
			if (--(*_pcount) == 0)
			{
				_del(_ptr);
				delete _pcount;
				_ptr = nullptr;
				_pcount = nullptr;
			}
		}

		~shared_ptr()
		{
			release();
		}

		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }
		T* get() const { return _ptr; }
		int use_count() const { return *_pcount; }
		
	private:
		T* _ptr;
		int* _pcount;
		function<void(T*)> _del = [](T* ptr) {delete ptr; };
	};

	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		unique_ptr(unique_ptr<T>&& up)
			:_ptr(up->_ptr),_del(up->_del)
		{
			up->_ptr = nullptr;
		}

		unique_ptr<T>& operator=(unique_ptr<T>&& up)
		{
			_ptr = up->_ptr;
			up->_ptr = nullptr;
			_del = up->_del;
		}

		template<class D>
		unique_ptr(T* ptr, D del)
			:_ptr(ptr), _del(del)
		{}

		unique_ptr(const unique_ptr<T> up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T> up) = delete;

		T* operator->() { return _ptr; }
		T& operator*() { return *_ptr; }

		~unique_ptr() { _del(_ptr); }
	private:
		T* _ptr;
		function<void(T*)> _del = [](T* ptr) {delete ptr; };
	};
}