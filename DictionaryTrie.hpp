/**
 * TODO: File Header
 *
 * Author: Samhita Kadali
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    struct TSTNode{
        char data;
        bool bword;
        unsigned int fr;
        struct TSTNode* left;
        struct TSTNode* mid;
        struct TSTNode* right;
    }
    
    TSTNode* newTSTNode(char inp){
        TSTNode* node = new TSTNode;
        node->data = inp;
        node->bword = false;
        node->fr = 0;
        node->left = node->mid = node->right = nullptr;
        return node;
    }
  public:
    /* TODO: add function header */
    DictionaryTrie();

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
