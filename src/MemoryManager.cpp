#include "MemoryManager.hpp"

#include "windows.h"

#include "assert.hpp"

MemoryManager::MemoryManager(size_t capacity) : m_capacity(capacity)
{
	m_current = m_base = static_cast<uint8_t*>(VirtualAlloc(
		nullptr,
		m_capacity,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE
	));
	ASSERT(m_base != nullptr);
}

MemoryManager::~MemoryManager()
{
	VirtualFree(m_base, 0, MEM_RELEASE);
}

uint8_t* MemoryManager::Alloc(size_t length, size_t align)
{
	uintptr_t current = reinterpret_cast<uintptr_t>(m_current);
	uint8_t* aligned = reinterpret_cast<uint8_t*>((current + align - 1) & ~(align - 1));
	m_current = aligned + length;
	ASSERT(m_current <= m_base + m_capacity);
	return aligned;
}

void MemoryManager::Clear()
{
	m_current = m_base;
}