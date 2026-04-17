#pragma once

#include <windows.h>
#include "assert.hpp"

template <size_t capacity = 512>
struct UTF8toWide {
	wchar_t buffer[capacity];
	explicit UTF8toWide(const char* utf8) 
	{
		int ret = MultiByteToWideChar(
		                              CP_UTF8,
			                          0,
		                              utf8,
			                          -1,
			                          buffer,
			                          capacity);
		// TODO check ret and add asserts
		ASSERT(ret != 0);
	}

	operator const wchar_t* () const
	{
		return buffer;
	}
};

