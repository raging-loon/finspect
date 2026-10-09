#ifndef FINSPECT_AHO_CORASICK_H_
#define FINSPECT_AHO_CORASICK_H_

#include <algorithm>
#include <array>
#include <vector>
#include <tuple>

#include "finspect/IO.h"

namespace finspect::aho_corasick
{

using ByteDictionary = std::vector<ByteBuffer>;
using SearchResults = std::vector<std::pair<int, int> >;


constexpr unsigned int MAX_ROUTES = 1 << 8;
    
struct Vertex
{
    std::array<int, MAX_ROUTES> next;

    int failureLink;
    int outputLink;

    std::vector<int> wordIdx;

    Vertex();
};

class SearchTrie
{
public:

    SearchTrie(const ByteDictionary& dictionary);

    SearchResults search(const ByteBuffer& sequence);

private:

    void insert(const ByteBuffer& seq, int idx);

    void buildDFA();

private:
    std::vector<Vertex> m_trie;
    ByteDictionary m_words;
};


} // namespace finspect::aho_corasick


#endif // FINSPECT_AHO_CORASICK_H_