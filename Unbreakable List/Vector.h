#pragma once

#include <iostream>
#include <cassert>
#include <new>

#ifdef _DEBUG

#define VECTOR_OK if (!ok ()) { std::cout << "Something wrong in your vector. This is dump for you\n"; dump (); }
#define VECTOR_CALCSUM container_.sumCalc();

#else

#define VECTOR_OK
#define VECTOR_CALCSUM

#endif

namespace icl
{
	/*void * operator new (size_t size, const char * file, const char * line, const char * funcname)
	{
		printf ("Allocated memory in: %s file, %s line, %s func", file, line, funcname);
		return calloc (size, 1);
	}*/

	// object * o = new object;

	// object * o = new (__FILE__, __LINE__, __FUNCSIG__) object;

	template <class T>
	class contShell
	{
	public:
		contShell ();
		T & operator () ();
		unsigned sumUpdate ();
		bool     sumCheck ();
		bool     ok ();

	private:
		const int _CHECK_START;
		unsigned checksum_;
		T object_;
		const int _CHECK_END;
	};

	template <typename T>
	class arrayShell
	{
	public:
		arrayShell (int size);
		~arrayShell ();
		T & operator [] (int i);
		const T & operator [] (int i) const;
		bool ok ();
		unsigned sumCalc ();
		bool sumCheck ();
		unsigned resize (int size);
		unsigned size ();
		unsigned clear ();
		void swap (arrayShell <T> & other);
		
	private:
		char * data_;
	};

	template <class T>
	class vector              
	{
	public:
		vector ();
		vector (unsigned size);
		vector (const vector <T> & other);
		vector (vector <T> && other);
		vector (contShell <vector <T>> * shell);
		~vector ();
		unsigned realloc (unsigned size);
		unsigned resize (unsigned size);
		unsigned push_back (T element);
		T pop_back ();
		unsigned size () const;
		void clear ();
		std::ostream & dump (std::ostream & stream);
		bool ok ();
		void swap (vector <T> & other);
		
		T & operator [] (unsigned iterator)
		{
			if (iterator >= size_)
				assert (!"vector: out of range");

			return container_[iterator];
		}
		
		const T & operator [] (unsigned iterator) const
		{
			if (iterator >= size_)
				assert (!"vector: out of range");

			return container_[iterator];
		}

		/*vector <T> & operator = (const vector <T> & other)
		{
			this->~vector ();
			new (this) vector <T> (other);

			return *this;
		}

		vector <T> & operator = (const vector <T> & other)
		{
			vector <T> victim (other);

			swap (victim);

			return *this;
		}*/

		// vector v = vector (15);
		
		// vector F ()
		// {
		//    vector v (15)
		//    return v;
		// }

		// vector v2 = F ();

		// vector G (vector & v)
		// {
		//     return v;
		// }

		// vector v3 = G (v2);


		vector <T> & operator = (vector <T> victim)
		{
			swap (victim);

			return *this;
		}

		template <typename T>
		friend std::ostream & operator << (std::ostream & s, vector <T> & v);


	private:
		arrayShell <T> container_;
		unsigned alloc_size_;
		unsigned size_;
		contShell<vector<T>> * shell_;
		unsigned contHash_;
	};

	template <typename T>
	vector<T>::vector () :
		container_ (0),
		alloc_size_ (0),
		size_ (0),
		contHash_ (0),
		shell_ (nullptr)
	{
	}

	template <typename T>
	vector<T>::vector (unsigned size) :
		container_ (0),
		alloc_size_ (0),
		size_ (0),
		contHash_ (0),
		shell_ (nullptr)
	{
		resize (size);
	}

	template <typename T>
	vector<T>::vector (const vector <T> & other) :
		container_ (0),
		alloc_size_ (0),
		size_ (0),
		contHash_ (0),
		shell_ (nullptr)
	{
		realloc (other.size ());
		for (int i = 0; i < other.size (); i++)
			push_back (other[i]);
	}

	template <typename T>
	vector<T>::vector (vector <T> && other) :
		container_ (0),
		alloc_size_ (0),
		size_ (0),
		contHash_ (0),
		shell_ (nullptr)
	{
		swap (other);
	}

	template<class T>
	inline vector<T>::vector (contShell<vector<T>>* shell) :
		container_ (0),
		alloc_size_ (0),
		size_ (0),
		contHash_ (0),
		shell_ (shell)
	{

	}

	template<class T>
	inline vector<T>::~vector ()
	{
	}

	template<class T>
	inline unsigned vector<T>::realloc (unsigned size)
	{
		alloc_size_ = size;
		return container_.resize(size);
	}


	template<class T>
	inline unsigned vector<T>::resize (unsigned size)
	{
		realloc (size * 1.5);
		
		if (size > size_)
			for (int i = size_; i < size; i++)
				container_[i] = T();

		size_ = size;

		return size_;
	}

	template <typename T>
	unsigned vector<T>::push_back (T element)
	{
		if (size_ >= alloc_size_)
		realloc (unsigned (size_ * 1.5 + 1));

		container_[size_] = element;
		size_++;

		return size_ - 1;
	}

	template <typename T>
	T vector<T>::pop_back ()
	{
		if (alloc_size_ == 0)
			return T ();

		T buff = container_[size_ - 1];
		size_--;

		if (size_ * 1.5 < alloc_size_)
			realloc (size_);

		return buff;
	}

	template <typename T>
	unsigned vector<T>::size () const
	{
		return size_;
	}

