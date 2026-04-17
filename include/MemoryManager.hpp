#pragma once
#include <cstdint>

class MemoryManager
{
private:
	uint8_t* m_base;
	size_t m_capacity;
	uint8_t* m_current;

public:
	MemoryManager() = delete;
	MemoryManager(const MemoryManager&) = delete;
	MemoryManager(MemoryManager&&) = delete;
	MemoryManager& operator=(const MemoryManager&) = delete;
	MemoryManager& operator=(MemoryManager&&) = delete;

	MemoryManager(size_t);
	~MemoryManager();

	uint8_t* Alloc(size_t length, size_t align);
	void Clear();
};