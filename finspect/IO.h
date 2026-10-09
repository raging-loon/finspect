#ifndef FINSPECT_IO_H_
#define FINSPECT_IO_H_

#include <fstream>
#include <vector>
#include <expected>
#include <cstdint>
#include <system_error>

namespace finspect
{
    
using ByteBuffer = std::vector<uint8_t>;

using OpenFileResult = std::expected<ByteBuffer, std::error_code>;

OpenFileResult OpenFile(const char* filename);

} // namespace finspect

#endif // FINSPECT_IO_H_