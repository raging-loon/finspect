#include <cstdio>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace fs = std::filesystem;


int main(int argc, char** argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: finspect <filename>\n");
        return 1;
    }

    const char* filename = argv[1];

    std::error_code error{};
    size_t size = fs::file_size(filename, error);

    if (error)
    {
        printf("Faield to get filesize: %s\n", error.message().c_str());
        return 1;
    }

    std::ifstream input{filename};

    std::vector<uint8_t> bytes{};
    bytes.resize(size);

    input.read(
        reinterpret_cast<char*>(bytes.data()), 
        size
    );


    for (int i = 0; i < std::min((size_t)10, size); i++)
    {
        printf(" %02x ", bytes[i]);
    }

    printf("\n");

    return 0;
}