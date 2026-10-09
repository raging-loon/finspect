#include <print>

#include <finspect/IO.h>
#include <finspect/AhoCorasick.h>

using namespace finspect;

using Trie = std::vector<aho_corasick::Vertex>;



int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::println("Usage: ./finspect <file>");
        return 1;
    }

    auto results = OpenFile(argv[1]);

    if (!results)
    {
        std::println("Failed to open file '{}': {}", argv[1], results.error().message());
        return 1;
    }

    std::string_view types[] = {
        "PDF", "PNG", "JPEG"
    };

    std::vector<ByteBuffer> dict = {
        ByteBuffer({'%', 'P', 'D', 'F', '-'}),
        ByteBuffer({u'\x89','P', 'N', 'G'}),
        ByteBuffer({u'\xFF', u'\xD8', u'\xFF'}),
    };

    aho_corasick::SearchTrie trie(dict);

    auto res = trie.search(results.value());

    for (auto& i : res)
    {
        int rlOffset = i.first - types[i.second].length();
        std::println("{}, {}", rlOffset, types[i.second]);
    }
    return 0;
}