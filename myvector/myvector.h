#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class myvector
{
private:
	T * vector;
	int size1;
	int cap;
	int index;

public:
	myvector(){
		size1 = 0;
		cap = 10;
		vector = new T[10];
		for (int i = 0; i < this->cap; i++)
		{
			this->vector[i] = NULL;
		}
		index = 0;
	}

	myvector(int capacity)
	{
		if (capacity > 0)
		{
			this->cap = capacity;
			this->size1 = this->cap;
			vector = new T[this->cap];
			for (int i = 0; i < this->cap; i++)
			{
				this->vector[i] = NULL;
			}
		}
		else
		{
			cout << "error: vector size less than 1" << endl;
		}
	}

	myvector(myvector const &tmp)
	{
		this->cap = tmp.cap;
		this->size1 = tmp.size();
		this->vector = new T[this->cap];
		for (int i = 0; i < tmp.size(); i++)
		{
			this->vector[i] = tmp.vector[i];
		}
	}

	myvector(const T array[], int cap)
	{
		if (cap < 1)
		{
			cout << "error: vector size less than 1" << endl;
		}
		else
		{
			this->cap = cap;
			this->vector = new T[this->cap];
			for (int i = 0; i < this->cap; i++)
			{
				this->vector[i] = array[i];
			}
		}
	}

	~myvector()
	{
		if (this->vector != NULL){
			delete[] this->vector;
			this->vector = NULL;
			this->size1 = 0;
			this->cap = 0;
		}
		if (vector != NULL){
			delete[] vector;
			vector = NULL;
		}
	}

	myvector& operator=(const myvector& tmp){
		this->cap = tmp.cap;
		if (this->vector != NULL)
			delete[] this->vector;
		this->vector = new T[this->cap];
		for (int i = 0; i < this->cap; i++)
		{
			this->vector[i] = tmp.vector[i];
		}

		return *this;
	}

	int size() const 
	{
		int count = 0;
		for (int i = 0; i < this->cap; i++){
			if (this->vector[i] != NULL){
				count++;
			}
		}

		return (this->size1 > count) ? this->size1 : count;;
	}

	int capacity() const // return the current capacity of the vector
	{
		return this->cap;
	}

	bool empty() const // return whether or not the vector is empty
	{
		return (this->size1 == 0);
	}

	void resize(int newsize) // resize the vector (change length) to the specified size, changing capacity as needed
	{
		if (newsize > 0)
		{
			if (newsize > this->cap)
			{
				this->reserve(newsize);
				this->size1 = newsize;
				this->cap = newsize;
			}
			else
			{
				this->size1 = newsize;
			}
		}
		else
		{
			cout << "error: vector size less than 1" << endl;
		}
	}
	void reserve(int size) // change the vector capacity to the specified size, or give an error if capacity would get smaller than length
	{
		if (size < this->size1)
		{
			cout << "capacity cannot be smaller than the length!" << endl;
		}
		else
		{
			T * old_vector = vector;
			vector = new T[size];
			for (int i = 0; i < this->size1; i++)
			{
				vector[i] = old_vector[i];
			}
			for (int i = this->size1; i < size; i++){
				vector[i] = NULL;
			}
			if (this->cap < size){
				this->cap = size;
			}
			delete[] old_vector;
		}
	}
	T &myvector<T>::operator [](int index) const
	{
		if (index < 0)
		{
			cout << "error: negative index!" << endl;
			return vector[0];
		}
		else if (index >= size())
		{
			cout << "error: greater than the vector size!" << endl;
			return vector[0];
		}
		else
		{
			return vector[index];
		}
	}

	T& at(int index)
	{
		if (index < 0)
		{
			cout << "error: negative index!" << endl;
			return vector[0];
		}
		else if (index >= this->size1)
		{
			cout << "error: greater than the vector size!" << endl;
			return vector[0];
		}
		else
		{
			return vector[index];
		}
	}

	void assign(int index, T const &value) // assign the second argument as the value of the vector at the position of the first argument
	{
		if (index < 0)
		{
			cout << "error: negative index!" << endl;
		}
		else if (index >= this->size1)
		{
			cout << "error: greater than the vector size!" << endl;
		}
		else
		{
			vector[index] = value;
		}
	}

	void push_back(T const &value) // increase length by 1 and add the argument as the value at the end
	{
		if (this->size1 == this->cap)
		{
			this->reserve(this->cap * 2 + 1);
		}
		if (this->size1 == 0){
			this->size1++;
			this->vector[size1] = NULL;
		}
		this->vector[this->size1-1] = value;
		this->size1++;
		this->vector[size1-1] = NULL;
	}

	T pop_back() // decrease length by 1, returning the value removed from the vector
	{
		if (this->size1 > 0)
		{
			T value = this->vector[this->size1 - 1];
			this->vector[this->size1 - 1] = NULL;
			this->size1--;
			return value;
		}
		else
		{
			cout << "error: empty vector!" << endl;
		}
	}

	void insert(int index, T const &value) // increase length by 1, put the value specified in the second argument at index specified by first argument and shift all values to the right in the vector down by one index
	{
		if (index < 0)
		{
			cout << "error: negative index!" << endl;
		}
		else if (index > this->size1)
		{
			cout << "error: out-of-bound index!" << endl;
		}
		else if (index == this->size1)
		{
			this->push_back(value);
			this->size1++;
		}
		else
		{
			if (this->size1 == this->cap)
			{
				this->reserve(this->cap * 2 + 1);
			}

			T tmp = this->vector[index];
			this->vector[index] = value;
			for (int i = index + 1; i < this->size1; i++)
			{
				T tmp2 = this->vector[i];
				this->vector[i] = tmp;
				tmp = tmp2;
			}
			this->vector[this->size1] = tmp;
			this->size1++;
		}
	}

	void erase(int index) // decrease length by 1, remove the item at the specified index, and shift all other items left to eliminate the "hole"
	{
		if (index < 0)
		{
			cout << "error: negative index!" << endl;
		}
		else if (index >= this->size1)
		{
			cout << "error: out-of-bound index!" << endl;
		}
		else
		{
			T * old_vector = vector;
			vector = new T[cap];
			for (int i = 0; i < cap; i++)
			{
				this->vector[i] = NULL;
			}
			int new_index = 0;
			for (int i = 0; i < this->size1; i++)
			{
				if (index == i) continue;
				this->vector[new_index] = old_vector[i];
				new_index++;
			}
			this->size1--;
			delete[] old_vector;
		}
	}

	void erase(int begin, int end) // same as erase(int), but removes all elements between the indexes specified by the first and second argument
	{
		if (begin > end)
		{
			cout << "error: can not erase backwards!" << endl;
		}
		else if (begin < 0)
		{
			cout << "error: a negative index!" << endl;
		}
		else if (end > this->size1)
		{
			cout << "error: out-of-bound index!" << endl;
		}
		else
		{
			int j = 0;
			for (int i = begin; i < end; i++)
			{
				this->erase(i - j);
				j++;
			}
		}
	}

	void clear() // remove all elements from the list
	{
		this->size1 = 0;
		this->cap = 0;
	}

	void print() const
	{
		for (int i = 0; i < this->size1; i++)
		{
			cout << "[" << i << "]:" << this->vector[i] << endl;
		}
	}

};

#endif