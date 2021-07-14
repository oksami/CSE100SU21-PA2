/**
 * TODO: File Header
 *
 * Author: Samhita Kadali
 */
#ifndef DICTIONARYTRIE_CPP
#include "DictionaryTrie.hpp"
#include <iostream>
#include <queue>
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
        return track;   //should i keep???
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
    vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                      unsigned int numCompletions) {
        vector<string> result;
        TSTNode* start = start(root, prefix);
        string c = start->data + "--";
        cout << c;
        result.push_back(c);
        return result;
        
    }

    /* TODO */
    DictionaryTrie::~DictionaryTrie() {}

#endif
