#pragma once

#include <cstdint>

inline constexpr uint64_t CORE_ASSET_FLAG = 1ULL << 63;
inline constexpr uint64_t FNV_PRIME = 0x00000100000001b3;
inline constexpr uint64_t FNV_OFFSET_BASIS = 0xcbf29ce484222325;

struct StringID {
private:
	uint64_t id = 0;

	static consteval uint64_t hash(const char* str)
	{
		uint64_t hash = FNV_OFFSET_BASIS;
		for (; *str; ++str) {
			hash ^= static_cast<uint8_t>(*str);
			hash *= FNV_PRIME;
		}
		return hash;
	}

public:
	constexpr StringID() = default;
	consteval explicit StringID(const char* str) noexcept : id(hash(str)) {};
	constexpr operator uint64_t () const { return id; }
	constexpr bool operator==(const StringID& other) const { return id == other.id; }
	constexpr bool operator!=(const StringID& other) const { return id != other.id; }
	constexpr bool is_core() const { return id & CORE_ASSET_FLAG; }
};

consteval uint64_t operator""_id(const char* str, size_t) noexcept
{
	return StringID(str);
}

