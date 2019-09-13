#pragma once

#include "Vector.h"
#include <vector>

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

	template <class T>
	class array_based_stack
	{
	public:
		array_based_stack (std::vector <T> * arr, unsigned size, unsigned start);
		unsigned size ();
		void push (T el);
		T pop ();
		void clear ();
		void setarr (std::vector <T>* arr);

	protected:
		unsigned max_size_;
		unsigned sp_;
		unsigned start_;
		std::vector <T>* arr_;
	};


	template<class T>
	inline array_based_stack<T>::array_based_stack (std::vector <T>* arr, unsigned size, unsigned start) :
		arr_ (arr),
		max_size_ (start + size),
		sp_ (start),
		start_ (start)
	{

	}

	template<class T>
	inline unsigned array_based_stack<T>::size ()
	{
		return sp_ - start_;
	}

	template<class T>
	inline void array_based_stack<T>::push (T el)
	{
		if (sp_ < max_size_)
			(*arr_)[sp_++] = el;
		else
			throw "stack overflow";
	}

	template<class T>
	inline T array_based_stack<T>::pop ()
	{
		if (sp_ > start_)
			return (*arr_)[--sp_];
		else
			throw "stack is empty";
	}

	template<class T>
	inline void array_based_stack<T>::clear ()
	{
		for (int i = start_; i < max_size_; i++)
			(*arr_)[i] = T ();
	}

	
}
