#pragma once

#include <expected>
#include <span>

enum class FileError
{
	not_found,
	access_denied,
	unknown
};

enum class FileMode;

class FileWrapper
{
private:
	void* m_handle;
	FileWrapper(void* handle);
	FileWrapper(const FileWrapper&) = delete;
	FileWrapper& operator=(const FileWrapper&) = delete;
public:
	static std::expected<FileWrapper, FileError> open(const char* filename, FileMode mode);
	FileWrapper(FileWrapper&&) noexcept;
	FileWrapper& operator=(FileWrapper&&) noexcept;
	~FileWrapper();

	void read(std::span<std::byte>) noexcept;
};

