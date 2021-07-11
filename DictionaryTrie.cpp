/**
 * TODO: File Header
 *
 * Author: Samhita Kadali
 */
#include "DictionaryTrie.hpp"
#include <iostream>
protected:

   /** Pointer to the root of this TST, or 0 if the TST is empty */
   TSTNode* root;
public:
    /* TODO */
    DictionaryTrie::DictionaryTrie(): root(0) {}

    /* TODO */
    bool DictionaryTrie::insert(string word, unsigned int freq) {
        TSTNode* node = root;
        char letter = word[0];
        
        //loop infinitely
        while(true){
            //left child
            if (letter < node->data) {
                if(node.left)
                    node = node->left;
                else{
                    node->left = newTSTNode*(letter)
                    node = node->left;
                    for (char c: word.substr(1,word.length())){
                        node->mid = newTSTNode*(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->fr = freq;
                    break;
                }
            }
            //right child
            else if (letter > node->data){
                if (node->right)
                    node = node->right;
                else{
                    node->right = newTSTNode*(letter);
                    node = node->right;
                    for (char c: word.substr(1,word.length())){
                        node->mid = newTSTNode*(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->fr = freq;
                    break;
                }
            }
            //middle child
            else{
                if(letter == word.back()){
                    node->bword=true;
                    return true;
                }
                else{
                    for (char c: word.substr(1,word.length())){
                        node->mid = newTSTNode*(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->fr = freq;
                    break;
                }
            }
        }
    }

    /* TODO */
    bool DictionaryTrie::find(string word) const {
       
    }

    /* TODO */
    vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                      unsigned int numCompletions) {
        return {};
    }

    /* TODO */
    DictionaryTrie::~DictionaryTrie() {}
