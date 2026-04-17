#pragma once

#include <cstdint>
#include "MemoryManager.hpp"

template <typename T>
class Array
{
private:
	T* m_data;
	size_t m_size = 0;
	const size_t capacity;
public:

	Array(MemoryManager, size_t capacity);

	void push(T&&);
	void pop();
	void remove(size_t);
	void clear();
};