#include "MemoryManager.hpp"

#include "windows.h"

void MemoryManager::Init(size_t capacity)
{
	m_base = static_cast<uint8_t*>(VirtualAlloc(
		nullptr,
		capacity,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE
	));
}

uint8_t* MemoryManager::Alloc(size_t length, size_t align)
{
	//assert(m_offset + length <= m_capacity);
	m_offset += length;
	return m_base + m_offset;
}

void MemoryManager::Clear()
{
	m_offset = 0;
}