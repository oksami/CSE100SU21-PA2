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
//protected:
    /** Pointer to the root of this TST, or 0 if the TST is empty */
    
//public:
    /* TODO */
DictionaryTrie::DictionaryTrie() {root = nullptr;}

//return end-node (last character of prefix)
TSTNode* DictionaryTrie::traverse(TSTNode* node, string prefix){
/*string tresult;
       //  stack< pair< string, int> q;
    string word;*/
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
}
    
    /*if(!node) return tresult;
    if(node)  word.push_back(node->data);
    if(node->bword == true) {   //if end
        tresult.push_back(word);
        cout << word;
        word.clear();
    }
    if(node->left) traverse(node->left);
    if(node->mid) traverse(node->mid);
    if(node->right) traverse(node->right);
    
    return tresult;
}
    /*
         q.push({node, {pref, true}});
         while(!q.empty()){
             TSTNode* node = q.front().first;
             cout << node->data;
             string pref = q.front().second.first;
             bool valid = q.front().second.second;
             q.pop();
             if(node->bword==true && valid==true)
                 tresult.push_back(pref);
             if(node->left) q.push({node->left, {pref, false}});
             if(node->mid) q.push({node->mid, {pref+node->data, true}});
             if(node->right) q.push({node->right, {pref, false}});
         }*/
     
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
                        letter = word[i+1];
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
        TSTNode* start = traverse(root, prefix);
        cout << start->data;
        return result;
        
        /*
        TSTNode* node = root;
        int i = 0;
        while(i<prefix.length()){
            if(node==NULL) return result;
            if(node->data == prefix[i]){
                node = node->mid;
                i++;
                continue;
            }
            if(node->data < prefix[i]) node = node->right;
            if(node == nullptr) return result;
            else node = node->left;
        }
        return traverse(node, prefix);*/
    }

    /* TODO */
    DictionaryTrie::~DictionaryTrie() {}

#endif
