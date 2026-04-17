#include "FileWrapper.hpp"
#include "StringUtils.hpp"

#include "windows.h"

enum class FileMode : DWORD
{
    read    = GENERIC_READ,
    write   = GENERIC_WRITE
};

FileWrapper::FileWrapper(HANDLE handle)
{
    m_handle = handle;
}

std::expected<FileWrapper, uint64_t> FileWrapper::open(const char* filename, FileMode mode)
{
    HANDLE handle = CreateFileW(
        UTF8toWide<MAX_PATH>(filename),
        static_cast<DWORD>(mode),
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        return std::unexpected(GetLastError());
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