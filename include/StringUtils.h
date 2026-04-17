#pragma once

#include <windows.h>

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
		if (ret == 0 && capacity > 0) {
			buffer[0] = L'\0';
		}
	}

	operator const wchar_t* () const
	{
		return buffer;
	}
};

