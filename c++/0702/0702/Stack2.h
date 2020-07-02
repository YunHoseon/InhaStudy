#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

template <class T>
class Stack2
{
	enum { MAX = 10 };
	T items[MAX];
	int top;
public:
	Stack2();
	bool isEmpty();
	bool isFull();
	bool push(const T &item);
	bool pop(T &item);
	~Stack2();
};

template <class T>

Stack2<T>::Stack2()
{
	top = 0;
}

template <class T>
bool Stack2<T>::isEmpty()
{
	return top == 0;
}

template<class T>
inline bool Stack2<T>::isFull()
{
	return top == MAX;
}

template <class T>
bool Stack2<T>::push(const T &item)
{
	if (top < MAX)
	{
		items[top++] = item;
		return true;
	}
	else
		return false;
}

template <class T>
bool Stack2<T>::pop(T &item)
{
	if (top > 0)
	{
		item - items[--top];
		return true;
	}
	else
		return false;
}