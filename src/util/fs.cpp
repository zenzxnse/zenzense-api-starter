#include "fs.h"

#include <fstream>

namespace util::fs {

bool exists(const Path& path) noexcept {
    std::error_code ec;
    return std::filesystem::exists(path, ec);
}

std::optional<std::string> read_text(const Path& path, std::error_code& ec) noexcept {
    ec.clear();
    std::ifstream f(path, std::ios::binary);
    if (!f) { ec = std::make_error_code(std::errc::no_such_file_or_directory); return std::nullopt; }

    std::string s;
    f.seekg(0, std::ios::end);
    const auto n = f.tellg();
    if (n < 0) { ec = std::make_error_code(std::errc::io_error); return std::nullopt; }
    s.resize(static_cast<size_t>(n));
    f.seekg(0, std::ios::beg);
    f.read(s.data(), static_cast<std::streamsize>(s.size()));
    if (!f && !s.empty()) { ec = std::make_error_code(std::errc::io_error); return std::nullopt; }
    return s;
}

std::optional<std::vector<std::byte>> read_binary(const Path& path, std::error_code& ec) noexcept {
    ec.clear();
    std::ifstream f(path, std::ios::binary);
    if (!f) { ec = std::make_error_code(std::errc::no_such_file_or_directory); return std::nullopt; }

    f.seekg(0, std::ios::end);
    const auto n = f.tellg();
    if (n < 0) { ec = std::make_error_code(std::errc::io_error); return std::nullopt; }

    std::vector<std::byte> buf(static_cast<size_t>(n));
    f.seekg(0, std::ios::beg);
    f.read(reinterpret_cast<char*>(buf.data()), static_cast<std::streamsize>(buf.size()));
    if (!f && !buf.empty()) { ec = std::make_error_code(std::errc::io_error); return std::nullopt; }
    return buf;
}

static bool maybe_create_parent(const Path& path, std::error_code& ec, bool create_parent_dirs) noexcept {
    if (!create_parent_dirs) return true;
    const auto parent = path.parent_path();
    if (parent.empty()) return true;
    return std::filesystem::create_directories(parent, ec) || !ec;
}

bool write_text(const Path& path, const std::string& content,
                std::error_code& ec, bool create_parent_dirs) noexcept {
    ec.clear();
    if (!maybe_create_parent(path, ec, create_parent_dirs)) return false;

    std::ofstream f(path, std::ios::binary | std::ios::trunc);
    if (!f) { ec = std::make_error_code(std::errc::permission_denied); return false; }
    f.write(content.data(), static_cast<std::streamsize>(content.size()));
    if (!f) { ec = std::make_error_code(std::errc::io_error); return false; }
    return true;
}

bool write_binary(const Path& path, const std::vector<std::byte>& data,
                  std::error_code& ec, bool create_parent_dirs) noexcept {
    ec.clear();
    if (!maybe_create_parent(path, ec, create_parent_dirs)) return false;

    std::ofstream f(path, std::ios::binary | std::ios::trunc);
    if (!f) { ec = std::make_error_code(std::errc::permission_denied); return false; }
    f.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
    if (!f) { ec = std::make_error_code(std::errc::io_error); return false; }
    return true;
}

bool remove_file(const Path& path, std::error_code& ec) noexcept {
    ec.clear();
    return std::filesystem::remove(path, ec);
}

bool create_directories(const Path& path, std::error_code& ec) noexcept {
    ec.clear();

    if (std::filesystem::exists(path, ec)) {
        ec.clear(); 
        return true;
    }
    if (ec) return false;

    std::filesystem::create_directories(path, ec);
    return !ec;
}


} // namespace util::fs
