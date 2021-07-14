/**
 * TODO: File Header
 *
 * Author: Samhita Kadali
 */
#ifndef DICTIONARYTRIE_CPP
#include "DictionaryTrie.hpp"
#include <iostream>
#include <functional>
#include <utility>
#include <queue>
#include <algorithm>
#include <stack>
#include <string>
#include <vector>
//protected:
    /** Pointer to the root of this TST, or 0 if the TST is empty */
    
//public:
    /* TODO */
DictionaryTrie::DictionaryTrie() {root = nullptr;}

    //return end-node (last character of prefix)
    TSTNode* DictionaryTrie::start(TSTNode* node, string prefix){
        TSTNode* track = node;
        int i = 0;
        
        //only following the tree up until the last character of the prefix
        while(i<prefix.length()){
            
            if(prefix[i] < node->data)
                track = node->left;
            if(prefix[i] > node->data)
                track = node->right;
            else{
                track = node->mid;
                i++;
                if(i == prefix.length()-1){
                    cout << track;
                    return track;
                }
            }
        }
        return track;   //should i keep??? or is the above return statement enough?
    }

    //find all suffixes of the prefix and insert into vector of that ENTIRE string and its frequency
    vector<pair<int, string>> DictionaryTrie::suffixes(TSTNode* node, string prefix){
        
        //initialize value to be returned
        vector<pair<int, string>> insert;
        
        //word to be inserted
        string word = prefix;
        
        //go through left subtree
        if(node->left) suffixes(node->left, prefix);
        
        //go through right subtree
        if(node->right) suffixes(node->right, prefix);
        
        if(node->mid){
            word += node->data;     //add suffix to prefix into word
            if(node->mid->bword == true){   //if word-end, insert word
                insert.push_back( make_pair( node->mid->f, word  ) );
            }
            suffixes(node->mid, word);    //continue down?
        }
        return insert;
    }

    
    bool DictionaryTrie::pairComparison(const pair<string, int> &x, const pair<string, int> &y){
        return x.second > y.second;
    }

    /* TODO */
    vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                      unsigned int numCompletions) {
        vector<string> result;
        TSTNode* startNode = start(root, prefix);   //find node to start at = last character of prefix
        
        vector<pair<int, string>> suf = suffixes(startNode, prefix);    //string of every completion
        
        sort(suf.begin(), suf.end(), []( const pair<int, string> &x, const pair<int, string> &y )
             {
                 return ( x.second > y.second );
             } );  //sorted in descending order
        
        //remove the least frequent, leaving only numCompletions
        suf.erase(suf.begin()+numCompletions, suf.end());
        
        //copy the strings ONLY into the vector<string>
        for(int i = 0; i < numCompletions; i++){
            result[i] = suf[i].first;
        }
        return result;
    }

    /* TODO */
    bool DictionaryTrie::insert(string word, unsigned int freq) {
        TSTNode* node;
        int i = 0;
        char letter = word[i];
        
        //check if empty --> insert first letter as root
        if(root == nullptr) root = new TSTNode(letter);
        
        //in any case, start at root
        node = root;
        
        //loop infinitely
        while(true){
            //left child
            if (letter < node->data) {
                if(node->left)
                    node = node->left;
                else{
                    node->left = new TSTNode(letter);
                    node = node->left;
                    
                    for (char & c: word.substr(i+1)){   //remaining letters NOT including first
                        node->mid = new TSTNode(c);
                        node = node->mid;
                    }
                    node->bword = true; //label last node as a word-node
                    node->f = freq;     //attach frequency to last node
                    return true;
                    break;
                }
            }
            //right child
            else if (letter > node->data){
                if (node->right)
                    node = node->right;
                else{
                    node->right = new TSTNode(letter);
                    node = node->right;
                    
                    for (char & c: word.substr(i+1)){
                        node->mid = new TSTNode(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->f = freq;
                    return true;
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
                    if(node->mid){
                        node = node->mid;
                        letter = word[++i];
                    }
                    else{
                        for (char & c: word.substr(i+1)){
                            node->mid = new TSTNode(c);
                            node = node->mid;
                        }
                        node->bword = true;
                        node->f = freq;
                        return true;
                        break;
                    }
                }
            }
        }
        return false;
    }

    /* TODO */
    bool DictionaryTrie::find(string word) const {
        TSTNode* node = root;
        if(!node) return false; //check if empty
        int i = 0;
        char letter = word[i];
        while(true){
            if(letter<node->data){
                if(node->left)
                    node = node->left;
                else
                    return false;
            }
            else if( letter > node->data){
                if(node->right)
                    node = node->right;
                else
                    return false;
            }
            else{
                if(letter == word.back() && node->bword == true)
                    return true;
                else{
                    if(node->mid && letter != word.back()){
                        node = node->mid;
                        letter = word[++i];
                    }
                    else
                        return false;
                }
            }
        }
    }



    

    /* TODO */
    DictionaryTrie::~DictionaryTrie() {}

#endif
