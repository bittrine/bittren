#pragma once
#include <cstdint>

class MemoryManager
{
private:
	uint8_t* m_base;
	size_t m_capacity;
	size_t m_offset;

public:
	MemoryManager() = delete;
	MemoryManager(const MemoryManager&) = delete;
	MemoryManager(MemoryManager&&) = delete;
	MemoryManager& operator=(const MemoryManager&) = delete;
	MemoryManager& operator=(MemoryManager&&) = delete;
	~MemoryManager() = delete;

	void Init(size_t);
	uint8_t* Alloc(size_t length, size_t align);
	void Clear();
};