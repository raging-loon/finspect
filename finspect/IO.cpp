#include "IO.h"

#include <filesystem>

namespace fs = std::filesystem;


namespace finspect
{


static inline auto UnexpectedErrorCode(std::errc errc)
{
    return std::unexpected(
        std::make_error_code(errc)
    );
}

static inline auto UnexpectedErrorCode(std::error_code& code)
{
    return std::unexpected(code);
}

OpenFileResult OpenFile(const char* filename)
{
    if (!filename)
        return UnexpectedErrorCode(std::errc::invalid_argument);
    
    std::error_code error{};

    size_t size = fs::file_size(filename, error);

    if (error)
        return UnexpectedErrorCode(error);


    std::ifstream input{filename};

    if (!input)
        return UnexpectedErrorCode(std::errc::io_error);

    ByteBuffer buffer{};
    buffer.resize(size);

    input.read(
        reinterpret_cast<char*>(buffer.data()),
        size
    );

    if (input.fail())
        return UnexpectedErrorCode(std::errc::io_error);
        
    return buffer;
}
    
} // namespace finspect
