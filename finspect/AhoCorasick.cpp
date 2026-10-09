#include "AhoCorasick.h"

#include <queue>

namespace finspect::aho_corasick
{

Vertex::Vertex() 
    : failureLink{ -1 },
    outputLink{ -1 },
    wordIdx{}
{
    std::fill(std::begin(next), std::end(next), -1);    
}

    
SearchTrie::SearchTrie(const ByteDictionary& dictionary)
    : m_trie{1}, m_words{dictionary}
{
    for (int i = 0; i < m_words.size(); i++)
        insert(m_words[i], i);

    buildDFA();
}

void SearchTrie::insert(const ByteBuffer& seq, int idx)
{
    int current = 0;

    for (uint8_t byte : seq)
    {   
        
        if (m_trie[current].next[byte] == -1)
        {
            m_trie[current].next[byte] = m_trie.size();
            m_trie.emplace_back();
        }
        current = m_trie[current].next[byte];
    }
    m_trie[current].wordIdx.push_back(idx);
}

void SearchTrie::buildDFA()
{
    std::queue<int> queue;

    m_trie[0].failureLink = 0;
    m_trie[0].outputLink = -1;

    for (int i = 0; i < MAX_ROUTES; i++)
    {
        int child = m_trie[0].next[i];

        if (child != -1)
        {
            m_trie[child].failureLink = 0;
            m_trie[child].outputLink = -1;
            queue.push(child);
        }
        else
            m_trie[0].next[i] = 0;
    }

    while (!queue.empty())
    {
        int curr = queue.front();
        queue.pop();

        for (int i = 0; i < MAX_ROUTES; i++)
        {
            int child = m_trie[curr].next[i];

            if (child != -1)
            {

                int failState = m_trie[curr].failureLink;

                while (failState != 0 && m_trie[failState].next[i] == -1)
                    failState = m_trie[failState].failureLink;

                if (m_trie[failState].next[i] != -1)
                    m_trie[child].failureLink = m_trie[failState].next[i];
                else
                    m_trie[child].failureLink = 0;

                int failNode = m_trie[child].failureLink;

                if (!m_trie[failNode].wordIdx.empty())
                    m_trie[child].outputLink = failNode;
                else 
                    m_trie[child].outputLink = m_trie[failNode].outputLink;

                queue.push(child);
            }
        }
    }
}

SearchResults SearchTrie::search(const ByteBuffer& sequence)
{
    SearchResults results{};

    int curr = 0;

    for (int i = 0; i < sequence.size(); i++)
    {
        uint8_t byte = sequence[i];

        while (curr != 0 && m_trie[curr].next[byte] == -1)
            curr = m_trie[curr].failureLink;
        
        curr = m_trie[curr].next[byte];

        int match = curr;

        while (match != -1 && match != 0)
        {
            for (int wordIdx : m_trie[match].wordIdx)
                results.push_back({i, wordIdx});
            match = m_trie[match].outputLink;
        }
    }
    return results;
}

} // namespace finspect::aho_corasick