	template <typename T>
	void vector<T>::clear ()
	{
		container_.clear ();
		alloc_size_ = 0;
		size_ = 0;
	}

	template<class T>
	inline std::ostream & vector<T>::dump (std::ostream & stream)
	{
		stream << "vector (" << ") [" << this << "]\n";
		stream << "{\n";
		stream << "\tdata [" << size_ << "]" << "\n";
		stream << "\t{\n";
		for (int i = 0; i < alloc_size_; i++)
		{
			if (i >= size_)
				stream << "\t      * ";
			else
				stream << "\t\t";
			stream << "[" << i << "] = " << container_[i] << "\n";
		}
		stream << "\t}\n";
		stream << "}\n";

		return stream;
	}

	template<class T>
	inline bool vector<T>::ok ()
	{
		if (!container_.ok())
			return false;

		if (shell_) 
			return shell_->ok ();

		return true;
	}

	template<typename T>
	std::ostream & operator<<(std::ostream & s, vector <T> & v)
	{
		for (int i = 0; i < v.size (); i++)
			s << "[" << v[i] << "] ";

		return s;
	}

	template<class T>
	inline contShell<T>::contShell () :
		_CHECK_START (rand ()),
		checksum_ (0),
		object_ (),
		_CHECK_END (_CHECK_START)
	{
	}

	template<class T>
	T & contShell<T>::operator()()
	{
		return object_;
	}

	template<class T>
	unsigned contShell<T>::sumUpdate ()
	{
		checksum_ = 0;

		unsigned tempChecksum = 0;

		unsigned * data = (unsigned *) this;
		for (unsigned i = 0; i < sizeof (*this) / 4; i++)
			tempChecksum  += data[i] ^ i;

		return checksum_ = tempChecksum;
	}

	template<class T>
	inline bool contShell<T>::sumCheck ()
	{
		unsigned prevSum = checksum_;
		sumUpdate ();
	
		return prevSum == checksum_;
	}

	template<class T>
	inline bool contShell<T>::ok ()
	{
		if (_CHECK_END != _CHECK_START)
			return false;

		return sumCheck ();
	}

	template<typename T>
	inline arrayShell<T>::arrayShell (int size) :
		data_ (new char [sizeof (int) * 4 + sizeof (T) * size])
	{
		for (unsigned i = 0; i < sizeof (int) * 4 + sizeof (T) * size; i++)
			data_[i] = 0;

		*(int *)(data_ + sizeof (int)) = size;
	}

	template<typename T>
	inline arrayShell<T>::~arrayShell ()
	{
		delete[] data_;
	}

	template<typename T>
	inline T & arrayShell<T>::operator[](int i)
	{
		return *(T *)(data_ + sizeof (int) * 3 + sizeof (T) * i);
	}

	template<typename T>
	inline const T & arrayShell<T>::operator[](int i) const
	{
		return *(T *)(data_ + sizeof (int) * 3 + sizeof (T) * i);
	}

	template<typename T>
	inline bool arrayShell<T>::ok ()
	{
		if (!data_)
			return false;

		int size = *(int *)(data_ + sizeof (int));
		if (*(int *)data_ != *(int *)(data_ + sizeof (int) * 3 + sizeof (T) * size))
			return false;

		if (!sumCheck ())
			return false;

		return true;
	}

	template<typename T>
	inline unsigned arrayShell<T>::sumCalc ()
	{
		int size = *(int *)(data_ + sizeof (int));
		int sizeOfArray = sizeof (int) * 4 + sizeof (T) * size; 
		unsigned summ = 0;

		int * hash = (int *)(data_ + sizeof (int) * 2);
		*hash = 0;

		int * array = (int *) (data_ + sizeof (int) * 3);

		for (int i = 0; i < sizeOfArray / sizeof (int); i++)
			summ += array[i] ^ i;

		*hash = summ;

		return summ;
	}

	template<typename T>
	inline bool arrayShell<T>::sumCheck ()
	{
		int hash = *(int *)(data_ + sizeof (int) * 2);

		return hash == sumCalc ();
	}

	template<typename T>
	inline unsigned arrayShell<T>::resize (int size)
	{
		char * newData = new char[sizeof (int) * 4 + sizeof (T) * size];
		for (unsigned i = 0; i < sizeof (int) * 4 + sizeof (T) * size; i++)
			newData[i] = 0;

		T * newArray = (T *)(newData + sizeof (int) * 3);
		T * Array = (T *)(data_ + sizeof (int) * 3);

		int * size_ = (int *)(data_ + sizeof (int));

		for (int i = 0; i < size && i < *size_; i++)
			newArray[i] = Array[i];

		*(int *)(newData + sizeof (int)) = size;

		delete(data_);

		data_ = newData;
		return size;
	}

	template <typename T>
	inline unsigned arrayShell<T>::size ()
	{
		return *(int *)(data_ + sizeof(int));
	}

	template <typename T>
	inline unsigned arrayShell<T>::clear ()
	{
		return resize(0);
	}

	template<typename T>
	inline void arrayShell<T>::swap (arrayShell<T>& other)
	{
		std::swap (data_, other.data_);
	}

	template <typename T> 
	inline void vector<T>::swap (vector <T> & other)
	{
		container_.swap (other.container_);
		std::swap (alloc_size_, other.alloc_size_);
		std::swap (size_, other.size_);
		std::swap (shell_, other.shell_);
	}
}