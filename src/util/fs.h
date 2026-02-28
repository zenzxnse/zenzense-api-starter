#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <cstddef>
#include <system_error>

namespace util::fs {

/**
 * @brief Alias for std::filesystem::path for convenience in filesystem operations.
 */
using Path = std::filesystem::path;

// Existence

/**
 * @brief Checks if the given path exists in the filesystem.
 *
 * This function determines whether a file or directory exists at the specified path.
 * It is a noexcept function and does not throw exceptions.
 *
 * @param path The filesystem path to check for existence.
 * @return true if the path exists, false otherwise.
 */
[[nodiscard]] bool exists(const Path& path) noexcept;

// Read

/**
 * @brief Reads the contents of a text file at the given path.
 *
 * Attempts to read the entire file as a string. If successful, returns the content
 * wrapped in std::optional. If an error occurs (e.g., file not found, permission denied),
 * sets the error code in `ec` and returns std::nullopt.
 *
 * This function is noexcept and does not throw exceptions.
 *
 * @param path The filesystem path to the text file.
 * @param ec Reference to an std::error_code object to store any error that occurs.
 * @return std::optional<std::string> containing the file content if successful, or std::nullopt on failure.
 */
[[nodiscard]] std::optional<std::string> read_text(const Path& path, std::error_code& ec) noexcept;

/**
 * @brief Reads the contents of a binary file at the given path.
 *
 * Attempts to read the entire file as a vector of bytes. If successful, returns the data
 * wrapped in std::optional. If an error occurs (e.g., file not found, permission denied),
 * sets the error code in `ec` and returns std::nullopt.
 *
 * This function is noexcept and does not throw exceptions.
 *
 * @param path The filesystem path to the binary file.
 * @param ec Reference to an std::error_code object to store any error that occurs.
 * @return std::optional<std::vector<std::byte>> containing the file data if successful, or std::nullopt on failure.
 */
std::optional<std::vector<std::byte>> read_binary(const Path& path, std::error_code& ec) noexcept;

// Write (creates parent dirs optionally)

/**
 * @brief Writes text content to a file at the given path.
 *
 * Attempts to write the provided string content to the file. If `create_parent_dirs` is true,
 * it will create any necessary parent directories. On success, returns true. On failure,
 * sets the error code in `ec` and returns false.
 *
 * This function is noexcept and does not throw exceptions.
 *
 * @param path The filesystem path where the file should be written.
 * @param content The string content to write to the file.
 * @param ec Reference to an std::error_code object to store any error that occurs.
 * @param create_parent_dirs If true, creates parent directories if they do not exist (default: true).
 * @return true if the write operation succeeds, false otherwise.
 */
bool write_text(const Path& path, const std::string& content,
                std::error_code& ec, bool create_parent_dirs = true) noexcept;

/**
 * @brief Writes binary data to a file at the given path.
 *
 * Attempts to write the provided vector of bytes to the file. If `create_parent_dirs` is true,
 * it will create any necessary parent directories. On success, returns true. On failure,
 * sets the error code in `ec` and returns false.
 *
 * This function is noexcept and does not throw exceptions.
 *
 * @param path The filesystem path where the file should be written.
 * @param data The binary data to write to the file.
 * @param ec Reference to an std::error_code object to store any error that occurs.
 * @param create_parent_dirs If true, creates parent directories if they do not exist (default: true).
 * @return true if the write operation succeeds, false otherwise.
 */
bool write_binary(const Path& path, const std::vector<std::byte>& data,
                  std::error_code& ec, bool create_parent_dirs = true) noexcept;

// FS ops

/**
 * @brief Removes the file at the given path.
 *
 * Attempts to delete the file specified by the path. On success, returns true. On failure
 * (e.g., file not found, permission denied), sets the error code in `ec` and returns false.
 *
 * This function is noexcept and does not throw exceptions.
 *
 * @param path The filesystem path of the file to remove.
 * @param ec Reference to an std::error_code object to store any error that occurs.
 * @return true if the file is successfully removed, false otherwise.
 */
bool remove_file(const Path& path, std::error_code& ec) noexcept;

/**
 * @brief Creates directories (including parents) at the given path.
 *
 * Attempts to create the directory structure specified by the path, including any parent
 * directories if they do not exist. On success, returns true. On failure, sets the error
 * code in `ec` and returns false.
 *
 * This function is noexcept and does not throw exceptions.
 *
 * @param path The filesystem path of the directories to create.
 * @param ec Reference to an std::error_code object to store any error that occurs.
 * @return true if the directories are successfully created, false otherwise.
 */
bool create_directories(const Path& path, std::error_code& ec) noexcept;

} // namespace util::fs