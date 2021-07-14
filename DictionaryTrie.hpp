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

  class TSTNode{
      public:
          TSTNode(char d): data(d){
              bword = false;
              f = NULL;
              left = mid = right = NULL;
          }
              char data;
              bool bword;
              unsigned int f;
              TSTNode* left;
              TSTNode* mid;
              TSTNode* right;
      };
/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    TSTNode* root;
    
    
public:
    
    TSTNode* start(TSTNode* node, string prefix);

    vector<pair<int, string>> suffixes(TSTNode* node, string prefix);
    
    bool pairComparison(const pair<string, int> &x, const pair<string, int> &y);
    
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
