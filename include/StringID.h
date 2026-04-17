#pragma once

#include <cstdint>
#include <string_view>

inline constexpr uint64_t FNV_PRIME = 1099511628211ULL;
inline constexpr uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;

constexpr uint64_t Hash(const char* str)
{
	uint64_t hash = FNV_OFFSET_BASIS;
	for (; *str; ++str) {
        hash ^= static_cast<uint8_t>(*str);
        hash *= FNV_PRIME;
    }
    return hash;
}

constexpr uint64_t operator""_id(const char* str, size_t)
{
	return Hash(str);
}

class StringID {
private:
	uint64_t id = 0;
public:
	constexpr StringID() = default;
	consteval StringID(const char* str) : id() {};
	constexpr uint64_t value() const { return id; };
	constexpr bool operator==(const StringID& other) const
	{
		return id == other.id;
	}
	constexpr bool operator!=(const StringID& other) const
	{
		return id != other.id;
	}
};