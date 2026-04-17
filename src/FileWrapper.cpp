#include "FileWrapper.hpp"
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include "windows.h"
#include "StringUtils.h"

enum class FileMode
{
    read    = GENERIC_READ,
    write   = GENERIC_WRITE
};

FileWrapper::FileWrapper(HANDLE handle)
{
    m_handle = handle;
}

std::expected<FileWrapper, FileError> FileWrapper::open(const char* filename, FileMode mode)
{
    const wchar_t* w_filename = UTF8toWide<MAX_PATH>(filename);

    // length of the string is 0
    if (w_filename[0] == L'\0')
    {
        return std::unexpected(FileError::unknown);
    }

    HANDLE handle = CreateFileW(
        w_filename,
        static_cast<DWORD>(mode),
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        return std::unexpected(FileError::unknown);
    }
    return FileWrapper(handle);
}

FileWrapper::~FileWrapper()
{
    if (m_handle != INVALID_HANDLE_VALUE) {
        CloseHandle(m_handle);
    }
}

FileWrapper& FileWrapper::operator=(FileWrapper&& file) noexcept
{   
    if (this == &file)
        return *this;
    m_handle = file.m_handle;
    file.m_handle = INVALID_HANDLE_VALUE;
    return *this;
}

FileWrapper::FileWrapper(FileWrapper&& file) noexcept
{
    m_handle = file.m_handle;
    file.m_handle = INVALID_HANDLE_VALUE;
}

void FileWrapper::read(std::span<std::byte> buf) noexcept
{

}