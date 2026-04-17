#include "Array.hpp"
#include <cstdint>
#include <utility>

template <typename T>
void Array<T>::push(T&& object)
{
	new (m_data + m_size) T(std::move(object));
	m_size++;
}

template <typename T>
void Array<T>::pop()
{
	m_data[--m_size].~T();
}

template <typename T>
void Array<T>::remove(size_t idx)
{
	m_data[idx] = std::move(m_data[--m_size]);
}

template <typename T>
void Array<T>::clear()
{
	for(size_t i = 0; i < m_size; i++) {
		m_data[i].~T();
	}
	m_size = 0;
}
