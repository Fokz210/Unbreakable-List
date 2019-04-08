#pragma once

#include "Vector.h"

namespace icl
{
	template <class T>
	class stack
	{
	public:
		stack ();
		stack (const stack <T> & other);
		stack <T> operator = (const stack <T> & other);
		void push (T el);
		T pop ();
		int size ();
		bool ok ();
		bool empty ();
		bool clear ();
		void dump ();

	private:
		vector <T> container_;
	};

	template<class T>
	inline stack<T>::stack () :
		container_ ()
	{
	}

	template<class T>
	inline stack<T>::stack (const stack<T>& other) :
		container_ (other.container_)
	{
	
	}

	template<class T>
	inline stack<T> stack<T>::operator=(const stack<T>& other)
	{
		container_ = other.container_;

		return *this;
	}

	template<class T>
	inline void stack<T>::push (T el)
	{
		container_.push_back (el);
	}
	template<class T>
	inline T stack<T>::pop ()
	{
		return container_.pop_back();
	}

	template<class T>
	inline int stack<T>::size ()
	{
		return container_.size();
	}

	template<class T>
	inline bool stack<T>::ok ()
	{
		return container_.ok();
	}

	template<class T>
	inline bool stack<T>::empty ()
	{
		return size () == 0;
	}

	template<class T>
	inline bool stack<T>::clear ()
	{
		container_.clear ();
	}

	template<class T>
	inline void stack<T>::dump ()
	{
		container_.dump (std::cout);
	}

}
